#include <util/delay.h>
#include <stdint.h>

#include "i2c.h"

int main(void)
{
    i2c_init();

    // Eanble the oscillator
    i2c_start_condition();
    i2c_write_byte(0xD0);
    i2c_write_byte(0x00);
    i2c_write_byte(0x00);
    i2c_stop_condition();

    // Setup 1Hz square wave output
    i2c_start_condition();
    i2c_write_byte(0xD0);
    i2c_write_byte(0x07);
    i2c_write_byte(0x10);
    i2c_stop_condition();

    while (1) {
        // Read the seconds value
        i2c_start_condition();
        i2c_write_byte(0xD0);
        i2c_write_byte(0x00);
        i2c_start_condition();
        i2c_write_byte(0xD1);
        i2c_read_byte(1);
        i2c_stop_condition();

        _delay_ms(100);
    }

    return 0;
}

