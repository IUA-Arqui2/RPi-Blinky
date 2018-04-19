#include "hal/rpi-gpio.h"

int notmain ( void )
{
    volatile unsigned long int cont;
    unsigned int estado = 0;
    RPI_GetGpio()->LED_GPFSEL |= 1 << LED_GPFBIT;
    LED_ON();
    LED_OFF();
    while(1){
        
        //delay
        for(cont = 0; cont < 400000; cont++)
        ;
        
        if(estado){
            estado = 0;
            LED_ON();
        } else{
            estado = 1;
            LED_OFF();
        }
    }
    return(0);
}
