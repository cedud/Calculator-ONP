# Reverse Polish Notation Integer Calculator

## Description
This project implements an integer calculator that evaluates mathematical expressions given in infix notation and converts them to postfix (Reverse Polish Notation). The calculator supports various operations and functions, handling integer arithmetic with operator precedence.

## Input Format
1. **n** - Number of formulas.
2. **n formulas**, each given in a valid infix notation and ending with a dot (`.`). Each token is separated by whitespace. 
3. **Operands** are positive integers (results of operations may be negative). Negative numbers are represented using the unary negation operator `N`.
4. **Operators** are single characters, and function names consist only of capital letters.

### Supported Operations
Operations are evaluated in the following order of precedence (from lowest to highest):

- **Addition and Subtraction**: `a + b`, `a - b`
- **Multiplication and Division**: `a * b`, `a / b` (integer division, rounding down). Division by `0` is not allowed (see output handling).
- **Conditional Operation**: `IF(a, b, c)` – returns `b` if `a > 0`, otherwise returns `c`.
- **Unary Negation**: `N a` – equivalent to `-a`.
- **Minimum and Maximum Functions**: `MIN(a1, a2, ...)`, `MAX(a1, a2, ...)` – these functions accept any number of parameters and are stored in postfix notation as `MINn` or `MAXn`, where `n` represents the number of parameters.
- **Parentheses**: `( ... )` – used to explicitly group expressions.

## Output Format
For each formula, the output consists of:

1. The formula converted to **postfix notation** (Reverse Polish Notation).
2. Step-by-step execution, displaying:
   - The operator or function being executed.
   - The content of the stack before execution.
3. The **final result** of the expression.
4. If a division by zero occurs, output `ERROR` and proceed to the next expression.
5. If an invalid expression is encountered, output `ERROR` and proceed to the next expression.

## Example
### **Input**
```
3
( 3 + 4 ) * 5.
IF( 0, 10, 20 ).
10 / 0.
```

### **Output**
```
3 4 + 5 *
* [3, 4]
+ [3, 4, 5]
* [7, 5]
Final Result: 35

IF 0 10 20
IF [0, 10, 20]
Final Result: 20

10 0 /
ERROR
```

## Installation & Usage
1. Clone the repository:
   ```sh
   git clone https://github.com/cedud/Calculator-ONP/
   cd Calculator-ONP
   ```
2. Compile and run the program:
   ```sh
   make # or manually compile
   ./calculator < input.txt
   ```
3. Provide input via a file or interactively.

## License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
