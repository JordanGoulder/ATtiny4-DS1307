#include <util/delay.h>
#include <stdint.h>

#include "i2c.h"

int main(void)
{
    i2c_init();

    // Eanble the oscillator
    i2c_write_byte(0xD0, 1, 0);
    i2c_write_byte(0x00, 0, 0);
    i2c_write_byte(0x00, 0, 1);

    // Setup 1Hz square wave output
    i2c_write_byte(0xD0, 1, 0);
    i2c_write_byte(0x07, 0, 0);
    i2c_write_byte(0x10, 0, 1);

    while (1) {
        // Read the seconds value
        i2c_write_byte(0xD0, 1, 0);
        i2c_write_byte(0x00, 0, 0);
        i2c_write_byte(0xD1, 1, 0);
        i2c_read_byte(0, 1);

        _delay_ms(100);
    }

    return 0;
}

