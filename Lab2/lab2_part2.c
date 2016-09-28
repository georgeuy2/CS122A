/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/27/2016 21:47:33 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[3];

const unsigned char tasksNum = 3;
const unsigned long periodBlink500 = 500;
const unsigned long periodBlink1000 = 1000;
const unsigned long periodBlink2500 = 2500;

const unsigned long tasksPeriodGCD = 500;

int TickFct_Blink500(int state);
int TickFct_Blink1000(int state);
int TickFct_Blink2500(int state);

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
   tasks[i].period = periodBlink500;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Blink500;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodBlink1000;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Blink1000;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodBlink2500;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Blink2500;

   ++i;
   TimerSet(tasksPeriodGCD);
   TimerOn();
   
   while(1) { Sleep(); }

   return 0;
}

enum SM1_States { SM1_Off, SM1_Blink_500 } SM1_State;
int TickFct_Blink500(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = SM1_Off;
         break;
      case SM1_Off:
         if (1) {
            state = SM1_Blink_500;
            B0=1;
         }
         break;
      case SM1_Blink_500:
         if (1) {
            state = SM1_Off;
            B0=0;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM1_Off:
         break;
      case SM1_Blink_500:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM1_State = state;
   return state;
}


enum SM2_States { SM2_Off, SM2_Blink_1000 } SM2_State;
int TickFct_Blink1000(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = SM2_Off;
         break;
      case SM2_Off:
         if (1) {
            state = SM2_Blink_1000;
            B2=1;
         }
         break;
      case SM2_Blink_1000:
         if (1) {
            state = SM2_Off;
            B2=0;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM2_Off:
         break;
      case SM2_Blink_1000:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM2_State = state;
   return state;
}


enum SM3_States { SM3_Off, SM3_Blink_2500 } SM3_State;
int TickFct_Blink2500(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = SM3_Off;
         break;
      case SM3_Off:
         if (1) {
            state = SM3_Blink_2500;
            B4=1;
         }
         break;
      case SM3_Blink_2500:
         if (1) {
            state = SM3_Off;
            B4=0;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM3_Off:
         break;
      case SM3_Blink_2500:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM3_State = state;
   return state;
}

