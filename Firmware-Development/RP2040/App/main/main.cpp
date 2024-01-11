#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/uart.h"
#include "hardware/pwm.h"
#include <string.h>
#include <string>
#include <sstream>

const uint LED_PIN = 2; // Use the onboard LED

// // Function to be called when the timer interrupt occurs
// bool timer_callback(struct repeating_timer *t) {
//     // Toggle the LED state
//     gpio_put(LED_PIN, !gpio_get(LED_PIN));
//     return true;
// }

#define ADC_SPS_A 250
#define ADC_SPS_B 500
#define ADC_SPS_C 1000
#define ADC_SPS_D 2000
#define UART_ID uart0
#define BAUD_RATE 115200

#define PWM_LED_PIN 2

bool updateWrapValue(char received_char, uint32_t* wrap_value) {
    switch (received_char) {
        case 'A':
            *wrap_value = (125000000 / 256) / ADC_SPS_A;
            break;
        case 'B':
            *wrap_value = (125000000 / 256) / ADC_SPS_B;
            break;
        case 'C':
            *wrap_value = (125000000 / 256) / ADC_SPS_C;
            break;
        case 'D':
            *wrap_value = (125000000 / 256) / ADC_SPS_D;
            break;
        default:
            return false; // No match found
    }

    return true; // Match found
}

void parseString(const std::string &input, uint32_t* wrap_value) {
    size_t ledNumPos = input.find("ledNum=");
    size_t configPos = input.find("Config=");

    if (ledNumPos != std::string::npos) {
        size_t commaPos = input.find(",", ledNumPos);
        if (commaPos != std::string::npos) {
            std::string ledNumStr = input.substr(ledNumPos + 7, commaPos - (ledNumPos + 7));
            uint32_t ledNum = std::stoi(ledNumStr);
            printf("LED NUMBER = %d", ledNum);
            // Process ledNum if needed
        }
    }

    if (configPos != std::string::npos) {
        char configChar = input[configPos + 7];
        updateWrapValue(configChar, wrap_value);
        printf("Config = %c", configChar);
    }
}

int main() {
    stdio_init_all();

    // Set up UART
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(0, GPIO_FUNC_UART); // Assuming UART TX is on GPIO 0
    gpio_set_function(1, GPIO_FUNC_UART); // Assuming UART RX is on GPIO 1

    gpio_set_function(PWM_LED_PIN, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(PWM_LED_PIN);

    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    pwm_config_set_clkdiv(&config, 256.f);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);

    uint32_t wrap_value = (125000000/ 256.f) / ADC_SPS_A;
    pwm_set_wrap(slice_num, wrap_value);  // Set period of 1024 cycles (0 to 1023 inclusive)
    pwm_set_gpio_level(PWM_LED_PIN, wrap_value/4);
    pwm_set_enabled(slice_num, true);

    std::string received_string;
    // Main loop (you can add your application logic here)
    while (true) {
        // Check if UART has received a character
        if (uart_is_readable(UART_ID)) {
            char received_char = uart_getc(UART_ID);
            uart_putc(UART_ID, received_char);
            uint32_t wrap_value = 0;
            // Adjust period based on received character
            // if (updateWrapValue(received_char, &wrap_value))
            // {
            //     pwm_set_wrap(slice_num, wrap_value);  // Set period of 1024 cycles (0 to 1023 inclusive)
            //     pwm_set_gpio_level(PWM_LED_PIN, wrap_value/4);
            // }
            if (received_char == '\n') {
                // End of the string received, process it
                parseString(received_string, &wrap_value);
                printf("\r\nWrap Value %d\r\n", wrap_value);
                // Adjust period based on the parsed value
                pwm_set_wrap(slice_num, wrap_value);
                pwm_set_gpio_level(PWM_LED_PIN, wrap_value / 4);

                // Clear the received_string for the next input
                received_string.clear();
            } else {
                // Append the character to the received string
                received_string += received_char;
            }
        }

        // Your main code goes here
    }

    return 0;
}
