#include <stdio.h>
#include "pico/stdlib.h"
#include <string>
#include <vector>
#include "pwmcontroller.hpp"
#include "uartcontroller.hpp"

int main() 
{
    stdio_init_all();

    std::vector<PWMController> pwmControllers = {PWMController(PWM_LED_PIN_N1, 1), PWMController(PWM_LED_PIN_N2, 2)};
    UARTController uartController(UART_ID, BAUD_RATE, TX_PIN, RX_PIN);

    std::string receivedString;

    while (true) 
    {
        if (uartController.isReadable()) 
        {
            char receivedChar = uartController.read();

            if (receivedChar == '\n') 
            {
                // End of the string received, process it
                auto ledConfig = uartController.parse(receivedString);

                for (auto & pwmController : pwmControllers) 
                {
                    if (pwmController.getLedNumber() == ledConfig.first)
                    {
                        pwmController.updateWrapValue(ledConfig.second);
                        pwmController.setPWMValues();
                        break;
                    }
                    
                }
                // Clear the receivedString for the next input
                receivedString.clear();
            } 
            else 
            {
                // Append the character to the received string
                receivedString += receivedChar;
            }
        }
    }

    return 0;
}
