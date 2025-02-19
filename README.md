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
4
MIN ( 100 , MAX ( 1 , 34 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) .
2 + MIN ( 100 , MAX ( 1 , 6 * 5 + 2 , 2 ) , 80 ,  MIN ( 66 , 36  , 35 , 77 ) , 50 , 60 ) * 3 .
N 400 + ( 11 - ( 3 * 2 ) ) / 2 + N N 200 .
IF ( ( 6 + 8 ) , ( 4 / 2 ) , MIN ( 8 , 2 , 1 , 0 , 3 ) ) * 2 * 6 / N ( 3 ) .
```

### **Output**
```
100  1  34  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6
MAX3 2 34 1 100
MIN4 77 35 36 66 80 34 100
MIN6 60 50 35 80 34 100
34

2  100  1  6  5  *  2  +  2  MAX3  80  66  36  35  77  MIN4  50  60  MIN6  3  *  +
* 5 6 1 100 2
+ 2 30 1 100 2
MAX3 2 32 1 100 2
MIN4 77 35 36 66 80 32 100 2
MIN6 60 50 35 80 32 100 2
* 3 32 2
+ 96 2
98

400  N  11  3  2  *  -  2  /  +  200  N  N  +
N 400
* 2 3 11 -400
- 6 11 -400
/ 2 5 -400
+ 2 -400
N 200 -398
N -200 -398
+ 200 -398
-198

6  8  +  4  2  /  8  2  1  0  3  MIN5  IF  2  *  6  *  3  N  /
+ 8 6
/ 2 4 14
MIN5 3 0 1 2 8 2 14
IF 0 2 14
* 2 2
* 6 4
N 3 24
/ -3 24
-8
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
