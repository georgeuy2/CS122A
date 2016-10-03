/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 10/2/2016 21:20:32 PST
*/

#include "usart_ATmega1284.h"
//#include "usart_ATmega32.h"
#include "FreeRTOS.h"
#include "task.h"
#include "croutine.h"
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


void init(){
	DDRD = 0xFF; PORTD = 0x00;		//output portD
	initUSART(0); // initializes USART0
	USART_Flush(0);
}


enum SM1_States { SM1_Start, SM1_OFF, SM1_ON } SM1_State;
unsigned char tempA = 0x00;

void TickFct_Blinking_LED() {
	
	switch(SM1_State) { // Transitions
		case SM1_Start:
			SM1_State = SM1_OFF;
		break;
		
		case SM1_OFF:
			if (1) {
			  SM1_State = SM1_ON;
			  if(USART_IsSendReady(0)){
				  while(USART_HasTransmitted(0)){
					tempA = 0;
					USART_Send(tempA,0);		// Sends tempA on USART0
				  }
			   }
			}
		break;
		
		case SM1_ON:
			if (1) {
			  SM1_State = SM1_OFF;
			  if(USART_IsSendReady(0)){
				  while(USART_HasTransmitted(0)){
					  tempA = 1;
					  USART_Send(tempA,0);		// Sends tempA on USART0
				  }
			  }
			}
		break;
		
		default:
			SM1_State = SM1_OFF;
	} // Transitions

	switch(SM1_State) { // State actions
		case SM1_Start:
		break;
		case SM1_OFF:
		break;
		case SM1_ON:
		break;
		default: // ADD default behaviour below
		break;
	} // State actions

}

void masterTask(){
	while(1){
		TickFct_Blinking_LED();
		vTaskDelay(1000);
	}
}

void StartSecPulse(unsigned portBASE_TYPE Priority){
	xTaskCreate( masterTask, (signed portCHAR *)"masterTask", configMINIMAL_STACK_SIZE, NULL, Priority, NULL);
}

int main() {
		init();	
		SM1_State = SM1_Start; // Initial state
		StartSecPulse(1);
		vTaskStartScheduler();
} // Main