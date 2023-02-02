// Playing a digital WAV recording repeatedly at different play-back speeds
// using the XTronical DAC Audio library
// plays first at normal speed, then fast, then slow and then repeats
// See www.xtronical.com for write ups on sound, the hardware required and how to make
// the wav files and include them in your code

#include "handler.h"

#define MANUAL_BUTTON 0
#define AUTO_BUTTON 4

XT_DAC_Audio_Class DacAudio(25,0);      // Create the main player class object. 
                                        // Use GPIO 25, one of the 2 DAC pins and timer 0
                                      
//XT_Wav_Class autoSeq(start8bit);     // create an object of type XT_Wav_Class that is used by 
XT_Wav_Class autoSeq(mono8bit);
XT_Wav_Class manualSeq(start8bit);
XT_Wav_Class sins(sin1kHz);
XT_Wav_Class autoSeq_neg2dB(auto_neg2dB);
XT_Wav_Class hop_part(hop);
XT_Wav_Class whistle_part(whistle);
XT_Wav_Class naMiejsca(na_miejsca);

int startTimeMillis = 15000;
bool wasPlayed = false;

bool currentState = false;
bool previousState = true;
bool isFinished = true;
bool buttonState = false;

autoSeqStruct sequence;
autoSeqStruct manualSeqStruct;

void setup() {
  Serial.begin(115200);
  Serial.println("starting");

  sequence.whistlePlayed = false;
  sequence.naMiejscaPlayed = false;
  sequence.hopPlayed = false;
  sequence.pauseOne = 2000;
  sequence.pauseTwo = 500;

  manualSeqStruct.hopPlayed = false;

  pinMode(AUTO_BUTTON, INPUT_PULLUP);
  pinMode(MANUAL_BUTTON, INPUT_PULLUP);
  delay(1);                             // Allow system to settle, otherwise garbage can play for first second
}

void loop() {
  DacAudio.FillBuffer();                // Fill the sound buffer with data, required once in your main loop
  
  if(isFinished){
    sequence.whistlePlayed = false;
    sequence.naMiejscaPlayed = false;
    sequence.hopPlayed = false;   
  }
  
  previousState = currentState;

  if(digitalRead(AUTO_BUTTON) == LOW && buttonState == false){
    currentState = !currentState;
    isFinished = !isFinished;
    buttonState = true;
    Serial.println("LOW");
   // isFinished = true;
  }

  if(digitalRead(AUTO_BUTTON) == HIGH && buttonState == true){
    buttonState = false;
    Serial.println("HIGH");
  }

//autoSequence(DacAudio, whistle_part, naMiejsca, hop_part, sequence);

  if(isFinished == false){
  isFinished = autoSequence(DacAudio, whistle_part, naMiejsca, hop_part, sequence);
  }

  if(millis() == startTimeMillis){
    Serial.println("Time has come");
  }

  

  /*
  if(millis()%500){
  Serial.print("finish status");
  Serial.println(isFinished);
  }*/
 
}


/*
//sins.Playing==false
  if(wasPlayed==false && millis() >= startTimeMillis)
  { 

    sins.Speed=NORMAL_SPEED;
    DacAudio.Play(&sins);           // Set to play initially at normal speed  

    Serial.print("w if "); 
    Serial.println(sins.Playing);  
    
    if(sins.TimeLeft == 0){
      Serial.println("zagrane");
    }
    wasPlayed = true;
   // SpeedIdx++;                         // Move to next position, ready for when this sample has completed 
  //delay(1000);
  }


*/