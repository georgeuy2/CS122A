/* Partner(s) Name & Email:
* Lab Section: 21
* Assignment: Lab 2 Exercise 1
* Exercise Description: Blink three LEDs connected to PD0,PD2, and PD4 at a rate of 1000ms. Use only
one task to complete this functionality.
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

enum SM1_States { Start, SM1_Wait, SM1_LED } SM1_State;

void Init(){
	SM1_State = Start;
}

void TickFct_LED() {
	switch(SM1_State) { // Transitions
		case Start:
		SM1_State = SM1_Wait;
		break;
		case SM1_Wait:
		if (1) {
			SM1_State = SM1_LED;
		}
		break;
		case SM1_LED:
		if (1) {
			SM1_State = SM1_Wait;
		}
		break;
		default:
		SM1_State = SM1_Wait;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_Wait:
		PORTD=0;
		break;
		case SM1_LED:
		PORTD=0x15;
		break;
		default: // ADD default behaviour below
		break;
	} // State actions

}

void LEDTask(){
	
	Init();
	while(1){
		TickFct_LED();
		vTaskDelay(1000);
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