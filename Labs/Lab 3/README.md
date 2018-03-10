# Lab 3 - Sudoku Solution Checker

### Link to Repository: [https://github.com/AshwinK97/Operating-Systems/tree/master/Labs/Lab%203](https://github.com/AshwinK97/Operating-Systems/tree/master/Labs/Lab%203)


## Group members:
Jasindan Rasalingam: 100584595  
Darron Singh: 100584624  
Kaushal Patel: 100586212  
Ashwin Kamalakannan: 100584423

## Description
Sudoku validator, checks if a solved sudoku puzzle meets all rules to make it valid.
We check if every row, column, and box to see if the values internally sum to 45 (sum of range 1-9).
9 threads for rows, 9 threads for columns, and 1 thread for boxes.
If any sums are not 45, an invalid puzzle message is printed and all threads are exited using an int 'valid' global variable as a boolean.

## Usage
To compile use the 'make' utility.  
To run simply type `./solution_check.o` <inputfile>, where the input file is the file containing your sudoku solution.
