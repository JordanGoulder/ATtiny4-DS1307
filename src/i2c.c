#include <avr/io.h>
#include <util/delay.h>

#define SCL (PORTB1)
#define SDA (PORTB0)

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

static void     delay(void);
static void     set_bit(uint8_t pin);
static void     clr_bit(uint8_t pin);
static void     start_condition(void);
static void     stop_condition(void);
static void     write_bit(uint8_t b);
static uint8_t  read_bit(void);
static uint8_t     write_byte(uint8_t data, uint8_t start, uint8_t stop);

void i2c_init(void)
{
    DDRB &= ~(_BV(SCL) | _BV(SDA));

    PORTB &= ~(_BV(SCL) | _BV(SDA));

    delay();
}

void delay(void)
{
    _delay_us(10);
}

void set_bit(uint8_t pin)
{
    DDRB &= ~_BV(pin);
}

void clr_bit(uint8_t pin)
{
    DDRB |= _BV(pin);
}

void start_condition(void)
{
    set_bit(SCL);
    set_bit(SDA);
    delay();
    clr_bit(SDA);
    delay();
    clr_bit(SCL);
    delay();
}

void stop_condition(void)
{
    clr_bit(SDA);
    delay();
    set_bit(SCL);
    delay();
    set_bit(SDA);
    delay();
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

    b = (PORTB >> SDA) & 0x01;

    clr_bit(SCL);

    return b;
}

static uint8_t write_byte(uint8_t data, uint8_t start, uint8_t stop)
{
    uint8_t ack = 0;

    if (start) { start_condition(); }

    for (uint8_t i = 0; i < 8; i++) {
        write_bit(data & 0x80);
        data <<= 1;
    }

    ack = read_bit();

    if (stop) { start_condition(); }

    if (ack == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

static uint8_t read_byte(uint8_t ack, uint8_t stop)
{
    uint8_t data = 0;

    for (uint8_t i = 0; i < 8; i++) {
        data <<= 1;
        data |= read_bit();
    }

    if (ack) {
        write_bit(0);
    } else {
        write_bit(1);
    }

    if (stop) { stop_condition(); }

    return data;
}
