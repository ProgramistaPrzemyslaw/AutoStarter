
#include "LED_display.h"
#include "handler.h"


#define MANUAL_BUTTON 0
#define AUTO_BUTTON 4
#define TIME_PIN 16


//extern const int digitPins[4];

XT_DAC_Audio_Class DAC(25,0);    

                                      
XT_Wav_Class autoSeq(mono8bit);
XT_Wav_Class manualSeq(start8bit);
XT_Wav_Class sins(sin1kHz);
XT_Wav_Class autoSeq_neg2dB(auto_neg2dB);
XT_Wav_Class hop_part(hop);
XT_Wav_Class whistle_part(whistle);
XT_Wav_Class naMiejsca(na_miejsca);

int startTimeMillis = 15000;
int selectedTime = 0;
bool wasPlayed = false;

bool currentState = false;
bool previousState = true;

bool autoFinish = true;
bool manualFinish = true;

bool autoButtonState = false;
bool manualButtonState = false;
bool timeButtonState = false;

autoSeqStruct sequence;
autoSeqStruct manualSeqStruct;

void setup() {
  Serial.begin(115200);
  Serial.println("starting");

  sequence.whistlePlayed = false;
  sequence.naMiejscaPlayed = false;
  sequence.hopPlayed = false;

  manualSeqStruct.hopPlayed = false;

  for(int i = 0; i <4; i++){
    pinMode(digitPins[i], OUTPUT);
  }

  pinMode(CLK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  pinMode(AUTO_BUTTON, INPUT_PULLUP);
  pinMode(MANUAL_BUTTON, INPUT_PULLUP);
  pinMode(TIME_PIN, INPUT_PULLUP);
  delay(1);                             
}

void loop() {
  DAC.FillBuffer();                
  


  if(digitalRead(AUTO_BUTTON) == LOW && autoButtonState == false){
    autoFinish = !autoFinish;
    autoButtonState = true;
    Serial.println("LOW");
  
  }

  if(digitalRead(AUTO_BUTTON) == HIGH && autoButtonState == true){
    autoButtonState = false;
    Serial.println("HIGH");
  }

  if(digitalRead(MANUAL_BUTTON) == LOW && manualButtonState == false){
    manualButtonState = true;
    manualFinish = manualSequence(DAC, hop_part, manualSeqStruct);
   // manualFinish = !manualFinish;
  }

  if(digitalRead(MANUAL_BUTTON) == HIGH && manualButtonState == true){
    manualButtonState = false;
  }

  if(digitalRead(TIME_PIN) == LOW && timeButtonState == false){
    
    
    measureTime(manualSeqStruct);

    measureTime(sequence);
    
    if(manualSeqStruct.measuredTime >= sequence.measuredTime){
      selectedTime = sequence.measuredTime;
    }else if(manualSeqStruct.measuredTime <= sequence.measuredTime){
      selectedTime = manualSeqStruct.measuredTime;
    }

    timeButtonState = true;
    
   // autoFinish = true;
  }

  if(digitalRead(TIME_PIN) == HIGH && timeButtonState == true){
    timeButtonState = false;
  }

//autoSequence(DAC, whistle_part, naMiejsca, hop_part, sequence);

  if(autoFinish == false){
    autoFinish = autoSequence(DAC, whistle_part, naMiejsca, hop_part, sequence);
  }else{
    sequence.whistlePlayed = false;
    sequence.naMiejscaPlayed = false;
    sequence.hopPlayed = false;  
  }

  if(manualFinish == true){
    manualSeqStruct.hopPlayed = false;
  }

  displayTime(selectedTime);
/*
  if(autoFinish){
    sequence.whistlePlayed = false;
    sequence.naMiejscaPlayed = false;
    sequence.hopPlayed = false;   
  }
  */

  if(millis() == startTimeMillis){
    Serial.println("Time has come");
  }

  

  /*
  if(millis()%500){
  Serial.print("finish status");
  Serial.println(autoFinish);
  }*/
 
}


/*
//sins.Playing==false
  if(wasPlayed==false && millis() >= startTimeMillis)
  { 

    sins.Speed=NORMAL_SPEED;
    DAC.Play(&sins);           // Set to play initially at normal speed  

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