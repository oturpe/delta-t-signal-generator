#ifndef _H_INDICATOR_BLINKER
#define _H_INDICATOR_BLINKER

/// \class IndicatorController
///
/// Attached to a single pin, blinks with constant frequency and 50 % duty
/// cycle.
class IndicatorController {
public:
    /// \brief
    ///    Initializes a new indicator blinker.
    ///
    /// \param port
    ///    Port where blinker light is connected.
    /// \param pin
    ///    Pin where blinker light is connected.
    ///
    /// \param halfPeriod
    ///    Blink half period in clock steps.
    IndicatorController(Port port, uint8_t pin, uint16_t halfPeriod);

public:
    /// \brief
    ///    Instructs the controller to advance one step in sequence, essentially
    ///    stepping the controller's clock.
    void run();

private:
    /// Port where blinker light is connected.
    const Port port;
    /// Port where blinker light is connected.
    const uint8_t pin;

    /// Defined blink half period
    uint16_t halfPeriod;
    /// Current status
    bool isLit;
    /// Remaining half period 
    uint16_t remainingPeriod;
};

#endif
