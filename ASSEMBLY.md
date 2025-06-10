# Beginner Combat Buggy Assembly Guide
## Step-by-Step Instructions

---

## Pre-Assembly Preparation

### Parts Inventory Check
**Verify you have all components before starting:**

**Shoulder Bolts:**
- [ ] 2× 5/16" × 3/4" shoulder screws (1/4"-20 thread)
- [ ] 2× 5/16" × 1" shoulder screws (1/4"-20 thread)

**Fasteners:**
- [ ] 4× M4 × 0.7mm × 4mm grub screws (cup point)
- [ ] 4× M4 × 0.70mm × 20mm button head screws
- [ ] M2 × 0.40mm × 5mm flat head threading screws
- [ ] 1/4"-20 nylon-insert lock nuts

**Electronics:**
- [ ] Drive motors (2×)
- [ ] Wheels with cores (4×)
- [ ] Motor controller/ESC
- [ ] Xiao microcontroller board
- [ ] Kill switch
- [ ] XT30 connectors
- [ ] Battery pack
- [ ] 3M Dual Lock tape

### Tool Setup
**Organize your workspace with:**
- [ ] Hex keys: 5/32" (4mm), 2.5mm, 2mm, 1.5mm
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
   - Use M2 threading screw to cut clean threads
   - Thread screw in completely, then back out
   - **Purpose:** Ensures grub screws will thread smoothly
   - Clean out any plastic debris

### Step 2: Prepare Grub Screw Connections
1. **Test fit grub screws**
   - Thread each M4 grub screw into wheel-to-core connection
   - Should thread smoothly after pre-threading
   - Back out screws but keep them with their respective wheels

**✓ Stage 1 Check:** All wheels have cores installed, connections are pre-threaded

---

## Stage 2: Drive Motor Installation

### Step 3: Mount Drive Motors to Chassis
1. **Position drive motors**
   - Align motors with chassis mounting holes
   - Ensure motor shafts are parallel and level
   - Check clearance for wheel installation

2. **Install motor mounting screws**
   - Use 4× M4 × 20mm button head screws
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
**⚠️ CRITICAL - Motor Polarity Setup:**

1. **Right Motor Wiring:**
   - **Red wire** → Positive (+) terminal
   - **Black wire** → Remaining terminal

2. **Left Motor Wiring:**
   - **Black wire** → Positive (+) terminal  
   - **Red wire** → Remaining terminal

3. **Wire routing:**
   - Keep motor wires away from wheels
   - Use cable ties or tape to secure
   - Leave enough length for component placement

### Step 6: Xiao Board Header Installation
1. **Install 7-pin right-angle headers**
   - Solder headers to power side of board
   - Ensure pins are straight and properly aligned
   - Test fit with intended connections

2. **Pin assignment verification:**
   - Power, Ground, Power, D9, D10
   - Double-check pin mapping with board documentation

### Step 7: Connector Modification
1. **Reshell connectors to 5-pin configuration**
   - **Pin order:** Power, Ground, [skip], White, Yellow
   - Use needle or micro flathead screwdriver
   - **Work under good lighting** - pins are small
   - Verify connections are secure

**✓ Stage 3 Check:**
- Motor wiring completed with correct polarity
- Headers installed and soldered cleanly
- Connectors properly modified and tested

---

## Stage 4: Power System Integration

### Step 8: Kill Switch Installation
1. **Choose switch placement**
   - Position for easy access during operation
   - Consider high-side or low-side switching
   - Plan wire routing to avoid mechanical interference

2. **Solder XT30 connectors**
   - **Battery side:** Male XT30 connector
   - **Robot side:** Female XT30 connector
   - Use proper polarity (red = positive, black = negative)
   - **Test continuity** before final installation

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
