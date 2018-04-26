
#include <stdint.h>
#include "rpi.h"
#include "rpi-gpio.h"

#define RPI_GPIO_BASE       ( PERIPHERAL_BASE + 0x200000UL )

typedef struct {
    rpi_reg_rw_t    GPFSEL[6];
    rpi_reg_ro_t    Reserved0;
    rpi_reg_wo_t    GPSET[2];
    rpi_reg_ro_t    Reserved1;
    rpi_reg_wo_t    GPCLR[2];
    rpi_reg_ro_t    Reserved2;
    rpi_reg_wo_t    GPLEV0;
    rpi_reg_wo_t    GPLEV1;
    rpi_reg_ro_t    Reserved3;
    rpi_reg_wo_t    GPEDS0;
    rpi_reg_wo_t    GPEDS1;
    rpi_reg_ro_t    Reserved4;
    rpi_reg_wo_t    GPREN0;
    rpi_reg_wo_t    GPREN1;
    rpi_reg_ro_t    Reserved5;
    rpi_reg_wo_t    GPFEN0;
    rpi_reg_wo_t    GPFEN1;
    rpi_reg_ro_t    Reserved6;
    rpi_reg_wo_t    GPHEN0;
    rpi_reg_wo_t    GPHEN1;
    rpi_reg_ro_t    Reserved7;
    rpi_reg_wo_t    GPLEN0;
    rpi_reg_wo_t    GPLEN1;
    rpi_reg_ro_t    Reserved8;
    rpi_reg_wo_t    GPAREN0;
    rpi_reg_wo_t    GPAREN1;
    rpi_reg_ro_t    Reserved9;
    rpi_reg_wo_t    GPAFEN0;
    rpi_reg_wo_t    GPAFEN1;
    rpi_reg_ro_t    Reserved10;
    rpi_reg_wo_t    GPPUD;
    rpi_reg_wo_t    GPPUDCLK0;
    rpi_reg_wo_t    GPPUDCLK1;
    rpi_reg_ro_t    Reserved11;
} rpi_gpio_t;


static rpi_gpio_t* rpiGpio = (rpi_gpio_t*)RPI_GPIO_BASE;

inline void gpio_init(gpio_t pin)
{
    rpiGpio->GPFSEL[pin.num/10] |= (pin.func << (pin.num%10*3));
}

inline void gpio_on(gpio_t pin)
{
    rpiGpio->GPSET[pin.num/32] = (pin.func << (pin.num%32));
}

inline void gpio_off(gpio_t pin)
{
    rpiGpio->GPCLR[pin.num/32] = (pin.func << (pin.num%32));
}



