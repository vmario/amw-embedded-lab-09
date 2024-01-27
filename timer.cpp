#include "timer.hpp"

#include <avr/io.h>

const Timer timer;

namespace {
/**
 * Konfiguracja Timer/Counter1.
 */
constexpr uint8_t TIMER1_MODE = _BV(WGM12);

/**
 * Preskaler Timer/Counter1.
 */
constexpr uint8_t TIMER1_PRESCALER = _BV(CS11);
}

void Timer::initialize() const
{
	OCR1A = F_CPU / TIMER_FREQUENCY / 8 - 1;
	TCCR1B = TIMER1_PRESCALER | TIMER1_MODE;
	TIMSK1 = _BV(OCIE1A);
}

