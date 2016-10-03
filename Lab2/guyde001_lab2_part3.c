/* Partner(s) Name & Email:
* Lab Section: 21
* Assignment: Lab 2 Exercise 3
* Exercise Description: Now we want to implement a state machine design where the LEDs will cycle
through each LED one after another. Once it reaches the last LED it will bounce and
go in the opposite direction. (Try simplifying your designs by using the shift operator.)
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/portpins.h>
#include <avr/pgmspace.h>

//FreeRTOS include files
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"

enum SM1_States { Start, SM1_Shift_LED} SM1_State;
//Global variables
unsigned char led = 1;
unsigned char reverse = 0;

void Init(){
	SM1_State = Start;
}

void TickFct_LED() {
	switch(SM1_State) { // Transitions
		case Start:
		SM1_State = SM1_Shift_LED;
		break;
		case SM1_Shift_LED:
		if (1) {
			SM1_State = SM1_Shift_LED;
			PORTD = led;
			if(led == 128){
				reverse = 1;
				led = led>>1;
			}
			else if(led == 1){
				reverse = 0;
				led = led << 1;
			}
			else if(reverse && led != 128 && led != 1){
				led = led >> 1;
			}
			else if( !reverse && led != 128 && led != 1){
				led = led << 1;
			}
		}
		break;
		default:
		SM1_State = SM1_Shift_LED;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_Shift_LED:
		break;
		default: // ADD default behaviour below
		break;
	} // State actions

}

void LEDTask(){
	
	Init();
	while(1){
		TickFct_LED();
		vTaskDelay(100);
	}
}

void StartSecPulse(unsigned portBASE_TYPE Priority){
	xTaskCreate( LEDTask, (signed portCHAR *)"LedTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL);
}
int main() {
	DDRD = 0xFF; PORTD = 0x00;
	
	StartSecPulse(1);
	vTaskStartScheduler();
} // Main