#include <ESP32Servo.h>

// Motor pin configuration
const int LEFT_MOTOR_PIN = D9;
const int RIGHT_MOTOR_PIN = D10;

// ESC pulse width constants (microseconds)
const int NEUTRAL_SPEED = 1500;  // Stop/neutral position
const int MIN_SPEED = 1000;      // Full reverse
const int MAX_SPEED = 2000;      // Full forward

// ESC calibration timing
const int ESC_CAL_DELAY = 2000;      // Delay for ESC calibration steps
const int STARTUP_DELAY = 3000;      // Initial power-up delay
const int TEST_STEP_DELAY = 2000;    // Delay between test steps

// Global variables
Servo leftESC;
Servo rightESC;
bool escsArmed = false;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting ESC Motor Test...");
    
    // Initialize ESP32Servo timers
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    
    // Wait for serial monitor
    delay(2000);
    
    // Arm the ESCs
    armESCs();
    
    // Show available commands
    printCommands();
}

void armESCs() {
    Serial.println("========== ESC ARMING SEQUENCE ==========");
    
    // Attach ESCs with proper pulse width range
    leftESC.attach(LEFT_MOTOR_PIN, MIN_SPEED, MAX_SPEED);
    rightESC.attach(RIGHT_MOTOR_PIN, MIN_SPEED, MAX_SPEED);
    Serial.println("✓ ESCs attached to pins");
    
    // Initial power-up delay
    Serial.println("⏳ Initial power-up delay...");
    delay(STARTUP_DELAY);
    Serial.println("✓ Power-up delay complete");

    // ESC Calibration Sequence
    Serial.println("🔧 Starting ESC calibration...");
    
    // Step 1: Set to neutral
    Serial.println("   Setting neutral position (1500μs)...");
    leftESC.writeMicroseconds(NEUTRAL_SPEED);
    rightESC.writeMicroseconds(NEUTRAL_SPEED);
    delay(ESC_CAL_DELAY);
    Serial.println("   ✓ Neutral position set");
    
    // Step 2: Brief high pulse (some ESCs need this)
    Serial.println("   Sending brief high pulse (1600μs)...");
    leftESC.writeMicroseconds(1600);
    rightESC.writeMicroseconds(1600);
    delay(500);
    
    // Step 3: Back to neutral
    Serial.println("   Returning to neutral...");
    leftESC.writeMicroseconds(NEUTRAL_SPEED);
    rightESC.writeMicroseconds(NEUTRAL_SPEED);
    delay(ESC_CAL_DELAY);
    
    escsArmed = true;
    Serial.println("✅ ESCs ARMED AND READY!");
    Serial.println("=========================================");
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
    if (!escsArmed) {
        Serial.println("❌ ESCs not armed! Cannot set motor speed.");
        return;
    }
    
    // Constrain values to safe range
    leftSpeed = constrain(leftSpeed, MIN_SPEED, MAX_SPEED);
    rightSpeed = constrain(rightSpeed, MIN_SPEED, MAX_SPEED);
    
    leftESC.writeMicroseconds(leftSpeed);
    rightESC.writeMicroseconds(rightSpeed);
    
    Serial.printf("🔧 Motor speeds set - Left: %d μs, Right: %d μs\n", leftSpeed, rightSpeed);
}

void stopMotors() {
    setMotorSpeed(NEUTRAL_SPEED, NEUTRAL_SPEED);
    Serial.println("⏹️  Motors stopped (neutral)");
}

void runBasicTest() {
    if (!escsArmed) {
        Serial.println("❌ Cannot run test - ESCs not armed!");
        return;
    }
    
    Serial.println("🧪 STARTING BASIC MOTOR TEST");
    Serial.println("===============================");
    
    // Test 1: Neutral (should be no movement)
    Serial.println("Test 1: Neutral position...");
    setMotorSpeed(NEUTRAL_SPEED, NEUTRAL_SPEED);
    delay(TEST_STEP_DELAY);
    
    // Test 2: Slow forward
    Serial.println("Test 2: Slow forward...");
    setMotorSpeed(1550, 1550); // Slightly above neutral
    delay(TEST_STEP_DELAY);
    
    // Test 3: Medium forward
    Serial.println("Test 3: Medium forward...");
    setMotorSpeed(1650, 1650);
    delay(TEST_STEP_DELAY);
    
    // Test 4: Back to neutral
    Serial.println("Test 4: Back to neutral...");
    stopMotors();
    delay(TEST_STEP_DELAY);
    
    // Test 5: Slow reverse
    Serial.println("Test 5: Slow reverse...");
    setMotorSpeed(1450, 1450); // Slightly below neutral
    delay(TEST_STEP_DELAY);
    
    // Test 6: Medium reverse
    Serial.println("Test 6: Medium reverse...");
    setMotorSpeed(1350, 1350);
    delay(TEST_STEP_DELAY);
    
    // Test 7: Stop
    Serial.println("Test 7: Final stop...");
    stopMotors();
    
    Serial.println("✅ BASIC TEST COMPLETE");
    Serial.println("========================");
}

void runTurnTest() {
    if (!escsArmed) {
        Serial.println("❌ Cannot run test - ESCs not armed!");
        return;
    }
    
    Serial.println("🔄 STARTING TURN TEST");
    Serial.println("=====================");
    
    // Left turn (right motor forward, left motor reverse)
    Serial.println("Left turn test...");
    setMotorSpeed(1400, 1600); // Left slower/reverse, right faster/forward
    delay(TEST_STEP_DELAY);
    
    stopMotors();
    delay(1000);
    
    // Right turn (left motor forward, right motor reverse)
    Serial.println("Right turn test...");
    setMotorSpeed(1600, 1400); // Left faster/forward, right slower/reverse
    delay(TEST_STEP_DELAY);
    
    stopMotors();
    Serial.println("✅ TURN TEST COMPLETE");
    Serial.println("======================");
}

void printCommands() {
    Serial.println("\n📋 AVAILABLE COMMANDS:");
    Serial.println("======================");
    Serial.println("'t' - Run basic motor test sequence");
    Serial.println("'r' - Run turn test");
    Serial.println("'s' - Stop all motors");
    Serial.println("'a' - Re-arm ESCs");
    Serial.println("'f' - Manual forward (medium speed)");
    Serial.println("'b' - Manual reverse (medium speed)");
    Serial.println("'h' - Show this help menu");
    Serial.println("======================\n");
}

void processSerialCommand() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        
        switch (command) {
            case 't':
                runBasicTest();
                break;
                
            case 'r':
                runTurnTest();
                break;
                
            case 's':
                stopMotors();
                break;
                
            case 'a':
                Serial.println("Re-arming ESCs...");
                escsArmed = false;
                armESCs();
                break;
                
            case 'f':
                Serial.println("Manual forward test...");
                setMotorSpeed(1650, 1650);
                delay(2000);
                stopMotors();
                break;
                
            case 'b':
                Serial.println("Manual reverse test...");
                setMotorSpeed(1350, 1350);
                delay(2000);
                stopMotors();
                break;
                
            case 'h':
                printCommands();
                break;
                
            default:
                Serial.println("Unknown command. Type 'h' for help.");
                break;
        }
    }
}

void loop() {
    processSerialCommand();
    
    // Small delay to prevent overwhelming the system
    delay(50);
}
