// Generic Avr helpers

#ifndef _H_OTURPE_AVR_UTILS
#define _H_OTURPE_AVR_UTILS

// Cleaner setting of bits
#define BV(x) (1<<x)

/// \enum Port
///
/// Symbols for referring to separate io ports.
enum Port { B, C, D };

/// \brief
///    Sets value of a single bith in a data register (PORTxn). Normally used
///    to set output pin high or low.
///    
/// \param port
///    Pin port
///    
/// \param pin
///    Pin index
///
/// \param enable
///    If pin is enabled (high). Otherwise it is disabled (low).
void setData(Port port, int pin, bool enable);

/// \brief
///    Sets value of a single bith in a data direction register (PORTxn).
///    Used to set a pin as input or output.
///    
/// \param port
///    Pin port
///    
/// \param pin
///    Pin index
///
/// \param enable
///    If pin is enabled (output) or disabled (input)
void setDataDirection(Port port, int pin, bool enable);

#endif //_H_OTURPE_AVR_UTILS
