#ifndef I2C_H
#define I2C_H

void    i2c_init(void);
void    i2c_start_condition(void);
void    i2c_stop_condition(void);
uint8_t i2c_write_byte(uint8_t data);
uint8_t i2c_read_byte(uint8_t ack);

#endif // I2C_H
