#include "timer.hpp"

#include <avr/io.h>

const Timer timer;

namespace {
/**
 * Preskaler Timer/Counter0.
 */
constexpr uint8_t TIMER0_PRESCALER = _BV(CS02);
}

void Timer::initialize() const
{
	TCCR0B = TIMER0_PRESCALER;
	TIMSK0 = _BV(TOIE0);
}

