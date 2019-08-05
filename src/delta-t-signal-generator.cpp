// Signal generator for Delta-T time machine from the Montauk Project.
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi
// Date: 2019-08-01

#include "AvrUtils.h"
#include "Atmega328pUtils.h"

#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "IndicatorController.h"

uint8_t sinTable[256] = {
    128, 153, 178, 201, 220, 236, 248,254, 255, 251, 242, 229, 211, 190, 166, 140, 115, 89, 65, 44, 26, 13, 4, 0, 1, 7, 19, 35, 54, 77, 102, 127
};

Atmega328p::TimerPrescalerValue clockPrescaler[16] = {
    Atmega328p::PSV_8,
    Atmega328p::PSV_8,
    Atmega328p::PSV_8,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1,
    Atmega328p::PSV_1
};

uint16_t clockTop[16] = {
    23438,
    16164,
    11147,
    61503,
    42416,
    29252,
    20174,
    13913,
    9595,
    6617,
    4564,
    3147,
    2171,
    1497,
    1032,
    712
};

/// Initializes pin D6 as fast pwm and enables it.
void initializePwm() {
    setDataDirection(D, 6, true);

    // Non-inverting mode
    TCCR0A |= BV(COM0A1);
    // Fast pwm mode
    TCCR0A |= BV(WGM01) | BV(WGM00);

    Atmega328p::setTimer0Prescaler(PWM_PRESCALER);

    // Enable pwm
    TCCR0A |= BV(COM0A1);
}

/// Initializes pin D3 as fast pwm and enables it.
void initializePwm2() {
    setDataDirection(D, 3, true);

    // Non-inverting mode
    TCCR2A |= BV(COM2B1);
    // Fast pwm mode
    TCCR2A |= BV(WGM21) | BV(WGM20);

    Atmega328p::setTimer2Prescaler(PWM_PRESCALER);

    // Enable pwm
    TCCR0A |= BV(COM2B1);
}

/// Initializes timer 1 as interrupt clock source.
void initializeInterruptClock() {
    // CTC mode
    TCCR1B |= BV(WGM12);

    Atmega328p::setTimer1Prescaler(Atmega328p::PSV_1);

    // Enalbe interrupt
    TIMSK1 |= BV(OCIE1A);
}

/// \brief
///    Set output frequency based on adjust input value.
///
/// \param adjustValue
///    Adjust voltage in adc's native range 0 ... 1023
void setFrequency(uint16_t adjustValue) {
    static Atmega328p::TimerPrescalerValue currentPrescaler = Atmega328p::PSV_1;

    uint16_t index = adjustValue / (1 << 6);
    Atmega328p::TimerPrescalerValue newPrescaler = clockPrescaler[index];

    if (newPrescaler != currentPrescaler) {
        Atmega328p::setTimer1Prescaler(newPrescaler);
        currentPrescaler = newPrescaler;
    }

    OCR1A = clockTop[index];
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

uint8_t interruptCounter = 0;
// interrupt when timer 1 match with OCR1A value
ISR(TIMER1_COMPA_vect){
    interruptCounter = (interruptCounter + 1) % 32;
    OCR0A = sinTable[interruptCounter];

    uint8_t cosIndex = (interruptCounter + 8) % 32;
    OCR2B = sinTable[cosIndex];
}

int main() {
    IndicatorController indicator(B, 0, 5);

    initializeAdc();
    initializePwm();
    initializePwm2();
    initializeInterruptClock();

    uint8_t counter = 0;

    sei();

    while (true) {
         indicator.run();

         uint16_t adjustValue = senseFrequencyAdjust();
         setFrequency(adjustValue);

        _delay_ms(LOOP_DELAY);
    }
}
