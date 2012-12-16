#include "sound.h"

#define LOOP 0xff

#define A6 E2
#define B6 B2
#define C6 C2
#define D6 D2
#define E6 E2
#define F6 F2
#define G6 G2

#define Gx5 Gx2

#define A5 E1
#define B5 B1
#define C5 C1
#define D5 D1
#define E5 E1
#define F5 F1
#define G5 G1


#define NOTE(x,l) ms(l*2), x

PROGMEM const unsigned int FurElise[] =   
        {
            10, 1,
            NOTE(E6,59),
			NOTE(p,1),
			NOTE(E6,59),
			NOTE(p,61),
			NOTE(E6,59),
			NOTE(p,61),
			NOTE(C6,59),
			NOTE(p,1),
			NOTE(E6,119),
			NOTE(p,1),
			NOTE(G6,119),
			NOTE(p,121),
			NOTE(G5,119),
			NOTE(p,121),
			NOTE(C6,119),
			NOTE(p,61),
			NOTE(G5,59),
			NOTE(p,121),
			NOTE(E5,119),
			NOTE(p,61),
			NOTE(A5,59),
			NOTE(p,61),
			NOTE(A5,59),
			NOTE(p,61),
			NOTE(Gx5,59),
			NOTE(p,1),
			NOTE(A5,119),
			NOTE(p,1),
			NOTE(G5,79),
			NOTE(p,1),
			NOTE(E6,79),
			NOTE(p,1),
			NOTE(G6,79),
			NOTE(p,1),
			NOTE(A6,119),
			NOTE(p,1),
			NOTE(F6,59),
            //n8,e2, n8,xd2, n8,e2, n8,xd2, n8,e2, n8,b1, n8,d2, n8,c2, n4,a1, n8,p, 
            //n8,c1, n8,e1, n8,a1, n4,b1, n8,p, n8,e1, n8,xg1, n8,b1, n4,c2, n8,p, n8,e1, 
            //n8,e2, n8,xd2, n8,e2, n8,xd2, n8,e2, n8,b1, n8,d2, n8,c2, n4,a1, n8,p, n8,c1, 
            //n8,e1, n8,a1, n4,b1, n8,p, n8,e1, n8,c2, n8,b1, n4,a1, 
            0
        };


//-----------------------------звуковой модуль----------------------------------
//указатели на регистры порта
#define PIN_SOUND (*(&PORT_SOUND-2))
#define DDR_SOUND (*(&PORT_SOUND-1))

//заглушка - пустая мелодия
const PROGMEM unsigned int Empty[] = 
        {
            1, 1,
            n4, p,
            0
        };

PGM_P const melody[] PROGMEM = { FurElise };

//переменные звукового модуля
volatile static unsigned int *pSong;
volatile static unsigned char state = SOUND_STOP; 
volatile static unsigned int  durationNote = 0; 
volatile static unsigned int  toneNote = 0; 
volatile static unsigned char indexNote = 0;
volatile static unsigned char statReg = 0;
volatile static unsigned char repeat = 0;

#ifndef SOUND_BPM  
  static unsigned char bpm = 0;
#endif


//флаги
#define SOUND_VOLUME     0
#define SOUND_GEN        1

#define SOUND_BPM_SONG    0
#define SOUND_REPEAT_SONG 1
#define SOUND_START_SONG  2
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
  pSong = (unsigned int *)pgm_read_word(&(Empty));
  state = SOUND_STOP;
  durationNote = 0;
  toneNote = 0;
  repeat = 0;
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



//обработчик команд звукового модуля
 void SOUND_Com(unsigned char com)
{
unsigned char saveSreg = SREG;
  cli();
  switch (com){
    
    /*команда стоп:*/
    case SOUND_STOP:
      state = SOUND_STOP;
      TIMSK0 &= ~(1<<OCIE0A);
      PORT_SOUND &= ~(1<<PINX_SOUND);
      break;
      
   /*команда воспроизведение*/
    case SOUND_PLAY:
      if (state == SOUND_PAUSE){
        state = SOUND_PLAY;          
        TIMSK0 |= (1<<OCIE0A);
      }
      else {
      #ifndef SOUND_BPM  
        bpm = pgm_read_word(&(pSong[SOUND_BPM_SONG]));
      #endif
        indexNote = SOUND_START_SONG;
        repeat = pgm_read_word(&(pSong[SOUND_REPEAT_SONG]));
        durationNote = 0;
        state = SOUND_PLAY;          
        TIMSK0 |= (1<<OCIE0A);        
      }
      break;  
      
      /*команда пауза*/ 
      case SOUND_PAUSE:
        state = SOUND_PAUSE;  
        TIMSK0 &= ~(1<<OCIE0A);
      break;
      
    default:
      break;
  }
  SREG = saveSreg;
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
   repeat = pgm_read_word(&(pSong[SOUND_REPEAT_SONG]));
   durationNote = 0;
   state = SOUND_PLAY;          
   TIMSK0 |= (1<<OCIE0A);       
}

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
      durationNote = pgm_read_word(&(pSong[indexNote]));
      if (durationNote) {
#ifndef SOUND_BPM
        durationNote = durationNote/bpm;
#endif
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
        if (repeat == LOOP){
          indexNote = SOUND_START_SONG;
          durationNote = 0;
          return;
        }
        repeat--;
        if (!repeat){
          state = SOUND_STOP;
          TIMSK0 &= ~(1<<OCIE0A); 
          PORT_SOUND &= ~(1<<PINX_SOUND);
          return;
        }
        else{
          indexNote = SOUND_START_SONG;
          durationNote = 0;
        }
        
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
