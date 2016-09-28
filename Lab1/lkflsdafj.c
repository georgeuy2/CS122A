/*
This code was automatically generated using the Riverside-Irvine State machine Builder tool
Version 2.7 --- 9/26/2016 17:1:59 PST
*/

#include "rims.h"

/*This code will be shared between state machines.*/
unsigned char bounce = 0;
unsigned char pattern = 0;
unsigned char song = 0;
typedef struct task {
   int state;
   unsigned long period;
   unsigned long elapsedTime;
   int (*TickFct)(int);
} task;

task tasks[4];

const unsigned char tasksNum = 4;
const unsigned long periodBounce_LED = 500;
const unsigned long periodPattern = 600;
const unsigned long periodSong = 100;
const unsigned long periodButtone_Listener = 200;

const unsigned long tasksPeriodGCD = 100;

int TickFct_Bounce_LED(int state);
int TickFct_Pattern(int state);
int TickFct_Song(int state);
int TickFct_Buttone_Listener(int state);

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
   tasks[i].period = periodBounce_LED;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Bounce_LED;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodPattern;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Pattern;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodSong;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Song;

   ++i;
   tasks[i].state = -1;
   tasks[i].period = periodButtone_Listener;
   tasks[i].elapsedTime = tasks[i].period;
   tasks[i].TickFct = &TickFct_Buttone_Listener;

   ++i;
   TimerSet(tasksPeriodGCD);
   TimerOn();
   
   while(1) { Sleep(); }

   return 0;
}

enum SM1_States { SM1_Wait, SM1_Bounce } SM1_State;
int TickFct_Bounce_LED(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
static unsigned char cnt = 0;
   switch(state) { // Transitions
      case -1:
         state = SM1_Wait;
         break;
      case SM1_Wait:
         if (bounce) {
            state = SM1_Bounce;
         }
         else if (!bounce) {
            state = SM1_Wait;
         }
         break;
      case SM1_Bounce:
         if (1) {
            state = SM1_Wait;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM1_Wait:
         break;
      case SM1_Bounce:
         B = 0;
         if(cnt == 0) {
         B0 = 1;
         }
         else if(cnt == 1) {
         B1 = 1;
         }
         else if(cnt == 2){
         B2 = 1;
         }
         else if(cnt == 3){
         B3 = 1;
         }
         else if(cnt == 4){
         B4 = 1;
         }
         else if(cnt == 5){
         B5 = 1;
         }
         else if(cnt == 6){
         B6 = 1;
         }
         else if(cnt == 7){
         B7 = 1;
         }
         if(A0 == 0){
         if(cnt == 7)
         cnt = 0;
         else 
         cnt++;
         }
         else if(A0 == 1){
         if(cnt == 0)
         cnt = 7;
         else
         cnt--;
         }
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM1_State = state;
   return state;
}


enum SM2_States { SM2_Wait, SM2_Pat, SM2_s3 } SM2_State;
int TickFct_Pattern(int state) {
   unsigned char arr[10] = {255, 85,  245, 95, 90, 170, 234, 250,  254, 25};
static unsigned char sz = 0;
   switch(state) { // Transitions
      case -1:
         sz = 0;
         state = SM2_s3;
         break;
      case SM2_Wait:
         if (pattern) {
            state = SM2_Pat;
            B = sz;
         }
         else if (!pattern) {
            state = SM2_s3;
         }
         break;
      case SM2_Pat:
         if (pattern) {
            state = SM2_Wait;
            sz++;

         }
         else if (!pattern) {
            state = SM2_s3;
         }
         break;
      case SM2_s3:
         if (pattern) {
            state = SM2_Wait;
         }
         else if (!pattern) {
            state = SM2_s3;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM2_Wait:
         break;
      case SM2_Pat:
         break;
      case SM2_s3:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM2_State = state;
   return state;
}


enum SM3_States { SM3_Wait, SM3_Song } SM3_State;
int TickFct_Song(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
unsigned char counter[] = {4,1,5,6,1,5,8,1,5, 2,2,2,2,2,1,1,1,1,1,1,1,1};
unsigned char songArray[] = {1, 2, 4,1,2,4,1,2,4, 0,1,2,4,8,9,0,9,0,9,0,9,0};
static unsigned char element = 0;
static unsigned char i =0;
unsigned char MAX_SIZE = 22;
   switch(state) { // Transitions
      case -1:
         state = SM3_Wait;
         break;
      case SM3_Wait:
         if (song) {
            state = SM3_Song;
         }
         break;
      case SM3_Song:
         if (i < counter[element]) {
            state = SM3_Song;
            B=songArray[element];
i++;

         }
         else if (i >= counter[element]) {
            state = SM3_Wait;
            i=0;
if(element < MAX_SIZE){
element++;
}
else if(!A3){
element=0;
B=0;
}
else if(element==22){
element=14;
}
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM3_Wait:
         break;
      case SM3_Song:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM3_State = state;
   return state;
}


enum SM4_States { SM4_Wait, SM4_button } SM4_State;
int TickFct_Buttone_Listener(int state) {
   /*VARIABLES MUST BE DECLARED STATIC*/
/*e.g., static int x = 0;*/
/*Define user variables for this state machine here. No functions; make them global.*/
   switch(state) { // Transitions
      case -1:
         state = SM4_Wait;
         break;
      case SM4_Wait:
         if (!A7 && !A6) {
            state = SM4_Wait;
            bounce = 1;
pattern = 0;
song=0;
         }
         else if (A7 || A6) {
            state = SM4_button;
            if(A7 && !A6){
bounce = 0;
pattern = 0;
song =1;
}
else if(!A7 && A6){
bounce = 0;
pattern = 1;
song =0;
}
         }
         break;
      case SM4_button:
         if (!A7 && !A6) {
            state = SM4_Wait;
            bounce = 1;
pattern = 0;
song =0;
         }
         else if (A7 || A6) {
            state = SM4_button;
         }
         break;
      default:
         state = -1;
      } // Transitions

   switch(state) { // State actions
      case SM4_Wait:
         break;
      case SM4_button:
         break;
      default: // ADD default behaviour below
         break;
   } // State actions
   SM4_State = state;
   return state;
}

