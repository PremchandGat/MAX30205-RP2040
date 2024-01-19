/*
    Written By Premchand Gat
    Github: PremchandGat
    Email: Premchandg278@gmail.com
*/
/* This openocd command i used to connect debugger */
// sudo openocd -f interface/cmsis-dap.cfg -c "adapter speed 5000" -f target/rp2040.cfg -s tcl

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include <stdio.h>
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "src/max30205.cpp"
#include "hardware/gpio.h"
#include "hardware/irq.h"

#define I2C_SDA 8
#define I2C_SCL 9
#define I2C_ID i2c0
#define MAX30205_INT_PIN 7
MAX30205 max30205(I2C_ID);

void initializeI2C(){
    // useful information for picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    bi_decl(bi_program_description("MAX30205 I2C Example Code"));
    // I2C is "open drain", pull ups to keep signal high when no data is being sent
    i2c_init(I2C_ID, 100000);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

int main(){
    stdio_init_all();
    initializeI2C();
    while (true)
    {
        printf("Temprature %f\n", max30205.readTemprature());
        sleep_ms(1000);
    }
    return 0;
}