#include "sound.h"

/*
  Comments are in Russian because I copypasted most of this file from Russian forum
  http://electronix.ru/forum/lofiversion/index.php/t99525.html
  (thanks to Sergey529)
*/

#define LOOP 0xff

#define A6 A2
#define B6 B2
#define C6 C2
#define D6 D2
#define E6 E2
#define F6 F2
#define G6 G2

#define Gx5 Gx2
#define Ax6 Ax2
#define Ax5 Ax1

#define A5 E1
#define B5 B1
#define C5 C1
#define D5 D1
#define E5 E1
#define F5 F1
#define G5 G1

#define NOTE(x,l) ms(l), (x == P ? P : x * 71 / 10)

PROGMEM const unsigned int SuperMario[] =   
{
		NOTE(f(1318), 131),
		NOTE(f(1318), 131),
		NOTE(P, 75),
		NOTE(f(1318), 262),
		NOTE(f(1046), 131),
		NOTE(f(1318), 262),
		NOTE(f(1567), 262),
		NOTE(P, 300),
		NOTE(f(783), 262),
		NOTE(P, 300),
		
		NOTE(f(1046), 262),
		NOTE(P, 150),
		NOTE(f(783), 262),
		NOTE(P, 150),
		NOTE(f(659), 262),
		NOTE(P, 150),
		NOTE(f(880), 262),
		NOTE(f(987), 262),
		NOTE(f(932), 131),
		NOTE(f(880), 262),
		NOTE(f(783), 196),
		
		NOTE(f(1318), 131),
		NOTE(f(1567), 131),
		NOTE(f(1760), 262),
		NOTE(P, 30),
		NOTE(f(1396), 131),
		NOTE(f(1567), 262),
		NOTE(P, 15),
		NOTE(f(1318), 262),
		NOTE(P, 15),
		NOTE(f(1046), 131),
		NOTE(f(1174), 131),
		NOTE(f(987), 262),
		
		NOTE(P, 150),
		NOTE(f(1046), 262),
		NOTE(P, 150),
		NOTE(f(783), 262),
		NOTE(P, 150),
		NOTE(f(659), 262),
		NOTE(P, 150),
        0
};


//-----------------------------звуковой модуль----------------------------------
//указатели на регистры порта
#define PIN_SOUND (*(&PORT_SOUND-2))
#define DDR_SOUND (*(&PORT_SOUND-1))

PGM_P const melody[] PROGMEM = { SuperMario };

//переменные звукового модуля
volatile static unsigned int *pSong;
volatile static unsigned char state = SOUND_STOP; 
volatile static unsigned int  durationNote = 0; 
volatile static unsigned int  toneNote = 0; 
volatile static unsigned char indexNote = 0;
volatile static unsigned char statReg = 0;

#ifndef SOUND_BPM  
  static unsigned char bpm = 0;
#endif


//флаги
#define SOUND_VOLUME     0
#define SOUND_GEN        1

#define SOUND_START_SONG  0
#define SOUND_COUNTER_CAP 256
#define SOUND_PROG_COUNTER 31
  
//инициализация звукового модуля
void SOUND_Init(void)
{
  //настройка вывода мк на выход
  PORT_SOUND &= ~(1<<PINX_SOUND);
  DDR_SOUND |= (1<<PINX_SOUND);
  
  //настройка таймера T0
  TIMSK0 |= (1<<TOIE0);   
  TCCR0A = (0<<WGM01)|(0<<WGM00);  //режим - нормал, прескалер - 
  TCCR0B = (0<<CS02)|(0<<CS01)|(1<<CS00);
  TCNT0 = 0;    
  OCR0A = 0;
   
  //инициализация переменных
  pSong = (unsigned int *)pgm_read_word(&(SuperMario));
  state = SOUND_STOP;
  durationNote = 0;
  toneNote = 0;
  indexNote = 0;
  statReg = 0;
#ifndef SOUND_BPM  
  bpm = 0;
#endif
}

void SOUND_SetSong(unsigned char numSong)
{
    if (numSong <= SOUND_AMOUNT_MELODY) {
      pSong = (unsigned int *)pgm_read_word(&(melody[numSong]));
    }
}

//проиграть мелодию под номером numSong
void SOUND_PlaySong(unsigned char numSong)
{
   if (numSong <= SOUND_AMOUNT_MELODY) {
      pSong = (unsigned int *)pgm_read_word(&(melody[numSong]));
   }
   #ifndef SOUND_BPM  
     bpm = pgm_read_word(&(pSong[SOUND_BPM_SONG]));
   #endif
   indexNote = SOUND_START_SONG;
   durationNote = 0;
   state = SOUND_PLAY;          
   TIMSK0 |= (1<<OCIE0A);       
}

int volatile durationCopy = 1;

inline static void SOUND_Duration(void)
{
  static unsigned char counter = 0;
  
  if (state == SOUND_PLAY){  
    if (durationNote){
       counter++;
       counter &= SOUND_PROG_COUNTER;
       if (!counter){
          durationNote--;   
       }
    }
    else {
		if (indexNote % 2 == 0 && durationCopy != 0)
		{
			toneNote = P;
			durationNote = durationCopy >> 2;
			durationCopy = 0;
			statReg &= ~(1<<SOUND_VOLUME);
			TIFR0 |=(1<<OCF0A); //вот здесь сомнения
			return;
		}
		
      durationNote = pgm_read_word(&(pSong[indexNote]));
      if (durationNote) {
#ifndef SOUND_BPM
        durationNote = durationNote/bpm;
#endif
        durationCopy = durationNote;
        indexNote++;
        toneNote = pgm_read_word(&(pSong[indexNote]));
        if (toneNote!=P) {
          statReg |= (1<<SOUND_VOLUME);
        }
        else{
          statReg &= ~(1<<SOUND_VOLUME);
        }
        indexNote++;
        TIFR0 |=(1<<OCF0A); //вот здесь сомнения
      }
      else{
          state = SOUND_STOP;
          TIMSK0 &= ~(1<<OCIE0A); 
          PORT_SOUND &= ~(1<<PINX_SOUND);
          return;
      }
    }
 }

}


inline static void SOUND_Tone(void)
{
  static unsigned int tone = 0;
  
  if (statReg & (1<<SOUND_GEN)){
    if (statReg & (1<<SOUND_VOLUME)){
       PORT_SOUND ^= (1<<PINX_SOUND);
    }
    tone = toneNote;
    statReg &= ~(1<<SOUND_GEN);
  }

  if (tone > SOUND_COUNTER_CAP) {
    tone -= SOUND_COUNTER_CAP;
  }
  else {
    OCR0A = tone;
    statReg |= (1<<SOUND_GEN);
  }
}

unsigned char SOUND_GetStatus()
{
	return state;
}

//прерывания таймера Т2_____________________________________
ISR(TIM0_OVF_vect)
{
  SOUND_Duration();
  //BUT_Debrief();
}

ISR(TIM0_COMPA_vect)
{
  SOUND_Tone();
}

