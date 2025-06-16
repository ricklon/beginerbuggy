# Robot Build Night Meeting Agenda
## FUBAR Labs Beginner Combat Robot - 1lb Class

**Date:** [Meeting Date]  
**Time:** [Meeting Time]  
**Location:** FUBAR Labs  
**Project Repository:** https://github.com/fubarlabs/begginerbuggy  
**Competition Class:** 1-pound Combat Robot (Antweight)

---

## 1. Combat Robot Overview: What Are We Building? (15 minutes)

### Project Introduction
- **1-Pound Combat Robot Platform** - Entry-level combat robotics
- **Competition Class:** Antweight (1 lb maximum weight)
- **Purpose:** Getting started in robot combat sports
- **Design Philosophy:** Durable, reliable, and competitive platform for beginners

### Combat Robot Fundamentals
- **Weight Budget:** Every gram counts - strategic weight allocation
- **Durability:** Designed to withstand impacts and weapon strikes
- **Weapon Systems:** Offensive capabilities within class constraints
- **Mobility:** Speed and maneuverability for tactical advantage
- **Competition Ready:** Meeting technical inspection requirements

### Learning Path
- **Build Skills:** Mechanical assembly, electronics integration, testing
- **Competition Skills:** Strategy, driving, field repairs
- **Community:** FUBAR Labs "Mechanical Mayhem" and regional events
- **Progression:** 1lb → 3lb → 12lb → higher weight classes

---

## 2. System Architecture and Weight Distribution (20 minutes)

### Core Combat Systems
- **Drive System:** Tank drive for combat maneuverability (~25-30% weight)
- **Weapon System:** Spinner, wedge, or lifter (~20-40% weight)
- **Frame/Armor:** Structural protection (~20-30% weight)
- **Electronics:** ESCs, receiver, battery (~15-25% weight)
- **Reserves:** Weight margin for modifications (~5-10% weight)

### Design Integration
- **Component Protection:** Shielding electronics from weapon impacts
- **Modularity:** Quick component swapping between matches
- **Access Points:** Easy reach for connections and adjustments
- **Impact Paths:** Routing forces around critical components

### Weight Management Strategy
- **Precision Scale:** 0.1g accuracy for final verification
- **Component Substitution:** Trading performance vs. weight
- **Material Selection:** Strength-to-weight optimization

---

## 3. Battery System and Power Management (25 minutes)

### Battery Specifications and Equipment
- **Battery:** OVONIC 3S LiPo 450mAh - $20 for 2 batteries
- **Voltage:** 11.1V nominal (3S configuration)
- **Capacity:** 450mAh - optimized for 1lb weight budget
- **Discharge Rate:** High-discharge capable for combat loads
- **Charger:** ISDT PD60 Balance Charger - $15
- **Kill Switch:** Lynx Kill Switch - $12.50 (combat robotics standard)

### Microcontroller Options
- **Budget Option:** Xiao ESP32C3 - $10
- **Advanced Option:** Xiao ESP32S3 - $17
- **Features:** WiFi capability, compact form factor
- **Programming:** Arduino IDE compatible

### Control System
- **Controller:** Xbox Standard Controller - $60
- **Interface:** Wireless connection to microcontroller
- **Advantages:** Familiar ergonomics, reliable operation

### Charging System and Procedures
- **Balance Charger:** Individual cell monitoring and balancing
- **Charging Location:** Fire-safe area with LiPo bags
- **Charging Rate:** 1C maximum (capacity in mAh = charge current in mA)
- **Voltage Monitoring:** Pre-charge cell voltage verification
- **Storage Charge:** 3.8V per cell for long-term storage
- **Field Charging:** Portable setup for competition day

### Battery Connection and Mounting
- **Main Power Connector:** Secure, accessible connection point
- **Battery Mounting:** Shock-resistant, secure retention system
- **Quick Disconnect:** Easy battery removal for charging/replacement
- **Polarity Protection:** Reverse connection prevention
- **Impact Protection:** Battery containment during combat

### Power Distribution Design
- **Main Kill Switch:** Large, accessible emergency disconnect
- **Drive Circuit:** Independent power path with fusing
- **Weapon Circuit:** Separate power with removable safety link
- **Electronics Power:** Clean, regulated power for radio systems

---

## 4. Remote Control System (15 minutes)

### Radio System Requirements
- **2.4GHz Spread Spectrum:** Modern interference-resistant technology
- **Failsafe Programming:** Safe shutdown on signal loss
- **Channel Assignment:** Drive (2 channels), weapon (1 channel), aux functions
- **Range Testing:** Verify operation at competition distances

### Transmitter Setup
- **Control Mixing:** Tank steering or differential drive setup
- **Weapon Switch:** Momentary or toggle for weapon control
- **Emergency Features:** Kill switch and panic stop functions
- **Ergonomics:** Comfortable operation under stress

### Receiver Installation
- **Antenna Placement:** Clear path, away from metal components
- **Shock Mounting:** Protection from combat impacts
- **Binding Process:** Secure pairing with transmitter
- **Signal Validation:** Pre-match radio check procedures

---

## 5. Electronic Speed Controllers (ESCs) (25 minutes)

### ESC Selection Guidelines
- **Budget Build:** Repeat Robotics dual ESC - proven, cost-effective
- **Performance Build:** Weka 20A v2.2 - higher current, more features
- **Weight Considerations:** Both are compact dual-channel designs
- **Availability:** Check stock before build session
- **Programming:** Both support standard PWM input from receivers

### Recommended ESC Options
**Option 1: Repeat Robotics Dual ESC - $19.99**
- **Current Rating:** Dual channel brushed ESC
- **Voltage Range:** 2-4S LiPo compatible  
- **Form Factor:** Compact dual channel design
- **Advantages:** Budget-friendly, proven in combat, excellent value
- **Source:** itgresa.com (verified current pricing)

**Option 2: WEKA 20A v2.2 Dual ESC - $40+**
- **Current Rating:** 20A per channel
- **Weight:** Only 3 grams without wires
- **Features:** Overcurrent protection, undervoltage protection, mixing enabled by default
- **Advantages:** Premium features, ultra-lightweight, advanced protection circuits
- **Source:** justcuzrobotics.com, also available through itgresa.com

### ESC Programming and Setup
- **Throttle Calibration:** Full range PWM signal setup (1000-2000μs typical)
- **Acceleration Limiting:** Prevent wheel spin and loss of control
- **Brake Strength:** Aggressive stopping for quick direction changes
- **Failsafe Behavior:** Stop motors on signal loss
- **Thermal Protection:** Prevent damage from overheating
- **Motor Direction:** Software reversing vs. wire swapping

### Installation and Protection
- **Dual ESC Wiring:** Single board drives both motors
- **Power Input:** Direct battery connection with fusing
- **Signal Input:** Receiver channels for left/right drive
- **Heat Sinking:** Thermal management in confined space
- **Shock Mounting:** Vibration dampening and impact protection
- **Wire Routing:** Protect connections from weapon damage

### Testing Procedures
- **Bench Testing:** Verify programming before installation
- **Block Testing:** Robot on blocks so wheels spin freely - CRITICAL!
- **Signal Testing:** Full range operation verification
- **Current Testing:** Monitor power draw during operation
- **Thermal Testing:** Check for overheating during extended runs

---

## 6. Drive Motors and Mobility (20 minutes)

### Motor Selection
- **Motors:** Repeat Motors Mk 4mm - 2 for $20
- **Type:** Brushed gear motors (required for selected ESCs)
- **Voltage Rating:** Compatible with 3S LiPo system
- **Mounting:** 4mm shaft with grub screw attachment
- **Source:** itgresa.com

### Drive System Assembly
- **Motor Mounting:** M4 screws with thread locker
- **Grub Screw Installation:** Secure wheel attachment
- **Wheel Selection:** Balance grip, weight, and durability
- **Differential Drive:** Independent left/right control

### Motor Wiring (Critical!)
- **Right Motor:** Red wire to positive, black to remaining terminal
- **Left Motor:** Black wire to positive, red to remaining terminal
- **Wire Protection:** Route away from weapon and impact zones
- **Connector System:** Easy field replacement if damaged

### Drive Testing
- **Block Testing:** Always test with robot elevated off table
- **Direction Verification:** Ensure correct forward/reverse operation
- **Current Testing:** Monitor ESC current draw
- **Performance Testing:** Speed and torque verification

---

## 7. Weapon Systems (30 minutes)

### 1lb Weapon Options
- **Horizontal Spinners:** Disk or bar weapons for kinetic impact
- **Vertical Spinners:** Drum weapons for lifting opponents
- **Wedges:** Passive weapons for getting under opponents
- **Lifters:** Servo or pneumatic lifting mechanisms

### Weapon Safety Features (Built-In)
- **Removable Safety Link:** Physical disconnection of weapon power
- **Weapon Switch:** Dedicated arming control separate from drive
- **Spin-Down Timer:** Weapons must stop within 60 seconds
- **Impact Limiting:** Design for safe energy levels
- **Secure Mounting:** Weapon retention during combat

### Weapon Installation Procedures
- **Safety Link Removal:** Always remove before any weapon work
- **Mounting Hardware:** High-strength fasteners with thread locker
- **Balance Verification:** Static and dynamic balance testing
- **Containment Testing:** Verify weapon stays attached under load
- **Emergency Stop Testing:** Verify immediate shutdown capability

### Weapon Testing Protocol
- **Safety Area:** Contained testing environment only
- **Safety Equipment:** Eye protection, hearing protection mandatory
- **Progressive Testing:** Start slow, gradually increase speed
- **Vibration Monitoring:** Watch for dangerous resonances
- **Spin-Down Verification:** Confirm 60-second stop requirement

---

## 8. Assembly and Integration (20 minutes)

### Mechanical Assembly Sequence
- **Frame/Chassis:** Base structure assembly first
- **Drive Installation:** Motors and wheels with proper alignment
- **Electronics Mounting:** ESCs, receiver, battery compartment
- **Weapon Installation:** Last step, with safety link removed
- **Final Fastening:** Thread locker on all critical connections

### Electrical Integration
- **Power Distribution:** Main switch, fusing, safety links
- **Signal Routing:** Keep power and signal wires separated
- **Connector System:** Standardized connections for field repairs
- **Wire Management:** Secure routing away from moving parts

### Weight Verification
- **Progressive Weighing:** Check weight at each assembly stage
- **Component Substitution:** Swap parts if over weight limit
- **Final Verification:** Official scale check before competition

### Integration Testing
- **Systems Check:** All subsystems operational independently
- **Combined Testing:** Drive and weapon systems together
- **Block Testing:** Always elevate robot during powered testing
- **Competition Simulation:** Full operational test sequence

---

## 9. Test Arena and Competition Prep (15 minutes)

### Test Arena Setup
- **Safety Barriers:** Polycarbonate walls for weapon containment
- **Test Blocks:** Elevate robot for safe wheel testing
- **Emergency Stop:** Remote kill capability
- **Tool Access:** Field repair station setup
- **Weight Station:** Precision scale for verification

### Pre-Competition Testing
- **Technical Inspection Prep:** Practice competition tech check
- **Weight Verification:** Multiple scale confirmations
- **Safety Systems Check:** All safety features operational
- **Performance Testing:** Speed, weapon function, reliability
- **Documentation:** Wiring diagrams and spare parts inventory

### Competition Day Procedures
- **Battery Management:** Charging schedule and rotation
- **Safety Link Protocol:** Installation/removal procedures
- **Field Repair Kit:** Essential tools and spare parts
- **Match Preparation:** Pre-fight checks and setup

---

## 10. Materials and Tools Organization (25 minutes)

### Required Materials List

#### Mechanical Hardware
- **Shoulder Screws:** 5/16" diameter, various lengths, 1/4"-20 thread
- **Grub Screws:** M4 × 0.7mm, 4mm long (wheel attachment)
- **Motor Mount Screws:** M4 × 0.70mm, 20mm button head
- **Lock Nuts:** 1/4"-20 nylon insert type
- **Thread Locker:** Medium strength (blue) Loctite

#### Electronic Components
- **Combat ESCs:** 
  - **Option 1:** Repeat Robotics Budget Brushed Dual ESC (2-4S)
  - **Option 2:** Weka 20A v2.2 Dual ESC (Just Cuz Robotics)
- **Gear Motors:** Appropriate for 1lb class
- **LiPo Battery:** High discharge rate, appropriate capacity
- **Radio System:** 2.4GHz with failsafe
- **XT30 Connectors:** High-current battery connections
- **Safety Links:** Removable weapon safety disconnects

#### Tools and Equipment
- **Hex Keys:** 2mm, 2.5mm, 4mm (5/32"), 1.5mm
- **Precision Scale:** 0.1g accuracy for weight verification
- **Soldering Station:** For connector assembly
- **LiPo Charger:** Balance charger with safety features
- **Test Blocks:** Elevate robot for safe testing
- **Multimeter:** Electrical testing and troubleshooting

### Procurement Strategy
- **Combat Robotics Specialists:** itgresa.com (ESCs, motors, general combat parts)
- **Advanced ESCs:** justcuzrobotics.com (Weka and high-end controllers)
- **Electronics:** Amazon (batteries, chargers, controllers, general electronics)
- **Mechanical Hardware:** McMaster-Carr (fasteners, structural components)
- **Lead Times:** Combat robotics parts may have longer lead times
- **Budget Planning:** Total electronics package ~$130-180 depending on options

### Current Pricing (Updated June 2025)
**Budget Build Option:**
- **ESC:** Repeat Robotics Dual ESC - $19.99 (itgresa.com)
- **Motors:** Repeat Drive Brushed (pricing varies by configuration)
- **Microcontroller:** Xiao ESP32C3 - $10-17
- **Battery:** OVONIC 3S LiPo 450mAh - $20-25 for 4-pack
- **Charger:** ISDT PD60 Balance Charger - $19.99
- **Kill Switch:** Lynx Anti-Spark Switch - Available from multiple vendors
- **Controller:** Xbox Standard Controller - $60

**Performance Build Option:**
- **ESC:** WEKA 20A v2.2 Dual ESC - $40+ (justcuzrobotics.com)
- **Motors:** DartBox V2 or similar high-performance options
- **Other components:** Same as budget build

**Key Supplier Update:**
- **itgresa.com:** Confirmed source for Repeat Robotics ESC ($19.99), Lynx Switch, WEKA ESCs
- **justcuzrobotics.com:** WEKA ESCs, DartBox motors, advanced combat electronics
- **Amazon/Suppliers:** OVONIC 3S 450mAh 4-packs ($20-25), ISDT PD60 charger ($19.99)

---

## 11. Build Session Planning and Next Steps (10 minutes)

### Session Organization
- **Team Formation:** Pair experienced with newcomer builders
- **Work Stations:** Organized tool and component distribution
- **Progress Milestones:** Realistic completion goals
- **Safety Officer:** Designated oversight for all operations
- **Documentation:** Build notes and lessons learned

### Follow-Up Activities
- **Testing Sessions:** Progressive capability validation
- **Competition Preparation:** Practice driving and strategy
- **Field Repair Training:** Between-match maintenance skills
- **Design Iteration:** Improvements based on testing

### Competition Timeline
- **Technical Inspection:** Pre-competition safety and rules check
- **FUBAR Labs Events:** Local "Mechanical Mayhem" competitions
- **Regional Events:** Broader combat robotics community
- **Skill Development:** Advanced building and strategy workshops

---

## Questions and Discussion (10 minutes)

### Technical Q&A
- Component selection and sourcing questions
- Assembly sequence and integration challenges
- Testing procedures and safety protocols
- Competition rules and preparation

### Action Items
- Material procurement assignments
- Build session scheduling and venue setup
- Tool inventory and organization
- Competition registration and timeline

---

**Total Estimated Time:** 2 hours 45 minutes

**Critical Reminders:**
- Always use test blocks when powering up - never let robot run off table
- Remove safety links before any weapon work
- Charge batteries in fire-safe location with LiPo bags
- Progressive testing - start slow, verify each system

**Competition Context:** Preparing for FUBAR Labs "Mechanical Mayhem" antweight events

**Contact:** [Meeting organizer contact information]