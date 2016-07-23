#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h> 
#include <avr/sleep.h>

#include "sound.h"

#define BUTTON DDB1

int main(void)
{
	/* Initial setup */
	cli();
	DDRB &= ~(1<<BUTTON);
	PORTB |= (1<<BUTTON);
	
	SOUND_Init();
	MCUCR &= ~((1 << ISC01) | (1 << ISC00));
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();

	/* Waiting for the door bell button press */
sleep:
	cli();
	GIMSK |= (1 << INT0); // enable INT0 diring the sleep_cpu execution
	sei();
	sleep_cpu();

	/* All code below is the interrupt handler (kinda) */
	/* The only reason to wake up is the button press. So if we are here, then we can start play melody without any additional checks. */
	GIMSK &= ~(1 << INT0); // disable INT0, we do not need it until next sleep

	while (1)
	{
		
		if (!(PINB & (1<<PINB1)))
		{
			SOUND_PlaySong(0);
			
			while (SOUND_GetStatus() == SOUND_PLAY)
			{
				// Running empty loop until the music stops
			}
		}
		else
			goto sleep;
	}
}

/* We do not perform any ISR handling routing because we already know that if we woke up, then the interrupt happened */
ISR(INT0_vect)
{
}
