#include <util/delay.h>
#include <stdint.h>

#include "i2c.h"

int main(void)
{
    i2c_init();

    _delay_ms(1000);

    i2c_write_byte(0xD0, 1, 0);
    i2c_write_byte(0x07, 0, 0);
    i2c_write_byte(0x90, 0, 1);

    while (1);

    return 0;
}

