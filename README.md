
# README - AVR CALCULATOR #

AVR-based simple calculator. It performs addition and substraction on non-negative integers.
Numbers are displayed on a display consisting of four single-digit 8-segment red common-cathode displays.
Keyboard is placed on a separate PCB and consists of 15 tact-switches.
Detailed information containing a schematic and registers description is available in Polish in the pdf documentation. 

## Basic Data ##

Author: Piotr Śmieja
Date: 21.08.2019
Contact: p.smieja@student.uw.edu.pl

## Purpose ##

This is a project for the AVR programming course at the Faculty of Physics, Warsaw University.

## Files ##

- main.c
- keyboard.h
- adc.h
- 8seg.h
- README.md
- Documentation.pdf

## Compilation and upload ##

The clock in my device is currently set to 8MHz.
Before uploading the program, one should set the CKSEL fusebits in the device (the default value is 1MHz) or the F_CPU definition in 8seg.h.

## Notes ##

0. Documentaion (in Polish) is provided in pdf format. Pictures of the working device are available on the website.

1. (keyboard input == displayed number) is a global int array displayedDigits[4]
for calculations, our array is coverted to an integer at the end of input process using numDisplayed()

2. keyboard works using one ADC input (PC0). Different voltage ranges acquired from the ADC are paired with different key codes
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

3. calculator works only for non-negative integers lower than 10,000. Negative values are not accepted by the device
there are however NO ERROR MESSAGES for this and you should expect nonsense when you try to perform operations like e.g. 100 - 200 = ?

4. clock frequency in my device is currently set to 8MHz. this value could be reduced to save power if battery power was considered.