#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"

#include <avr/interrupt.h>
#include <util/delay.h>

volatile bool falstart;

/**
 * Preskaler Timer/Counter1.
 */
constexpr uint8_t TIMER1_PRESCALER = _BV(CS12) | _BV(CS10);

/**
 * Konfiguracja Timer/Counter1.
 */
constexpr uint8_t TIMER1_MODE = _BV(WGM12);

/**
 * Obsługa przerwania komparatora Timer/Counter1.
 */
ISR(TIMER1_OVF_vect)
{
	TCCR1B = 0;
	TCNT1 = 0xFFFF;
	falstart = true;
}

/**
 * Obsługa przerwania komparatora Timer/Counter1.
 */
ISR(TIMER0_OVF_vect)
{
	display.print(1.0 * TCNT1 / (16'000'000 / 1024) * 1000, 3);
	display.refresh();
}

ISR(PCINT1_vect)
{
	TCCR1B = 0;
	falstart = true;
}

void buzzerOn()
{
	DDRB |= _BV(5);
	//DDRD |= _BV(3);
}

void buzzerOff()
{
	DDRB &= ~_BV(5);
	//DDRD &= ~_BV(3);
}

void mainLoop()
{
	_delay_ms(5'000);
	if (falstart) {
		falstart = false;
		return;
	}
	TCNT1 = 0;
	buzzerOn();
	TCCR1B = TIMER1_PRESCALER;
	_delay_ms(20);
	buzzerOff();
}

/**
 * Funkcja główna.
 */
int main()
{
	shifter.initialize();
	timer.initialize();

	PCICR |= _BV(PCIE1);
	PCMSK1 |= _BV(PCINT9);
	TIMSK1 = _BV(TOIE1);

	sei();

	while (true) {
		mainLoop();
	}
}
