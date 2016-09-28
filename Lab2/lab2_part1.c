/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/27/2016 21:24:45 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_Wait, SM1_LED } SM1_State;

TickFct_LED() {
   switch(SM1_State) { // Transitions
      case -1:
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
         B=0;
         break;
      case SM1_LED:
         B=0x15;
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodLED = 1000; // 1000 ms default
   TimerSet(periodLED);
   TimerOn();
   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_LED();
      while(!SM1_Clk);
      SM1_Clk = 0;
   } // while (1)
} // Main