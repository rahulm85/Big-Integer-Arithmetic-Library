# Big Integer Arithmetic Library

A C++ project demonstrating arbitrary-precision integer arithmetic using string-based digit storage.

## Project overview

The implementation represents large integer values as digit strings rather than relying on built-in integer limits. The documented operations include:

- Addition
- Subtraction with sign handling
- Multiplication using the schoolbook algorithm
- Removal of leading zeroes and normalization of negative zero

## Implementation notes

The original project describes a single-file C++ implementation with a `BigInt` class, arithmetic operators, and a simple interactive console menu.

## Build

The original source project documents a standard C++ compilation flow:

```bash
g++ -std=c++11 -o bigint Big_Int.cpp
./bigint
```

The source file is not included in this repository yet; the command above applies once an authorized copy of `Big_Int.cpp` has been added.

## Limitations noted by the original project

- Division and modulus are not implemented.
- Input validation for non-digit characters is not described.
- Schoolbook multiplication has quadratic time complexity, O(n²).

## Original project and attribution

The original implementation is maintained by **kapujaganmohanreddy**:

- [Original GitHub repository](https://github.com/kapujaganmohanreddy/Big-Int)

The original repository does not show a license file. Source code has therefore not been copied into this repository. Please obtain the author's permission or a suitable license before redistributing or modifying the original implementation.

## Possible extensions

- Add input validation and clearer error handling.
- Add division and modulus.
- Add automated tests for sign combinations, zero, leading zeroes, and large operands.
- Separate the class interface, implementation, and test program.
