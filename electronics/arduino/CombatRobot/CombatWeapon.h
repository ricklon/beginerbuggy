// ============================================================================
// CombatWeapon.h - Weapon control library for combat robots
// 
// This file contains DECLARATIONS (what the classes can do).
// See CombatWeapon.cpp for IMPLEMENTATIONS (how they do it).
// 
// Usage: #include "CombatWeapon.h" in your main sketch
// ============================================================================

#ifndef COMBAT_WEAPON_H
#define COMBAT_WEAPON_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include <Bluepad32.h>

// ============================================================================
// WEAPON TYPES
// ============================================================================

enum WeaponType {
    WEAPON_NONE,
    WEAPON_VERTICAL_SPINNER,
    WEAPON_HORIZONTAL_SPINNER,
    WEAPON_LIFTER,
    WEAPON_FLIPPER
};

// ============================================================================
// BASE WEAPON CLASS
// ============================================================================
// All weapon types inherit from this base class.
// This defines the common interface that all weapons share.
// ============================================================================

class CombatWeapon {
public:
    // Constructor and destructor
    CombatWeapon();
    virtual ~CombatWeapon() {}
    
    // Setup and initialization
    virtual void begin(int weaponPin);
    virtual void setConnectionTime(unsigned long connectTime);
    
    // Main control loop - must be overridden by each weapon type
    virtual void update(ControllerPtr controller) = 0;
    
    // Safety controls
    virtual void emergencyStop();
    bool isArmed();
    void disarm();
    
    // Status checking
    bool isActive();
    unsigned long getActiveTime();
    
    // Configuration
    void setSafetyDelay(unsigned long delayMs);
    void setEnableButton(int button);
    void setVerboseDebug(bool enabled);
    
protected:
    // Protected members - accessible by derived classes
    int pin;
    bool armed;
    bool active;
    unsigned long connectionTime;
    unsigned long safetyDelay;
    unsigned long activationTime;
    int enableButton;
    bool verboseDebug;
    
    // Helper methods
    bool checkSafetyDelay();
    void debugPrint(const char* message);
};

// ============================================================================
// NO WEAPON CLASS
// ============================================================================
// Safe default when no weapon is installed.
// All methods do nothing - prevents null pointer errors.
// ============================================================================

class NoWeapon : public CombatWeapon {
public:
    NoWeapon();
    
    void begin(int weaponPin) override;
    void update(ControllerPtr controller) override;
    void emergencyStop() override;
};

// ============================================================================
// SPINNER WEAPON CLASS
// ============================================================================
// Controls brushless motor spinners (vertical or horizontal).
// Features: variable speed, smooth ramp up/down, rumble feedback.
// ============================================================================

class SpinnerWeapon : public CombatWeapon {
public:
    // Constructor
    SpinnerWeapon(WeaponType type = WEAPON_VERTICAL_SPINNER);
    
    // Required overrides
    void begin(int weaponPin) override;
    void update(ControllerPtr controller) override;
    void emergencyStop() override;
    
    // Spinner-specific configuration
    void setSpinUpTime(unsigned long milliseconds);
    void setSpinDownTime(unsigned long milliseconds);
    void setMaxSpeed(int speed);
    void setIdleSpeed(int speed);
    void setControlMode(int mode);        // 0=toggle, 1=hold, 2=variable
    void setRumbleFeedback(bool enabled);
    
private:
    // Hardware interface
    Servo weaponESC;
    WeaponType spinnerType;
    ControllerPtr lastController;
    
    // Speed control
    int currentSpeed;
    int targetSpeed;
    int maxSpeed;
    int idleSpeed;
    int neutralSpeed;
    
    // Timing
    unsigned long spinUpTime;
    unsigned long spinDownTime;
    unsigned long lastUpdateTime;
    
    // Control state
    int controlMode;
    bool toggleState;
    bool lastButtonState;
    
    // Rumble feedback
    bool rumbleEnabled;
    bool hasRumbledArmed;
    int lastRumbleSpeed;
    
    // Helper methods
    void updateSpeed();
    void updateRumble();
};

// ============================================================================
// LIFTER WEAPON CLASS
// ============================================================================
// Controls servo-based lifters and arms.
// Features: position control, smooth movement, button or analog control.
// ============================================================================

class LifterWeapon : public CombatWeapon {
public:
    // Constructor
    LifterWeapon();
    
    // Required overrides
    void begin(int weaponPin) override;
    void update(ControllerPtr controller) override;
    void emergencyStop() override;
    
    // Lifter-specific configuration
    void setRange(int minAngle, int maxAngle);
    void setSpeed(int degreesPerSecond);
    void setControlMode(int mode);  // 0=buttons, 1=analog stick
    void setUpButton(int button);
    void setDownButton(int button);
    
private:
    // Hardware interface
    Servo lifterServo;
    
    // Position control
    int currentAngle;
    int targetAngle;
    int minAngle;
    int maxAngle;
    int speed;  // degrees per second
    
    // Control state
    int controlMode;
    int upButton;
    int downButton;
    unsigned long lastUpdateTime;
    
    // Helper methods
    void updatePosition();
};

// ============================================================================
// FLIPPER WEAPON CLASS
// ============================================================================
// Controls pneumatic flippers via solenoid valve.
// Features: timed pulses, cooldown periods, tap or hold modes.
// ============================================================================

class FlipperWeapon : public CombatWeapon {
public:
    // Constructor
    FlipperWeapon();
    
    // Required overrides
    void begin(int weaponPin) override;
    void update(ControllerPtr controller) override;
    void emergencyStop() override;
    
    // Flipper-specific configuration
    void setFireDuration(unsigned long milliseconds);
    void setCooldownTime(unsigned long milliseconds);
    void setControlMode(int mode);  // 0=tap to fire, 1=hold
    
private:
    // Hardware interface
    int solenoidPin;
    
    // Firing state
    bool firing;
    unsigned long fireStartTime;
    unsigned long lastFireTime;
    
    // Configuration
    unsigned long fireDuration;
    unsigned long cooldownTime;
    int controlMode;
    bool lastButtonState;
    
    // Helper methods
    bool canFire();
    void fire();
    void checkFireTimeout();
};

#endif // COMBAT_WEAPON_H