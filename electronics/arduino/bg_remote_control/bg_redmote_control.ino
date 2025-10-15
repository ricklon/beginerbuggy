#include <Bluepad32.h>
#include <ESP32Servo.h>

// ============================================================================
// CONFIGURATION - Adjust these for your robot
// ============================================================================

// Motor pins
const int LEFT_MOTOR_PIN = D9;
const int RIGHT_MOTOR_PIN = D10;

// Motor direction adjustment (flip these if motors spin wrong way)
const bool INVERT_LEFT_MOTOR = false;
const bool INVERT_RIGHT_MOTOR = false;

// Automatic turn compensation - don't change this!
// When BOTH motors are inverted, the turning differential gets reversed.
// This flag automatically compensates by swapping turn directions in the code.
const bool INVERT_TURN_DIRECTION = (INVERT_LEFT_MOTOR && INVERT_RIGHT_MOTOR);

// Control sensitivity
const int JOYSTICK_DEAD_ZONE = 102;  // 20% dead zone (out of 512 max)
const int TRIGGER_THRESHOLD = 10;     // Minimal threshold to prevent accidental bumps

// Turn settings
const unsigned long TURN_BURST_DURATION = 250;  // Bumper tap = 250ms turn

// Timing
const unsigned long UPDATE_INTERVAL = 50;      // Motor update rate (20Hz)
const unsigned long COMMAND_TIMEOUT = 1000;    // Safety timeout if no input

// ESC calibration settings
const int ESC_CAL_DELAY = 2000;
const int STARTUP_DELAY = 3000;

// Debug output (set to false to reduce serial spam)
const bool VERBOSE_DEBUG = true;

// ============================================================================
// ESC CONSTANTS - Standard PWM values for ESCs (don't change unless you know why)
// ============================================================================

const int NEUTRAL_SPEED = 1500;  // ESC stopped position
const int MIN_SPEED = 1000;      // Full reverse
const int MAX_SPEED = 2000;      // Full forward

// ============================================================================
// CONTROL STATES - Robot can only be in one state at a time
// ============================================================================

enum ControlState {
    STATE_STOPPED,          // No input or safety stop
    STATE_JOYSTICK,         // Precision control with left stick
    STATE_TRIGGER,          // Fast movement with triggers
    STATE_BUMPER_TURNING    // Quick aim adjustment with bumpers
};

// ============================================================================
// GLOBAL VARIABLES
// ============================================================================

// Bluepad32 controller management
ControllerPtr myControllers[BP32_MAX_GAMEPADS];
bool controllerConnected = false;

// Motor control
Servo leftESC;
Servo rightESC;
int leftSpeed = NEUTRAL_SPEED;
int rightSpeed = NEUTRAL_SPEED;
bool escsArmed = false;

// State management
ControlState currentState = STATE_STOPPED;
unsigned long turnStartTime = 0;
bool turnBurstActive = false;  // True during 250ms tap turn
unsigned long lastCommandTime = 0;
unsigned long lastUpdate = 0;

// ============================================================================
// ESC INITIALIZATION
// ============================================================================

void armESCs() {
    Serial.println("=== Starting ESC Arming Sequence ===");
    
    // Attach ESCs to pins
    leftESC.attach(LEFT_MOTOR_PIN, MIN_SPEED, MAX_SPEED);
    rightESC.attach(RIGHT_MOTOR_PIN, MIN_SPEED, MAX_SPEED);
    
    // Wait for ESC power-up
    Serial.println("Waiting for ESC power-up...");
    delay(STARTUP_DELAY);

    // Set neutral position for arming
    Serial.println("Setting neutral position for arming...");
    leftESC.writeMicroseconds(NEUTRAL_SPEED);
    rightESC.writeMicroseconds(NEUTRAL_SPEED);
    delay(ESC_CAL_DELAY);
    
    escsArmed = true;
    Serial.println("=== ESCs Armed and Ready! ===\n");
}

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

// Apply dead zone to joystick input
int applyDeadZone(int value, int deadZone) {
    return (abs(value) < deadZone) ? 0 : value;
}

// Invert motor direction around neutral point
// IMPORTANT: This is applied in each control handler, not at the end.
// This preserves the motor differential needed for proper turning.
int invertSpeed(int speed) {
    return MIN_SPEED + (MAX_SPEED - speed);
}

// Stop all motors
void stopMotors() {
    leftSpeed = NEUTRAL_SPEED;
    rightSpeed = NEUTRAL_SPEED;
    currentState = STATE_STOPPED;
    
    if (VERBOSE_DEBUG) {
        Serial.println("Motors STOPPED");
    }
}

// ============================================================================
// CONTROL MODE HANDLERS
// ============================================================================

void handleJoystickControl(ControllerPtr ctl) {
    // Get joystick input with dead zone applied
    int axisX = applyDeadZone(ctl->axisX(), JOYSTICK_DEAD_ZONE);  // -512 to +512
    int axisY = applyDeadZone(ctl->axisY(), JOYSTICK_DEAD_ZONE);  // -512 to +512
    
    // If both motors are inverted, flip turn direction to maintain correct behavior
    if (INVERT_TURN_DIRECTION) {
        axisX = -axisX;
    }
    
    // Arcade drive mixing:
    // Left motor = Forward/Back + Turn
    // Right motor = Forward/Back - Turn
    // This makes the robot turn by running motors at different speeds
    int leftMotorInput = axisY + (axisX/2);
    int rightMotorInput = axisY - (axisX/2);
    
    // Keep values in valid range
    leftMotorInput = constrain(leftMotorInput, -512, 512);
    rightMotorInput = constrain(rightMotorInput, -512, 512);
    
    // Map to ESC range (1000-2000 microseconds)
    leftSpeed = map(leftMotorInput, -512, 512, MIN_SPEED, MAX_SPEED);
    rightSpeed = map(rightMotorInput, -512, 512, MIN_SPEED, MAX_SPEED);
    
    // Apply motor inversion immediately if needed
    if (INVERT_LEFT_MOTOR) leftSpeed = invertSpeed(leftSpeed);
    if (INVERT_RIGHT_MOTOR) rightSpeed = invertSpeed(rightSpeed);
    
    currentState = STATE_JOYSTICK;
    
    if (VERBOSE_DEBUG) {
        Serial.printf("JOYSTICK - Left: %d, Right: %d\n", leftSpeed, rightSpeed);
    }
}

void handleTriggerControl(ControllerPtr ctl) {
    // Get trigger values (0-1023)
    // NOTE: Bluepad32 naming is confusing!
    // throttle() = LEFT trigger, brake() = RIGHT trigger
    int leftTrigger = ctl->throttle();   // Reverse (0-1023)
    int rightTrigger = ctl->brake();     // Forward (0-1023)
    
    // Check which trigger(s) are pressed
    bool leftPressed = (leftTrigger > TRIGGER_THRESHOLD);
    bool rightPressed = (rightTrigger > TRIGGER_THRESHOLD);
    
    // SAFETY: Both triggers = emergency stop
    if (leftPressed && rightPressed) {
        leftSpeed = NEUTRAL_SPEED;
        rightSpeed = NEUTRAL_SPEED;
        
        if (VERBOSE_DEBUG) {
            Serial.println("TRIGGER - Both pressed, EMERGENCY STOP");
        }
        return;
    }
    
    // Right trigger = Forward boost
    if (rightPressed) {
        // Map trigger pull to forward speed range
        leftSpeed = map(rightTrigger, 0, 1023, NEUTRAL_SPEED, MAX_SPEED);
        rightSpeed = leftSpeed;  // Both motors same speed = straight line
        
        // Apply motor inversion immediately if needed
        if (INVERT_LEFT_MOTOR) leftSpeed = invertSpeed(leftSpeed);
        if (INVERT_RIGHT_MOTOR) rightSpeed = invertSpeed(rightSpeed);
        
        if (VERBOSE_DEBUG) {
            Serial.printf("TRIGGER - Forward boost: %d\n", leftSpeed);
        }
    }
    // Left trigger = Reverse retreat
    else if (leftPressed) {
        // Map trigger pull to reverse speed range
        leftSpeed = map(leftTrigger, 0, 1023, NEUTRAL_SPEED, MIN_SPEED);
        rightSpeed = leftSpeed;  // Both motors same speed = straight line
        
        // Apply motor inversion immediately if needed
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
    
    // If both motors are inverted, swap bumper behavior to maintain correct turn direction
    if (INVERT_TURN_DIRECTION) {
        bool temp = leftBumper;
        leftBumper = rightBumper;
        rightBumper = temp;
    }
    
    // Start a turn if not already turning
    if ((leftBumper || rightBumper) && currentState != STATE_BUMPER_TURNING) {
        turnStartTime = millis();
        turnBurstActive = true;  // Start 250ms burst
        currentState = STATE_BUMPER_TURNING;
        
        if (VERBOSE_DEBUG) {
            Serial.printf("BUMPER - Starting %s turn\n", leftBumper ? "LEFT" : "RIGHT");
        }
    }
    
    // Set turn direction (full speed in-place turn)
    if (leftBumper) {
        leftSpeed = MIN_SPEED;   // Left motor reverse
        rightSpeed = MAX_SPEED;  // Right motor forward
    } else if (rightBumper) {
        leftSpeed = MAX_SPEED;   // Left motor forward
        rightSpeed = MIN_SPEED;  // Right motor reverse
    }
    
    // Apply motor inversion immediately if needed
    if (INVERT_LEFT_MOTOR) leftSpeed = invertSpeed(leftSpeed);
    if (INVERT_RIGHT_MOTOR) rightSpeed = invertSpeed(rightSpeed);
}

// ============================================================================
// MAIN CONTROL LOGIC
// ============================================================================

void processGamepad(ControllerPtr ctl) {
    if (!escsArmed) return;
    
    // Update command watchdog
    lastCommandTime = millis();
    
    // Get button states
    bool leftBumper = ctl->l1();
    bool rightBumper = ctl->r1();
    int leftTrigger = ctl->throttle();
    int rightTrigger = ctl->brake();
    int axisX = ctl->axisX();
    int axisY = ctl->axisY();
    
    // ========================================================================
    // STATE PRIORITY LOGIC (highest to lowest)
    // ========================================================================
    
    // PRIORITY 1: BUMPERS (Quick aim - overrides everything)
    if (leftBumper || rightBumper) {
        handleBumperControl(ctl);
    }
    // PRIORITY 2: TRIGGERS (Fast movement - overrides joystick)
    else if (leftTrigger > TRIGGER_THRESHOLD || rightTrigger > TRIGGER_THRESHOLD) {
        handleTriggerControl(ctl);
        turnBurstActive = false;  // Cancel any active turn burst
    }
    // PRIORITY 3: JOYSTICK (Precision control)
    else if (abs(axisX) > JOYSTICK_DEAD_ZONE || abs(axisY) > JOYSTICK_DEAD_ZONE) {
        handleJoystickControl(ctl);
        turnBurstActive = false;  // Cancel any active turn burst
    }
    // PRIORITY 4: NOTHING PRESSED
    else {
        // If we were in a bumper turn burst and it's complete, stop
        if (turnBurstActive && (millis() - turnStartTime >= TURN_BURST_DURATION)) {
            turnBurstActive = false;
            stopMotors();
            
            if (VERBOSE_DEBUG) {
                Serial.println("BUMPER - Turn burst complete, STOPPED");
            }
        }
        // If we were doing something else, stop
        else if (!turnBurstActive && currentState != STATE_STOPPED) {
            stopMotors();
        }
    }
}

void processControllers() {
    // Check if any controller is available
    bool hasActiveController = false;
    
    for (auto myController : myControllers) {
        if (myController && myController->isConnected() && myController->hasData()) {
            processGamepad(myController);
            hasActiveController = true;
            break;  // Only process first connected controller
        }
    }
    
    // Safety: Stop if no controller data
    if (!hasActiveController) {
        stopMotors();
    }
}

// ============================================================================
// MOTOR UPDATE
// ============================================================================

void updateMotors() {
    if (!escsArmed) return;
    
    // Send commands directly to ESCs
    // (Motor inversion is now handled in each control handler)
    leftESC.writeMicroseconds(leftSpeed);
    rightESC.writeMicroseconds(rightSpeed);
}

// ============================================================================
// BLUEPAD32 CALLBACKS
// ============================================================================

void onConnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == nullptr) {
            myControllers[i] = ctl;
            controllerConnected = true;
            Serial.printf("Controller connected at index %d\n", i);
            break;
        }
    }
}

void onDisconnectedController(ControllerPtr ctl) {
    for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
        if (myControllers[i] == ctl) {
            myControllers[i] = nullptr;
            controllerConnected = false;
            stopMotors();
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
    Serial.println("\n=== Combat Robot Controller ===");
    Serial.println("Initializing...\n");
    
    // Initialize ESP32Servo library
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    
    // Configure ESC PWM frequency (50Hz standard for ESCs)
    leftESC.setPeriodHertz(50);
    rightESC.setPeriodHertz(50);
    
    // Initialize Bluepad32
    BP32.setup(&onConnectedController, &onDisconnectedController);
    
    // Arm the ESCs
    armESCs();
    
    Serial.println("Setup complete!");
    Serial.println("Waiting for controller connection...\n");
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void loop() {
    unsigned long currentMillis = millis();
    
    // Update Bluepad32 and process controller input
    if (BP32.update()) {
        processControllers();
    }
    
    // SAFETY: Command timeout watchdog
    // If no commands received for COMMAND_TIMEOUT, stop motors
    if (controllerConnected && (currentMillis - lastCommandTime > COMMAND_TIMEOUT)) {
        if (currentState != STATE_STOPPED) {
            Serial.println("SAFETY: Command timeout - stopping motors");
            stopMotors();
        }
    }
    
    // Update motors at fixed interval
    if (currentMillis - lastUpdate >= UPDATE_INTERVAL) {
        lastUpdate = currentMillis;
        updateMotors();
    }
    
    // Small delay to prevent watchdog issues
    vTaskDelay(1);
}

// ============================================================================
// BEGINNER NOTES
// ============================================================================

/*
 * CONTROL SCHEME:
 * ---------------
 * Left Joystick: Precision maneuvering (arcade drive)
 *   - Forward/back: Y-axis
 *   - Turn left/right: X-axis
 *   - Use for: Careful positioning, navigation
 * 
 * Right Trigger: Forward boost (0-100% speed)
 *   - Use for: Charging at opponent for collision
 * 
 * Left Trigger: Reverse retreat (0-100% speed)
 *   - Use for: Quick escape
 * 
 * Left Bumper: Spin left in place
 *   - Tap: Quick 250ms burst then auto-stop
 *   - Hold: Continuous spin until release
 *   - Use for: Quick weapon aiming
 * 
 * Right Bumper: Spin right in place
 *   - Same behavior as left bumper
 * 
 * 
 * STATE PRIORITIES:
 * ----------------
 * 1. Bumpers (highest) - Override everything for quick aim
 * 2. Triggers - Override joystick for boost/retreat
 * 3. Joystick - Default precision control
 * 4. Nothing pressed - Stop
 * 
 * Special: Both triggers = Emergency stop
 * 
 * 
 * ESC BASICS:
 * -----------
 * ESCs (Electronic Speed Controllers) control brushless motors
 * They use PWM signals measured in microseconds:
 *   - 1000μs = Full reverse
 *   - 1500μs = Neutral (stopped)
 *   - 2000μs = Full forward
 * 
 * The 50Hz frequency means 20ms between pulses (standard for ESCs)
 * 
 * 
 * SAFETY FEATURES:
 * ---------------
 * - Controller disconnect: Immediate stop
 * - Command timeout: Stop if no input for 1 second
 * - Both triggers: Emergency neutral
 * - Dead zones: Prevent drift from centered sticks
 * 
 * 
 * TUNING TIPS:
 * -----------
 * - Joystick too sensitive? Increase JOYSTICK_DEAD_ZONE
 * - Turn too slow? Decrease TURN_BURST_DURATION
 * - Motors backwards? Flip INVERT_LEFT/RIGHT_MOTOR
 * 
 * 
 * IMPORTANT - Motor Inversion Logic:
 * ---------------------------------
 * Motor inversion is tricky! Here's how it works:
 * 
 * 1. SINGLE MOTOR INVERTED (left OR right):
 *    - Straight movement works correctly
 *    - Turning works correctly
 *    - Example: If your robot goes straight but curves slightly, one motor
 *      might be wired backwards - flip that motor's INVERT flag
 * 
 * 2. BOTH MOTORS INVERTED (left AND right):
 *    - This is common for front-wheel drive robots!
 *    - Straight movement works, BUT turning gets reversed
 *    - The code automatically detects this and compensates by:
 *      a) Flipping joystick X-axis (turn direction)
 *      b) Swapping left/right bumper behavior
 *    - Controller behavior stays consistent: right bumper = turn right
 * 
 * How to test:
 * 1. Set both INVERT flags to false
 * 2. Test triggers: Right trigger = forward? Left trigger = reverse?
 * 3. If backwards, set BOTH INVERT flags to true
 * 4. Test bumpers: Right bumper should still turn right
 * 5. Test joystick: Right stick should still turn right
 * 
 * The code handles all the complexity automatically!
 */
