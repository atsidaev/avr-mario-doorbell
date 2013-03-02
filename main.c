#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h> 

#include "sound.h"

int main(void)
{

	SOUND_Init();
	sei();
	
	SOUND_PlaySong(0);

label:
	while (/*SOUND_GetStatus() == SOUND_PLAY*/1)
	{
		
	}
	SOUND_PlaySong(0);
	//goto label;
}
