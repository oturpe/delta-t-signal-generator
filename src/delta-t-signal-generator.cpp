// Signal generator for Delta-T time machine from the Montauk Project.
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi
// Date: 2019-08-01

#include "AvrUtils.h"

#include "config.h"

#include <util/delay.h>

#include "IndicatorController.h"


int main() {
    IndicatorController indicator(B, 0, 5);

    while (true) {
         indicator.run();
        _delay_ms(LOOP_DELAY);
    }
}
