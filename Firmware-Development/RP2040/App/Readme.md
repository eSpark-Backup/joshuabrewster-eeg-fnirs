# RPI PICO C++ Project Setup Guide

This guide walks you through installing and building a C++ project for Raspberry Pi Pico using Visual Studio Code and the Pico SDK.

## Installation Steps

### Platform-Specific Instructions

If you are on a platform other than Windows, please refer to the official Raspberry Pi Pico documentation for detailed instructions:

[Getting Started with Raspberry Pi Pico (PDF)](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)

1. **Download the Latest Release:**
   - Visit the [GitHub repository](https://github.com/example/repository).
   - Download the latest release by clicking "Download the latest release."

2. **Install the Executable:**
   - Run the downloaded executable installer.
   - Follow on-screen instructions, ensuring to select "Clone and build example in this folder" before clicking "Finish."
   - ![image](https://github.com/eSpark-Consultants/joshuabrewster-eeg-fnirs/assets/106241042/35fcb878-1198-477c-b8c5-43fe0e929dbf)
   - If you see this output then everything is installed properly.
   - ![image](https://github.com/eSpark-Consultants/joshuabrewster-eeg-fnirs/assets/106241042/0d024d45-054c-4ad3-a359-dc23ff465572)


3. **Open Project in Visual Studio Code:**
   - Navigate to the project folder where the executable was installed.
   - Open the folder in Visual Studio Code.

4. **Configure GCC 10.3.1 ARM-none-eabi Compiler:**
   - If not already installed, install the CMake extension.
   - Navigate to the CMake extension in Visual Studio Code.
   - Configure GCC 10.3.1 ARM-none-eabi compiler.
   - ![image](https://github.com/eSpark-Consultants/joshuabrewster-eeg-fnirs/assets/106241042/040aa6c9-953b-4a6e-9b0e-288f600c5be4)


## Troubleshooting

If you encounter errors during setup, follow these steps:

- **PICO_SDK_PATH Error:**
  - If encountering errors related to `PICO_SDK_PATH`, add a new environmental variable:
    - Variable Name: `PICO_SDK_PATH`
    - Variable Value: `C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\pico-sdk`

- **Ninja Error:**
  - If encountering errors related to Ninja, add the following path in environmental variables :
    - `C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\ninja`

## Building the Project

Once setup is complete and any issues are addressed:

- Click "Build" within Visual Studio Code to build the project.

## UF2 File Location

After successfully building the project, the UF2 file will be located in the build folder.
