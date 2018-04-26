#include "BSP/bsp.h"

int notmain ( void )
{
    unsigned int estado = 0;
    static leds_t r = led_r;
    bsp_init();
    
    while(1){
        //delay
        delay_ms(1000);
        
        if (estado) {
            estado = 0;
            led_on(r);
        } else {
            estado = 1;
            led_off(r);
        }
    }
    return(0);
}
