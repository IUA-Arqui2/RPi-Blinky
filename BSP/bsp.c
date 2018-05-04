#include  "bsp.h"
#include  "HAL/rpi-gpio.h"
gpio_t pines[3];

void bsp_init(){
    pines[0].func = 1;
    pines[1].func = 1;
    pines[2].func = 1;
    
    pines[0].num = 2;
    pines[1].num = 3;
    pines[2].num = 4;
    
    gpio_init(pines[0]);
    gpio_init(pines[1]);
    gpio_init(pines[2]);
}

void led_off( leds_t pin){
    gpio_off(pines[pin]);
}
void led_on( leds_t pin){
    gpio_on(pines[pin]);
}

 void delay_ms(uint32_t ms){
    volatile uint32_t cont = ms;
    volatile float mili;
    
    while(cont){
        cont--;
        for( mili=0 ; mili < 5 ; mili+=0.1){}
    }
}
