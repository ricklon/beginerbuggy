# Combat Buggy Wiring Diagrams and Soldering Guide

## Table of Contents
1. [System Overview](#system-overview)
2. [Component Connections](#component-connections)
3. [Power Distribution](#power-distribution)
4. [ESC Wiring Options](#esc-wiring-options)
5. [Soldering Procedures](#soldering-procedures)
6. [Wire Management](#wire-management)
7. [Testing and Verification](#testing-and-verification)
8. [Troubleshooting](#troubleshooting)

---

## System Overview

### Main Electrical Components
- **Power Source:** OVONIC 3S LiPo 450mAh battery (11.1V nominal)
- **Main Switch:** Lynx Anti-Spark Kill Switch
- **Motor Controller:** Repeat Robotics Dual ESC or Weka 20A v2.2
- **Microcontroller:** Xiao ESP32C3/S3
- **Motors:** Repeat Drive Brushed gear motors (2x)
- **Connectors:** XT30 for main power

### Electrical System Architecture
```
[Battery] → [XT30] → [Kill Switch] → [ESC] → [Motors]
                         ↓
                   [Microcontroller] → [Receiver/Controller]
```

---

## Component Connections

### Main Power Circuit

#### Battery to Kill Switch
```
Battery (+) → Red Wire → Kill Switch Input (+)
Battery (-) → Black Wire → Common Ground
```

#### Kill Switch to ESC
```
Kill Switch Output (+) → Red Wire → ESC V+ Input
Common Ground → Black Wire → ESC GND Input
```

#### ESC to Motors
```
ESC Motor A (+) → Red Wire → Motor 1 (+)
ESC Motor A (-) → Black Wire → Motor 1 (-)
ESC Motor B (+) → Red Wire → Motor 2 (+)
ESC Motor B (-) → Black Wire → Motor 2 (-)
```

### Control Circuit

#### ESP32 to ESC Signal Connections
```
ESP32 Pin D0 → ESC Channel A Signal (Left Motor)
ESP32 Pin D1 → ESC Channel B Signal (Right Motor)
ESP32 GND → ESC Signal Ground
ESP32 5V → ESC 5V Output (if available)
```

---

## Power Distribution

### Main Power Path Diagram
```
[3S LiPo Battery]
    |
    | XT30 Connector
    |
[Lynx Kill Switch]
    |
    | High Current Path (Drive Motors)
    |
[Motor Controller/ESC]
    |
    ├─ Motor A (Left Drive)
    └─ Motor B (Right Drive)
```

### Auxiliary Power
```
[ESC 5V Output] → [ESP32 5V Input]
                → [Receiver Power]
```

### Power Specifications
- **Main Circuit:** 11.1V nominal (12.6V fully charged)
- **Maximum Current:** 20A per motor channel
- **Control Circuit:** 5V regulated from ESC
- **Signal Levels:** 3.3V PWM signals from ESP32

---

## ESC Wiring Options

### Option 1: Repeat Robotics Budget Dual ESC

#### Connector Pinout
```
Power Input:
- Red Wire: Battery Positive (V+)
- Black Wire: Battery Negative (GND)

Motor Outputs:
- Motor A: Red/Black wire pair
- Motor B: Red/Black wire pair

Signal Input:
- Channel A: White/Orange wire (PWM signal)
- Channel B: White/Orange wire (PWM signal)
- Ground: Brown/Black wire (Signal ground)
```

#### Connection Sequence
1. **Power Connections First:**
   - Solder XT30 connector to main power input
   - Connect kill switch in series with positive lead
   - Verify polarity before applying power

2. **Motor Connections:**
   - Use 16-18 AWG wire for motor connections
   - Solder directly to motor terminals
   - Apply heat shrink tubing over connections

3. **Signal Connections:**
   - Connect to ESP32 PWM outputs
   - Use 22-24 AWG wire for signal connections
   - Keep signal wires away from power wires

### Option 2: Weka 20A v2.2 Dual ESC

#### Features and Connections
- **Weight:** Only 3g without wires
- **Protection:** Overcurrent and undervoltage protection
- **Mixing:** Enabled by default for tank steering

#### Wiring Differences
```
Power Input: Same as Repeat ESC
Motor Outputs: Higher current capacity (20A per channel)
Signal Input: Standard servo-style connectors
Additional Features: Built-in mixing for differential drive
```

---

## Soldering Procedures

### Required Tools and Materials
- **Soldering Iron:** 25-40W with fine tip
- **Solder:** 60/40 rosin core, 0.6-0.8mm diameter
- **Flux:** Additional rosin flux for clean joints
- **Heat Shrink:** Various sizes (2mm, 4mm, 6mm)
- **Wire Strippers:** For 16-24 AWG wire
- **Multimeter:** For continuity testing

### General Soldering Guidelines

#### Preparation Steps
1. **Clean all surfaces** with isopropyl alcohol
2. **Pre-tin all wires and pads** before joining
3. **Use appropriate wire gauge:**
   - Main power: 16-18 AWG
   - Motor connections: 16-18 AWG
   - Signal wires: 22-24 AWG

#### Soldering Technique
1. **Heat the joint** - not the solder
2. **Feed solder into the joint** - let it flow naturally
3. **Remove solder first**, then iron
4. **Keep joint still** until solder cools
5. **Inspect joint** - should be shiny and cone-shaped

### Specific Connection Procedures

#### XT30 Connector Installation
**Critical Safety Note:** XT30 connectors are polarized. Incorrect installation can damage components.

```
Male Connector (Battery Side):
- Larger terminal: Positive (Red wire)
- Smaller terminal: Negative (Black wire)

Female Connector (Robot Side):
- Larger socket: Positive (Red wire)
- Smaller socket: Negative (Black wire)
```

**Installation Steps:**
1. **Slide heat shrink** over wire before soldering
2. **Strip wire 4-5mm** - just enough to fill terminal cup
3. **Pre-tin stripped wire** with thin solder coating
4. **Heat terminal cup** with soldering iron
5. **Insert wire and add solder** to fill cup completely
6. **Hold steady** until solder cools (3-5 seconds)
7. **Slide heat shrink** over connection and shrink with heat gun
8. **Test with multimeter** for continuity and correct polarity

#### Motor Terminal Connections
**Motor Wire Gauge:** Use 16-18 AWG for adequate current capacity

**Procedure:**
1. **Clean motor terminals** with fine sandpaper if needed
2. **Strip wire 3-4mm** - enough to wrap around terminal
3. **Pre-tin wire and terminal** lightly
4. **Wrap wire around terminal** clockwise (tightening direction)
5. **Solder connection** with adequate heat and solder
6. **Cover with heat shrink** extending beyond bare metal
7. **Test motor direction** before final assembly

#### ESC Power Input Soldering
**Wire Gauge:** 16-18 AWG for main power, 22-24 AWG for signals

**Power Input Steps:**
1. **Identify correct pads** on ESC (usually marked V+ and GND)
2. **Pre-tin ESC pads** with thin layer of solder
3. **Strip and pre-tin wires** - keep length minimal
4. **Solder red wire to V+** pad quickly to avoid overheating
5. **Solder black wire to GND** pad
6. **Strain relief** with cable tie or heat shrink boot

#### Signal Wire Connections
**Important:** Signal wires carry 3.3V or 5V logic levels - use appropriate wire gauge

**ESP32 to ESC Signal Connections:**
1. **Use servo-style connectors** if ESC has them
2. **Solder directly to pads** if no connectors available
3. **Color coding:**
   - Red: 5V power (if needed)
   - Black/Brown: Ground
   - White/Orange: PWM signal
4. **Keep signal wires short** to minimize interference

---

## Wire Management

### Routing Guidelines
- **Separate power and signal wires** by at least 10mm
- **Use shortest practical wire lengths** to reduce weight
- **Secure all connections** with heat shrink or electrical tape
- **Avoid sharp edges** that could cut wires during combat
- **Plan for disassembly** - don't permanently trap wires

### Protection Methods
1. **Heat Shrink Tubing:** Primary protection for all solder joints
2. **Cable Ties:** Strain relief and organization
3. **Split Loom Tubing:** Protection in high-wear areas
4. **3M Dual Lock:** Secure component mounting without permanent attachment

### Weight Optimization
- **Minimize wire length** - every inch adds weight
- **Use appropriate gauge** - don't oversize unnecessarily
- **Remove excess insulation** where safe to do so
- **Bundle related wires** with thin cable ties

---

## Testing and Verification

### Pre-Power Testing
**Always test before applying power!**

#### Continuity Tests
1. **Battery to kill switch:** Verify switch operation
2. **Kill switch to ESC:** Check correct polarity
3. **ESC to motors:** Verify no shorts between channels
4. **Signal connections:** Check ESP32 to ESC signal paths

#### Resistance Tests
1. **Motor resistance:** Should be 1-10 ohms typically
2. **Power path resistance:** Should be near zero
3. **Insulation resistance:** Check for shorts to chassis

### Initial Power-Up Procedure
**Safety First: Always test with robot on blocks!**

1. **Set kill switch to OFF**
2. **Connect battery** - verify no sparks or heating
3. **Check voltage at ESC input** with multimeter
4. **Turn kill switch to ON** - verify voltage passes through
5. **Check 5V output** from ESC if used for ESP32 power
6. **Program and test ESP32** before connecting to motors

### Motor Direction Testing
1. **Connect one motor at a time**
2. **Apply brief forward command** from ESP32
3. **Observe wheel rotation direction**
4. **Swap motor wires if direction is incorrect**
5. **Test both motors** before final assembly

---

## Troubleshooting

### Common Issues and Solutions

#### No Power to System
**Symptoms:** No LED indicators, no motor response
**Check:**
- Battery voltage (should be >11V for 3S)
- Kill switch continuity
- XT30 connector polarity
- Blown fuses or damaged components

#### Motors Not Responding
**Symptoms:** Power present but motors don't move
**Check:**
- ESC programming and calibration
- Signal wire connections
- Motor wire continuity
- ESP32 PWM output signals

#### Wrong Motor Direction
**Symptoms:** Robot moves opposite to commanded direction
**Solutions:**
- Swap motor wires at ESC output
- Modify software channel mapping
- Check PWM signal polarity

#### Intermittent Operation
**Symptoms:** System works sometimes, fails randomly
**Check:**
- Loose solder joints
- Damaged wire insulation
- Poor connections under vibration
- Inadequate strain relief

#### ESC Overheating
**Symptoms:** ESC becomes hot during operation
**Causes:**
- Overcurrent from stalled motors
- Inadequate cooling airflow
- Damaged ESC components
- Excessive ambient temperature

### Diagnostic Tools
1. **Multimeter:** Voltage, current, and resistance measurements
2. **Oscilloscope:** PWM signal analysis (if available)
3. **Current Clamp:** Monitor motor current draw
4. **Battery Tester:** Verify battery health and capacity

### Field Repair Kit
**Essential Items for Competition Day:**
- Spare XT30 connectors
- Pre-tinned wire lengths
- Heat shrink tubing
- Portable soldering iron
- Multimeter
- Spare ESC (if budget allows)
- Electrical tape
- Wire strippers/crimpers

---

## Safety Considerations

### Electrical Safety
- **Never work on live circuits** - always disconnect battery
- **Verify kill switch operation** before each use
- **Use proper fusing** to protect against overcurrent
- **Insulate all connections** to prevent shorts
- **Keep spare batteries** in proper storage containers

### LiPo Battery Safety
- **Charge only with balance charger** (ISDT PD60 recommended)
- **Never charge unattended** - monitor temperature and voltage
- **Store at 3.8V per cell** for long-term storage
- **Use fireproof charging bags** for safety
- **Dispose of damaged batteries** at proper recycling centers

### Competition Safety
- **Remove weapon safety link** only when authorized
- **Test all safety systems** before each match
- **Have emergency procedures** clearly planned
- **Carry proper documentation** of wiring and safety systems

---

## Revision History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2025-07-08 | Initial creation of wiring guide |
| | | Added comprehensive soldering procedures |
| | | Included both ESC options (Repeat and Weka) |
| | | Added troubleshooting section |

---

**Remember:** When in doubt about any electrical connection, stop and verify before proceeding. A careful build now prevents failures during competition!
