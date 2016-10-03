/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 10/2/2016 21:20:32 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_OFF, SM1_ON } SM1_State;

TickFct_Blinking_LED() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_OFF;
         break;
         case SM1_OFF: 
         if (1) {
            SM1_State = SM1_ON;
            B=0;
         }
         break;
      case SM1_ON: 
         if (1) {
            SM1_State = SM1_OFF;
            B=1;
         }
         break;
      default:
         SM1_State = SM1_OFF;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_OFF:
         break;
      case SM1_ON:
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodBlinking_LED = 1000; // 1000 ms default
   TimerSet(periodBlinking_LED);
   TimerOn();
   
   SM1_State = -1; // Initial state
   B = 0; // Init outputs

   while(1) {
      TickFct_Blinking_LED();
      while(!SM1_Clk);
      SM1_Clk = 0;
   } // while (1)
} // Main