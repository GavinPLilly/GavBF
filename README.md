# GavBF

An in terminal [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck "Brainfuck Wikipedia page") interpreter and debugger.

![Screenshot from 2022-11-01 19-40-36](https://user-images.githubusercontent.com/66760957/199380925-4c3e2366-5113-4a8b-949e-a23eb7acd8be.png)

## Running gavbf
Compile the program by running ```make```.\
The program requires the Ncurses library to link with.\
To use gavbf run the gavbf program followed by the path to a program. Some example programs are included in the "programs" directory.\
```./gavbf programs/helloworld.bf```

# Display
Once the program starts you, a number of outlines will be drawn. The windows are as follows:
  * Program: Displays the input program. The next instruction to be executed will be highlighted
  * Input: Brainfuck programs may request user input. When this happens, the user input will be displayed in the input window.
  * Output: The printed output of the program.
  * Pointers: Display the current state of the instruction and data pointers
  
## How to use gavbf
The folling command control the program execution, and are inspired by similar GDB commands
  * c: <ins>C</ins>ontinue execution
  * s: <ins>S</ins>tep one character. This will not skip over non-instruction characters
  * n: <ins>N</ins>ext. Execute the next instruction
  * q: <ins>Q</ins>uit. Exit gavbf
