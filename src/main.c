#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "i2c.h"
#include "bcd.h"

int main(void)
{
    DDRB |= _BV(DDB0);

    i2c_init();

    // Eanble the oscillator
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x00);
    i2c_write(0x00);
    i2c_stop();

    // Setup 1Hz square wave output
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x07);
    i2c_write(0x10);
    i2c_stop();

    while (1) {
        // Read the seconds value
        i2c_start();
        i2c_write(0xD0);
        i2c_write(0x00);
        i2c_start();
        i2c_write(0xD1);
        uint8_t bcd_secs = 0x7F & i2c_read(1);
        i2c_stop();

        uint8_t secs = bcd_to_bin(bcd_secs);

        if (secs == 59) {
            PORTB |= _BV(PORTB0);
        } else {
            PORTB &= ~_BV(PORTB0);
        }

        _delay_ms(100);
    }

    return 0;
}

