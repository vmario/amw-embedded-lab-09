#include "shifter.hpp"
#include "display.hpp"
#include "timer.hpp"

#include <avr/interrupt.h>
#include <util/delay.h>

/**
 * Obsługa przerwania przepełnienia Timer/Counter1.
 */
ISR(TIMER1_OVF_vect)
{
}

/**
 * Odliczany czas.
 *
 * @param Wartość aktualnie odliczonego czasu w milisekundach.
 */
uint16_t currentTime()
{
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
}

/**
 * Pętla główna.
 */
void mainLoop()
{
}

/**
 * Inicjalizacja przerwań.
 */
void interruptsInitialize()
{
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
