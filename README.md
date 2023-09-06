<div align="center">

[![CodeQL](https://github.com/Ziocash/UPO-Algorithms-1/actions/workflows/codeql.yml/badge.svg)](https://github.com/Ziocash/UPO-Algorithms-1/actions/workflows/codeql.yml)[![Valgrind](https://github.com/Ziocash/UPO-Algorithms-1/actions/workflows/valgrind.yml/badge.svg)](https://github.com/Ziocash/UPO-Algorithms-1/actions/workflows/valgrind.yml)

</div>

# UPO-Algorithms-1 Repository

Laboratory course - Sperimental part.<br/>
The course provides knowledge about **ADT** or **Abstract Data Types**, sorting algorithms and advanced C use (e.g.: generic pointers).

## Wiki

This repo also provides a [detailed wiki](https://github.com/Ziocash/UPO-Algorithms-1/wiki) about all structures and functions.

## Requirements

- C standard **C11**
- Linux (currently compiled on **WSL-Ubuntu**)
- C Compiler: GNU Compiler Collection (**GCC**) `-Wall -Wextra -std=c11 -pedantic -g`
- Debugger: GNU Debugger (**GDB**)
- Memory Debugger: **Valgrind**

## ADT

ADT implemented in this project:

- Stack `struct upo_stack_node_s`
- Binary search tree `struct upo_bst_node_s`
- Hash table (separate chaining) `struct upo_ht_sepchain_list_node_s` (linear probing) `struct upo_ht_linprob_slot_s`

Additional implementations:

- Sorting algorithms
- Extra exercises:
  - Generic functions in [intro-exercises](./intro-exercises)

## UPO alglib core toolkit

Collection of algorithms and abstract data types developed at the [Computer Science Institute](http://www.di.unipmn.it) of the [University of Piemonte Orientale](http://www.uniupo.it) for the *Algorithm 1 - Lab* course.

### Toolkit code

This repository contains a toolkit provided by Prof. [Marco Guazzone](https://github.com/sguazt).

[Toolkit download](./UPOalglib_core_toolkit.zip)
