// ============================================================================
// CombatWeapon.cpp - Implementation of weapon control library
// 
// This file contains the IMPLEMENTATIONS (how methods work).
// See CombatWeapon.h for DECLARATIONS (what methods exist).
// ============================================================================

#include "CombatWeapon.h"

// ============================================================================
// BASE WEAPON CLASS - Implementation
// ============================================================================

CombatWeapon::CombatWeapon() 
    : pin(-1)
    , armed(false)
    , active(false)
    , connectionTime(0)
    , safetyDelay(3000)  // 3 second default
    , activationTime(0)
    , enableButton(0)
    , verboseDebug(true)
{
}

void CombatWeapon::begin(int weaponPin) {
    pin = weaponPin;
    armed = false;
    active = false;
    debugPrint("Weapon initialized");
}

void CombatWeapon::setConnectionTime(unsigned long connectTime) {
    connectionTime = connectTime;
    debugPrint("Safety delay started");
}

bool CombatWeapon::checkSafetyDelay() {
    if (connectionTime == 0) return false;
    return (millis() - connectionTime >= safetyDelay);
}

void CombatWeapon::emergencyStop() {
    armed = false;
    active = false;
    debugPrint("EMERGENCY STOP");
}

bool CombatWeapon::isArmed() {
    return armed && checkSafetyDelay();
}

void CombatWeapon::disarm() {
    armed = false;
    active = false;
}

void CombatWeapon::setSafetyDelay(unsigned long delayMs) {
    safetyDelay = delayMs;
}

void CombatWeapon::setEnableButton(int button) {
    enableButton = button;
}

void CombatWeapon::setVerboseDebug(bool enabled) {
    verboseDebug = enabled;
}

bool CombatWeapon::isActive() {
    return active;
}

unsigned long CombatWeapon::getActiveTime() {
    if (!active) return 0;
    return millis() - activationTime;
}

void CombatWeapon::debugPrint(const char* message) {
    if (verboseDebug) {
        Serial.print("[WEAPON] ");
        Serial.println(message);
    }
}

// ============================================================================
// NO WEAPON CLASS - Implementation
// ============================================================================

NoWeapon::NoWeapon() : CombatWeapon() {
}

void NoWeapon::begin(int weaponPin) {
    // Intentionally empty - no weapon to initialize
}

void NoWeapon::update(ControllerPtr controller) {
    // Intentionally empty - no weapon to control
}

void NoWeapon::emergencyStop() {
    // Intentionally empty - nothing to stop
}

// ============================================================================
// SPINNER WEAPON CLASS - Implementation
// ============================================================================

SpinnerWeapon::SpinnerWeapon(WeaponType type)
    : CombatWeapon()
    , spinnerType(type)
    , lastController(nullptr)
    , currentSpeed(1500)
    , targetSpeed(1500)
    , maxSpeed(2000)
    , idleSpeed(1500)
    , neutralSpeed(1500)
    , spinUpTime(2000)
    , spinDownTime(3000)
    , lastUpdateTime(0)
    , controlMode(2)  // Default to variable speed
    , toggleState(false)
    , lastButtonState(false)
    , rumbleEnabled(true)
    , hasRumbledArmed(false)
    , lastRumbleSpeed(1500)
{
}

void SpinnerWeapon::begin(int weaponPin) {
    CombatWeapon::begin(weaponPin);
    
    weaponESC.attach(weaponPin, 1000, 2000);
    weaponESC.writeMicroseconds(neutralSpeed);
    
    currentSpeed = neutralSpeed;
    targetSpeed = neutralSpeed;
    
    delay(2000);  // Wait for ESC to arm
    
    armed = true;
    debugPrint("Spinner ESC armed");
}

void SpinnerWeapon::update(ControllerPtr controller) {
    lastController = controller;
    
    // One-time rumble when weapon becomes armed
    if (!hasRumbledArmed && isArmed() && rumbleEnabled && controller) {
        controller->playDualRumble(0 /* delayedStartMs */, 
                                   200 /* durationMs */, 
                                   0x40 /* weakMagnitude */, 
                                   0x80 /* strongMagnitude */);
        hasRumbledArmed = true;
        debugPrint("Weapon ARMED - rumble sent");
    }
    
    // If not armed yet, just idle
    if (!isArmed()) {
        targetSpeed = neutralSpeed;
        updateSpeed();
        updateRumble();
        return;
    }
    
    // Get button state based on configured enable button
    bool buttonPressed = false;
    if (enableButton == 0) buttonPressed = (controller->brake() > 10);  // R2
    else if (enableButton == 1) buttonPressed = controller->r1();       // R1
    else if (enableButton == 2) buttonPressed = controller->r2();       // R2 button
    
    // Handle different control modes
    if (controlMode == 0) {
        // Toggle mode - tap button to start/stop
        if (buttonPressed && !lastButtonState) {
            toggleState = !toggleState;
            targetSpeed = toggleState ? maxSpeed : neutralSpeed;
            active = toggleState;
            
            if (active) {
                activationTime = millis();
                debugPrint("SPINNER ON");
            } else {
                debugPrint("SPINNER OFF");
            }
        }
        lastButtonState = buttonPressed;
        
    } else if (controlMode == 1) {
        // Hold mode - hold button to spin
        if (buttonPressed) {
            targetSpeed = maxSpeed;
            if (!active) {
                active = true;
                activationTime = millis();
                debugPrint("SPINNER ON");
            }
        } else {
            targetSpeed = neutralSpeed;
            if (active) {
                active = false;
                debugPrint("SPINNER OFF");
            }
        }
        
    } else if (controlMode == 2) {
        // Variable speed mode - right stick Y controls speed
        int stickInput = controller->axisRY();
        
        // Apply dead zone
        if (abs(stickInput) < 50) {
            stickInput = 0;
        }
        
        // Only positive direction (push up = faster)
        if (stickInput > 0) {
            // Map stick position to speed
            targetSpeed = map(stickInput, 50, 512, neutralSpeed, maxSpeed);
            
            if (!active) {
                active = true;
                activationTime = millis();
                debugPrint("SPINNER ACTIVE");
            }
        } else {
            targetSpeed = neutralSpeed;
            if (active) {
                active = false;
                debugPrint("SPINNER IDLE");
            }
        }
    }
    
    updateSpeed();
    updateRumble();
}

void SpinnerWeapon::updateSpeed() {
    unsigned long currentTime = millis();
    
    // Initialize timing on first call
    if (lastUpdateTime == 0) {
        lastUpdateTime = currentTime;
        return;
    }
    
    unsigned long deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;
    
    // Calculate ramp rate based on whether spinning up or down
    int rampTime = (targetSpeed > currentSpeed) ? spinUpTime : spinDownTime;
    int speedRange = maxSpeed - neutralSpeed;
    float rampRate = (float)speedRange / (float)rampTime;  // speed units per millisecond
    
    int maxChange = (int)(rampRate * deltaTime);
    
    // Ramp towards target speed
    if (currentSpeed < targetSpeed) {
        currentSpeed = min(currentSpeed + maxChange, targetSpeed);
    } else if (currentSpeed > targetSpeed) {
        currentSpeed = max(currentSpeed - maxChange, targetSpeed);
    }
    
    // Send to ESC
    weaponESC.writeMicroseconds(currentSpeed);
}

void SpinnerWeapon::updateRumble() {
    if (!rumbleEnabled || !lastController) return;
    
    // Calculate speed as percentage
    int speedRange = maxSpeed - neutralSpeed;
    int currentRelative = currentSpeed - neutralSpeed;
    int speedPercent = (currentRelative * 100) / speedRange;
    speedPercent = constrain(speedPercent, 0, 100);
    
    // Only update rumble if speed changed significantly
    int lastSpeedPercent = ((lastRumbleSpeed - neutralSpeed) * 100) / speedRange;
    int speedDelta = abs(speedPercent - lastSpeedPercent);
    
    if (speedDelta > 5) {  // 5% threshold
        // Map speed to rumble intensity
        uint8_t rumbleIntensity = map(speedPercent, 0, 100, 0, 0xFF);
        
        if (speedPercent > 10) {  // Only rumble above 10% speed
            // Send continuous rumble that matches weapon speed
            lastController->playDualRumble(
                0,                      // Start immediately
                100,                    // Short pulse duration
                rumbleIntensity / 2,    // Weak motor
                rumbleIntensity         // Strong motor
            );
        }
        
        lastRumbleSpeed = currentSpeed;
    }
}

void SpinnerWeapon::emergencyStop() {
    CombatWeapon::emergencyStop();
    targetSpeed = neutralSpeed;
    currentSpeed = neutralSpeed;
    weaponESC.writeMicroseconds(neutralSpeed);
    toggleState = false;
}

void SpinnerWeapon::setSpinUpTime(unsigned long milliseconds) {
    spinUpTime = milliseconds;
}

void SpinnerWeapon::setSpinDownTime(unsigned long milliseconds) {
    spinDownTime = milliseconds;
}

void SpinnerWeapon::setMaxSpeed(int speed) {
    maxSpeed = constrain(speed, neutralSpeed, 2000);
}

void SpinnerWeapon::setIdleSpeed(int speed) {
    idleSpeed = constrain(speed, 1000, neutralSpeed);
}

void SpinnerWeapon::setControlMode(int mode) {
    controlMode = constrain(mode, 0, 2);
}

void SpinnerWeapon::setRumbleFeedback(bool enabled) {
    rumbleEnabled = enabled;
}

// ============================================================================
// LIFTER WEAPON CLASS - Implementation
// ============================================================================

LifterWeapon::LifterWeapon()
    : CombatWeapon()
    , currentAngle(0)
    , targetAngle(0)
    , minAngle(0)
    , maxAngle(180)
    , speed(90)  // degrees per second
    , controlMode(0)
    , upButton(1)    // R1
    , downButton(0)  // R2
    , lastUpdateTime(0)
{
}

void LifterWeapon::begin(int weaponPin) {
    CombatWeapon::begin(weaponPin);
    
    lifterServo.attach(weaponPin, 500, 2500);
    lifterServo.write(minAngle);
    currentAngle = minAngle;
    targetAngle = minAngle;
    
    armed = true;
    debugPrint("Lifter initialized");
}

void LifterWeapon::update(ControllerPtr controller) {
    if (!isArmed()) {
        targetAngle = minAngle;
        updatePosition();
        return;
    }
    
    if (controlMode == 0) {
        // Button mode - up/down buttons
        bool upPressed = (upButton == 1) ? controller->r1() : (controller->brake() > 10);
        bool downPressed = (downButton == 0) ? (controller->throttle() > 10) : controller->l1();
        
        if (upPressed) {
            targetAngle = maxAngle;
            if (!active) {
                active = true;
                activationTime = millis();
                debugPrint("LIFTER UP");
            }
        } else if (downPressed) {
            targetAngle = minAngle;
            if (active) {
                debugPrint("LIFTER DOWN");
            }
            active = false;
        }
        
    } else if (controlMode == 1) {
        // Analog stick mode - right stick Y controls position
        int stickInput = controller->axisRY();
        if (abs(stickInput) > 50) {
            targetAngle = map(stickInput, -512, 512, minAngle, maxAngle);
            active = (targetAngle > (minAngle + 10));
        }
    }
    
    updatePosition();
}

void LifterWeapon::updatePosition() {
    unsigned long currentTime = millis();
    
    if (lastUpdateTime == 0) {
        lastUpdateTime = currentTime;
        return;
    }
    
    unsigned long deltaTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;
    
    // Calculate maximum angle change based on speed setting
    float maxChange = ((float)speed * (float)deltaTime) / 1000.0;
    
    // Move towards target angle
    if (currentAngle < targetAngle) {
        currentAngle = min(currentAngle + (int)maxChange, targetAngle);
    } else if (currentAngle > targetAngle) {
        currentAngle = max(currentAngle - (int)maxChange, targetAngle);
    }
    
    lifterServo.write(currentAngle);
}

void LifterWeapon::emergencyStop() {
    CombatWeapon::emergencyStop();
    targetAngle = minAngle;
}

void LifterWeapon::setRange(int minA, int maxA) {
    minAngle = constrain(minA, 0, 180);
    maxAngle = constrain(maxA, 0, 180);
}

void LifterWeapon::setSpeed(int degreesPerSecond) {
    speed = constrain(degreesPerSecond, 10, 360);
}

void LifterWeapon::setControlMode(int mode) {
    controlMode = constrain(mode, 0, 1);
}

void LifterWeapon::setUpButton(int button) {
    upButton = button;
}

void LifterWeapon::setDownButton(int button) {
    downButton = button;
}

// ============================================================================
// FLIPPER WEAPON CLASS - Implementation
// ============================================================================

FlipperWeapon::FlipperWeapon()
    : CombatWeapon()
    , solenoidPin(-1)
    , firing(false)
    , fireStartTime(0)
    , lastFireTime(0)
    , fireDuration(150)    // 150ms pulse default
    , cooldownTime(1000)   // 1 second cooldown
    , controlMode(0)
    , lastButtonState(false)
{
}

void FlipperWeapon::begin(int weaponPin) {
    CombatWeapon::begin(weaponPin);
    
    solenoidPin = weaponPin;
    pinMode(solenoidPin, OUTPUT);
    digitalWrite(solenoidPin, LOW);
    
    armed = true;
    debugPrint("Flipper initialized");
}

void FlipperWeapon::update(ControllerPtr controller) {
    // Check if currently firing needs to timeout
    checkFireTimeout();
    
    // Don't allow new fires if not armed or already firing
    if (!isArmed() || firing) {
        return;
    }
    
    // Get button state
    bool buttonPressed = false;
    if (enableButton == 0) buttonPressed = (controller->brake() > 10);  // R2
    else if (enableButton == 1) buttonPressed = controller->r1();       // R1
    else if (enableButton == 2) buttonPressed = controller->r2();       // R2 button
    
    if (controlMode == 0) {
        // Tap mode - fire on button press
        if (buttonPressed && !lastButtonState && canFire()) {
            fire();
        }
        lastButtonState = buttonPressed;
        
    } else if (controlMode == 1) {
        // Hold mode - fire while held (with cooldown)
        if (buttonPressed && canFire()) {
            fire();
        }
    }
}

bool FlipperWeapon::canFire() {
    return (millis() - lastFireTime >= cooldownTime);
}

void FlipperWeapon::fire() {
    digitalWrite(solenoidPin, HIGH);
    firing = true;
    active = true;
    fireStartTime = millis();
    lastFireTime = millis();
    activationTime = millis();
    
    debugPrint("FLIPPER FIRED!");
}

void FlipperWeapon::checkFireTimeout() {
    if (firing && (millis() - fireStartTime >= fireDuration)) {
        digitalWrite(solenoidPin, LOW);
        firing = false;
        active = false;
        debugPrint("Flipper retracted");
    }
}

void FlipperWeapon::emergencyStop() {
    CombatWeapon::emergencyStop();
    digitalWrite(solenoidPin, LOW);
    firing = false;
}

void FlipperWeapon::setFireDuration(unsigned long milliseconds) {
    fireDuration = constrain(milliseconds, 50, 1000);
}

void FlipperWeapon::setCooldownTime(unsigned long milliseconds) {
    cooldownTime = constrain(milliseconds, 200, 5000);
}

void FlipperWeapon::setControlMode(int mode) {
    controlMode = constrain(mode, 0, 1);
}