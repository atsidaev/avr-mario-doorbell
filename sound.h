//***************************************************************************
//
//  Author(s)...: Pashgan  http://ChipEnable.Ru
//
//  Target(s)...: atmega
//
//  Compiler....: GNU GCC
//
//  Description.: Звуковой модуль
//
//  Data........: 13.03.2011
//
//***************************************************************************
#ifndef SOUND_H
#define SOUND_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

//*************************** настройки *************************************

#define SOUND_BPM       24  //если закомментировать длительность нот будет 
                              //расчитываться из заданного в мелодии BPM`а

#define SOUND_TIM_PRE   1U  //зачение предделителя таймера 

#include "tone.h"   //здесь определены частота и длительности нот

//пин мк на котором будет генериться звук
#define PORT_SOUND PORTB
#define PINX_SOUND 0

//количество мелодий
#define SOUND_AMOUNT_MELODY 1

//***************************************************************************

//команды звукового модуля
#define SOUND_STOP      0
#define SOUND_PLAY      1
#define SOUND_PAUSE     2

//функции звукового модуля
void SOUND_Init(void);
void SOUND_Com(unsigned char com);
void SOUND_PlaySong(unsigned char numSong);
unsigned char SOUND_GetStatus();

#endif //SOUND_H
