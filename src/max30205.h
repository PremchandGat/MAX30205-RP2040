/*
    Written By Premchand Gat
    Github: PremchandGat
    Email: Premchandg278@gmail.com
*/

#pragma once
#include <stdio.h>
#include "hardware/i2c.h"

/* --------------------------------------------------------- MAX30205 Register Map ------------------------------------------------------*/
#define MAX30205_TEMPRATURE_REG 0x00    // Read Only
#define MAX30205_CONFIGURATION_REG 0x01 // Read/Write
#define MAX30205_THYST_REG 0x02         // Read/Write
#define MAX30205_TOS_REG 0x03           // Read/Write

/*
LOGIC INPUTS    I2C SLAVE ADDRESS
A2  A1  A0      B7  B6  B5  B4  B3  B2  B1  R/W     READ ADD    WRITE ADD
0   0   0       1   0   0   1   0   0   0   1/0     0x91        0x90
*/
#define MAX30205_ADDR 0x48 // 7 (1001000) Bit address

/*
                UPPER BYTE                                        |                                 LOWER BYTE
    D15     D14     D13     D12     D11     D10     D9      D8    |  D7      D6      D5      D4      D3      D2      D1      D0
    S       64      32      16      8       4       2       1     |  1/2     1/4     1/8     1/16    1/32    1/64    1/128   1/256
            2^6     2^5     2^4     2^3     2^2     2^1     2^0   |  2^-1    2^-2    2^-3    2^-4    2^-5    2^-6    2^-7    2^-8
*/
/*----------------------------------------------------------------END-----------------------------------------------------------------*/

#define INT_MASK 0x2

class MAX30205
{
public:
    MAX30205(i2c_inst_t *i2c);
    float readTemprature(void);
    void setupIntruppt(void);
    void setIntruppt(uint8_t *currTempBytes);

private:
    void read_addr(uint8_t reg, uint8_t *buf, int len);
    void write_byte(uint8_t *buffer, int len);
    i2c_inst_t *_i2c;
};