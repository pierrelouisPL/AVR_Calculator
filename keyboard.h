#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <avr/io.h>
#include "adc.h"

/* left column of valuesAndIDs array provides lower bounds of the adcRead() values
 * expected for the keys with codes in the right column. When main() requests
 * pressedKey(), adcRead() is compared in loop to all the possible values in the
 * left col. of valuesAndIDs, and pressedKey() returns the key code */

int valuesAndIDs[16][2] = {{1023, 9999}, // error message
                           {991, 100}, // NO KEY
                           {924, 1},   // 1
                           {865, 4},   // 4
                           {814, 7},   // 7
                           {758, 101}, // +
                           {703, 102}, // -
                           {646, 103}, // C
                           {586, 0},   // 0
                           {526, 8},   // 8
                           {462, 5},   // 5
                           {396, 2},   // 2
                           {323, 3},   // 3
                           {242, 6},   // 6
                           {152, 9},   // 9
                           {52,  104}  // =
                           // < 52 => code: 105 => CE
                          };

int pressedKey() {
	int n = adcRead();

	for (int i = 0; i < 16; i++) {
		if (n > valuesAndIDs[i][0])
			return valuesAndIDs[i][1];
	}

	return 105;

}

#endif