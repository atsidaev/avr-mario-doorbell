#include <stdio.h>
#include <stdlib.h>

/*
  PC application that converts notes of melody to the door bell frequencies.
  Build with gcc and simply execute.
*/

int notefreq[12] = {4186, 4434, 4698, 4978, 5274, 5587, 5919, 6271, 6644, 7040, 7458, 7902};

int note2freq(int note)
{
  return notefreq[note % 12] / (1 << (9 - (note / 12)));
}

void play( const char *song)
{
  char *p = (char *)song;
  int defdur = 4;
  int defscale = 6;
  int bpm = 63;

  // Parse defaults
  while (*p)
  {
    char param;
    int value;

    while (*p == ' ') p++;
    if (!*p) return;
    if (*p == ':') break;

    param = *p++;
    if (*p != '=') return;

    p++;
    value = 0;
    while (*p >= '0' && *p <= '9') value = value * 10 + (*p++ - '0');

    switch (param)
    {
      case 'd': defdur = 32 / value; break;
      case 'o': defscale = value; break;
      case 'b': bpm = value; break;
    }

    while (*p == ' ') p++;
    if (*p == ',') p++;
  }
  p++;

  while (*p)
  {
    int note = -1;
    int scale = defscale;
    int dur = defdur;
    int durRaw = 0;
    int ms;
    int freq;

    // Skip whitespace
    while (*p == ' ') p++;
    if (!*p) return;

    // Parse duration
    if (*p >= '0' && *p <= '9')
    {
      int value = 0;
      while (*p >= '0' && *p <= '9') value = value * 10 + (*p++ - '0');

      durRaw = value;
      dur = 32 / value;
    }

    // Parse note
    switch (*p)
    {
      case 0: return;
      case 'C': case 'c': note = 0; break;
      case 'D': case 'd': note = 2; break;
      case 'E': case 'e': note = 4; break;
      case 'F': case 'f': note = 5; break;
      case 'G': case 'g': note = 7; break;
      case 'A': case 'a': note = 9; break;
      case 'H': case 'h': note = 11; break;
      case 'B': case 'b': note = 11; break;
      case 'P': case 'p': note = -1; break;
      case 'S': case 's': note = -2; break; // Silence of fixed length (not dependent on bitrate, needed for the hacks)
    }
    p++;
    if (*p == '#')
    {
      note++;
      p++;
    }
    if (*p == 'b')
    {
      note--;
      p++;
    }

    // Parse special duration
    if (*p == '.')
    {
      dur += dur / 2;
      p++;
    }

    // Parse scale
    if (*p >= '0' && *p <= '9') scale = (*p++ - '0');

    // Parse special duration (again...)
    if (*p == '.')
    {
      dur += dur / 2;
      p++;
    }

    // Skip delimiter
    while (*p == ' ') p++;
    if (*p == ',') p++;

    // Play note
    ms = dur * 60000 / (bpm * 8);

    // Fixed silence
    if (note == -2)
      ms = durRaw;

    if (note < 0)
      freq = 0;
    else
      freq = note2freq((scale + 1) * 12 + note);

    if (freq)
    {
      //printf("Freq: %d, pause: %d\n", freq, ms * 7 / 8);
      printf("NOTE(f(%d), %d),\n", freq, ms * 7 / 8);
      //printf("NOTE(P, %d),\n", ms / 8);
      //BuzzerSetFrequency(freq);
      //delay_ms(ms * 7 / 8);
      //BuzzerSetFrequency(0);
      //delay_ms(ms / 8);
    }
    else
     printf("NOTE(P, %d),\n", ms);
  }
  //BuzzerSetFrequency(0);
}


void main(int argc, char** argv)
{
	if (argc == 1)
	{
		printf("Usage: converter <melody.mus>\n");
		exit(1);
	}

	FILE* file = fopen(argv[1], "r");
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* song = (char*)malloc(size + 1);
	fread(song, 1, size, file);
	song[size] = 0;

	play(song);
}
