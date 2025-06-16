# Beginner Combat Buggy Assembly Guide
## Step-by-Step Instructions

---

## Pre-Assembly Preparation

### Procurement Information
**Specialized Combat Robotics Parts:**
- **itgresa.com:** Repeat Robotics ESC ($15), Repeat Motors Mk 4mm ($20), combat-specific parts
- **justcuzrobotics.com:** Weka 20A v2.2 ESC ($40), advanced combat electronics
- **Amazon:** OVONIC batteries ($20), ISDT charger ($15), Xbox controller ($60)
- **McMaster-Carr:** Fasteners, mechanical hardware

**Budget Planning:** Total cost approximately $130-180 depending on component choices

### Parts Inventory Check
**Verify you have all components before starting:**

**Shoulder Bolts:**
- [ ] 2× 5/16" × 3/4" shoulder screws (1/4"-20 thread)
- [ ] 1/4"-20 nylon-insert lock nuts

**Fasteners:**
- [ ] 8× M4 × 0.7mm × 8mm grub screws (cup point) - *Updated quantity and length*
- [ ] M2 × 6mm screws for motor mounting
- [ ] M2 × 0.40mm × 5mm flat head threading screws
- [ ] 4× M4 × 0.70mm × 20mm button head screws

**Electronics:**
- [ ] Repeat Drive Brushed motors or compatible brushed gear motors
- [ ] Combat ESC: Repeat Robotics Dual ($19.99) or WEKA 20A v2.2 ($40+)
- [ ] Xiao ESP32C3 ($10) or ESP32S3 ($17) microcontroller
- [ ] OVONIC 3S LiPo 450mAh batteries - 4-pack ($20-25)
- [ ] ISDT PD60 Balance Charger - $19.99
- [ ] Lynx Anti-Spark Switch (pricing varies by vendor)
- [ ] Xbox Standard Controller - $60
- [ ] XT30 connectors and wiring
- [ ] 3M Dual Lock tape

### Tool Setup
**Organize your workspace with:**
- [ ] Hex keys: 5/32" (4mm), 2.5mm, 2mm, 1.5mm, plus appropriate size for M2×5 screws
- [ ] 7/16" wrench
- [ ] Needle or micro flathead screwdriver
- [ ] Soldering iron and supplies
- [ ] Good lighting/work lamp
- [ ] Loctite thread locker (KEEP SEALED until final assembly)

---

## Stage 1: Wheel Preparation

### Step 1: Install Wheel Cores
1. **Insert cores into wheels**
   - Press cores firmly into wheel hubs
   - Ensure cores are fully seated and flush
   - Check that core orientation matches wheel design

2. **Pre-thread wheel connections**
   - Use M4 threading screw to cut clean threads
   - Thread screw in completely, then back out
   - **Purpose:** Ensures grub screws will thread smoothly
   - Clean out any plastic debris

### Step 2: Prepare Grub Screw Connections
1. **Test fit grub screws**
   - Thread M4 × 8mm grub screws into connections (8 total available)
   - Should thread smoothly after pre-threading
   - **Note:** 8 grub screws provided for wheel attachment and other securing points
   - Back out screws but keep them organized by intended location

**✓ Stage 1 Check:** All wheels have cores installed, connections are pre-threaded

---

## Stage 2: Drive Motor Installation

### Step 3: Mount Drive Motors to Chassis
1. **Position drive motors**
   - Align motors with chassis mounting holes
   - Ensure motor shafts are parallel and level
   - Check clearance for wheel installation

2. **Install motor mounting screws**
   - Use M2 × 5mm screws for motor mounting
   - **Do NOT apply Loctite yet** - this is temporary mounting
   - Tighten to snug fit, allow for adjustment

### Step 4: Attach Wheels to Motors
1. **Install drive wheels (motor-powered wheels)**
   - Slide wheel onto motor shaft
   - Locate flat section on motor shaft
   - Position first grub screw against flat section
   - **Tighten first grub screw firmly**

2. **Install second grub screw**
   - Position 180° opposite from first grub screw
   - This prevents wheel from spinning on shaft
   - **Tighten second grub screw**

3. **Install dead shaft wheels (non-powered)**
   - Mount remaining wheels to chassis
   - Use grub screws as wheel locks/axle retention
   - Ensure wheels spin freely

**✓ Stage 2 Check:** 
- All wheels installed and secure
- Drive wheels don't slip on motor shafts
- Dead shaft wheels spin freely
- Motors are securely mounted

---

## Stage 3: Electronics Preparation

### Step 5: Motor Controller Wiring




### Step 6: ESP32 Microcontroller Setup
1. **Install headers on Xiao ESP32C3 or ESP32S3**
   - Solder headers as needed for connections
   - Ensure pins are straight and properly aligned
   - Test fit with intended connections

2. **Programming preparation:**
   - Set up Arduino IDE with ESP32 board support
   - Verify board can be programmed before final installation

### Control System Setup
1. **Xbox Controller Configuration:**
   - Pair Xbox Standard Controller with ESP32 microcontroller
   - Configure wireless connection and button mapping
   - Test controller response and range
   - Set up emergency stop functions

2. **Programming the control system:**
   - Upload control software to ESP32
   - Configure drive mixing (tank steering or arcade style)
   - Set up weapon control (if applicable)
   - Test failsafe behavior

**✓ Stage 3 Check:**
- Motor wiring completed with correct polarity
- Headers installed and soldered cleanly
- Connectors properly modified and tested

---

## Stage 4: Power System Integration

### Step 8: Lynx Kill Switch Installation
1. **Choose switch placement**
   - Position Lynx kill switch for easy access during operation
   - Consider high-side switching for safety
   - Plan wire routing to avoid mechanical interference

2. **Solder XT30 connectors**
   - **Battery side:** Connect to OVONIC 3S LiPo 450mAh battery
   - **Robot side:** Female XT30 connector to robot power system
   - Use proper polarity (red = positive, black = negative)
   - **Test continuity** before final installation

### Battery System Setup
1. **OVONIC 3S LiPo 450mAh Battery (4-pack recommended):**
   - **Specifications:** 11.1V, 80C discharge rate, XT30 connector
   - **Weight:** 35g per battery, perfect for 1lb weight budget
   - **Pricing:** $20-25 for 4-pack (better value than 2-pack)
   - Verify cell voltages before first use (should be ~3.7-3.85V per cell)
   - Use ISDT PD60 charger for all charging operations
   - Always charge in fire-safe location with LiPo bag
   - Monitor charging - never leave unattended

2. **ISDT PD60 Charger ($19.99):**
   - **Specifications:** 60W, 6A max, 1-4S LiPo capable
   - **Input:** USB-C (5-20V), works with power banks or wall adapters
   - **Features:** Balance charging, upgradeable firmware, silent cooling
   - Balance charge at 1A rate (450mA) for 450mAh batteries
   - Storage charge to 3.8V per cell for long-term storage
   - Check for damage before each use

### Step 9: Power System Connections
1. **Connect battery to kill switch**
   - Verify polarity before connection
   - Ensure secure, tight connection
   - Test switch operation (ON/OFF)

2. **Connect kill switch to motor controller**
   - Route power through kill switch
   - Verify voltage at motor controller with switch ON
   - Confirm zero voltage with switch OFF

3. **Connect motor controller to motors**
   - Use prepared motor wiring from Stage 3
   - **Double-check polarity** before powering up
   - Secure all connections

**✓ Stage 4 Check:**
- Kill switch operates correctly
- All power connections secure and correct polarity
- System ready for initial testing

---

## Stage 5: System Integration and Testing

### Step 10: Component Mounting
1. **Mount components with 3M Dual Lock**
   - Clean mounting surfaces with alcohol
   - Apply Dual Lock to chassis and components
   - Position components for easy access and protection
   - **Press firmly** to ensure good adhesion

2. **Secure wire routing**
   - Keep wires away from wheels and moving parts
   - Use additional Dual Lock or cable ties
   - Ensure no pinch points or stress on connections

### Step 11: Initial System Testing
**⚠️ SAFETY FIRST - ALWAYS TEST ON BLOCKS**

1. **Pre-power checklist:**
   - [ ] Kill switch in OFF position
   - [ ] All connections secure
   - [ ] Robot elevated on blocks (wheels can't touch ground)
   - [ ] Clear workspace around robot

2. **Power-up sequence:**
   - Connect battery
   - Turn kill switch to ON
   - **Immediately verify no unexpected movement**
   - Check for proper voltage at all components

3. **Motor function test:**
   - Test each motor individually
   - Verify correct rotation direction
   - Check that wheels don't slip on shafts
   - **Turn OFF immediately after testing**

**✓ Stage 5 Check:**
- All components securely mounted
- Initial testing successful with no issues
- Robot ready for final assembly

---

## Stage 6: Final Assembly and Locking

### Step 12: Final Testing and Adjustment
1. **Complete operational test:**
   - **Robot still on blocks** - wheels off ground
   - Test all motor functions
   - Verify kill switch emergency stop
   - Check for any loose connections or components

2. **Make final adjustments:**
   - Tighten any loose mechanical connections
   - Adjust component positions if needed
   - Verify all systems operate as expected

### Step 13: Apply Thread Locker (FINAL STEP)
**⚠️ PERMANENT - Only do this when completely satisfied with assembly**

1. **Disassemble critical connections:**
   - Remove motor mounting screws one at a time
   - Apply small drop of Loctite to threads
   - Reinstall and tighten to proper torque

2. **Apply to all threaded connections:**
   - Motor mount screws
   - Grub screws (if accessible)
   - Any chassis fasteners
   - **Do NOT over-apply** - small amount is sufficient

3. **Final cure time:**
   - Allow 24 hours for full cure
   - Avoid disassembly during cure period

**✓ Final Check:**
- All threaded connections have thread locker
- Robot tested and operational
- Assembly documentation complete

---

## Final Safety Verification

### Pre-Operation Checklist
Before each use, verify:
- [ ] Battery fully charged and properly connected
- [ ] Kill switch operates correctly
- [ ] All mechanical connections tight
- [ ] No loose wires or components
- [ ] Wheels secure on shafts
- [ ] Clear operating area

### Emergency Procedures
- **Immediate shutdown:** Kill switch to OFF position
- **Runaway robot:** Kill switch first, then disconnect battery
- **Electrical issues:** Disconnect battery, do not attempt field repairs
- **Mechanical damage:** Stop operation, assess damage before continuing

---

## Troubleshooting Guide

### Motor Not Running
1. Check kill switch position
2. Verify battery voltage
3. Check motor controller connections
4. Test motor resistance (should be low, not infinite)

### Motor Running Wrong Direction
1. Swap motor wires at controller
2. Check control signal polarity
3. Verify controller programming

### Wheel Slipping on Motor Shaft
1. Check grub screw tightness
2. Verify flat section alignment
3. Clean motor shaft if oily

### Intermittent Operation
1. Check all wire connections
2. Verify battery connections
3. Test kill switch continuity
4. Check for loose Dual Lock mounting

---

## Maintenance Schedule

### After Each Use
- Check for loose screws or components
- Verify battery connections
- Clean debris from wheels and chassis

### Weekly (Heavy Use)
- Test kill switch operation
- Check motor mounting tightness
- Verify all electrical connections

### Monthly
- Deep clean chassis and components
- Check thread locker integrity
- Lubricate moving parts if needed

---

**Assembly Complete!**  
**Your combat robot is ready for testing and competition.**

**Remember:** Always operate on blocks for initial testing, never let the robot run off a table or work surface.