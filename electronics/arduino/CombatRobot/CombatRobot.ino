// ============================================================================
// Combat Robot Controller - SPARC Compliant
// ============================================================================
// Beginner-friendly ESP32-based controller for combat robots with weapon support
// Features: Drive control, weapon systems, Bluetooth pairing, safety features
// ============================================================================

#include <Bluepad32.h>
#include <ESP32Servo.h>
#include <uni.h>
#include "CombatWeapon.h"  // Our weapon library

// ============================================================================
// WEAPON SELECTION - Choose ONE weapon type!
// ============================================================================
// Uncomment ONE of these lines to select your weapon:

//#define USE_VERTICAL_SPINNER
//#define USE_HORIZONTAL_SPINNER
//#define USE_LIFTER
//#define USE_FLIPPER
#define USE_NO_WEAPON  // Default - safe for testing

// ============================================================================
// CONFIGURATION
// ============================================================================

// SPARC Pairing Mode
const bool PAIRING_MODE = false;  // Set to true to pair new controllers

// Pin assignments
const int LEFT_MOTOR_PIN = D9;
const int RIGHT_MOTOR_PIN = D10;
const int WEAPON_PIN = D8;

// Motor direction adjustment
const bool INVERT_LEFT_MOTOR = true;
const bool INVERT_RIGHT_MOTOR = true;
const bool INVERT_TURN_DIRECTION = (INVERT_LEFT_MOTOR && INVERT_RIGHT_MOTOR);

// Control sensitivity
const int JOYSTICK_DEAD_ZONE = 102;
const int TRIGGER_THRESHOLD = 10;
const unsigned long TURN_BURST_DURATION = 250;  // milliseconds

// Timing constants
const unsigned long UPDATE_INTERVAL = 50;     // milliseconds
const unsigned long COMMAND_TIMEOUT = 1000;   // milliseconds

// ESC settings
const int ESC_CAL_DELAY = 2000;    // milliseconds
const int STARTUP_DELAY = 3000;    // milliseconds
const bool VERBOSE_DEBUG = true;

// ESC speed constants
const int NEUTRAL_SPEED = 1500;    // microseconds
const int MIN_SPEED = 1000;        // microseconds
const int MAX_SPEED = 2000;        // microseconds

// ============================================================================
// WEAPON INSTANTIATION - Automatic based on #define
// ============================================================================

#if defined(USE_VERTICAL_SPINNER)
    SpinnerWeapon weapon(WEAPON_VERTICAL_SPINNER);
    #define WEAPON_NAME "Vertical Spinner"
#elif defined(USE_HORIZONTAL_SPINNER)
    SpinnerWeapon weapon(WEAPON_HORIZONTAL_SPINNER);
    #define WEAPON_NAME "Horizontal Spinner"
#elif defined(USE_LIFTER)
    LifterWeapon weapon;
    #define WEAPON_NAME "Lifter"
#elif defined(USE_FLIPPER)
    FlipperWeapon weapon;
    #define WEAPON_NAME "Flipper"
#else
    NoWeapon weapon;
    #define WEAPON_NAME "None"
#endif

// ============================================================================
// CONTROL STATES
// ============================================================================

enum ControlState {
    STATE_STOPPED,
    STATE_JOYSTICK,
    STATE_TRIGGER,
    STATE_BUMPER_TURNING
};

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

// Controller management
ControllerPtr myControllers[BP32_MAX_GAMEPADS];
bool controllerConnected = false;

// Drive motors
Servo leftESC;
Servo rightESC;
int leftSpeed = NEUTRAL_SPEED;
int rightSpeed = NEUTRAL_SPEED;
bool escsArmed = false;

// State management
ControlState currentState = STATE_STOPPED;
unsigned long turnStartTime = 0;
bool turnBurstActive = false;
unsigned long lastCommandTime = 0;
unsigned long lastUpdate = 0;

// ============================================================================
// WEAPON CONFIGURATION
// ============================================================================

void configureWeapon() {
    Serial.print("Weapon type: ");
    Serial.println(WEAPON_NAME);
    
    #if defined(USE_VERTICAL_SPINNER) || defined(USE_HORIZONTAL_SPINNER)
        weapon.setControlMode(2);           // Variable speed (right stick)
        weapon.setSpinUpTime(2000);         // 2 seconds to full speed
        weapon.setSpinDownTime(3000);       // 3 seconds to stop
        weapon.setMaxSpeed(2000);           // Full power
        weapon.setSafetyDelay(3000);        // 3 second safety delay
        weapon.setRumbleFeedback(true);     // Enable rumble feedback
        
        Serial.println("  Control: Right stick Y-axis (push up = faster)");
        Serial.println("  Rumble: Enabled (intensity matches speed)");
        Serial.println("  Safety: 3-second delay after connection");
        
    #elif defined(USE_LIFTER)
        weapon.setUpButton(1);              // R1 = up
        weapon.setDownButton(0);            // R2 = down
        weapon.setControlMode(0);           // Button mode
        weapon.setRange(0, 90);             // 0-90 degrees
        weapon.setSpeed(120);               // 120 degrees/second
        weapon.setSafetyDelay(3000);        // 3 second safety delay
        
        Serial.println("  Control: R1 = Up, R2 = Down");
        Serial.println("  Range: 0-90 degrees");
        
    #elif defined(USE_FLIPPER)
        weapon.setEnableButton(0);          // R2
        weapon.setControlMode(0);           // Tap mode
        weapon.setFireDuration(150);        // 150ms pulse
        weapon.setCooldownTime(1000);       // 1 second cooldown
        weapon.setSafetyDelay(3000);        // 3 second safety delay
        
        Serial.println("  Control: R2 = Fire");
        Serial.println("  Duration: 150ms pulse");
    #else
        Serial.println("  No weapon configured");
    #endif
}

// ============================================================================
// ESC INITIALIZATION
// ============================================================================

void armESCs() {
    Serial.println("\n=== Starting ESC Arming Sequence ===");
    
    // Attach and initialize drive ESCs
    leftESC.attach(LEFT_MOTOR_PIN, MIN_SPEED, MAX_SPEED);
    rightESC.attach(RIGHT_MOTOR_PIN, MIN_SPEED, MAX_SPEED);
    
    Serial.println("Waiting for ESC power-up...");
    delay(STARTUP_DELAY);

    Serial.println("Setting neutral position for arming...");
    leftESC.writeMicroseconds(NEUTRAL_SPEED);
    rightESC.writeMicroseconds(NEUTRAL_SPEED);
    delay(ESC_CAL_DELAY);
    
    escsArmed = true;
    Serial.println("=== Drive ESCs Armed! ===\n");
    
    // Initialize weapon system
    Serial.println("=== Initializing Weapon System ===");
    weapon.begin(WEAPON_PIN);
    configureWeapon();
    Serial.println("=== Weapon System Ready! ===\n");
}

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

int applyDeadZone(int value, int deadZone) {
    return (abs(value) < deadZone) ? 0 : value;
}

int invertSpeed(int speed) {
    return MIN_SPEED + (MAX_SPEED - speed);
}

void stopMotors() {
    leftSpeed = NEUTRAL_SPEED;
    rightSpeed = NEUTRAL_SPEED;
    currentState = STATE_STOPPED;
    
    if (VERBOSE_DEBUG) {
        Serial.println("Motors STOPPED");
    }
}

// ============================================================================
// DRIVE CONTROL HANDLERS
// ============================================================================

void handleJoystickControl(ControllerPtr ctl) {
    int axisX = applyDeadZone(ctl->axisX(), JOYSTICK_DEAD_ZONE);
    int axisY = applyDeadZone(ctl->axisY(), JOYSTICK_DEAD_ZONE);
    
    if (INVERT_TURN_DIRECTION) {
        axisX = -axisX;
    }
    
    // Mix for differential drive
    int leftMotorInput = constrain(axisY + (axisX / 2), -512, 512);
    int rightMotorInput = constrain(axisY - (axisX / 2), -512, 512);
    
    // Map to ESC range
    leftSpeed = map(leftMotorInput, -512, 512, MIN_SPEED, MAX_SPEED);
    rightSpeed = map(rightMotorInput, -512, 512, MIN_SPEED, MAX_SPEED);
    
    // Apply motor direction inversion
    if (INVERT_LEFT_MOTOR) leftSpeed = invertSpeed(leftSpeed);
    if (INVERT_RIGHT_MOTOR) rightSpeed = invertSpeed(rightSpeed);
    
    currentState = STATE_JOYSTICK;
    
    if (VERBOSE_DEBUG) {
        Serial.printf("JOYSTICK - Left: %d, Right: %d\n", leftSpeed, rightSpeed);
    }
}

void handleTriggerControl(ControllerPtr ctl) {
    int leftTrigger = ctl->throttle();
    int rightTrigger = ctl->brake();
    
    bool leftPressed = (leftTrigger > TRIGGER_THRESHOLD);
    bool rightPressed = (rightTrigger > TRIGGER_THRESHOLD);
    
    // Both triggers = emergency stop
    if (leftPressed && rightPressed) {
        leftSpeed = NEUTRAL_SPEED;
        rightSpeed = NEUTRAL_SPEED;
        weapon.emergencyStop();
        
        if (VERBOSE_DEBUG) {
            Serial.println("TRIGGER - EMERGENCY STOP");
        }
        return;
    }
    
    // Right trigger = forward boost
    if (rightPressed) {
        leftSpeed = map(rightTrigger, 0, 1023, NEUTRAL_SPEED, MAX_SPEED);
        rightSpeed = leftSpeed;
        
        if (INVERT_LEFT_MOTOR) leftSpeed = invertSpeed(leftSpeed);
        if (INVERT_RIGHT_MOTOR) rightSpeed = invertSpeed(rightSpeed);
        
        if (VERBOSE_DEBUG) {
            Serial.printf("TRIGGER - Forward boost: %d\n", leftSpeed);
        }
    }
    // Left trigger = reverse retreat
    else if (leftPressed) {
        leftSpeed = map(leftTrigger, 0, 1023, NEUTRAL_SPEED, MIN_SPEED);
        rightSpeed = leftSpeed;
        
        if (INVERT_LEFT_MOTOR) leftSpeed = invertSpeed(leftSpeed);
        if (INVERT_RIGHT_MOTOR) rightSpeed = invertSpeed(rightSpeed);
        
        if (VERBOSE_DEBUG) {
            Serial.printf("TRIGGER - Reverse retreat: %d\n", leftSpeed);
        }
    }
    
    currentState = STATE_TRIGGER;
}

void handleBumperControl(ControllerPtr ctl) {
    bool leftBumper = ctl->l1();
    bool rightBumper = ctl->r1();
    
    // Swap if turn direction is inverted
    if (INVERT_TURN_DIRECTION) {
        bool temp = leftBumper;
        leftBumper = rightBumper;
        rightBumper = temp;
    }
    
    // Start turn burst on button press
    if ((leftBumper || rightBumper) && currentState != STATE_BUMPER_TURNING) {
        turnStartTime = millis();
        turnBurstActive = true;
        currentState = STATE_BUMPER_TURNING;
        
        if (VERBOSE_DEBUG) {
            Serial.printf("BUMPER - Starting %s turn\n", leftBumper ? "LEFT" : "RIGHT");
        }
    }
    
    // Execute turn
    if (leftBumper) {
        leftSpeed = MIN_SPEED;
        rightSpeed = MAX_SPEED;
    } else if (rightBumper) {
        leftSpeed = MAX_SPEED;
        rightSpeed = MIN_SPEED;
    }
    
    // Apply motor direction inversion
    if (INVERT_LEFT_MOTOR) leftSpeed = invertSpeed(leftSpeed);
    if (INVERT_RIGHT_MOTOR) rightSpeed = invertSpeed(rightSpeed);
}

// ============================================================================
// MAIN CONTROL LOGIC
// ============================================================================

void processGamepad(ControllerPtr ctl) {
    if (!escsArmed) return;
    
    lastCommandTime = millis();
    
    // Update weapon (happens every loop)
    weapon.update(ctl);
    
    // Get controller inputs
    bool leftBumper = ctl->l1();
    bool rightBumper = ctl->r1();
    int leftTrigger = ctl->throttle();
    int rightTrigger = ctl->brake();
    int axisX = ctl->axisX();
    int axisY = ctl->axisY();
    
    // Priority: Bumpers > Triggers > Joystick
    if (leftBumper || rightBumper) {
        handleBumperControl(ctl);
    }
    else if (leftTrigger > TRIGGER_THRESHOLD || rightTrigger > TRIGGER_THRESHOLD) {
        handleTriggerControl(ctl);
        turnBurstActive = false;
    }
    else if (abs(axisX) > JOYSTICK_DEAD_ZONE || abs(axisY) > JOYSTICK_DEAD_ZONE) {
        handleJoystickControl(ctl);
        turnBurstActive = false;
    }
    else {
        // No input - check for turn burst timeout
        if (turnBurstActive && (millis() - turnStartTime >= TURN_BURST_DURATION)) {
            turnBurstActive = false;
            stopMotors();
            
            if (VERBOSE_DEBUG) {
                Serial.println("BUMPER - Turn burst complete, STOPPED");
            }
        }
        else if (!turnBurstActive && currentState != STATE_STOPPED) {
            stopMotors();
        }
    }
}

void processControllers() {
    bool hasActiveController = false;
    
    // Find first active controller
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            processGamepad(myController);
            hasActiveController = true;
            break;  // Only use one controller at a time
        }
    }
    
    // Safety: stop everything if no active controller
    if (!hasActiveController) {
        stopMotors();
        weapon.emergencyStop();
    }
}

void updateMotors() {
    if (!escsArmed) return;
    
    leftESC.writeMicroseconds(leftSpeed);
    rightESC.writeMicroseconds(rightSpeed);
}

// ============================================================================
// BLUEPAD32 CALLBACKS
// ============================================================================

void onConnectedController(ControllerPtr ctl) {
    bool foundEmptySlot = false;
    
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            ControllerProperties properties = ctl->getProperties();
            
            Serial.printf("Controller attempting connection: %02x:%02x:%02x:%02x:%02x:%02x\n",
                properties.btaddr[0], properties.btaddr[1], properties.btaddr[2],
                properties.btaddr[3], properties.btaddr[4], properties.btaddr[5]);
            
            // Handle pairing mode
            if (PAIRING_MODE) {
                bd_addr_t controller_addr;
                memcpy(controller_addr, properties.btaddr, 6);
                uni_bt_allowlist_add_addr(controller_addr);
                uni_bt_allowlist_set_enabled(true);
                
                Serial.println("\n*** CONTROLLER SUCCESSFULLY PAIRED! ***");
                Serial.println("*** Set PAIRING_MODE to false and re-upload ***\n");
            }
            
            myControllers[i] = ctl;
            controllerConnected = true;
            foundEmptySlot = true;
            
            // Tell weapon about connection time (for safety delay)
            weapon.setConnectionTime(millis());
            
            Serial.printf("Controller connected at index %d\n", i);
            break;
        }
    }
    
    if (!foundEmptySlot) {
        Serial.println("SAFETY: Controller connection rejected - no available slots");
        ctl->disconnect();
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            myControllers[i] = nullptr;
            controllerConnected = false;
            
            // Emergency stop on disconnect
            stopMotors();
            weapon.emergencyStop();
            
            Serial.printf("Controller disconnected from index %d\n", i);
            break;
        }
    }
}

// ============================================================================
// SETUP
// ============================================================================

void setup() {
    Serial.begin(115200);
    Serial.println("\n=== Combat Robot Controller - SPARC COMPLIANT ===");
    Serial.println("Initializing...\n");
    
    // Allocate PWM timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    
    // Set servo frequency
    leftESC.setPeriodHertz(50);
    rightESC.setPeriodHertz(50);
    
    // Initialize Bluepad32
    BP32.setup(&onConnectedController, &onDisconnectedController);
    
    // SPARC Compliance Setup
    Serial.println("=== SPARC Radio Control Compliance ===");
    
    if (!PAIRING_MODE) {
        uni_bt_allowlist_set_enabled(true);
        Serial.println("SECURITY: Controller allowlist ENABLED");
        
        // Display paired controllers
        const bd_addr_t* addresses;
        int total;
        uni_bt_allowlist_get_all(&addresses, &total);
        
        if (total > 0) {
            Serial.printf("\nPaired controllers (%d):\n", total);
            for (int i = 0; i < total; i++) {
                Serial.printf("  %d. %02x:%02x:%02x:%02x:%02x:%02x\n", i + 1,
                    addresses[i][0], addresses[i][1], addresses[i][2],
                    addresses[i][3], addresses[i][4], addresses[i][5]);
            }
        } else {
            Serial.println("\n*** WARNING: NO CONTROLLERS PAIRED! ***");
            Serial.println("Set PAIRING_MODE = true to pair a controller\n");
        }
        
    } else {
        uni_bt_allowlist_set_enabled(false);
        Serial.println("\n*** PAIRING MODE ACTIVE ***");
        Serial.println("Turn on your controller to pair it\n");
    }
    
    Serial.println("SPARC Failsafe: Active (SPARC 6.4.1)");
    Serial.println("Radio System: 2.4GHz Bluetooth (SPARC 6.1)\n");
    
    // Arm ESCs and initialize weapon
    armESCs();
    
    Serial.println("=== Setup Complete! ===");
    Serial.println("Waiting for controller connection...\n");
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void loop() {
    unsigned long currentMillis = millis();
    
    // Update Bluepad32 and process controllers
    if (BP32.update()) {
        processControllers();
    }
    
    // SPARC Failsafe - stop if no command received
    if (controllerConnected && (currentMillis - lastCommandTime > COMMAND_TIMEOUT)) {
        if (currentState != STATE_STOPPED) {
            Serial.println("SPARC FAILSAFE: Signal lost - stopping all motors");
            stopMotors();
            weapon.emergencyStop();
        }
    }
    
    // Update motors at fixed interval
    if (currentMillis - lastUpdate >= UPDATE_INTERVAL) {
        lastUpdate = currentMillis;
        updateMotors();
    }
    
    // Small delay for task scheduling
    vTaskDelay(1);
}