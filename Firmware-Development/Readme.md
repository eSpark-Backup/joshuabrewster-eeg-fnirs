# Joshuabrewster-EEEG-fNIRS

**Light Sensor Integration with RP2040 and BT40 Boards**

## Setup

### Programming RP2040

1. Download the UF2 file from [this link](https://github.com/eSpark-Consultants/joshuabrewster-eeg-fnirs/tree/Development/Firmware-Development/RP2040/App/binaries).

2. Program the RP2040 board using the UF2 file. Ensure PIN2 of RP2040 is connected to LED1_P11 of the Light Sensor Circuit Board, PIN4 is connected to LED2_P13, and GND is connected to GND.

### Building and Flashing BT40 Board

1. Clone the [BT40 project repository](https://github.com/eSpark-Consultants/joshuabrewster-eeg-fnirs/tree/Development/Firmware-Development/nRF/Application).
2. Ensure PIN1 (RX) of RP2040 is connected to the corresponding TX pin on the BT40 board, PIN2 (TX) is connected to the corresponding RX pin on the BT40 board.
   
![image](https://github.com/eSpark-Consultants/joshuabrewster-eeg-fnirs/assets/106241042/74981331-7812-480d-8c11-4f2ebd432fdc)

3. Follow the instructions in the repository to build and flash the BT40 board.
