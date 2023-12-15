#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"
#include "buzzer.h"

#define LED_RED BIT6              
#define LED_GREEN BIT0             
#define LEDS (BIT0 | BIT6)


#define SW1 BIT0
#define SWITCHES (BIT0)


void main(void)
{
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;

  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;

  configureClocks();
  enableWDTInterrupts();
  or_sr(0x18);
}



void
switch_interrupt_handler()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);

  P2IES &= (p2val | ~SWITCHES);

  if (p2val & SW1) {
    P1OUT |= LED_RED;
    P1OUT &= ~LED_GREEN;
  } else {
    P1OUT |= LED_GREEN;
    P1OUT &= ~LED_RED;
  }
}


void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
