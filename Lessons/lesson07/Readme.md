🧠 Lesson 7 — Building Our Own RTOS Architecture

After understanding startup code, linker scripts, and memory mapping, we've finally reached the point where everything comes together—building our own Real-Time Operating System (RTOS).

Before implementing scheduling algorithms, it's important to understand how the kernel itself is organized. Every RTOS, whether it's a minimal educational kernel or a production-grade operating system like FreeRTOS, Zephyr, or RTX, is built upon the same fundamental concepts.

In this lesson, we'll explore the architecture of our minimal RTOS and understand how its various components collaborate to enable multitasking on a Cortex-M microcontroller.

🏗 High-Level Architecture

At the highest level, the system consists of three layers.
```
+--------------------------------------+
|        Application Tasks             |
|  Task1  Task2  Task3 ... TaskN       |
+--------------------------------------+
                │
                ▼
+--------------------------------------+
|             RTOS Kernel              |
|  Scheduler                           |
|  Ready Set                           |
|  Task Control Blocks                 |
|  Kernel Services                     |
|  SysTick + PendSV                    |
+--------------------------------------+
                │
                ▼
+--------------------------------------+
|      Cortex-M Hardware               |
|  CPU • SysTick • NVIC                |
+--------------------------------------+
```
The Application Layer contains the user-created tasks.

The RTOS Kernel manages task scheduling, timing, context switching, and kernel services.

The Hardware Layer provides the processor features that make multitasking possible, particularly SysTick and PendSV.

🧩 Core Building Blocks

📋 Task Control Blocks (TCBs)

Every task created by the kernel is represented by a Task Control Block.

The TCB stores all runtime information required to resume a task.

Typical contents include:

 - Current stack pointer
 - Task state
 - Delay timeout
 - Scheduling information

During every context switch, the scheduler saves the current stack pointer into the task's TCB and restores the stack pointer of the next task.

Without the TCB, the kernel would have no way of remembering where each task stopped executing.

📚 Individual Task Stacks

Unlike a traditional bare-metal application that shares a single stack, every task owns its own independent stack.
```
Task A
──────────────
|            |
|  Stack A   |
|            |
──────────────

Task B
──────────────
|            |
|  Stack B   |
|            |
──────────────
```
Each stack contains:

 - Local variables
 - Function call frames
 - Saved CPU registers

Because stacks are isolated, tasks can execute independently without interfering with one another.

🎯 Ready Set

Instead of scanning every task continuously, our RTOS uses a Ready Set bitmap.
```
Task Index

3   2   1   0
───────────────
1   0   1   1
```

Each bit represents one application task.

Bit	Meaning
1	Task is ready to execute
0	Task is delayed or blocked

This allows the scheduler to determine runnable tasks with only a few CPU instructions.

Bitmaps are one of the reasons embedded RTOS kernels remain extremely efficient.

🧠 Scheduler

The Scheduler is the decision-making engine of the RTOS.

Whenever a scheduling event occurs, it determines which task should execute next.

Our RTOS supports two scheduling policies.

🔄 Round Robin Scheduling
⚡ Priority-Based Preemptive Scheduling

These two algorithms will be explored in the following lessons.

🛠 Kernel Services

The kernel exposes a small collection of APIs used by application tasks.

Examples include:

OS_init()
OS_run()
OS_delay()
OSThread_start()

These services provide a simple interface for creating threads, starting the scheduler, and delaying task execution.

⏱ SysTick Interrupt

The Cortex-M SysTick timer provides the periodic heartbeat of the RTOS.

Every tick interrupt performs several important operations.

SysTick Interrupt

↓

OS_tick()

↓

Update delays

↓

Wake expired tasks

↓

Invoke scheduler

Without SysTick, there would be no notion of time inside the operating system.

🔄 PendSV Handler

The actual context switch is performed by the PendSV exception.

Save Context

↓

Scheduler selects next task

↓

Restore Context

↓

Continue execution

PendSV is intentionally configured as the lowest-priority interrupt, ensuring that context switching never delays time-critical interrupt service routines.

During a context switch, PendSV:

 - Saves registers R4-R11
 - Stores the current task's stack pointer
 - Loads the next task's stack pointer
 - Restores CPU registers
 - Returns directly into the next task

This entire operation happens transparently to the application.

😴 Idle Thread

Every RTOS requires a task that always remains runnable.

Our kernel creates an Idle Thread during initialization.

Whenever no application task is ready, the scheduler automatically switches to the Idle Thread.

Typical responsibilities include:
- Background processing
- Low-power management
- CPU idle statistics

This guarantees the processor always has valid code to execute.

🎯 Key Takeaways
 - Every task owns an independent Task Control Block (TCB) and stack.
 - The Ready Set bitmap enables efficient task selection.
 - The Scheduler determines which runnable task executes next.
 - SysTick provides the periodic timing source for delays and scheduling.
 - PendSV performs efficient context switching at the lowest interrupt priority.
 - The Idle Thread ensures the CPU always has a runnable task.
 - Together, these components form the core architecture of a lightweight multitasking RTOS.