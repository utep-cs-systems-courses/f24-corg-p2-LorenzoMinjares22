#include <msp430.h>

#include "libTimer.h"

#include "led.h"

#include "buzzer.h"
#include "blink.h"


//#define LED_RED BIT6

//#define LED_GREEN BIT0

//#define LEDS (BIT6 | BIT0)

#define SW1 BIT3



#define SW2 BIT0

#define SW3 BIT1

#define SW4 BIT2

#define SW5 BIT3



//#define SWITCH_A SW1

//#define SWITCH_B SW2

 

#define SWITCH_1 SW1



#define SWITCH_2 SW2

#define SWITCH_3 SW3

#define SWITCH_4 SW4

#define SWITCH_5 SW5



#define SWITCH_P2 (SWITCH_2 | SWITCH_3 | SWITCH_4 | SWITCH_5)



volatile int red_on = 0;

volatile int green_on = 0;

volatile int redDim = 0;



int main(void) {

  WDTCTL = WDTPW + WDTHOLD;    // Stop watchdog timer
  configureClocks();           // Setup master clock
  enableWDTInterrupts();
  P1DIR |= LEDS;    // Set LED pins as outputs
  P1OUT &= ~LEDS;   // Initialize LEDs to off Initialize LEDs
  buzzer_init();               // Initialize buzzer

  P1DIR |= LEDS;               // Set LED pins as outputs
  P1OUT &= ~LEDS;              // Turn off all LEDs

  P2REN |= SWITCH_P2;          // Enable pull-up resistors for P2 buttons
  P2OUT |= SWITCH_P2;
  P2IE |= SWITCH_P2;  

  or_sr(0x18);



}


void switch_interrupt_handler_P1() {

  char p1val = P1IN;



  P1IES |= (p1val & SWITCH_1);

  P1IES &= (p1val | ~SWITCH_1);



  if (p1val & SW1) {

    P1OUT &= ~LEDS;

    P1OUT &= ~LED_GREEN;

    buzzer_set_period(0);

    redControl(1);



  } else {

    P1OUT |= LEDS;

    red_on = 1;

    green_on = 1;

    redControl(0);

    P1OUT |= LED_GREEN;

    buzzer_set_period(800);

  }

  //P1IFG &= SWITCH_1;

}



/*

void song(int A, int B, int C4, int D, int E, int F, int G) {

  buzzer_set_period(A);

  buzzer_set_period(0);

  }*/



void switch_interrupt_handler_P2_2() {

  char p2val = P2IN;



  P2IES |= (p2val & SWITCH_2);

  P2IES &= (p2val | ~SWITCH_2);



  if(p2val & SW2) {

    P1OUT &= ~LED_RED;

    buzzer_set_period(0);

  } else {

    red_on = redControl(red_on);

    buzzer_set_period(800);

    redControl(1);

  }



  //P2IFG &= ~SWITCH_2;



}



void switch_interrupt_handler_P2_3() {

  char p2val = P2IN;

  P2IES |= (p2val & SWITCH_3);

  P2IES &= (p2val |  ~SWITCH_3);

  if(p2val & SW3) {

    P1OUT &= ~LED_GREEN;

    green_on = 0;

    buzzer_set_period(0);

  } else {

    P1OUT |= LED_GREEN;

    buzzer_set_period(3300);

    green_on = 1;

  }

}


volatile int dimDutyCycle = 0; // Duty cycle (0-100%)

volatile int dimEnabled = 0;  // Whether dimming is active



void switch_interrupt_handler_P2_4() {

  char p2val = P2IN;



  P2IES |= (p2val & SWITCH_4);

  P2IES &= (p2val | ~SWITCH_4);



  if (p2val & SWITCH_4) {

    setDimEnabled(0); // Disable dimming on release

  } else {

    setDimEnabled(1); // Enable dimming

    static int dutyCycle = 0;

    dutyCycle += 20;  // Increment duty cycle by 20%

    if (dutyCycle > 100) {

      dutyCycle = 0; // Reset to 0% after 100%

    }

    setDimDutyCycle(dutyCycle); // Update duty cycle

  }

}






void switch_interrupt_handler_P2_5() {

  char p2val = P2IN;

  P2IES |= (p2val & SWITCH_5);

  P2IES &= (p2val | ~SWITCH_5);

  if(p2val & SW5) {

    buzzer_set_period(0);

  } else {

    buzzer_set_period(4940);

    __delay_cycles(1000000);

    buzzer_set_period(4940);

    __delay_cycles(1000000);

    buzzer_set_period(0);

    /* buzzer_set_period(4940);

    __delay_cycles(2500000);

    buzzer_set_period(5240);

    */

  }

}



void __interrupt_vec(PORT2_VECTOR) Port_2() {

  if (P2IFG & SW2) {

    P2IFG &= ~SW2;

    switch_interrupt_handler_P2_2();

  }

  if (P2IFG & SW3) {

    P2IFG &= ~SW3;

    switch_interrupt_handler_P2_3();

  }

  if (P2IFG & SW4) {

    P2IFG &= ~SW4;

    switch_interrupt_handler_P2_4();

  }

  if (P2IFG & SW5) {

    P2IFG &= ~SW5;

    switch_interrupt_handler_P2_5();

  }

}


void __interrupt_vec(WDT_VECTOR) WDT() {

  blinkDimmingLogic(); // Call dimming logic in blink.c

  

}

