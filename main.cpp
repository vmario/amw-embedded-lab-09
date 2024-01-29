#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"

#include <avr/interrupt.h>
#include <util/delay.h>

#if 1
/**
 * Czy był falstart?
 */
volatile bool falseStart;
#endif

/**
 * Obsługa przerwania przepełnienia Timer/Counter1.
 */
ISR(TIMER1_OVF_vect)
{
#if 1
	TCCR1B = 0;
	TCNT1 = 0xFFFF;
	falseStart = true;
#endif
}

/**
 * Odliczany czas.
 *
 * @param Wartość aktualnie odliczonego czasu w milisekundach.
 */
uint16_t currentTime()
{
#if 1
	return 1.0 * TCNT1 / (16'000'000 / 1024) * 1000;
#endif
#if 1
	return TCNT1;
#endif
	return 8888;
}

/**
 * Obsługa przerwania przepełnienia Timer/Counter0.
 */
ISR(TIMER0_OVF_vect)
{
	display.print(currentTime(), 3);
	display.refresh();
}

/**
 * Przerwanie od przycisku.
 */
ISR(PCINT1_vect)
{
#if 1
	TCCR1B = 0;
	falseStart = true;
#endif
}

/**
 * Pętla główna.
 */
void mainLoop()
{
#if 1
	_delay_ms(5'000);
#endif

#if 1
	if (falseStart) {
		falseStart = false;
		return;
	}
#endif

#if 1
	TCNT1 = 0;
#endif

#if 1
	DDRB |= _BV(5);
	//DDRD |= _BV(3);
#endif

#if 1
	TCCR1B = _BV(CS12) | _BV(CS10);
#endif

#if 1
	_delay_ms(20);
	DDRB &= ~_BV(5);
	//DDRD &= ~_BV(3);
#endif
}

/**
 * Inicjalizacja przerwań.
 */
void interruptsInitialize()
{
#if 1
	PCMSK1 |= _BV(PCINT9);
	PCICR |= _BV(PCIE1);
#endif
#if 1
	TIMSK1 = _BV(TOIE1);
#endif
}

/**
 * Funkcja główna.
 */
int main()
{
	shifter.initialize();
	timer.initialize();
	interruptsInitialize();

	sei();

	while (true) {
		mainLoop();
	}
}
