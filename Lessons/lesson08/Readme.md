🧠 Priority-Based Preemptive Scheduler


In the previous lesson, we implemented a Round Robin scheduler, where each ready task received an equal opportunity to execute. While this approach is simple and fair, many real-time applications require certain tasks to execute immediately when they become ready.

In this lesson, we evolve our kernel into a Priority-Based Preemptive Scheduler, where the scheduler always executes the highest-priority ready task.

Unlike Round Robin, tasks are no longer treated equally. Each task is assigned a priority, and the scheduler ensures that the most important ready task always owns the CPU.

🎯 Why Priority Scheduling?

Consider a motor controller and an LED blinking task.

If both tasks receive the CPU equally, the LED task could delay the motor control loop, potentially causing instability.

Instead, we assign:

🔴 Motor Control → Priority 31
🟠 Communication → Priority 20
🟢 LED Blink → Priority 5
⚪ Idle Thread → Priority 0

Whenever the motor-control task becomes ready, it immediately preempts the currently running lower-priority task.

This deterministic behavior is one of the foundations of real-time operating systems.

🏗 Kernel Architecture

The kernel still uses the same fundamental components developed in previous lessons:

Task Control Blocks (TCBs)
Individual task stacks
PendSV for context switching
SysTick for timing

The major change is how runnable tasks are selected.

Instead of cycling through tasks, the scheduler uses a priority bitmap.

uint32_t OS_readySet;
uint32_t OS_delayedSet;

Each bit represents one priority level.

Example:

Priority : 31 ... 5 4 3 2 1 0
Bitmap   :  1 ... 0 1 0 0 0 0

A set bit means:

✔ Task exists

✔ Task is ready

⚡ Highest Number = Highest Priority

Our implementation uses:

Priority 31  → Highest
Priority 30
...
Priority 1
Priority 0   → Idle Thread

Therefore,

bit31  → Priority 31
bit30  → Priority 30
...
bit0   → Priority 0

Finding the highest-priority task becomes extremely efficient.

🔍 Finding the Next Task

The scheduler simply finds the Most Significant Set Bit (MSB).

#define LOG2(x) (32U - __builtin_clz(x))

next = OS_thread[LOG2(OS_readySet)];

__builtin_clz() counts the number of leading zeros.

Example:

OS_readySet

10010000...

^

Highest set bit
LOG2()
↓

Priority 31

This makes task selection an O(1) operation, regardless of how many tasks exist.

⚙ Scheduler Flow

The scheduler is remarkably compact.

if (OS_readySet == 0U) {
    next = OS_thread[0];
}
else {
    next = OS_thread[LOG2(OS_readySet)];
}

If no application task is ready,

➡ the Idle Thread executes.

Otherwise,

➡ the highest-priority ready task is selected.

If that task differs from the currently running task:

OS_next = next;
SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;

PendSV is triggered to perform the context switch.

⏳ Delaying a Task

When a task calls:

OS_delay(ticks);

the kernel:

✔ removes it from the Ready Set

✔ inserts it into the Delayed Set

OS_readySet &= ~bit;
OS_delayedSet |= bit;

The scheduler immediately searches for another runnable task.

⏰ SysTick Processing

Every SysTick interrupt performs timeout management.

workingSet = OS_delayedSet;

For each delayed task:

decrement timeout
if timeout reaches zero
remove from delayed set
insert back into ready set
OS_readySet   |= bit;
OS_delayedSet &= ~bit;

The task instantly becomes eligible for execution again.

🚀 Immediate Preemption

Suppose:

Task A
Priority = 10

Running...

Now,

Task B
Priority = 20

becomes ready.

The scheduler immediately chooses Task B.

Task A
↓

PendSV

↓

Task B

No waiting for a time slice.

No cyclic rotation.

Higher-priority tasks execute as soon as they are ready.

📊 Round Robin vs Priority Scheduling
Feature	Round Robin	Priority Scheduler
Selection	Circular order	Highest-priority ready task
Fairness	Equal CPU time	Based on priority
Lookup	Cyclic search	Bitmap + MSB
Complexity	Simple	Slightly higher
Response Time	Waits for next turn	Immediate preemption
Best For	General multitasking	Real-time systems
💡 Why Use Bitmaps?

A bitmap offers several advantages:

🚀 Constant-time scheduling
🚀 Minimal RAM usage
🚀 Very fast insertion/removal
🚀 Scales well to many tasks
🚀 Ideal for Cortex-M microcontrollers

This is why bitmap-based schedulers are widely used in embedded RTOS kernels.

🧩 Core Functions
OS_sched()

Selects the highest-priority runnable task.

OS_delay()

Moves the current task from the Ready Set to the Delayed Set.

OS_tick()

Updates delayed tasks and wakes them when their timeout expires.

OSThread_start()

Assigns each task a unique priority and registers it with the scheduler.

🎯 Key Takeaways
✔ Every task has a unique priority level.
✔ Higher numerical value corresponds to a higher priority.
✔ The scheduler always selects the highest-priority ready task.
✔ Bitmaps enable constant-time task selection.
✔ SysTick manages task delays and wake-ups.
✔ PendSV performs context switching only when a different task should execute.
✔ Immediate preemption ensures deterministic response times for real-time applications.