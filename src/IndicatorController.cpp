#include <avr/io.h>

#include "AvrUtils.h"

#include "IndicatorController.h"

IndicatorController::IndicatorController(
    Port port,
    uint8_t pin,
    uint16_t halfPeriod
) :
    port(port),
    pin(pin),
    halfPeriod(halfPeriod),
    isLit(false),
    remainingPeriod(halfPeriod) {
    setDataDirection(port, pin, true);    
}

void IndicatorController::run() {
    remainingPeriod--;

    if (!remainingPeriod) {
        // Flip state and reset remaining period
        isLit = !isLit;
        setData(port, pin, isLit);
        remainingPeriod = halfPeriod;
    }
}
