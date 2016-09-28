/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/26/2016 16:51:26 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char bounceLED = 0;
unsigned char patSeq = 0;
unsigned char music = 0;
typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[4];

const unsigned char tasksNum = 4;
const unsigned long periodButtonListener = 1000;
const unsigned long periodBouncing_LED = 100;
const unsigned long periodPattern_Sequencer = 1000;
const unsigned long periodMusic = 100;

const unsigned long tasksPeriodGCD = 100;

int TickFct_ButtonListener(int state);
int TickFct_Bouncing_LED(int state);
int TickFct_Pattern_Sequencer(int state);
int TickFct_Music(int state);

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
   tasks[i].period = periodButtonListener;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_ButtonListener;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodBouncing_LED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Bouncing_LED;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodPattern_Sequencer;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Pattern_Sequencer;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodMusic;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Music;

   ++i;
   TimerSet(tasksPeriodGCD);
   TimerOn();
   
   while(1) { Sleep(); }

   return 0;
}

enum SM1_States { SM1_Wait, SM1_ButtonPress } SM1_State;
int TickFct_ButtonListener(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = SM1_Wait;
         break;
      case SM1_Wait:
         if (A7 || A6) {
            state = SM1_ButtonPress;
            if(A7 && !A6){
bounceLED = 0;
patSeq = 0;
music = 1;
//B = 4;
}
else if( !A7 && A6){ 
bounceLED = 0;
patSeq = 1;
music = 0;
//B=2;
}
         }
         else if (!A7 && !A6) {
            state = SM1_Wait;
            bounceLED = 1;
patSeq = 0;
music = 0;
//B=1;
         }
         break;
      case SM1_ButtonPress:
         if (!A7 && !A6) {
            state = SM1_Wait;
            bounceLED = 1;
patSeq = 0;
music = 0;
//B=1;
         }
         else if (A7 || A6) {
            state = SM1_ButtonPress;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM1_Wait:
         break;
      case SM1_ButtonPress:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM1_State = state;
   return state;
}


enum SM2_States { SM2_Wait, SM2_Increment, SM2_Decrement } SM2_State;
int TickFct_Bouncing_LED(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
unsigned char bounceArray [8] = {1, 3, 7, 15, 31, 63, 127, 255};
static unsigned char MAX_bounce = 0;
static unsigned char finishTask = 0;
static unsigned char led = 0;
   switch(state) { // Transitions
      case -1:
         state = SM2_Wait;
         break;
      case SM2_Wait:
         if (bounceLED) {
            state = SM2_Increment;
            MAX_bounce = 7;

         }
         break;
      case SM2_Increment:
         if (!bounceLED) {
            state = SM2_Wait;
            led = 0;
finishTask = 0;
         }
         else if (finishTask) {
            state = SM2_Decrement;
            finishTask = 0;
         }
         else if (!finishTask) {
            state = SM2_Increment;
            B= bounceArray[led];
if(led < MAX_bounce){
led++;
}
else{
finishTask = 1;
}
         }
         break;
      case SM2_Decrement:
         if (finishTask) {
            state = SM2_Increment;
            if(MAX_bounce >= 1){
MAX_bounce--;
}
finishTask = 0;
         }
         else if (!bounceLED) {
            state = SM2_Wait;
         }
         else if (!finishTask) {
            state = SM2_Decrement;
            B= bounceArray[led];
if(led >= 1){
led--;
}
else{
finishTask = 1;
}
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM2_Wait:
         break;
      case SM2_Increment:
         break;
      case SM2_Decrement:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM2_State = state;
   return state;
}


enum SM3_States { SM3_Wait, SM3_Pattern } SM3_State;
int TickFct_Pattern_Sequencer(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
unsigned char pattern[10] ={255, 85, 170, 15, 240, 195, 60, 102, 153, 24};
static unsigned char MAX_ARRAY = 10;
static unsigned char MIN_ARRAY = 0;
static unsigned char trans = 0;
   switch(state) { // Transitions
      case -1:
         state = SM3_Wait;
         break;
      case SM3_Wait:
         if (patSeq) {
            state = SM3_Pattern;
            trans = 0;
         }
         else if (!patSeq) {
            state = SM3_Wait;
         }
         break;
      case SM3_Pattern:
         if (patSeq) {
            state = SM3_Pattern;
            if(trans < MAX_ARRAY){
trans++;
}
else if(trans >= MAX_ARRAY){
trans = MIN_ARRAY;
}
else if(trans > MIN_ARRAY){
trans--;
}
else if(trans <= MIN_ARRAY){
trans = MAX_ARRAY;
}
B = pattern[trans];
         }
         else if (!patSeq) {
            state = SM3_Wait;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM3_Wait:
         break;
      case SM3_Pattern:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM3_State = state;
   return state;
}


enum SM4_States { SM4_Wait, SM4_Music, SM4_Counter } SM4_State;
int TickFct_Music(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
unsigned char musicLED[] = {1, 2, 4,1,2,4,1,2,4, 0,1,2,4,8,9,0,9,0,9,0,9,0};
unsigned char counter[] = {4,1,5,6,1,5,8,1,5, 2,2,2,2,2,1,1,1,1,1,1,1,1};
static  unsigned char element = 0;
static unsigned char i = 0;
unsigned char MAX_SIZE_MUSIC = 22;

   switch(state) { // Transitions
      case -1:
         state = SM4_Wait;
         break;
      case SM4_Wait:
         if (!music) {
            state = SM4_Wait;
         }
         else if (music) {
            state = SM4_Counter;
         }
         break;
      case SM4_Music:
         if (!music) {
            state = SM4_Wait;
            element = 0;
i = 0;
         }
         else if (music) {
            state = SM4_Counter;
         }
         break;
      case SM4_Counter:
         if (i >= counter[element] && music) {
            state = SM4_Music;
            i=0;
if(element < MAX_SIZE_MUSIC){
element++;
}
else if(element==22){
element=14;
}
         }
         else if (i < counter[element] && music) {
            state = SM4_Counter;
            B = musicLED[element];
i++;

         }
         else if (!music) {
            state = SM4_Wait;
            element = 0;
i = 0;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM4_Wait:
         break;
      case SM4_Music:
         break;
      case SM4_Counter:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM4_State = state;
   return state;
}

