A simple C program that converts a complicated declaration into a human readable text.

This is an exercice from the book : The ANSI C programming Language, but with a more advanced implmentation.

basically, i extended the grammer by eliminating left recursivity, and applying left factoring.
# Grammer:
```
dcl     ==> A dirdcl
A       ==> * A | epsilon
dirdcl  ==> id dirdcl1 | ( dcl ) dirdcl1
dirdcl1 ==> ( ) dirdcl1 | [ dirdcl2 | epsilon
dirdcl2 ==> ] dirdcl1 | number ] dirdcl1

```
# LL(1) table:
|   | * | ( | ) | [ | ] | number | id | $ | 
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| dcl | dcl ==> A dirdcl | dcl ==> A dirdcl |  |  |  |  | dcl ==> A dirdcl |  |
| A | A ==> * A | A ==> epsilon |  |  |  |  | A ==> epsilon |  |
| dirdcl  |  | dirdcl ==> ( dcl ) dirdcl1 |  |  |  |  | dirdcl ==> id dirdcl1 |  |
| dirdcl1  |  | dirdcl1 ==> ( ) dirdcl1 | dirdcl1 ==> epsilon | dirdcl1 ==> [ dirdcl2 |  |  | | dirdcl1 ==> epsilon |
| dirdcl2  | |  |  |  | dirdcl2 ==> ] dirdcl1 | dirdcl2 ==> number ] dirdcl1 |  |  |

# Notes:
-The program only support identifiers with one character.<br />
-Supports one-digit array lengths.<br />
-No support for function args.<br />
-No support for constants declaration.<br />

# Examples:
