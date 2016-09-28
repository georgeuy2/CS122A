/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/26/2016 9:44:26 PST
*/

#include "rims.h"

/*Define user variables and functions for this state machine here.*/
unsigned char pattern2[3] = {255, 85, 170};
unsigned char pattern[9]={1,2,4,8,16,32,64,128, 3};
unsigned char counter[3]= {1, 2, 3};
unsigned char led = 0;
unsigned char trans=0;
unsigned char MAX_ARRAY = 8;
unsigned char time = 0;
unsigned char MIN_ARRAY = 0;
unsigned char SM1_Clk;
void TimerISR() {
   SM1_Clk = 1;
}

enum SM1_States { SM1_Wait, SM1_LED, SM1_Song } SM1_State;

TickFct_State_machine_1() {
   switch(SM1_State) { // Transitions
      case -1:
         SM1_State = SM1_Wait;
         break;
         case SM1_Wait: 
         if (1) {
            SM1_State = SM1_LED;
            if(A0 && trans < MAX_ARRAY){
            trans++;
            }
            else if (A0 && trans >= MAX_ARRAY){
            trans = MIN_ARRAY;
            }
            else if (!A0 && trans > MIN_ARRAY){
            trans--;
            }
            else if(!A0 && trans <= MIN_ARRAY) {
            trans = MAX_ARRAY;
            }
            B = pattern[trans];
            
            
         }
         else if (A2) {
            SM1_State = SM1_Song;
         }
         break;
      case SM1_LED: 
         if (1) {
            SM1_State = SM1_Wait;
         }
         break;
      case SM1_Song: 
         if (counter[trans] <=3) {
            SM1_State = SM1_Song;
            time = counter[trans];
            pattern[led];
            
         }
         break;
      default:
         SM1_State = SM1_Wait;
   } // Transitions

   switch(SM1_State) { // State actions
      case SM1_Wait:
         break;
      case SM1_LED:
         break;
      case SM1_Song:
         break;
      default: // ADD default behaviour below
      break;
   } // State actions

}

int main() {

   const unsigned int periodState_machine_1 = 500;
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