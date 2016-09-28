/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/28/2016 11:24:3 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char reverse = 0;
typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[2];

const unsigned char tasksNum = 2;
const unsigned long periodLED = 200;
const unsigned long periodButton = 100;

const unsigned long tasksPeriodGCD = 100;

int TickFct_LED(int state);
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
   tasks[i].period = periodLED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_LED;

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

enum SM1_States { SM1_Shift_LED } SM1_State;
int TickFct_LED(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static unsigned char led = 1;

   switch(state) { // Transitions
      case -1:
         state = SM1_Shift_LED;
         break;
      case SM1_Shift_LED:
         if (1) {
            state = SM1_Shift_LED;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM1_Shift_LED:
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
         
         
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM1_State = state;
   return state;
}


enum SM2_States { SM2_Wait, SM2_Press, SM2_Release } SM2_State;
int TickFct_Button(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/

   switch(state) { // Transitions
      case -1:
         state = SM2_Wait;
         break;
      case SM2_Wait:
         if (!A0) {
            state = SM2_Wait;
         }
         else if (A0) {
            state = SM2_Press;
         }
         break;
      case SM2_Press:
         if (1) {
            state = SM2_Release;
         }
         break;
      case SM2_Release:
         if (!A0) {
            state = SM2_Wait;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
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
   SM2_State = state;
   return state;
}

