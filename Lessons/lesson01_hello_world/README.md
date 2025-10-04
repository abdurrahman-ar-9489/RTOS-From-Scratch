🧭 Lesson 01 — Hello World of Embedded Systems 💡

Goal: Blink an LED on the EK-TM4C123GXL board using bare-metal C.

⚡ Concept Overview

Before diving into RTOS, let’s begin with the simplest embedded exercise — LED blinking.
This introduces the essential concepts of register-level programming, clock gating, and GPIO control.

🧩 Key idea:
Everything inside a microcontroller is a peripheral — and peripherals only work when clocked and configured properly.

🧠 Step-by-Step Implementation

🔹 Step 1: Enable the Clock for GPIO Port F

By default, no peripheral receives a clock.
To enable it, we must set the corresponding bit in the Run Mode Clock Gating Control Register (RCGCGPIO).

// Base address: 0x400FE000 + 0x608 = 0x400FE608
uint32_t *RCGCGPIO = (uint32_t *)0x400FE608U;
*RCGCGPIO = 0x20U;  // Enable clock for GPIO Port F

💡 This is known as “Clock Gating” — saving power by providing clocks only to required modules.

🔹 Step 2: Enable Digital Functionality for GPIO Pins

GPIO pins default to a tristate (Hi-Z) mode.
We use the GPIODEN register to enable them as digital pins.

// Base address: 0x40025000 + 0x51C = 0x4002551C
uint32_t *GPIODEN = (uint32_t *)0x4002551CU;
*GPIODEN = 0x0EU;   // Enable PF1–PF3 (LED pins)

🔹 Step 3: Configure the Pins as Output

The GPIODIR register determines whether each pin acts as input (0) or output (1).

// Base address: 0x40025000 + 0x400 = 0x40025400
uint32_t *GPIODIR = (uint32_t *)0x40025400U;
*GPIODIR = 0x0EU;   // Set PF1–PF3 as outputs

🔹 Step 4: Write Data to the LEDs

Finally, use GPIODATA to drive the pins high or low.

// Base address: 0x40025000 + 0x3FC = 0x400253FC
uint32_t *GPIODATA = (uint32_t *)0x400253FCU;

// Turn ON Red LED (PF1)
*GPIODATA = 0x02U;

// Turn OFF all LEDs
*GPIODATA = 0x00U;
