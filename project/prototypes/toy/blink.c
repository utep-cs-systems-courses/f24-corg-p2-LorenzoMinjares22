#include <msp430.h>

#include "libTimer.h"

#include "led.h"

#include <stdlib.h>



static int once = 0;



void blink (void) {

  P1DIR |= LEDS;

  P1OUT &= ~LED_RED;

  P1OUT |= LED_RED;



  configureClocks();

  enableWDTInterrupts();



  if(once) {

    //P1IFG &= LED_RED;

    P1OUT &= ~LED_RED;

    WDTCTL = WDTPW | WDTHOLD;

    once = 0;

  }



  /*

  if(c) {

    P1OUT &= ~LED_RED;

    return 1;

    }*/

  /*

  int a = 0;

  while(a < 25) {

      P1OUT &= ~LED_RED;

      __delay_cycles(800000);

      P1OUT |= LED_RED;

      __delay_cycles(800000);

      a++;

      }*/



  or_sr(0x18);

}



// blink state machine

static int blinkLimit = 5;   //  state var representing reciprocal of duty cycle

void blinkUpdate() // called every 1/250s to blink with duty cycle 1/blinkLimit

{

  static int blinkCount = 0; // state var representing blink state

  blinkCount ++;

  if (blinkCount >= blinkLimit) {

    blinkCount = 0;

    redControl(1);

  } else

    redControl(0);

}



void oncePerSecond()
{
  blinkLimit++; //reduce duty cycle
  if(blinkLimit >= 8){
    blinkLimit =0;
    once =1;
    blink();
  }
}





void timeAdvStateMachines() // called every 1/250 sec

{

  blinkUpdate();

  // secondUpdate();

}





void __interrupt_vec(WDT_VECTOR) WDT()/* 250 interrupts/sec */

{

  // handle blinking

  timeAdvStateMachines();

} 
