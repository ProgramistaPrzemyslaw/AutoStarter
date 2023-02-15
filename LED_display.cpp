#include "include/LED_display.h"
#include "include/handler.h"

void displayTime(int time){
    digitBuffer[0] = time/10000;
    digitBuffer[1] = (time%10000)/1000;
    digitBuffer[2] = (time%1000)/100;
    digitBuffer[3] = (time%100)/10;

    
    for(byte i = 0; i < 4; i++){
        digitalWrite(digitPins[i],LOW);
    }

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, B11111111);
    digitalWrite(LATCH_PIN, HIGH);

    //delayMicroseconds(100);
    digitalWrite(digitPins[digitNum],HIGH);

    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, ~digitReg[digitBuffer[digitNum]]);
    digitalWrite(LATCH_PIN, HIGH);


    if(digitNum>3)
    digitNum = 0;
    else 
    digitNum ++;

    
}
