# C-complex-declarations-parser
Creating a simple C parser for complicated declarations.

This is an exercice from the "ANSI C programming language" book.

it is based on the following grammer 
    dcl: optional *s dir-dcl
    dir-dcl : name | (dcl) | dir-dcl[optioanl size] | dir-dcl()