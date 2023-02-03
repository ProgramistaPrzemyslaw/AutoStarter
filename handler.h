#pragma once
#include "Arduino.h"
#include "XT_DAC_Audio.h"
#include "untitled.h"
#include "start8bit.h"
#include "sekwencja_krotka8bit.h"
#include "mono8bit_sekw.h"
#include "sin1kHz.h"
#include "mono8bit_sekw_-2dB.h"
#include "buzz.h"
#include "whistle8bit.h"
#include "na_miejsca.h"

struct autoSeqStruct{
bool whistlePlayed;
bool naMiejscaPlayed;
bool hopPlayed;
int pauseOne;
int pauseTwo;
int measuredTime;
};

bool autoSequence(XT_DAC_Audio_Class &DAC, XT_Wav_Class &whistle, XT_Wav_Class &naMiejsca, XT_Wav_Class &hop, autoSeqStruct &sequence);
void manualSequence(XT_DAC_Audio_Class &DAC, XT_Wav_Class &hop, autoSeqStruct &sequence);
void measureTime();
void displayTime();
void resetStruct();