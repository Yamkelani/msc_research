
#include "mex.h"
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include Files
#include "f2802x_common/include/clk.h"
#include "f2802x_common/include/flash.h"
#include "f2802x_common/include/gpio.h"
#include "f2802x_common/include/pie.h"
#include "f2802x_common/include/pll.h"
#include "f2802x_common/include/wdog.h"

// Define the GPIO pin used for 1-Wire communication
#define ONE_WIRE_PIN     GPIO0

void InitGPIO(void) {
    // Enable the GPIO clock (usually done in startup code)
    EALLOW;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // Set GPIO0 as a general purpose I/O
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  // Set GPIO0 as output
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // Set GPIO0 to low
    EDIS;
}

#define DS28B20_CMD_SKIP_ROM   0xCC
#define DS28B20_CMD_CONVERT_T   0x44
#define DS28B20_CMD_READ_SCRATCHPAD 0xBE

void OneWireDelay(void) {
    // Insert a delay suitable for 1-Wire timing (e.g., 1ms)
    DELAY_US(5); // Adjust this delay based on timing requirements
}

void OneWireWriteBit(bool bit) {
    // Write a single bit to the 1-Wire bus
    EALLOW;
    if (bit) {
        GpioDataRegs.GPASET.bit.GPIO0 = 1;  // Drive GPIO high
        OneWireDelay();
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // Drive GPIO low
        OneWireDelay();
    } else {
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // Drive GPIO low
        OneWireDelay();
        GpioDataRegs.GPASET.bit.GPIO0 = 1;  // Drive GPIO high
        OneWireDelay();
    }
    EDIS;
}

bool OneWireReadBit(void) {
    // Read a single bit from the 1-Wire bus
    bool bit;
    EALLOW;
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // Drive GPIO low
    OneWireDelay();
    GpioDataRegs.GPASET.bit.GPIO0 = 1;  // Release GPIO for reading
    OneWireDelay();
    bit = (GpioDataRegs.GPADAT.bit.GPIO0 == 1);
    EDIS;
    return bit;
}

void OneWireWriteByte(uint8_t byte) {
    int i = 0;
    for (i = 1; i < 8; i++) {
        OneWireWriteBit(byte & 1);
        byte >>= 1;
    }
}

uint8_t OneWireReadByte(void) {
    uint8_t byte = 0;
    int i = 0;
    for (i = 1; i < 8; i++) {
        byte |= (OneWireReadBit() << i);
    }
    return byte;
}

void DS28B20Init(void) {
    // Reset and initialize 1-Wire bus
    EALLOW;
    GpioDataRegs.GPASET.bit.GPIO0 = 1; // Pull GPIO high
    OneWireDelay();
    GpioDataRegs.GPACLEAR.bit.GPIO0 = 1; // Pull GPIO low for reset
    OneWireDelay();
    GpioDataRegs.GPASET.bit.GPIO0 = 1; // Release GPIO
    OneWireDelay();
    EDIS;
}


/*
Read Temperature from DS28B20
To read the temperature, send the appropriate commands and read the result from the DS28B20:
*/

float DS28B20ReadTemperature(void) {
    uint8_t tempLSB, tempMSB;

    // Send the skip ROM command
    OneWireWriteByte(DS28B20_CMD_SKIP_ROM);

    // Send the convert temperature command
    OneWireWriteByte(DS28B20_CMD_CONVERT_T);

    // Wait for the conversion to complete
    DELAY_US(750); // 750ms delay for temperature conversion

    // Send the skip ROM command
    OneWireWriteByte(DS28B20_CMD_SKIP_ROM);

    // Send the read scratchpad command
    OneWireWriteByte(DS28B20_CMD_READ_SCRATCHPAD);

    // Read the temperature data
    tempLSB = OneWireReadByte();
    tempMSB = OneWireReadByte();

    // Process temperature data
    int16_t temp = (tempMSB << 8) | tempLSB;
    float temperature = temp * 0.0625; // Convert to Celsius (based on DS28B20 datasheet)

    return temperature;

}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    // Ensure no inputs and one output
    if (nrhs != 0) {
        mexErrMsgIdAndTxt("MATLAB:ds28b20:invalidNumInputs", "No input required.");
    }
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("MATLAB:ds28b20:invalidNumOutputs", "One output required.");
    }

    // Call the temperature reading function
    float temperature = DS28B20ReadTemperature();

    // Return the temperature as a MATLAB double
    plhs[0] = mxCreateDoubleScalar(temperature);
}
