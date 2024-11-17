# **Simple Assembly Language Emulator**

This project implements a simple assembly language emulator using C. The emulator processes a sequence of instructions from an input file and executes them while simulating components like a program counter, accumulator, memory, and instruction register.

---

## **Features**
- Simulates basic assembly operations (`LOAD`, `ADD`, `STORE`, etc.).
- Reads instructions and data from an input file.
- Maintains a simulated memory (`dm`) and program counter (`p_counter`).
- Outputs the state of the machine after each operation.
- Provides error handling for invalid instructions and file input.

---

## **Supported Instructions**
| **Instruction** | **Description**                                  |
|------------------|--------------------------------------------------|
| `LOAD`           | Loads a value from memory into the accumulator. |
| `ADD`            | Adds a value from memory to the accumulator.    |
| `STORE`          | Stores the accumulator's value into memory.     |
| `SUB`            | Subtracts a value from memory from the accumulator. |
| `IN`             | Reads a value into the accumulator from input.  |
| `OUT`            | Outputs the value in the accumulator.           |
| `HALT`           | Ends program execution.                         |
| `JMP`            | Sets the program counter to a specific address. |
| `SKIPZ`          | Skips the next instruction if the accumulator is zero. |
| `SKIPG`          | Skips the next instruction if the accumulator is greater than zero. |
| `SKIPL`          | Skips the next instruction if the accumulator is less than zero. |

---

## **Project Structure**
- **`main()` Function**:
  - Initializes memory and program variables.
  - Reads instructions from the input file into `instruction_memory`.
  - Executes instructions using a loop and switch statement.

- **Key Components**:
  - `p_counter`: Tracks the current instruction.
  - `acc`: Accumulator for arithmetic operations.
  - `dm`: Simulated memory array.
  - `instruction` struct: Stores the opcode and memory address for each instruction.

---

## **Usage**

### **Compilation**
Compile the program using `gcc`:
```bash
gcc -o emulator emulator.c
