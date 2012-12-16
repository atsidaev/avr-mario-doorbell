#include "sound.h"

#define LOOP 0xff

PROGMEM const unsigned int FurElise[] =   
        {
            18, 1,
            n8,e2, n8,xd2, n8,e2, n8,xd2, n8,e2, n8,b1, n8,d2, n8,c2, n4,a1, n8,p, 
            n8,c1, n8,e1, n8,a1, n4,b1, n8,p, n8,e1, n8,xg1, n8,b1, n4,c2, n8,p, n8,e1, 
            n8,e2, n8,xd2, n8,e2, n8,xd2, n8,e2, n8,b1, n8,d2, n8,c2, n4,a1, n8,p, n8,c1, 
            n8,e1, n8,a1, n4,b1, n8,p, n8,e1, n8,c2, n8,b1, n4,a1, 
            0
        };


PROGMEM const unsigned int Mozart[] = 
        {
            16, 1,
            n16, xf1, n16, e1, n16,xd1, n16,e1, n4,g1, n16,a1, n16,g1, n16,xf1, n16,g1,
            n4,b1, n16,c2, n16,b1, n16,xa1, n16,b1, n16,xf2, n16,e2, n16,xd2, n16,e2, 
            n16,xf2, n16,e2, n16,xd2, n16,e2, n4,g2, n8,e2, n8,g2, n32,d2, n32,e2, 
            n16,xf2, n8,e2, n8,d2, n8,e2, n32,d2, n32,e2, n16,xf2, n8,e2, n8,d2, n8,e2, 
            n32,d2, n32,e2, n16,xf2, n8,e2, n8,d2, n8,xc2, n4,b1, 
            0
        };

PROGMEM const unsigned int Minuet[] = 
        {
            18, 1,
            n4,d2, n8,g1, n8,a1, n8,b1, n8,c2, n4,d2, n4,g1, n4,g1, n4,e2, n8,c2, 
            n8,d2, n8,e2, n8,xf2, n4,g2, n4,g1, n4,g1, n4,c2, n8,d2, n8,c2, n8,b1, 
            n8,a1, n4,b1, n8,c2, n8,b1, n8,a1, n8,g1, n4,xf1, n8,g1, n8,a1, n8,b1, 
            n8,g1, n4,b1, n2,a1, 
            0
        };


PROGMEM const unsigned int Sirene2[] = 
        {
            1, LOOP,
            ms(500), c2, ms(500), g2, 
            0
        };

//-----------------------------звуковой модуль----------------------------------
//указатели на регистры порта
#define PIN_SOUND (*(&PORT_SOUND-2))
#define DDR_SOUND (*(&PORT_SOUND-1))

//заглушка - пустая мелодия
PROGMEM unsigned int Empty[] = 
        {
            1, 1,
            n4, p,
            0
        };

PROGMEM unsigned int PROGMEM* melody[] = {Empty, FurElise, Mozart, Minuet, Sirene2};

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
  
  //настройка таймера T2
  TIMSK |= (1<<TOIE2);   
  TCCR2 = (0<<WGM01)|(0<<WGM00)|(0<<CS02)|(0<<CS01)|(1<<CS00);  //режим - нормал, прескалер - 
  TCNT2 = 0;    
  OCR2 = 0;
   
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
      TIMSK &= ~(1<<OCIE2);
      PORT_SOUND &= ~(1<<PINX_SOUND);
      break;
      
   /*команда воспроизведение*/
    case SOUND_PLAY:
      if (state == SOUND_PAUSE){
        state = SOUND_PLAY;          
        TIMSK |= (1<<OCIE2);
      }
      else {
      #ifndef SOUND_BPM  
        bpm = pgm_read_word(&(pSong[SOUND_BPM_SONG]));
      #endif
        indexNote = SOUND_START_SONG;
        repeat = pgm_read_word(&(pSong[SOUND_REPEAT_SONG]));
        durationNote = 0;
        state = SOUND_PLAY;          
        TIMSK |= (1<<OCIE2);        
      }
      break;  
      
      /*команда пауза*/ 
      case SOUND_PAUSE:
        state = SOUND_PAUSE;  
        TIMSK &= ~(1<<OCIE2);
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
   TIMSK |= (1<<OCIE2);       
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
        TIFR |=(1<<OCF2); //вот здесь сомнения
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
          TIMSK &= ~(1<<OCIE2); 
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
    OCR2 = tone;
    statReg |= (1<<SOUND_GEN);
  }
}

//прерывания таймера Т2_____________________________________
ISR(TIMER2_OVF_vect)
{
  SOUND_Duration();
  BUT_Debrief();
}


ISR(TIMER2_COMP_vect)
{
  SOUND_Tone();
}
