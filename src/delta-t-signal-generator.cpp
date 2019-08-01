// Signal generator for Delta-T time machine from the Montauk Project.
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi
// Date: 2019-08-01

#include "AvrUtils.h"

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

uint32_t indicatorCounter = 0;

/// \brief
///    Toggles the indicator led state.
void toggleIndicator() {
    static bool lit;

    if (lit) {
        INDICATOR_DATA &= ~BV(INDICATOR_DATA_PIN);
    }
    else {
        INDICATOR_DATA |= BV(INDICATOR_DATA_PIN);
    }

    lit = !lit;
}

int main() {
    INDICATOR_DATA_DIR |= BV(INDICATOR_DATA_DIR_PIN);

    while (true) {
        if (indicatorCounter == INDICATOR_HALF_PERIOD) {
            toggleIndicator();
            indicatorCounter = 0;
        }
        else {
            indicatorCounter++;
        }

        _delay_ms(LOOP_DELAY);
    }
}
