# Triton VM

## Overview
Triton VM ISA is a 32-bit virtual machine with a specific instruction set architecture (ISA), memory layout, register setup, and operation set designed for efficient computation and control flow. 

## Memory Layout
The memory of Triton VM ISA is divided into several sections including Stack, Boot Sector, Free Memory, Video Memory, and more, each having a designated address range.

## Registers
Triton VM ISA features a variety of registers, including but not limited to Zero Register, Return Address, Stack Pointer, and Program Counter, each serving a unique purpose in computations and program execution.

### Conventions
The documentation defines conventions for referring to any register, as well as any register excluding a specific set of registers.

## Operations
Triton VM ISA supports a variety of operations, categorized into Math, Control Flow, and Memory/Register Access. Each operation is detailed with its instruction, inputs, and a brief description.

### Math Operations
Include basic arithmetic, shift, logical, and comparison operations.

### Control Flow Operations
Include instructions for jumping and conditional execution based on register values.

### Memory/Register Access Operations
Include loading, storing, setting register values, interrupt requests, and system calls.

## Macros
Triton VM ISA includes macros for additional control flow and stack access operations, providing convenient shortcuts for common instruction sequences.
