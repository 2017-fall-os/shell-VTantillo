# Theory of Operation Systems Unix Shell
### Victor Tantillo

## Description
The purpose of this lab was to implement a simple shell program that has most of the basic functionalities.
    - Execute commands with either the absolute path, or look up the command using the path variable.
    - Type "exit" to close the shell.
    - Pipe input from one command to another.
    - Execute background tasks
    - Change directories using the "chdir" function.

## Usage
To run the shell after navigating to the directory, type the "make" command and it will compile all the files.  "./vSh" starts the shell and prints out the prompt.  To exit, just type "exit" as the command and the shell will close returning you to the regular prompt.

## Notes
There is a bug where if you put a space after the token it duplicates that last token.  This bug makes it so the pipe doesn't work correctly.  The pipe only works for 2 commands.  Worked with Kimberly Kato on some of the extra methods and the logic for piping.  We used the recommended book "Linux Programming Interface" for help with the piping.
