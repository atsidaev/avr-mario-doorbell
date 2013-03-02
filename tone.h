/*****************************************************************************
*
*   Tone definition. Each tone are set up with a value which will give the 
*   right frequency when applied to a 16-bits timer with PWM. These values are based
*   on a CLKcpu running @ 1Mhz.
*
*   First find the frequency for all tones. 
*
*   Formula:    ToneX = Bf * 2^(ToneX/12)
*   
*   ToneX: the actual tone, e.g. C0 = 3
*   Bf: Basefrequency = 220Hz (A)
*
*       
*   E.g: For tone C0 this would be:     C0 = 220 * 2^(3/12)
*                                       C0 = 261,6256...
*
*   Now we must find which value to put in a 16-bits timer with PWM to achieve 
*   this frequency
*
*   Formula:    Timer value = 1Mhz / ToneHz / 2
*
*   E.g: For tone C0 this would be:     Timer value = 1000000 / 261,6256... / 2
*                                       Timer value = 1911
*
*   Set up a 16-bits timer to run at Phase/Freq-correct PWM, top value = ICR1,
*   set OC1A when upcounting, clear when downcounting.
*   
*****************************************************************************/

#define f(x) (F_CPU/(x*2*SOUND_TIM_PRE))
#define fn(x) ((x*F_CPU)/(1000000UL * SOUND_TIM_PRE))

#ifdef SOUND_BPM
  #define COEF SOUND_BPM
#else
  #define COEF 1
#endif

#define dn(x) ((24U*F_CPU)/(x*SOUND_TIM_PRE*256UL*32UL)/COEF)
#define ms(x) (((x)*F_CPU)/(SOUND_TIM_PRE*256UL*32UL*1000UL))

#define n1  dn(1)    //целая нота
#define n2  dn(2)    //половинная нота
#define n4  dn(4)    //четверть
#define n8  dn(8)    //восьмая
#define n3  dn(12)   //восьмая триоль
#define n16 dn(16)   //шестнадцатая
#define n6  dn(12)   //секстоль
#define n32 dn(32)   //тридцать вторая

#define A   fn(2273)        // tone 0
#define xA  fn(2145)        // tone 1
#define Ax  fn(2145)        // tone 1
#define B   fn(2025)        // tone 2
#define C0  fn(1911)       // tone 3
#define xC0 fn(1804)        // ...
#define Cx0 fn(1804)
#define D0  fn(1703)
#define xD0 fn(1607)
#define Dx0 fn(1607)
#define E0  fn(1517)
#define F0  fn(1432)
#define xF0 fn(1351)
#define Fx0 fn(1351)
#define G0  fn(1275)
#define xG0 fn(1204)
#define Gx0 fn(1204)
#define A0  fn(1136)
#define xA0 fn(1073)
#define Ax0 fn(1073)
#define B0  fn(1012)
#define C1  fn(956)
#define xC1 fn(902)
#define Cx1 fn(902)
#define D1  fn(851)
#define xD1 fn(804)
#define Dx1 fn(804)
#define E1  fn(758)
#define F1  fn(716)
#define xF1 fn(676)
#define Fx1 fn(676)
#define G1  fn(638)
#define xG1 fn(602)
#define Gx1 fn(602)
#define A1  fn(568)
#define xA1 fn(536)
#define Ax1 fn(536)
#define B1  fn(506)
#define C2  fn(478)
#define xC2 fn(451)
#define Cx2 fn(451)
#define D2  fn(426)
#define xD2 fn(402)
#define Dx2 fn(402)
#define E2  fn(379)
#define F2  fn(356)
#define xF2 fn(338)
#define Fx2 fn(338)
#define G2  fn(319)
#define xG2 fn(301)
#define Gx2 fn(301)
#define A2  fn(284)
#define xA2 fn(268)
#define Ax2 fn(268)
#define B2  fn(253)
#define C3  fn(239)
#define xC3 fn(225)
#define Cx3 fn(225)
#define D3  fn(213)
#define xD3 fn(201)
#define Dx3 fn(201)
#define E3  fn(190)
#define F3  fn(179)
#define xF3 fn(169)
#define Fx3 fn(169)
#define G3  fn(159)
#define xG3 fn(150)
#define Gx3 fn(150)
#define A3  fn(142)
#define xA3 fn(134)
#define Ax3 fn(134)
#define B3  fn(127)
#define C4  fn(119)


#define P   1           // pause



/******************************************************************************
*
*   The tone definitions are duplicated to accept both upper and lower case
*
******************************************************************************/

#define a   fn(2273)        // tone 0
#define xa  fn(2145)       // tone 1
#define ax  fn(2145)        // tone 1
#define b   fn(2024)        // tone 2
#define c0  fn(1911)        // tone 3
#define xc0 fn(1804)        // ...
#define cx0 fn(1804)
#define d0  fn(1703)
#define xd0 fn(1607)
#define dx0 fn(1607)
#define e0  fn(1517)
#define f0  fn(1432)
#define xf0 fn(1351)
#define fx0 fn(1351)
#define g0  fn(1275)
#define xg0 fn(1204)
#define gx0 fn(1204)
#define a0  fn(1136)
#define xa0 fn(1073)
#define ax0 fn(1073)
#define b0  fn(1012)
#define c1  fn(956)
#define xc1 fn(902)
#define cx1 fn(902)
#define d1  fn(851)
#define xd1 fn(804)
#define dx1 fn(804)
#define e1  fn(758)
#define f1  fn(716)
#define xf1 fn(676)
#define fx1 fn(676)
#define g1  fn(638)
#define xg1 fn(602)
#define gx1 fn(602)
#define a1  fn(568)
#define xa1 fn(536)
#define ax1 fn(536)
#define b1  fn(506)
#define c2  fn(478)
#define xc2 fn(451)
#define cx2 fn(451)
#define d2  fn(426)
#define xd2 fn(402)
#define dx2 fn(402)
#define e2  fn(379)
#define f2  fn(356)
#define xf2 fn(338)
#define fx2 fn(338)
#define g2  fn(319)
#define xg2 fn(301)
#define gx2 fn(301)
#define a2  fn(284)
#define xa2 fn(268)
#define ax2 fn(268)
#define b2  fn(253)
#define c3  fn(239)
#define xc3 fn(225)
#define cx3 fn(225)
#define d3  fn(213)
#define xd3 fn(201)
#define dx3 fn(201)
#define e3  fn(190)
#define f3  fn(179)
#define xf3 fn(169)
#define fx3 fn(169)
#define g3  fn(159)
#define xg3 fn(150)
#define gx3 fn(150)
#define a3  fn(142)
#define xa3 fn(134)
#define ax3 fn(134)
#define b3  fn(127)
#define c4  fn(119)



#define p   1
