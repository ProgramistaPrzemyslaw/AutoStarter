#include "handler.h"

bool autoSequence(XT_DAC_Audio_Class &DAC, XT_Wav_Class &whistle, XT_Wav_Class &naMiejsca, XT_Wav_Class &hop, autoSeqStruct &sequence){


bool finished = false;
bool wasPlayed = false;
if(sequence.whistlePlayed == false){
    DAC.Play(&whistle);
    sequence.pauseOne = millis()+3200;
    sequence.whistlePlayed = true;
    Serial.println("whistle");
}else if(sequence.whistlePlayed == true && millis() >= sequence.pauseOne && sequence.naMiejscaPlayed == false){
    DAC.StopAllSounds();
    DAC.Play(&naMiejsca);
    sequence.pauseTwo = millis()+2500;
    sequence.naMiejscaPlayed = true;
    Serial.println("set");
}else if(sequence.naMiejscaPlayed == true && millis() >= sequence.pauseTwo && sequence.hopPlayed == false){
    DAC.StopAllSounds();
    DAC.Play(&hop);
    sequence.hopPlayed = true;
    Serial.println("buzz");
}   

    if(sequence.hopPlayed == true && millis() >= sequence.pauseTwo + 134){ //134 is exact duration of sound
        finished = true; 
        Serial.println("czemu to tu jest?");
    }else{
        finished = false;
    }

    return finished;

}


void manualSequence(XT_DAC_Audio_Class &DAC, XT_Wav_Class &hop, autoSeqStruct &sequence){

}