#include <avr/io.h>

#include "AvrUtils.h"

void setData(Port port, int pin, bool enable) {
    if (enable) {
        // Enable pin
        switch (port) {
            case B:
                PORTB |= BV(pin);
                return;
            case C:
                PORTC |= BV(pin);
                return;
            case D:
                PORTD |= BV(pin);
                return;
            default:
                // Should not happen
                return;
        }
    }
    else {
        // Disable pin
        switch (port) {
            case B:
                PORTB &= ~BV(pin);
                return;
            case C:
                PORTC &= ~BV(pin);
                return;
            case D:
                PORTD &= ~BV(pin);
                return;
            default:
                // Should not happen
                return;
        }
    }
}

void setDataDirection(Port port, int pin, bool enable) {
    if (enable) {
        // Enable pin
        switch (port) {
            case B:
                DDRB |= BV(pin);
                return;
            case C:
                DDRC |= BV(pin);
                return;
            case D:
                DDRD |= BV(pin);
                return;
            default:
                // Should not happen
                return;
        }
    }
    else {
        // Disable pin
        switch (port) {
            case B:
                DDRB &= ~BV(pin);
                return;
            case C:
                DDRC &= ~BV(pin);
                return;
            case D:
                DDRD &= ~BV(pin);
                return;
            default:
                // Should not happen
                return;
        }
    }
}
