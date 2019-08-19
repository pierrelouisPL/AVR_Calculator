
# README - AVR CALCULATOR #

## Basic Info ##

Author: Piotr Śmieja
Date: 18 VII 2019
Contact: p.smieja@student.uw.edu.pl

## Intorduction and Purpose ##

This is a project for the AVR programming course at the Faculty of Physics, Warsaw University

## Files ##

- main.c
- keyboard.h
- adc.h
- 8seg.h
- README.md
- Documentation.pdf

## Notes ##

0. Documentaion (in Polish) is provided in the pdf format. Pictures of the working device are available on the project website.

1. (keyboard input == displayed number) is a global int array displayedDigits[4].
For calculations, our array is coverted to int at the end of input process using numDisplayed()

2. The keyboard works using one ADC input (PC0). Different voltage ranges acquired from the ADC are paired with different key codes
these codes with their boundary values are given by valuesAndIDs[] array from keyboard file
you can get the code of a pressed key with int pressedKey() function
 - codes 0 to 9 refer to digit keys
 - code 100 is returned when no key is pressed
 - codes 101 to 105 refer to function keys as follows
 	> 101 => +
	> 102 => -
    > 103 => C
    > 104 => =
    > 105 => CE

3. The calculator works only for non-negative integers lower than 10,000. Negative values are not accepted by the device.
There are however NO ERROR MESSAGES for this and you should expect nonsense when you try to perform operations like e.g. 100 - 200 = ?
