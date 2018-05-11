/**
\brief This is a program which shows how to use the bsp modules for the board
       and leds.

\note: Since the bsp modules for different platforms have the same declaration,
       you can use this project with any platform.

Load this program on your boards. The LEDs should start blinking furiously.

\author Thomas Watteyne <watteyne@eecs.berkeley.edu>, August 2014.
*/

#include "msp430f1611.h"
#include "stdint.h"
#include "stdio.h"
// bsp modules required
#include "board.h"
#include "leds.h"


uint8_t check_fsr_count;
uint8_t ansum_count;
uint8_t test;

void some_delay(void);
void init_all() {
	check_fsr_count = 0;
	ansum_count = 0;
	P2DIR &= 0xFE; //GIO0 Input으로 설정
	P2DIR |= 0x02;	//GIO1 Output으로 설정
}

void buzzer_on() {
	int j;
	uint16_t delay;

	while (1) {
		P2OUT |= 0x2;
		for (delay = 0xff; delay > 0; delay--);
		P2OUT &= 0xFD;
		for (delay = 0xff; delay > 0; delay--);
	}
}
void buzzer_off() {
	P2OUT &= 0xFD;	//Buzzer off
}
/**
\brief The program starts executing here.
*/
int mote_main(void) {
	uint8_t i;
	uint8_t j;
	
   board_init();
   init_all();

	leds_all_on();
	while (1) {
		if (P2IN & 0x01)	//초록색이 켜지는 것 - Sungut
		{
			check_fsr_count++;
			some_delay();
			if (check_fsr_count > 10) {
				buzzer_off();
				ansum_count = 0;
				leds_error_off();
				leds_radio_on();
				some_delay();
			}
		}
		else {
			check_fsr_count = 0;
			ansum_count++;
			if (ansum_count > 30) {
				buzzer_on();
				ansum_count = 40;
			}
			leds_error_on();
			leds_radio_off();
			some_delay();
		}
	}

   board_reset();
   
   return 0;
}

void some_delay(void) {
   volatile uint16_t delay;
   for (delay=0xffff;delay>0;delay--);
}