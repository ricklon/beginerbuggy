# Beginner Buggy Assembly Instructions

## Required Hardware

### Shoulder Bolts
- 2× Alloy Steel Shoulder Screw
  - 5/16" Shoulder Diameter
  - 3/4" Shoulder Length
  - 1/4"-20 Thread
  - $1.75 each

- 2× Alloy Steel Shoulder Screw
  - 5/16" Shoulder Diameter
  - 1" Shoulder Length
  - 1/4"-20 Thread
  - $1.79 each

### Screws and Fasteners
- 4× Alloy Steel Cup-Point Set Screw (Grub Screw)
  - M4 × 0.7mm Thread
  - 4mm Long
  - Sold in pack of 100
  - $5.33/pack

- 4× Button Head Hex Drive Screw (Motor Mount)
  - Black-Oxide Alloy Steel
  - M4 × 0.70mm Thread
  - 20mm Long
  - Sold in pack of 100
  - $14.37/pack

- Black-Oxide Alloy Steel Hex Drive Flat Head Screw (Threading Screw)
  - 90° Countersink Angle
  - M2 × 0.40mm Thread
  - 5mm Long
  - Sold in pack of 25
  - $8.51/pack

### Nuts
- High-Strength Steel Nylon-Insert Locknut
  - Black-Oxide
  - 1/4"-20 Thread Size
  - Sold in pack of 20
  - $5.44/pack

## Required Tools

### Hand Tools
- Hex Keys/Allen Wrenches:
  - 5/32" or 4mm (for shoulder bolts)
  - 2mm (for M4 grub screws)
  - 2.5mm (for M4 button head screws)
  - 1.5mm (for M2 flat head screw)
- 7/16" wrench (for 1/4"-20 lock nuts)
- Needle or very small flathead screwdriver (for connector work)

### Other Tools
- Light source (for detailed work)
- Soldering iron and supplies
- Loctite thread locker

## Mechanical Assembly

### 1. Wheel Assembly
- Install cores into wheels
- Pre-thread using the threading screw to ensure proper alignment
- Install grub screws into wheel-to-core connectors

### 2. Motor Installation
- Attach drive motors using grub screws
  - Place first grub screw on the flat section
  - Place second grub screw opposite to the first
- Mount dead shaft wheels
  - Secure using grub screws as wheel locks

## Electronics Assembly

### 1. Motor Controller Wiring
- Right Motor:
  - Red wire to positive (+)
  - Black wire to remaining terminal
- Left Motor:
  - Black wire to positive (+)
  - Red wire to remaining terminal

### 2. Xiao Board Setup
- Install 7-pin right-angle headers on power side
- Connect to: power, ground, power, D9, D10

### 3. Connector Modification
- Reshell connectors to 5-pin configuration
- Pin order: power, ground, [skip], white, yellow
- Note: Requires needle or tiny flathead screwdriver and good lighting

### 4. Kill Switch Installation
- Install switch in power circuit (high or low side)
- Solder XT30 connectors to both ends

## Final Assembly

### 1. Power System Connection
- Connect battery to kill switch
- Connect kill switch to motor controller
- Connect motor controller to motors

### 2. Securing Components
- Mount all components using 3M Dual Lock hook and loop tape
- Apply Loctite to all threaded connections once satisfied with assembly

## Important Notes
- Double-check all electrical connections before powering on
- Ensure all mechanical connections are secure
- Test all functions before applying Loctite

## Safety Warnings
- Always disconnect battery before making any modifications
- Ensure proper polarity on all electrical connections
- Use appropriate safety equipment when soldering
- Keep Loctite away from electrical components
