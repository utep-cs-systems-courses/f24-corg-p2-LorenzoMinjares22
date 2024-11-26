#include <msp430.h>

#include "libTimer.h"

#include "led.h"

#include "buzzer.h"



#define A 4400

#define B 4940

#define C4 2620

#define D 2940

#define E 3300

#define F 3490

#define G 3920



#define Q 2500

#define H 5000

#define W 10000

#define Ei 1250



typedef struct {

  int note;

  int duration;

} Note;

/*

Note zelda[] = {

  {C4, Q},{D,Q},{E,Q},{F,Q},{G,Q},{A,Q},{B,Q},{C,H}

  };*/



void song() {



  // Note zelda[] = { {C4,H}, {D,Ei} };

  /*  

  int zelda[] = {4940,2940,4400,3920,4400,4940,2940,4400};

  int durations[] = {5000,2500,5000,1250,1250,5000,2500,5000};

  */

  int i;

  /*for(i = 0; i < 6; i++) {

    buzzer_set_period(4000);//zelda[i].note);

    int dur = durations[i];

    play(dur);

    buzzer_set_period(0);

    }*/



  or_sr(0x18);



}



void play(int dur) {

  buzzer_init();

  configureClocks();



  switch(dur) {

  case Q:

    __delay_cycles(250000);

    break;

  case Ei:

    __delay_cycles(125000);

    break;

  case 5000:

    __delay_cycles(500000);

    break;

  case W:

    __delay_cycles(1000000);

    break;

  default:

    __delay_cycles(1000000);

    break;

  }



}
