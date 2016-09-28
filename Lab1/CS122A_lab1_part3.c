/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/28/2016 9:42:12 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char score= 0;
unsigned char ledOn= 0;



typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[2];

const unsigned char tasksNum = 2;
const unsigned long periodBlink_LED = 250;
const unsigned long periodButton = 50;

const unsigned long tasksPeriodGCD = 50;

int TickFct_Blink_LED(int state);
int TickFct_Button(int state);

unsigned char processingRdyTasks = 0;
void TimerISR() {
   unsigned char i;
   if (processingRdyTasks) {
      printf("Period too short to complete tasks\n");
   }
   processingRdyTasks = 1;
   for (i = 0; i < tasksNum; ++i) { // Heart of scheduler code
      if ( tasks[i].elapsedTime >= tasks[i].period ) { // Ready
         tasks[i].state = tasks[i].TickFct(tasks[i].state);
         tasks[i].elapsedTime = 0;
      }
      tasks[i].elapsedTime += tasksPeriodGCD;
   }
   processingRdyTasks = 0;
}
int main() {
   // Priority assigned to lower position tasks in array
   unsigned char i=0;
   tasks[i].state = -1;
   tasks[i].period = periodBlink_LED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Blink_LED;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodButton;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Button;

   ++i;
   TimerSet(tasksPeriodGCD);
   TimerOn();
   
   while(1) { Sleep(); }

   return 0;
}

enum SM1_States { SM1_Wait, SM1_BlinkLED } SM1_State;
int TickFct_Blink_LED(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/

   switch(state) { // Transitions
      case -1:
         state = SM1_Wait;
         break;
      case SM1_Wait:
         if (1) {
            state = SM1_BlinkLED;
         }
         break;
      case SM1_BlinkLED:
         if (1) {
            state = SM1_Wait;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM1_Wait:
         ledOn = 0;
         B0=0;
         
         break;
      case SM1_BlinkLED:
         ledOn = 1;
         B0=1;
         
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM1_State = state;
   return state;
}


enum SM3_States { SM3_Wait, SM3_Press, SM3_Release } SM3_State;
int TickFct_Button(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/

   switch(state) { // Transitions
      case -1:
         state = SM3_Wait;
         break;
      case SM3_Wait:
         if (!A0) {
            state = SM3_Wait;
         }
         else if (A0) {
            state = SM3_Press;
            if(A0 == ledOn && score <= 254){
score++;
}
if(score > 0 && A0 != ledOn){
score--;
}
score << 1;
B = (B & 0xE1) | score;
         }
         break;
      case SM3_Press:
         if (1) {
            state = SM3_Release;
         }
         break;
      case SM3_Release:
         if (!A0) {
            state = SM3_Wait;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM3_Wait:
         break;
      case SM3_Press:
         if(A0 == ledOn && score <= 254){
         score++;
         }
         if(score > 0 && A0 != ledOn){
         score--;
         }
         score << 1;
         B = (B & 0xE1) | score;
         break;
      case SM3_Release:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM3_State = state;
   return state;
}

