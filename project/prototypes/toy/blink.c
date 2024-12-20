#include <msp430.h>

#include "led.h"

 

static int dimDutyCycle = 0; // Duty cycle (0-100%)

static int dimEnabled = 0;  // Whether dimming is active



// Function to update the dimming state (called in WDT interrupt)

void blinkDimmingLogic() {

  static int pwmCounter = 0;



  if (dimEnabled) {

    pwmCounter++;

    if (pwmCounter < dimDutyCycle) {

      P1OUT |= LED_RED; // Turn RED LED on

    } else {

      P1OUT &= ~LED_RED; // Turn RED LED off

    }



    if (pwmCounter >= 100) { // Reset counter after full cycle

      pwmCounter = 0;

    }

  }

}



// Function to enable/disable dimming

void setDimEnabled(int enabled) {

  dimEnabled = enabled;

  if (!enabled) {

    P1OUT &= ~LED_RED; // Turn off RED LED when dimming is disabled

  }

}



// Function to set the dimming duty cycle

void setDimDutyCycle(int dutyCycle) {

  dimDutyCycle = dutyCycle;

}

