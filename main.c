#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h> 
#include <avr/sleep.h>

#include "sound.h"

#define BUTTON DDB1

int main(void)
{
	cli();
	DDRB &= ~(1<<BUTTON);
	PORTB |= (1<<BUTTON);
	
	SOUND_Init();
	MCUCR &= ~((1 << ISC01) | (1 << ISC00));
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();

sleep:
	cli();
	GIMSK |= (1 << INT0); // enable INT0
	sei();
	sleep_cpu();
	GIMSK &= ~(1 << INT0); // disable INT0

	while (1)
	{
		
		if (!(PINB & (1<<PINB1)))
		{
			SOUND_PlaySong(0);
			
			while (SOUND_GetStatus() == SOUND_PLAY)
			{
			
			}
		}
		else
			goto sleep;
	}
}

ISR(INT0_vect)
{
}
