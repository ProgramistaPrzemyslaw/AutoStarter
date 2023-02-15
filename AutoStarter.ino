
#include "include/LED_display.h"
#include "include/handler.h"





#define MANUAL_BUTTON 15
#define AUTO_BUTTON 0
#define TIME_PIN 2


//extern const int digitPins[4];

XT_DAC_Audio_Class DAC(25,0);    

                                      
XT_Wav_Class autoSeq(mono8bit);
XT_Wav_Class manualSeq(start8bit);
XT_Wav_Class sins(sin1kHz);
XT_Wav_Class autoSeq_neg2dB(auto_neg2dB);
XT_Wav_Class hop_part(hop_3dB);
XT_Wav_Class whistle_part(whistle);
XT_Wav_Class naMiejsca(na_miejsca);

int startTimeMillis = 15000;
int selectedTime = 12340;
bool wasPlayed = false;

bool wasAuto = false;
bool wasManual = true;

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
  pinMode(TIME_PIN, INPUT);
  delay(1);                             
}

void loop() {
  DAC.FillBuffer();                
  


  if(digitalRead(AUTO_BUTTON) == LOW && digitalRead(TIME_PIN) == HIGH && autoButtonState == false){
    autoFinish = !autoFinish;
    autoButtonState = true;
    Serial.println("LOW");
    wasAuto = true;
  
  }

  if(digitalRead(AUTO_BUTTON) == LOW && digitalRead(TIME_PIN) == LOW && autoButtonState == true){
    autoButtonState = false;
    Serial.println("HIGH");
  }

  if(digitalRead(MANUAL_BUTTON) == LOW && manualButtonState == false){
    manualButtonState = true;
    manualFinish = manualSequence(DAC, hop_part, manualSeqStruct);
    wasManual = true;
   // manualFinish = !manualFinish;
  }

  if(digitalRead(MANUAL_BUTTON) == HIGH && manualButtonState == true){
    manualButtonState = false;
  }

  if(digitalRead(TIME_PIN) == LOW && timeButtonState == false){
    
    if(wasManual == true)
    selectedTime = measureTime(manualSeqStruct);

    if(wasAuto == true)
    selectedTime = measureTime(sequence);
    
    wasAuto = false;
    wasManual = false;

    

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