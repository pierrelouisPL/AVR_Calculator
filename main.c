#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "8seg.h"
#include "keyboard.h"

enum inputStatus {first, second, res};
enum operation {add, substract, none};

int numSum = 0;
int presentDigit = 0; // 0,1,2,3
int displayedDigits[4];

enum inputStatus status = first;
enum operation operationPending = none;

int numDisplayed() {
	int n = 0;
	// could be replaced with a loop
	n += displayedDigits[0];
	n += displayedDigits[1] * 10;
	n += displayedDigits[2] * 100;
	n += displayedDigits[3] * 1000;

	return n;
}

/* this is the function we use when we display a sum at the end of the calculations
 * this is NOT to display the given int
 * but to assign this int to displayedDigits[] array
 * we utilize the fact that displayedDigits[] is a global var. maybe it's not the prettiest solution
 * but for this application it seems appropriate */
void updateDisplayedDigits(int input) {
	displayedDigits[0] = (input%10) / 1;
	displayedDigits[1] = (input%100) / 10;
	displayedDigits[2] = (input%1000) / 100;
	displayedDigits[3] = (input%10000) / 1000;
}

void clearDisplayedDigits() {
	for (int i = 0; i < 4; i++) {
		displayedDigits[i] = 0;
	}
}

void waitForRelease() {
	// when the key is pressed we don't want to proceed
	// so we wait until it is released
	while(pressedKey() != 100) {
		// in this time we still want to show the num on the display
		displayDigits(displayedDigits);
	}
}

int main() {

	displayPinSetup();
	adcSetup();

	//keyboard setup
	PINC |= (1 << PC0);

	numSum = 0;
	presentDigit = 0;
	clearDisplayedDigits();
	status = first;
	operationPending = none;

	while(1) {

		// if something pressed (code 100 means that no key is pressed)
		 if (pressedKey() != 100) {

			/* very important
			 * if the result is currently displayed
			 * we don't show it when new input is started
			 * so if a number key is pressed -> it starts a new input
			 * with a prev res as a pres numSum
			 * if a f. key is pressed -> we go to the second input
			 */
			
			// digit key
			if (pressedKey() < 100) {
				//if res displayed
				if (status == res) {
					// reset screen
					clearDisplayedDigits();
					numSum = 0;
					status = first;
				}
				//if already all digits taken, do nothing
				if (presentDigit >= 4) ;
				//if not we add the digit to the displayed number
				else {
					//we move every digit onscreen to the left by 1 place
					for (int i = presentDigit; i > 0; i--) {
						displayedDigits[i] = displayedDigits[i-1];
					}
					//we write input to the 0th digit (10^0)
					displayedDigits[0] = pressedKey();
					presentDigit++;
					waitForRelease();
				}
			}

			// a function key
			else if (pressedKey() > 100) {
				// first our reaction to res
				if (status == res) {
					clearDisplayedDigits();
					//numSum remains unchanged
				}

               	//  *******************  C   => we clear basically everything
               	if (pressedKey() == 103) {
               		clearDisplayedDigits();
               		numSum = 0;
               		presentDigit = 0;
               		status = first;
               		waitForRelease();
               	}

               	//  *******************  CE   *****************************
               	
               	if (pressedKey() == 105) {
               		clearDisplayedDigits();
               		presentDigit = 0;
               		waitForRelease();
               	}

               	// *******************  =   *****************************
               	if (pressedKey() == 104) {
               		
               		if (operationPending == add) {
               			numSum += numDisplayed();
               			updateDisplayedDigits(numSum);
               			status = res;

               		}

               		else if (operationPending == substract) {
               			numSum -= numDisplayed();
               			updateDisplayedDigits(numSum);
               			status = res;
               		}

               		// e.g. if u press = during 1st input
               		else {// (operationPending == none) 
               			// do nothing
               		}

               		waitForRelease();
               	}

               	//  *******************   +  *****************************
               	if (pressedKey() == 101) {

               		if ((status == second) && (operationPending == substract)) {
               			numSum -= numDisplayed();
               		}

               		else { // status == first || operationPending == add
               			numSum += numDisplayed();
               		}

               		operationPending = add;
               		status = second;      	
               		presentDigit = 0;
               		waitForRelease();
               		clearDisplayedDigits();
               	}

               	//  *******************   -  *****************************
               	if (pressedKey() == 102) {

               		if ((status == second) && (operationPending == substract)) {
               			numSum -= numDisplayed();
               		}

               		else { // status == first || operationPending == add
               			numSum += numDisplayed();
               		}

               		operationPending = substract;
               		status = second;      	
               		presentDigit = 0;
               		waitForRelease();
               		clearDisplayedDigits();
               	}
			}

			// error message (extremely unlikely to happen)
			else {
				// I
				int errorMessage[4] = {9,9,9,8};
				displayDigits(errorMessage);
			}
		}

		//we still have to display the number if nothing happens
		displayDigits(displayedDigits);
	}

	return 0;
}