#include "BSP/bsp.h"
#include "BSP/HAL/gpu.h"


#define SCREEN_WIDTH    1024
#define SCREEN_HEIGHT   768
#define SCREEN_BPP      16


int notmain ( void )
{
    
    bsp_init();
    uint32_t black = 0xffff;

    // Checkerboard pattern
    uint16_t* screen = gpu_init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);

    while(1){
        for (int y=0 ; y<SCREEN_HEIGHT ; y++) {
            for (int x=0 ; x<SCREEN_WIDTH ; x++) {
                int a = (y / 50) % 2;
                int b = (x / 50) % 2;
                if ((a^b) == 1)
                    screen[y*SCREEN_WIDTH+x] = black--;
                else
                    screen[y*SCREEN_WIDTH+x] = 0x0000;
            }
        }
    }
    return(0);
}
