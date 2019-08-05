// This is the configuration file. Ideally, any configuration and calibration
// of the device should be done by changing this file only.

// Needed by util/delay.h
#define F_CPU 6000000UL

// Pwm prescaler value
#define PWM_PRESCALER Atmega328p::PSV_1

// Delay between two executions of main loop, given in millisecond.
#define LOOP_DELAY 200
