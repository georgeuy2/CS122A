/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/27/2016 23:37:45 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char led = 1;
unsigned char reverse = 0;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_Shift_LED } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Shift_LED;
         break;
         case SM1_Shift_LED: 
         if (1) {
            SM1_State = SM1_Shift_LED;
            B = led;
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

int main() {

   const unsigned int periodState_machine_1 = 200;
   TimerSet(periodState_machine_1);
   TimerOn();
   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_State_machine_1();
      while(!SM1_Clk);
      SM1_Clk = 0;
   } // while (1)
} // Main