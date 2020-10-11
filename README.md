# brainfuck-interpreter
* brainfuck.c takes a text file bf.txt as input, which contains code written in the esoteric language Brainfuck, and interprets it.
  * Brainfuck Syntax:
    *  \> := Increment pointer.
    *  \< := Decrement pointer.
    *  \+ := Increment value at pointer.
    *  \- := Decrement value at pointer.
    *  \[ := Begin loop (continues while value at pointer is non-zero).
    *  \] := End loop
    *  \, := Read character from input into value at pointer
    *  \. := Print value to output as a character.
* when running brainfuck.c, it interprets and executes the text from left to right.
  1. Upon detection of a loop enter ("["), the contents inside the loop bounds are added into an array to further interpret until current pointer has value of zero.
  2. Upon detection of a loop exit ("]") the interpreter will continue at towards the end of file.
  3. Upon detection of a print ("."), the interpreter will print the ASCII number of the character and store the content into an array to print at the very end as an ASCII value. 

As I have only uploaded the C file, you must compile the code before running: gcc -o ./bf ./brainfuck.c

Run the executable with the bf.txt: ./bf ./bf.txt

Program cannot-do's:
 * Will not throw fail if there is a begin loop but not end loop or if there is a nested loop.
 * Will continue interpretation after reading a non-defined syntax. This will cause unexpected output.
