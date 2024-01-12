#include <stdio.h>
#include "pico/stdlib.h"

#define ADC_SPS_A 250
#define ADC_SPS_B 500
#define ADC_SPS_C 1000
#define ADC_SPS_D 2000

#define PWM_LED_PIN_N1 2
#define PWM_LED_PIN_N2 3

class PWMController 
{
    public:
        PWMController(uint8_t pwmPin, uint8_t ledNumber);
        void init();
        void updateWrapValue(char configChar);
        void setPWMValues(void);
        uint8_t getLedNumber(void);
        ~PWMController();

    private:
        const uint8_t _ledNumber;
        uint8_t _pwmPin;
        uint _sliceNum;
        uint32_t _wrapValue;
};