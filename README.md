# Big Integer Arithmetic Library (C++)

[![Build and test](https://github.com/rahulm85/Big-Integer-Arithmetic-Library/actions/workflows/ci.yml/badge.svg)](https://github.com/rahulm85/Big-Integer-Arithmetic-Library/actions/workflows/ci.yml)

A standalone C++11 console application implementing arbitrary-precision signed integer addition, subtraction, and multiplication using decimal digit strings.

## Features

- Stores magnitude as a decimal string, avoiding built-in integer-size limits.
- Supports positive, negative, and zero values.
- Implements addition, subtraction, and schoolbook multiplication.
- Normalizes leading zeroes and prevents negative zero.
- Rejects empty values, sign-only values, and non-digit input.
- Includes a small assertion-based test program.

## Files

- `BigInt.cpp`: BigInt class implementation and interactive console calculator.
- `tests.cpp`: basic tests for arithmetic, signs, zero, large values, and invalid input.

## Build and run

Requires a C++11-compatible compiler such as g++.

```bash
g++ -std=c++11 -Wall -Wextra -pedantic BigInt.cpp -o bigint
./bigint
```

Enter expressions in the form `<integer> <operator> <integer>`:

```text
> 999999999999999999999 + 1
= 1000000000000000000000
> -25 * 12
= -300
> 100 - 250
= -150
> q
```

## Run tests

```bash
g++ -std=c++11 -Wall -Wextra -pedantic tests.cpp -o bigint_tests
./bigint_tests
```

## Complexity

For operands with n and m digits, addition and subtraction are O(max(n,m)); schoolbook multiplication is O(n*m) time and O(n+m) auxiliary space.

## Scope and limitations

Division, modulus, decimal/fractional values, and optimized multiplication algorithms are not implemented. This is an educational integer-arithmetic project, not a cryptographic library; do not use it as a production cryptographic primitive.

## Usage

This project is provided as an independently written educational implementation. No source files from the earlier reference repository are copied here.
