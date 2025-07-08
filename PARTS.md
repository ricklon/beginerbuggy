# Combat Buggy Parts List and Bill of Materials

## Build Options Overview

| Component Category | Budget Build | Performance Build |
|-------------------|--------------|-------------------|
| **Total Cost** | $130-150 | $170-190 |
| **ESC** | Repeat Robotics Dual ($19.99) | Weka 20A v2.2 ($40+) |
| **Motors** | Repeat Motors Mk 4mm ($20) | Repeat Motors Mk 4mm ($20) |
| **Other Components** | Same | Same |

---

## Electronic Components

### Motor Speed Controllers (ESCs)

#### Option 1: Budget Build - Repeat Robotics Dual ESC
- **Part:** Repeat Robotics Budget Brushed Dual ESC (2-4S)
- **Price:** $19.99
- **Supplier:** itgresa.com
- **Features:** Dual channel brushed ESC, 2-4S LiPo compatible
- **Weight:** TBD
- **Quantity:** 1

#### Option 2: Performance Build - Weka 20A v2.2 Dual ESC
- **Part:** Weka 20A v2.2 Dual ESC
- **Price:** $40+
- **Supplier:** justcuzrobotics.com, also available through itgresa.com
- **Features:** 20A per channel, 3g weight without wires, overcurrent/undervoltage protection, mixing enabled
- **Weight:** 3g (without wires)
- **Quantity:** 1

### Drive Motors

- **Part:** Repeat Motors Mk 4mm
- **Price:** $20 for 2 motors
- **Supplier:** itgresa.com
- **Specifications:** Brushed gear motors, 4mm shaft with grub screw attachment, 3S LiPo compatible
- **Quantity:** 2

### Power System

#### Battery
- **Part:** OVONIC 3S LiPo 450mAh
- **Specifications:** 11.1V, 80C discharge rate, XT30 connector, 35g weight
- **Price:** $20-25 for 4-pack (recommended for competition rotation)
- **Supplier:** Amazon
- **Quantity:** 4-pack recommended (minimum 2)

#### Battery Charger
- **Part:** ISDT PD60 Balance Charger
- **Price:** $19.99
- **Specifications:** 60W, 6A max, 1-4S LiPo capable, USB-C input (5-20V)
- **Features:** Balance charging, upgradeable firmware, silent cooling
- **Supplier:** Amazon
- **Quantity:** 1

#### Kill Switch
- **Part:** Lynx Anti-Spark Kill Switch
- **Price:** Varies by vendor
- **Specifications:** High-current anti-spark design for combat robotics
- **Supplier:** itgresa.com, justcuzrobotics.com, various combat robotics vendors
- **Quantity:** 1

### Control System

#### Microcontroller - Budget Option
- **Part:** Xiao ESP32C3
- **Price:** $10
- **Features:** WiFi capability, compact form factor, Arduino IDE compatible
- **Quantity:** 1

#### Microcontroller - Advanced Option
- **Part:** Xiao ESP32S3
- **Price:** $17
- **Features:** Enhanced features over ESP32C3, WiFi capability
- **Quantity:** 1

#### Controller
- **Part:** Xbox Standard Controller
- **Price:** $60
- **Features:** Wireless connection to microcontroller, familiar ergonomics, reliable operation
- **Supplier:** Amazon, electronics retailers
- **Quantity:** 1

### Electrical Components

#### Power Connectors
- **Part:** XT30 Connectors (Male and Female)
- **Specifications:** High-current battery connections, male for battery side, female for robot side
- **Supplier:** Amazon, electronics suppliers
- **Quantity:** 2-4 pairs (spares recommended)

#### Wiring
- **Power Wires:** 16-18 AWG for main power and motor connections
- **Signal Wires:** 22-24 AWG for control signals
- **Heat Shrink Tubing:** Various sizes (2mm, 4mm, 6mm)
- **Solder:** 60/40 rosin core, 0.6-0.8mm diameter
- **Supplier:** Amazon, electronics suppliers

---

## Mechanical Components

### Fasteners

#### Torx Screws (NEW)
- **Part:** M3 × 12mm Torx Flat Head Thread-Forming Screws
- **Drive Size:** T8
- **Application:** Chassis mounting, plastic component attachment
- **Features:** 90° countersink, thread-forming for plastic
- **Supplier:** McMaster-Carr
- **Quantity:** TBD

- **Part:** M2 × 0.4mm × 6mm Torx Flat Head Screws
- **Drive Size:** T6
- **Material:** Zinc-plated steel
- **Application:** Motor mounting, electronics mounting
- **Supplier:** McMaster-Carr
- **Quantity:** TBD

#### Standard Fasteners
- **Part:** M4 × 0.7mm × 8mm Grub Screws (cup point)
- **Application:** Wheel attachment and securing points
- **Supplier:** McMaster-Carr
- **Quantity:** 8

- **Part:** M2 × 0.40mm × 5mm Flat Head Threading Screws
- **Application:** Various chassis connections
- **Supplier:** McMaster-Carr
- **Quantity:** TBD

- **Part:** M4 × 0.70mm × 20mm Button Head Screws
- **Application:** Motor mounting, structural connections
- **Supplier:** McMaster-Carr
- **Quantity:** 4

#### Shoulder Bolts
- **Part:** 5/16" × 7/8" or 1" Shoulder Screws (1/4"-20 thread)
- **Application:** Pivot points, structural connections
- **Supplier:** McMaster-Carr
- **Quantity:** 2

- **Part:** 1/4"-20 Nylon-Insert Lock Nuts
- **Application:** Securing shoulder screws
- **Supplier:** McMaster-Carr
- **Quantity:** 2

### Assembly Materials

#### Thread Locker
- **Part:** Loctite Medium Strength (Blue) Thread Locker
- **Application:** All critical threaded connections
- **Note:** Apply only during final assembly
- **Supplier:** Hardware stores, Amazon
- **Quantity:** 1 small bottle

#### Component Mounting
- **Part:** 3M Dual Lock Tape
- **Application:** Securing components without permanent attachment
- **Features:** Strong, removable mounting system
- **Supplier:** Amazon, industrial suppliers
- **Quantity:** 1 roll

### Mechanical Hardware

#### Chassis
- **Material:** Lightweight aluminum or titanium frame
- **Source:** Custom fabrication or 3D printing from provided CAD files
- **Files:** Available in `cad/` directory
- **Weight:** Optimized for 1lb weight budget

#### Wheels
- **Part:** Foam wheels with hex cores
- **Files:** CAD files available for 3D printing cores
- **Application:** Drive and support wheels
- **Quantity:** 4 (typically)

---

## Tools Required

### Hand Tools

#### Torx Keys (UPDATED)
- **T6 Torx L-Key:** 1-1/4" overall length (for M2 screws)
- **T8 Torx L-Key:** 1-3/4" overall length (for M3 screws)
- **Quality:** Professional grade recommended (Wera, Wiha, Bondhus)
- **Supplier:** McMaster-Carr, Amazon, tool suppliers

#### Hex Keys
- **Sizes:** 5/32" (4mm), 2.5mm, 2mm, 1.5mm
- **Additional:** Appropriate size for M2×5 screws
- **Quality:** Good quality L-keys or ball-end sets
- **Supplier:** Hardware stores, Amazon

#### Other Hand Tools
- **7/16" Wrench:** For lock nuts
- **Needle or Micro Flathead Screwdriver:** Fine adjustment work
- **Wire Strippers:** For 16-24 AWG wire
- **Precision Scale:** 0.1g accuracy for weight verification

### Electrical Tools

#### Soldering Equipment
- **Soldering Iron:** 25-40W with fine tip, temperature controlled preferred
- **Solder:** 60/40 rosin core, 0.6-0.8mm diameter
- **Flux:** Additional rosin flux for clean joints
- **Heat Gun or Hair Dryer:** For heat shrink tubing
- **Multimeter:** For continuity testing and voltage measurement

#### Testing Equipment
- **Test Blocks:** Elevate robot for safe wheel testing during assembly
- **LiPo Battery Tester:** Verify cell voltages
- **Work Light:** Good lighting for precise work (minimum 500 lux)

### Safety Equipment
- **Safety Glasses:** Required during soldering and assembly
- **Sand Bucket:** For smothering LiPo fires during motor/robot testing
- **Fire Extinguisher:** Electrical fire rated for general electrical safety
- **LiPo Charging Bag:** Fire-safe charging container
- **Well-Ventilated Area:** Or fume extractor for soldering

---

## Suppliers and Procurement

### Primary Suppliers

- **itgresa.com:** Repeat Robotics ESC ($19.99), Repeat Motors ($20), Lynx Kill Switch, Weka ESCs
- **justcuzrobotics.com:** Weka 20A v2.2 ESC ($40+), advanced combat electronics
- **Amazon:** OVONIC batteries ($20-25), ISDT charger ($19.99), Xbox controllers ($60), XT30 connectors
- **McMaster-Carr:** All fasteners, precision hardware, thread locker, professional tools

### Lead Times
- **Combat Robotics Parts:** May have longer lead times, order early
- **Standard Electronics:** Usually 1-3 days from Amazon
- **Precision Fasteners:** McMaster-Carr typically next-day delivery

### Budget Planning
- **Budget Build:** $130-150 | **Performance Build:** $170-190 | **Tools:** $50-100 (one-time)

---

## Weight Budget Analysis

| Component Category | Typical Weight | Notes |
|-------------------|----------------|--------|
| **Electronics** | 120-150g | ESC, motors, battery, microcontroller |
| **Chassis** | 150-200g | Aluminum/titanium frame |
| **Fasteners** | 20-30g | All screws, bolts, hardware |
| **Wheels** | 40-60g | Foam wheels with cores |
| **Miscellaneous** | 30-50g | Wiring, mounting materials |
| **Total Target** | ~450g | 4g margin for 454g limit |

### Weight Optimization Tips
- **Minimize wire length** - every inch adds weight
- **Use appropriate fastener sizes** - don't oversize
- **Choose lightweight chassis materials**
- **Remove excess material** where structurally safe

---

## Quality and Specification Notes

### Critical Specifications
- **XT30 Polarity:** Male connector on battery (larger terminal = positive)
- **Thread Pitch:** M2 × 0.4mm fine pitch for precision mounting
- **Battery Capacity:** 450mAh optimized for 1lb weight budget
- **ESC Current Rating:** Must handle motor stall current safely

### Quality Recommendations
- **Torx Tools:** Quality bits prevent stripping
- **Battery Safety:** Use balance charger, never leave charging unattended. Keep sand bucket nearby during testing - LiPo fires must be smothered, not extinguished with water
- **Fastener Quality:** Use proper grade fasteners from reputable suppliers
- **Competition Spares:** Carry extra XT30 connectors and fasteners

---

## Revision History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2025-07-08 | Initial consolidated parts list creation |
| | | Added specific Torx fastener specifications |
| | | Consolidated information from ASSEMBLY.md and AGENDA.md |
| | | Added detailed supplier information and pricing |

---

**Note:** This parts list consolidates information previously scattered across multiple documents. All builders should verify current pricing and availability before ordering, as costs and suppliers may change.
