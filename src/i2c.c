#include <avr/io.h>
#include <util/delay.h>

#define SCL (PORTB1)
#define SDA (PORTB2)

static void     delay(void);
static void     set_bit(uint8_t pin);
static void     clr_bit(uint8_t pin);
static void     write_bit(uint8_t b);
static uint8_t  read_bit(void);

void i2c_init(void)
{
    DDRB &= ~_BV(SCL);
    DDRB &= ~_BV(SDA);

    PORTB &= ~_BV(SCL);
    PORTB &= ~_BV(SDA);
}

void i2c_start(void)
{
    set_bit(SCL);
    set_bit(SDA);
    delay();
    clr_bit(SDA);
    delay();
    clr_bit(SCL);
    delay();
}

void i2c_stop(void)
{
    clr_bit(SDA);
    delay();
    set_bit(SCL);
    delay();
    set_bit(SDA);
    delay();
}

uint8_t i2c_write(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++) {
        write_bit(data & 0x80);
        data <<= 1;
    }

    return (read_bit());
}

uint8_t i2c_read(uint8_t ack)
{
    uint8_t data = 0;

    for (uint8_t i = 0; i < 8; i++) {
        data <<= 1;
        if (read_bit()) {
            data |= 0x01;
        }
    }

    write_bit(ack);

    return data;
}

void __attribute__ ((noinline)) delay(void)
{
    _delay_us(5);
}

void set_bit(uint8_t pin)
{
    DDRB &= ~_BV(pin);
}

void clr_bit(uint8_t pin)
{
    DDRB |= _BV(pin);
}

void write_bit(uint8_t b)
{
    if (b > 0) {
        set_bit(SDA);
    } else {
        clr_bit(SDA);
    }

    delay();
    set_bit(SCL);
    delay();
    clr_bit(SCL);
}

uint8_t read_bit(void)
{
    uint8_t b;

    set_bit(SDA);
    delay();
    set_bit(SCL);
    delay();

    b = PORTB & _BV(SDA);

    clr_bit(SCL);

    return b;
}

