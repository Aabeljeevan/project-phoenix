# Embedded C - Module 1
# Memory & MCU Boot Process

---

# Lesson 1 - Memory Fundamentals

## Why do microcontrollers have Flash and RAM?

Microcontrollers use two different memories because they serve different purposes.

### Flash Memory

Flash is a non-volatile memory.

Characteristics:

- Stores firmware permanently
- Stores program instructions (.text)
- Stores constant data (.rodata)
- Stores initial values of initialized global/static variables
- Retains data after power OFF
- Requires a special programming sequence to modify

Examples:

- main()
- Reset_Handler()
- Interrupt handlers
- Constant lookup tables
- Firmware image

---

### RAM

RAM is volatile memory.

Characteristics:

- Fast read/write memory
- Stores variables while the program executes
- Loses contents after power OFF

RAM contains:

- .data
- .bss
- Heap
- Stack

---

# Firmware Image

The firmware image stored in Flash contains:

- Vector Table
- Startup Code
- Reset_Handler()
- main()
- Other functions
- Constants (.rodata)
- Initial values for .data variables

The firmware image itself remains in Flash.

Only the initialized variable values are copied into RAM during startup.

---

# Memory Sections

## .text

Contains executable program instructions.

Stored in Flash.

Example:

```c
int main(void)
{
}
```

---

## .rodata

Contains read-only constant data.

Stored in Flash.

Example:

```c
const int speed = 100;
```

---

## .data

Contains initialized global and static variables.

Example:

```c
int global = 10;

static int counter = 5;
```

Important:

The initial values are stored in Flash.

During startup they are copied into RAM.

---

## .bss

Contains uninitialized global and static variables.

Example:

```c
int counter;

static int errorFlag;
```

Startup code clears the entire .bss section to zero before calling main().

---

## Stack

Stores:

- Local variables
- Return addresses
- Saved CPU registers
- Function parameters (depending on the calling convention)

Example:

```c
void func(void)
{
    int x = 10;
}
```

The variable x exists only while func() executes.

---

# Variable Placement

```c
int global = 10;
```

→ .data

---

```c
int counter;
```

→ .bss

---

```c
const int speed = 100;
```

→ .rodata

---

```c
void func(void)
{
    int x = 5;
}
```

→ Stack

---

# MCU Boot Process

After RESET:

```
Power ON
     │
     ▼
CPU starts execution
     │
     ▼
Reads Initial Stack Pointer
(0x08000000)
     │
     ▼
Initializes SP
     │
     ▼
Reads Reset_Handler Address
(0x08000004)
     │
     ▼
Jumps to Reset_Handler()
     │
     ▼
Copies .data
Flash → RAM
     │
     ▼
Clears .bss
     │
     ▼
Calls SystemInit()
     │
     ▼
Calls main()
```

---

# Why is the Stack Pointer initialized first?

Reset_Handler may:

- Create local variables
- Call other functions
- Save return addresses

All of these require a valid stack.

Therefore the CPU initializes the Stack Pointer before executing Reset_Handler.

---

# Vector Table

The vector table is located at the beginning of Flash.

Example:

| Address | Contents |
|----------|----------|
| 0x08000000 | Initial Stack Pointer |
| 0x08000004 | Reset_Handler Address |
| 0x08000008 | NMI_Handler |
| 0x0800000C | HardFault_Handler |

The CPU reads these entries automatically after reset.

---

# Startup File

Typical STM32 startup file:

```asm
.section .isr_vector

.word _estack

.word Reset_Handler

.word NMI_Handler

.word HardFault_Handler
```

Important:

`.word` stores a 32-bit value (an address).

The vector table contains addresses, not executable instructions.

---

# Why not use BL Reset_Handler?

Because:

```
BL Reset_Handler
```

is an instruction.

The vector table is **not executable code**.

It is simply a table of addresses.

The CPU reads the Reset_Handler address from the vector table and performs the jump in hardware.

---

# Linker Script (.ld)

The linker script decides where each section is placed in memory.

Example:

```ld
MEMORY
{
FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K

RAM (xrw) : ORIGIN = 0x20000000, LENGTH = 40K
}
```

---

Example:

```ld
.text :
{
*(.text)
} > FLASH
```

Meaning:

Place the .text section into Flash.

---

```ld
.data :
{
*(.data)
} > RAM
```

Meaning:

Place initialized variables into RAM.

---

```ld
.bss :
{
*(.bss)
} > RAM
```

Meaning:

Place uninitialized variables into RAM.

---

# Compiler vs Linker

Compiler:

- Converts C code into object files
- Decides which section (.text, .data, .bss, .rodata) each variable belongs to

Linker:

- Combines object files
- Places sections into Flash or RAM according to the linker script
- Resolves addresses
- Generates the final firmware image

---

# _estack

The linker script creates the symbol:

```
_estack
```

which represents the top of RAM.

The startup file places `_estack` as the first entry in the vector table.

After reset, the CPU loads this value into the Stack Pointer.

---

# Complete Boot Flow

```
Your C Code
      │
      ▼
Compiler
      │
      ▼
Object Files
(.text .data .bss)
      │
      ▼
Linker
(.ld)
      │
      ▼
Firmware Image
      │
      ▼
Flash Memory
      │
      ▼
CPU Reset
      │
      ▼
Vector Table
      │
      ▼
Reset_Handler
      │
      ▼
Initialize RAM
      │
      ▼
SystemInit()
      │
      ▼
main()
```

---

# Key Takeaways

- Flash stores firmware permanently.
- RAM stores runtime variables.
- The CPU starts from the vector table after reset.
- The first vector table entry is the Initial Stack Pointer.
- The second entry is the Reset_Handler address.
- The startup file builds the vector table.
- The linker script places sections into memory.
- `.word` stores addresses, not instructions.
- `.data` is copied from Flash to RAM.
- `.bss` is cleared before `main()`.
- `main()` is **not** the first function executed after power-on.

---

# Interview Questions

1. Why does a microcontroller use both Flash and RAM?
2. What is stored in `.text`, `.rodata`, `.data`, and `.bss`?
3. Why is `.data` copied from Flash to RAM?
4. Why is `.bss` cleared during startup?
5. Why is the Initial Stack Pointer the first vector table entry?
6. What is the purpose of the vector table?
7. Why does the startup file use `.word` instead of `BL`?
8. What is the role of the linker script?
9. Who decides where `.text` and `.data` are placed in memory?
10. Explain the complete MCU boot sequence from RESET to `main()`.