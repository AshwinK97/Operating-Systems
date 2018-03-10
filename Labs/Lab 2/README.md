### Link to Repository: [https://github.com/AshwinK97/Operating-Systems/tree/master/Labs/Lab%202](https://github.com/AshwinK97/Operating-Systems/tree/master/Labs/Lab%202)

# Shell Utility
This repository contains files for the shell utility project for lab 2. The shell will allow users to perform basic directory operations such as changing and listing directories. You can also run shell commands from a batch file.

# Group members:
Jasindan Rasalingam: 100584595  
Darron Singh: 100584624  
Kaushal Patel: 100586212  
Ashwin Kamalakannan: 100584423

# Shell Commands

## `cd`
Allows user to change directory to specified path  
**Does not support spaces in path names.**

### `cd`
stays in the current working directory
### `cd ..`
changes to the ***parent*** directory
### `cd /`
changes to the ***root*** directory
### `cd Documents`
changes to the ***documents*** directory


## `dir` or `ls`
Displays all content in specified directory  
**Does not support spaces in path names.**

### `dir` 
displays contents of ***root*** directory
### `dir ..`
displays contents of ***current*** directory
### `dir /`
displays contents of ***parent*** directory
### `dir Music`
displays contents of ***music*** directory


## `environ` or `env`
Displays all environment variables (PWD, SHELL, etc.)


## `clr` or `clear`
Clears the screen by printing 100 blank lines to stdout


## `help`
Displays this help screen


## `pause`
Pauses the shell, waits for user to press **`<enter>`**


## `quit` or `exit`
Exits shell utility and will exit with status of last command
