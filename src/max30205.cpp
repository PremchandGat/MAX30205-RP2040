/*
    Written By Premchand Gat
    Github: PremchandGat
    Email: Premchandg278@gmail.com
*/

#include "max30205.h"

MAX30205::MAX30205(i2c_inst_t *i2c)
{
    _i2c = i2c;
}

/* Read Address */
void MAX30205::read_addr(uint8_t reg, uint8_t *buf, int len)
{
    if (i2c_write_blocking(_i2c, MAX30205_ADDR, &reg, 1, true) /*true to keep master control of bus*/ == PICO_ERROR_GENERIC)
    {
        /* Device not found */
        printf("MAX30205 Not found\n");
    };
    if (i2c_read_blocking(_i2c, MAX30205_ADDR, buf, len, false) /* false - finished with bus */ == PICO_ERROR_GENERIC)
    {
        /* Device not found */
        printf("MAX30205 Not found\n");
    }
}

/* Write Data */
void MAX30205::write_byte(uint8_t *buffer, int len)
{
    /*  buffer = {ADDRESS, value1, value2, ..... valueN }
        len = Elements in buffer
    */
    i2c_write_blocking(_i2c, MAX30205_ADDR, buffer, len, false);
}

/* Read Temprature */
float MAX30205::readTemprature()
{
    uint8_t readRaw[2];
    read_addr(MAX30205_TEMPRATURE_REG, readRaw, 2);
    int16_t raw = readRaw[0] << 8 | readRaw[1]; // combine two bytes
    return raw * 0.00390625;                    // convert to temperature
}