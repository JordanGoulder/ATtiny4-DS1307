#ifndef I2C_H
#define I2C_H

void    i2c_init(void);
uint8_t i2c_write_byte(uint8_t data, uint8_t start, uint8_t stop);
uint8_t i2c_read_byte(uint8_t ack, uint8_t stop);

#endif // I2C_H
