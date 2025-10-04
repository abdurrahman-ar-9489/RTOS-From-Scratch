<p align="center">
  <img src="/Images/TivaCLaunchPad.png" width="800" alt="Tiva C LaunchPad Board">
</p>

# 🚀 RTOS from Scratch

Welcome to **RTOS-from-Scratch** — a hands-on journey into embedded systems and real-time operating systems!  

This repository is my **step-by-step implementation of Miro Samek’s Modern Embedded Systems Programming course**, where I explore the inner workings of ARM Cortex-M microcontrollers and build a minimal RTOS from the ground up.

## 🔥 Why This Repo?

- 🟢 Learn **how to access GPIO**: control LEDs, read buttons, and interface with hardware pins.  
- 💡 Learn **how embedded systems boot**: from reset vectors to startup code.  
- ⚡ Explore **interrupts, race conditions, and superloop architectures**.  
- 🛠 Understand **why RTOS exists** and how scheduling, context switching, and multitasking work.  
- 📚 Follow my journey: **code + diagrams + reflections** for each lesson.

## 📂 Repository Structure
```
lessons/
├── lesson01_hello_world/ # Blink LEDs, first embedded program
├── lesson02_startup_code/ # Startup sequence, linker script, and main()
├── lesson03_interrupts/ # NVIC, ISRs, and priorities
├── lesson04_race_conditions/ # Shared variables, critical sections
├── lesson05_superloop/ # Cooperative multitasking and limitations
├── lesson06_rtos_intro/ # Round-robin scheduling, SysTick
├── lesson07_rtos_advanced/ # Preemption, tasks, queues, semaphores
include/ # Shared headers
docs/ # Datasheets, MCU user guides, and other notes

```
## 🛠️ Tools & Environment

- 💻 **IDE:** Keil MicroVision  
- 🏗 **Board:** EK-TM4C123GXL  
- 📊 **Logic Analyzer:** USB Logic Analyzer 24MHz, 8 channel
- 🛠 **Logic Analyzer Application:** Logic

## 💡 Learning Path

- **Lesson 1:** 👋 Hello World of Embedded Systems — LED toggle  
- **Lesson 2:** ⚙ Startup Code — Boot sequence & linker scripts  
- **Lesson 3:** 🛎 Interrupts — NVIC, ISR mechanics, priorities  
- **Lesson 4:** ⚠ Race Conditions — Shared variables, critical sections  
- **Lesson 5:** 🔄 Superloop Architecture - Foreground and Background Architecture  
- **Lesson 6:** ⏱ RTOS Basics — Round-robin scheduling, SysTick  
- **Lesson 7:** 🏁 Advanced RTOS — Preemption, tasks, queues, semaphores

## 🔗 LinkedIn Blog / Learning Journey

I’m sharing reflections, insights, and diagrams on **LinkedIn**:  
👉 [Follow my Embedded Systems journey](https://www.linkedin.com/in/abdur-rahman-ar1411/)  

💡 **Tip:** Each lesson folder contains code, a brief README, and optional diagrams/notes to help you follow along.
