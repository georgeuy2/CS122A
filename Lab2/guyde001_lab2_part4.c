/* Partner(s) Name & Email:
* Lab Section: 21
* Assignment: Lab 2 Exercise 4
* Exercise Description: (Challenge) Expand upon exercise 3 by adding a button which will reverse the
direction of the LED cycle whenever it is pressed. (Hint: Review priorities to
implement this.)
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

enum SM1_States { SM1_Start, SM1_Shift_LED} SM1_State;
enum SM2_States { SM2_Start, SM2_Wait, SM2_Press, SM2_Release } SM2_State;

//Global variable
unsigned char reverse = 0;
unsigned char b1 = 0x00;

void Init(){
	SM1_State = SM1_Start;
	SM2_State = SM2_Start;
}

void Shift_LED() {
	static unsigned char led = 1;
	   switch(SM1_State) { // Transitions
		   case SM1_Start:
		   SM1_State = SM1_Shift_LED;
		   break;
		   case SM1_Shift_LED:
		   if (1) {
			   SM1_State = SM1_Shift_LED;
		   }
		   break;
		   default:
		   SM1_State = SM1_Start;
		   break;
	   } // Transitions

	   switch(SM1_State) { // State actions
		   case SM1_Shift_LED:
		   
		   
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
		   PORTD = led;
		   
		   break;
		   default: // ADD default behaviour below
		   break;
	   }
} // Transitions


void Button() {
	b1 = ~PINA & 0x02;

	 switch(SM2_State) { // Transitions
		 case SM2_Start:
			SM2_State = SM2_Wait;
		 break;
		 
		 case SM2_Wait:
			if (!b1) {
			 SM2_State = SM2_Wait;
			}
			else if (b1) {
			 SM2_State = SM2_Press;
			}
		 break;
		 
		 case SM2_Press:
			if (1) {
			 SM2_State = SM2_Release;
			}
		 break;
		 
		 case SM2_Release:
			if (!b1) {
			 SM2_State = SM2_Wait;
			}
		 break;
		 
		 default:
			SM2_State = SM2_Start;
			break;
	 } // Transitions

	 switch(SM2_State) { // State actions
		 case SM2_Wait:
		 break;
		 
		 case SM2_Press:
			if(reverse == 1){
			 reverse = 0;
			}
			else if(reverse == 0){
			 reverse = 1;
			}
		 break;
		 
		 case SM2_Release:
		 break;
		 
		 default: // ADD default behaviour below
		 break;
	 } // State actions
}

void ShiftLED_Task(){
	while(1){
		Shift_LED();
		vTaskDelay(200);
	}
}

void Button_Task(){
	while(1){
		Button();
		vTaskDelay(100);
	}
}


void StartSecPulse(unsigned portBASE_TYPE Priority){
	xTaskCreate( ShiftLED_Task, (signed portCHAR *)"ShiftLED_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL);
	xTaskCreate( Button_Task, (signed portCHAR *)"Button_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL);
}
int main() {
	Init();
	DDRA = 0x00; PORTA = 0xFF;    //output
	DDRD = 0xFF; PORTD = 0x00;    //input
	
	StartSecPulse(1);
	vTaskStartScheduler();
} // Main