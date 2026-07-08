# Module 1 - Memory

## Lesson 1 - Memory Fundamentals

---

# Why do Embedded Systems have Flash and RAM?

Microcontrollers use two different memories because each serves a different purpose.

## Flash Memory

Flash is a non-volatile memory.

Characteristics:
- Stores firmware permanently
- Stores program instructions (.text)
- Stores constant data (.rodata)
- Stores initial values of initialized global/static variables
- Retains data after power OFF
- Can only be written using a special Flash programming sequence

Examples:
- Application code
- Startup code
- Reset Handler
- Vector Table
- Constant lookup tables

---

## RAM

RAM is volatile memory.

Characteristics:
- Stores variables during program execution
- Fast read/write
- Loses data after power OFF

RAM contains:
- .data
- .bss
- Heap
- Stack

---

# Firmware Image

The firmware image stored in Flash contains:

- Vector Table
- Startup Code (Reset Handler)
- main()
- Other functions
- Constant data
- Initial values for .data

The firmware image is NOT copied entirely into RAM.

Only initialized variables are copied from Flash to RAM during startup.

---

# Startup Sequence

Power ON

↓

CPU starts execution from Flash (0x08000000)

↓

CPU reads Vector Table

↓

CPU jumps to Reset Handler

↓

Startup code copies .data from Flash to RAM

↓

Startup code clears .bss

↓

Stack Pointer is initialized

↓

main() is called

---

# Memory Sections

## .text

Contains program instructions.

Stored in Flash.

Example:
main()
Reset_Handler()

---

## .rodata

Contains constant data.

Stored in Flash.

Example:

const int speed = 100;

---

## .data

Contains initialized global/static variables.

Example:

int global = 10;

static int count = 5;

Initial values are stored in Flash.

Runtime variables exist in RAM.

---

## .bss

Contains uninitialized global/static variables.

Example:

int counter;

static int errorFlag;

The startup code clears this section to zero before main().

---

## Stack

Stores local (automatic) variables.

Example:

void func(void)
{
    int x = 10;
}

The stack frame is created when entering the function.

It is destroyed when the function returns.

---

# Variable Placement Examples

int global = 10;          --> .data

int counter;              --> .bss

static int value = 5;     --> .data

static int error;         --> .bss

int local = 20;           --> Stack

const int speed = 100;    --> .rodata (typically Flash)

---

# Important Concepts Learned

Flash stores code.

RAM stores variables.

Global variables live for the lifetime of the program.

Local variables exist only while their function is active.

Startup code prepares RAM before calling main().

The Reset Handler calls main().

The firmware image remains in Flash.

Only variable data is copied into RAM.

Flash cannot be modified using normal assignment.

Writing Flash requires a special programming sequence.