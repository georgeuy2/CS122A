/* Partner(s) Name & Email: Gian Ocampo(gocam001@ucr.edu)
* Lab Section: 21
* Assignment: Lab 1 Exercise 5
* Exercise Description: Create a google doc that has a specification and diagrams for future people learning to program
state machines . Make it interesting and fun. Perhaps a game or a real application. Show and
demo to your TA.
*
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char score= 0;
unsigned char ledOn = 0;
unsigned char playerLife = 7;
unsigned char gameOver = 0;

typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[3];

const unsigned char tasksNum = 3;
const unsigned long periodBlink_LED = 400;
const unsigned long periodButton = 200;
const unsigned long periodLifeLED = 400;

const unsigned long tasksPeriodGCD = 200;

int TickFct_Blink_LED(int state);
int TickFct_Button(int state);
int TickFct_LifeLED(int state);

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
   tasks[i].state = -1;
   tasks[i].period = periodLifeLED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_LifeLED;

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
         if (!gameOver) {
            state = SM1_BlinkLED;
            B0=0;
ledOn = 0;
         }
         break;
      case SM1_BlinkLED:
         if (!gameOver) {
            state = SM1_Wait;
            B0=1;
ledOn = 1;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM1_Wait:
         break;
      case SM1_BlinkLED:
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
static unsigned char buttonPress = 0;
   switch(state) { // Transitions
      case -1:
         state = SM3_Wait;
         break;
      case SM3_Wait:
         if (!A0) {
            state = SM3_Wait;
         }
         else if (A0 && !gameOver) {
            state = SM3_Press;
            buttonPress = 1;
if(buttonPress == ledOn){
score++;
}
if(buttonPress != ledOn && playerLife!= 0){
//score--;
playerLife--;
}
if(playerLife == 0){
B = score;
gameOver = 1;
}
score << 1;
B = (B & 0xE1) | score;
         }
         break;
      case SM3_Press:
         if (1) {
            state = SM3_Release;
            buttonPress = 0;
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
         buttonPress = 1;
         if(buttonPress == ledOn){
         score++;
         }
         if(buttonPress != ledOn && playerLife!= 0){
         //score--;
         playerLife--;
         }
         if(playerLife == 0){
         B = score;
         gameOver = 1;
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


enum SM2_States { SM2_LifeLED, SM2_gameOver } SM2_State;
int TickFct_LifeLED(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
static unsigned char temp = 0;
   switch(state) { // Transitions
      case -1:
         state = SM2_LifeLED;
         break;
      case SM2_LifeLED:
         if (!gameOver) {
            state = SM2_LifeLED;
         }
         else if (gameOver) {
            state = SM2_gameOver;
         }
         break;
      case SM2_gameOver:
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM2_LifeLED:
         temp= playerLife << 5;
         B = (B & 0x1F) | temp;
         break;
      case SM2_gameOver:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM2_State = state;
   return state;
}

