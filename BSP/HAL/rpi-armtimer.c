
#include <stdint.h>
#include "rpi-armtimer.h"

static rpi_arm_timer_t* rpiArmTimer = (rpi_arm_timer_t*)RPI_ARMTIMER_BASE;

rpi_arm_timer_t* RPI_GetArmTimer(void)
{
    return rpiArmTimer;
}

void RPI_ArmTimerInit(void)
{
    RPI_GetArmTimer()->Control = RPI_ARMTIMER_CTRL_23BIT | RPI_ARMTIMER_CTRL_PRESCALE_1 |
                                RPI_ARMTIMER_CTRL_ENABLE | RPI_ARMTIMER_CTRL_INT_ENABLE;
}

void RPI_ClearIRQ(void){
    RPI_GetArmTimer()->IRQClear = 1;
}
