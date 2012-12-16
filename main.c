#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h> 

#include "sound.h"

int main(void)
{

	SOUND_Init();
	sei();
	
	SOUND_SetSong(0);
	SOUND_Com(SOUND_PLAY);
	while (1)
	{
		
	}
}
