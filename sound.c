#include "sound.h"

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

//~ E,E,E,C,E,G,G,C,G,E,A,B,A#,G,E,G,A,F,G,E ,C,D,B,C,G,E,A,B,A#, G,E,G,A,F,G,E,C,D,B

//~ G,F#,F,D#,E,G#,A,,C,A,C,D,G,F#,F,E,C,C,C ,G ,F#, F,D#,E,G#A,C,A,C,D,D#,D,C

//~ C,C,C,C,D,E,C,A,G,C,C,C,C,D,E,C,C,C,C,D, E,C, A,G,E,E,E,C,E,G,G,E,C,G,G#,A,F,F,A,B,A,A , A,G, F,E,C,A,G,E,C,G,G#,A,F,F,A,B,F,F,F,E,D,C

//const char simpsons[] PROGMEM = "d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6";

PROGMEM const unsigned int FurElise[] =   
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
	NOTE(f(1396), 131),
	NOTE(f(1567), 262),
	NOTE(f(1318), 262),
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
	//~ NOTE(f(880), 262),
	//~ NOTE(f(987), 262),
	//~ NOTE(f(932), 131),
	//~ NOTE(f(880), 262),
	//~ NOTE(f(783), 196),
	//~ NOTE(f(1318), 131),
	//~ NOTE(f(1567), 131),
	//~ NOTE(f(1760), 262),








           
           //~ NOTE(E6,16),
			//~ NOTE(E6,16),
			//~ NOTE(P,32),
			//~ NOTE(E6,8),
			//~ NOTE(C6,16),
			//~ NOTE(E6,8),
			//~ NOTE(G6,8),
			//~ NOTE(P,8),
			//~ NOTE(G6,8),
			//~ NOTE(P,8),
			//~ NOTE(C6,8),
			//~ NOTE(P,16),
			//~ NOTE(G6,8),
			//~ NOTE(P,16),
			//~ NOTE(E6,8),
			//~ NOTE(P,16),
			//~ NOTE(A6,8),
			//~ NOTE(B6,8),
			//~ NOTE(Ax6,16),
			//~ NOTE(A6,8),
			//~ NOTE(G6,16),
			//~ NOTE(E6,16),
			//~ NOTE(G6,16),
			//~ NOTE(A6,8),
			//~ NOTE(F6,16),
			//~ NOTE(G6,8),
			//~ NOTE(E6,8),
			//~ NOTE(C6,16),
			//~ NOTE(D6,16),
			//~ NOTE(B6,8),
			//~ NOTE(P,16),
			//~ NOTE(C6,8),
			//~ NOTE(P,16),
			//~ NOTE(G6,8),
			//~ NOTE(P,16),
			//~ NOTE(E6,8),
			//~ NOTE(P,16),
			//~ NOTE(A,8),
			//~ NOTE(B,8),
			//~ NOTE(A#,16),
			//~ NOTE(A,8),
			//~ NOTE(G.,16),
			//~ NOTE(E6,16),
			//~ NOTE(G6,16),
			//~ NOTE(A6,8),
			//~ NOTE(F6,16),
			//~ NOTE(G6,8),
			//~ NOTE(E6,8),
			//~ NOTE(C6,16),
			//~ NOTE(D6,16),
			//~ NOTE(B,8),
			//~ NOTE(P,8),
			//~ NOTE(G6,16),
			//~ NOTE(F#6,16),
			//~ NOTE(F6,16),
			//~ NOTE(D#6,16),
			//~ NOTE(P,16),
			//~ NOTE(E6,16),
			//~ NOTE(P,16),
			//~ NOTE(G#,16),
			//~ NOTE(A,16),
			//~ NOTE(C6,16),
			//~ NOTE(P,16),
			//~ NOTE(A,16),
			//~ NOTE(C6,16),
			//~ NOTE(D6,16),
			//~ NOTE(P,8),
			//~ NOTE(G6,16),
			//~ NOTE(F#6,16),
			//~ NOTE(F6,16),
			//~ NOTE(D#6,16),
			//~ NOTE(P,16),
			//~ NOTE(E6,16),
			//~ NOTE(P,16),
			//~ NOTE(C7,16),
			//~ NOTE(P,16),
			//~ NOTE(C7,16),
			//~ NOTE(C7,16)
          
            //~ NOTE(p, 100),
            //~ NOTE(E6,59),
			//~ NOTE(p,10),
			//~ NOTE(E6,59),
			//~ NOTE(p,61),
			//~ NOTE(E6,59),
			//~ NOTE(p,61),
			//~ NOTE(C6,59),
			//~ NOTE(p,1),
			//~ NOTE(E6,119),
			//~ NOTE(p,1),
			//~ NOTE(G6,119),
			//~ NOTE(p,121),
			//~ NOTE(G5,119),
			//~ NOTE(p,121),
			//~ 
			//~ NOTE(C6,119),
			//~ NOTE(p,61),
			//~ NOTE(G5,59),
			//~ NOTE(p,121),
			//~ NOTE(E5,119),
			//~ NOTE(p,61),
			//~ NOTE(A5,59),
			//~ NOTE(p,61),
			//~ NOTE(B5,59),
			//~ NOTE(p,61),
			
			//~ NOTE(Ax5,59),
			//~ NOTE(p,61),
			//~ NOTE(Gx5,59),
			//~ NOTE(p,1),
			//~ NOTE(A5,119),
			//~ NOTE(p,1),
			//~ NOTE(G5,79),
			//~ NOTE(p,1),
			//~ NOTE(E6,79),
			//~ NOTE(p,1),
			//~ NOTE(G6,79),
			//~ NOTE(p,1),
			//~ NOTE(A6,119),
			//~ NOTE(p,1),
			//~ NOTE(F6,59),
			//~ 
            //~ n8,e2, n8,xd2, n8,e2, n8,xd2, n8,e2, n8,b1, n8,d2, n8,c2, n4,a1, n8,p, 
            //~ n8,c1, n8,e1, n8,a1, n4,b1, n8,p, n8,e1, n8,xg1, n8,b1, n4,c2, n8,p, n8,e1, 
            //~ n8,e2, n8,xd2, n8,e2, n8,xd2, n8,e2, n8,b1, n8,d2, n8,c2, n4,a1, n8,p, n8,c1, 
            //~ n8,e1, n8,a1, n4,b1, n8,p, n8,e1, n8,c2, n8,b1, n4,a1, 
            0
        };


//-----------------------------звуковой модуль----------------------------------
//указатели на регистры порта
#define PIN_SOUND (*(&PORT_SOUND-2))
#define DDR_SOUND (*(&PORT_SOUND-1))

PGM_P const melody[] PROGMEM = { FurElise };

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
  pSong = (unsigned int *)pgm_read_word(&(FurElise));
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

