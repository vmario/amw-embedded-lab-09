#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"
#include "adc.hpp"

#include <avr/interrupt.h>
#include <util/delay.h>

bool stop{true};

/**
 * Obsługa przerwania komparatora Timer/Counter1.
 */
ISR(TIMER1_COMPA_vect)
{
	static uint16_t counter;
	if (!stop) {
		counter++;
	}
	display.print(counter, 3);
	display.refresh();
}

/**
 * Funkcja główna.
 */
int main()
{
	shifter.initialize();
	timer.initialize();

	sei();

	_delay_ms(1000);
	stop = false;

	while (true) {
		if (bit_is_clear(PINC, 1)) {
			stop = true;
		}
	}
}
