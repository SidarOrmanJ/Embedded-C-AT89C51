# Embedded Systems Projects (AT89C51)

This repository contains my embedded systems projects developed using C programming and simulation via Proteus Design Suite. These projects demonstrate my ability to program microcontrollers, interface hardware components, and construct embedded applications.

## Projects Included

### 1. **Assignment 8 - Multi-Channel Thermometer**

- **File:** `Assignment_8_MultiChannel_Thermometer.c`
- **Description:** A multi-channel temperature monitoring system using the AT89C51 microcontroller with a 4051 MUX for channel selection and ADC0804 for analog-to-digital conversion. Displays sorted temperatures on a 16x2 LCD display.
- **Key Features:**
  - 4-channel temperature reading via MUX/ADC
  - Temperature conversion from ADC values
  - Sorted temperature display on LCD
  - Real-time monitoring with formatting

### 2. **Term Project - Scrolling Text LED Display**

- **File:** `TermProject_ScrollingText_LED.c`
- **Description:** An LED matrix scrolling text display system. Animates text with smooth character transitions across the display. Includes custom character lookup table and bit-shifting animation logic.
- **Key Features:**
  - Smooth character animation and transitions
  - Custom 8x8 character bitmap lookup table (62 characters)
  - Dynamic shift operations for scrolling effect
  - Real-time display refresh

### 3. **Thermometer - Simple ADC to LCD Temperature Display**

- **File:** `Thermometer_ADC_LCD.c`
- **Description:** A simple temperature reading and display system using ADC0804 for analog-to-digital conversion and a 16x2 LCD for display. Reads temperature sensor data and continuously updates the LCD.
- **Key Features:**
  - ADC0804 interfacing and reading
  - LCD control and data display
  - Real-time temperature conversion
  - Live LED status indicator

## Tools & Technologies Used

- **Microcontroller:** AT89C51 (8051 Architecture)
- **Language:** Embedded C (Keil C51)
- **Simulation:** Proteus Design Suite (VSM Studio)
- **Components:** LCD 16x2, ADC0804, 4051 MUX, Temperature Sensors
- **Peripherals:** Port I/O, SFR registers (P0-P3)

## C Programming Skills Demonstrated

✓ Low-level microcontroller programming  
✓ Hardware interfacing (LCD, ADC, MUX)  
✓ I/O port manipulation using SFR bits  
✓ Real-time data acquisition and conversion  
✓ Embedded systems algorithms (sorting, display formatting)  
✓ Proteus simulation and debugging

## Proteus Project Files

The original Proteus Design Suite simulation files (`.pdsprj`) contain the complete circuit schematics and simulations:

- `Assignmen_t8 (1).pdsprj` - Assignment 8 circuit
- `TermProject_Sidar_Orman (4).pdsprj` - Term Project circuit
- `thermomete+in+r+C.pdsprj` - Thermometer circuit

_All C source code has been extracted and is available in this repository for reference and compilation._
