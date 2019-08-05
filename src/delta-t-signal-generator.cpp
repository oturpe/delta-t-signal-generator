// Signal generator for Delta-T time machine from the Montauk Project.
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi
// Date: 2019-08-01

#include "AvrUtils.h"
#include "Atmega328pUtils.h"

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

#include "IndicatorController.h"

/// Initializes pins D5 and D6 as phase correct pwm and enables them.
void initializePwm() {
    setDataDirection(D, 6, true);

    // Non-inverting mode
    TCCR0A |= BV(COM0A1) | BV(COM0B1);
    // Fast pwm mode
    TCCR0A |= BV(WGM00) | BV(WGM00);

    Atmega328p::setTimer0Prescaler(PWM_PRESCALER);

    // Enable pwm
    TCCR0A |= BV(COM0A1);
}

/// Initializes analog to digital conversion by setting the reference and
/// prescaler.
void initializeAdc() {
    Atmega328p::setVoltageReference(Atmega328p::VREF_VCC);
    Atmega328p::setAdcPrescalerValue(Atmega328p::ADC_PSV_32);

    // Enable adc
    ADCSRA |= BV(ADEN);

    // Disable digital input from pins that are used for adc.
    DIDR0 |= BV(ADC0D) | BV(ADC1D) | BV(ADC2D) | BV(ADC3D);
}

/// Sense frequency adjust potentiometer position.
///
/// This function starts analog to digital conversion and waits until a value
/// is available.
///
/// Returns value in range 0 ... 1023. 
///
/// \return
///   Voltage
uint16_t senseFrequencyAdjust() {
    // Select analog input ADC4
    ADMUX &= ~BV(MUX3) & ~BV(MUX1) & ~BV(MUX0);
    ADMUX |= BV(MUX2);

    // start conversion and wait until value is available
    ADCSRA |= BV(ADSC);
    while(ADCSRA & BV(ADSC));

    return ADC;
}

int main() {
    IndicatorController indicator(B, 0, 5);

    initializeAdc();
    initializePwm();

    uint8_t brightness = 0;

    while (true) {
         indicator.run();

         uint8_t frequency = senseFrequencyAdjust()/4;
         // TODO: Use this value properly
         OCR0A = frequency;
         OCR0B = 0xff - frequency;

        _delay_ms(LOOP_DELAY);
    }
}
