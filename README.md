This is an exercise from the book: The ANSI C Programming Language, but with a more advanced implementation.

basically, I extended the grammar by eliminating left recursivity and applying left factoring.
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
-The program only supports identifiers with one character.<br />
-Supports one-digit array lengths.<br />
-No support for function args.<br />
-No support for constants declaration.<br />

# Examples:
![examples](https://user-images.githubusercontent.com/63020343/201544807-5da66464-ce43-4afc-87b6-eecb0c3550ca.png)
