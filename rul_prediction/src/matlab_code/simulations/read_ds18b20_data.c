#include "F2802x_Device.h"  // Device-specific header file
#include "F2802x_Headers.h" // General header file
#include "F2802x_GlobalPrototypes.h" // Function prototypes
#include "F2802x_Lib.h" // Libraries


// Define the pin number for the DS18B20
#define DS18B20_PIN GPIO0

// Function to drive GPIO low
void GPIO_WRITE_LOW(uint32_t pin) {
    GPIO_writePin(pin, 0);  // Use GPIO_writePin to drive the pin low
}

// Function to drive GPIO high
void GPIO_WRITE_HIGH(uint32_t pin) {
    GPIO_writePin(pin, 1);  // Use GPIO_writePin to drive the pin high
}

// Function to read GPIO value
uint8_t GPIO_READ(uint32_t pin) {
    return GPIO_readPin(pin);  // Use GPIO_readPin to read the pin value
}


// Reset and presence pulse
void ds18b20_reset(void) {
    GPIO_WRITE_LOW(DS18B20_PIN); 
    DELAY_US(480);  // 480 µs delay

    GPIO_WRITE_HIGH(DS18B20_PIN); 
    DELAY_US(70);  // 70 µs delay

    if (GPIO_READ(DS18B20_PIN) == 0) {
        // Presence pulse detected
    } else {
        // No presence pulse, error
    }
}

// Write a byte to the DS18B20
void ds18b20_write_byte(uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        if (byte & 0x01) {
            GPIO_WRITE_LOW(DS18B20_PIN);
            DELAY_US(1);  // 1 µs delay
            GPIO_WRITE_HIGH(DS18B20_PIN);
            DELAY_US(60); // 60 µs delay
        } else {
            GPIO_WRITE_LOW(DS18B20_PIN);
            DELAY_US(60); // 60 µs delay
            GPIO_WRITE_HIGH(DS18B20_PIN);
            DELAY_US(1); // 1 µs delay
        }
        byte >>= 1;
    }
}

// Read a byte from the DS18B20
uint8_t ds18b20_read_byte(void) {
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++) {
        GPIO_WRITE_LOW(DS18B20_PIN);
        DELAY_US(1);  // 1 µs delay
        GPIO_WRITE_HIGH(DS18B20_PIN);
        DELAY_US(10); // 10 µs delay

        if (GPIO_READ(DS18B20_PIN) == 1) {
            byte |= (1 << i);
        }
        DELAY_US(50); // 50 µs delay
    }
    return byte;
}

// Read temperature from DS18B20
float ds18b20_read_temperature(void) {
    ds18b20_reset();
    ds18b20_write_byte(0xCC);  // Skip ROM command
    ds18b20_write_byte(0x44);  // Start conversion command

    DELAY_MS(750); // Wait for conversion to complete

    ds18b20_reset();
    ds18b20_write_byte(0xCC);  // Skip ROM command
    ds18b20_write_byte(0xBE);  // Read Scratchpad command

    uint8_t lsb = ds18b20_read_byte();
    uint8_t msb = ds18b20_read_byte();

    int16_t temp = (msb << 8) | lsb;
    return temp * 0.0625;  // Convert to Celsius
}
