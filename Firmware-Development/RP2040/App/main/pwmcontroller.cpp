#include "pwmcontroller.hpp"
#include "hardware/pwm.h"

PWMController::PWMController(uint8_t pwmPin, uint8_t ledNumber) : _pwmPin(pwmPin), _ledNumber(ledNumber) 
{
    init();
}

void PWMController::init() 
{
    gpio_set_function(_pwmPin, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to the PWM pin
    _sliceNum = pwm_gpio_to_slice_num(_pwmPin);

    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, PWM_CLOCK_DIVIDER);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(_sliceNum, &config, true);

    _wrapValue = (RPI_PICO_CLOCK_FREQUENCY / PWM_CLOCK_DIVIDER) / ADC_SPS_A;
    pwm_set_wrap(_sliceNum, _wrapValue);  // Set period
    pwm_set_gpio_level(_pwmPin, _wrapValue * PWM_DUTY_CYCLE);
    pwm_set_enabled(_sliceNum, true);
}

void PWMController::updateWrapValue(char configChar) 
{
    switch (configChar) 
    {
        case 'A':
            _wrapValue = (RPI_PICO_CLOCK_FREQUENCY / PWM_CLOCK_DIVIDER) / ADC_SPS_A;
            break;
        case 'B':
            _wrapValue = (RPI_PICO_CLOCK_FREQUENCY / PWM_CLOCK_DIVIDER) / ADC_SPS_B;
            break;
        case 'C':
            _wrapValue = (RPI_PICO_CLOCK_FREQUENCY / PWM_CLOCK_DIVIDER) / ADC_SPS_C;
            break;
        case 'D':
            _wrapValue = (RPI_PICO_CLOCK_FREQUENCY / PWM_CLOCK_DIVIDER) / ADC_SPS_D;
            break;
        default:
            // No match found
            break;
    }
}

void PWMController::setPWMValues(void) 
{
    pwm_set_wrap(_sliceNum, _wrapValue);
    pwm_set_gpio_level(_pwmPin, _wrapValue * PWM_DUTY_CYCLE);
}

uint8_t PWMController::getLedNumber(void)
{
    return _ledNumber;
}

PWMController::~PWMController() {
    // Cleanup if needed
}