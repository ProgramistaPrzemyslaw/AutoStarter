#pragma once
#include "Arduino.h"

#define CLK_PIN 21
#define LATCH_PIN 22
#define DATA_PIN 23
#define MAX_TIME_SEC 99999



const int digitPins[4] = {17, 5, 18, 19};
static int digitNum = 0;
static int digitBuffer[4] = {0,0,0,0};
const byte digitReg[] = {
  B00111111, //0
  B00000110, //1
  B01011011, //2
  B01001111, //3
  B01100110, //4
  B01101101, //5
  B01111101, //6
  B00000111, //7
  B01111111, //8
  B01101111  //9
};

void displayTime(int time);