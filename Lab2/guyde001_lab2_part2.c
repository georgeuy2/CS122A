/* Partner(s) Name & Email:
* Lab Section: 21
* Assignment: Lab 2 Exercise 2
* Exercise Description: BFrom the previous lab we had you implement three LEDs that blinked at different
rates. PD0 at a rate of 500ms, PD2 at a rate of 1000ms and PD4 at a rate of
2500ms. Implement the same functionality using the FreeRTOS library. Use multiple
tasks to complete this functionality and make them visible in your code.
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

//3 states
enum SM1_States { SM1_Start, SM1_Off, SM1_Blink_500 } SM1_State;
enum SM2_States { SM2_Start, SM2_Off, SM2_Blink_1000 } SM2_State;
enum SM3_States { SM3_Start, SM3_Off, SM3_Blink_2500 } SM3_State;

void Init(){
	SM1_State = SM1_Start;
	SM2_State = SM2_Start;
	SM3_State = SM3_Start;
}

void Blink500() {
	switch(SM1_State) { // Transitions
	  case SM1_Start:
		SM1_State = SM1_Off;
	  break;
      
	  case SM1_Off:
        if (1) {
	      SM1_State = SM1_Blink_500;
	      PORTD= (PORTD & 0xFE) | 0x01;	//changes the right most bits to 1 or 0
        }
      break;
      
	  case SM1_Blink_500:
        if (1) {
	      SM1_State = SM1_Off;
	      PORTD= (PORTD & 0xFE) | 0x00;
        }
      break;
      
	  default:
      SM1_State = SM1_Start;
      } // Transitions

      switch(SM1_State) { // State actions
	      case SM1_Off:
	      break;
	      case SM1_Blink_500:
	      break;
	      default: // ADD default behaviour below
	      break;
      }

}

void Blink1000() {
	/*VARIABLES MUST BE DECLARED STATIC*/
	/*e.g., static int x = 0;*/
	/*Define user variables for this state machine here. No functions; make them global.*/
	switch(SM2_State) { // Transitions
		case SM2_Start:
		SM2_State = SM2_Off;
		break;
		case SM2_Off:
		if (1) {
			SM2_State = SM2_Blink_1000;
			PORTD= (PORTD & 0xFB) | 0x04; //changes the 3rd LED to 1 or 0
		}
		break;
		case SM2_Blink_1000:
		if (1) {
			SM2_State = SM2_Off;
			PORTD= (PORTD & 0xFB) | 0x00;
		}
		break;
		default:
		SM2_State = SM2_Start;
	} // Transitions

	switch(SM2_State) { // State actions
		case SM2_Off:
		break;
		case SM2_Blink_1000:
		break;
		default: // ADD default behaviour below
		break;
	} 
}

void Blink2500() {
	/*Define user variables for this state machine here. No functions; make them global.*/
	switch(SM3_State) { // Transitions
		case SM3_Start:
		SM3_State = SM3_Off;
		break;
		case SM3_Off:
		if (1) {
			SM3_State = SM3_Blink_2500;
			PORTD= (PORTD & 0xEF) | 0x10; //changes the 5th LED to 1 or 0
		}
		break;
		case SM3_Blink_2500:
		if (1) {
			SM3_State = SM3_Off;
			PORTD= (PORTD & 0xEF) | 0x00;
		}
		break;
		default:
		SM3_State = SM3_Start;
	} // Transitions

	switch(SM3_State) { // State actions
		case SM3_Off:
		break;
		case SM3_Blink_2500:
		break;
		default: // ADD default behavior below
		break;
	} // State actions
}

//all the taks to be called
void Blink500_Task(){
	Init();
	while(1){
		Blink500();
		vTaskDelay(500);
	}
}

void Blink1000_Task(){
	Init();
	while(1){
		Blink1000();
		vTaskDelay(1000);
	}
}

void Blink2500_Task(){
Init();
while(1){
	Blink2500();
	vTaskDelay(2500);
}
}

//task create for each state machine
void StartSecPulse(unsigned portBASE_TYPE Priority){
	xTaskCreate( Blink500_Task, (signed portCHAR *)"Blink500_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL);
	xTaskCreate( Blink1000_Task, (signed portCHAR *)"Blink1000_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL);
	xTaskCreate( Blink2500_Task, (signed portCHAR *)"Blink2500_Task", configMINIMAL_STACK_SIZE, NULL, Priority, NULL);
}
int main() {
	DDRD = 0xFF; PORTD = 0x00; //output in port D
	
	StartSecPulse(1);
	vTaskStartScheduler();
} // Main