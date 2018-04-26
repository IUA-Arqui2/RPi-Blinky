#include <stdint.h>
 typedef enum {
     led_r,
     led_g,
     led_b
 } leds_t;
 
 void bsp_init();
 void led_off( leds_t pin);
 void led_on( leds_t pin);
 void delay_ms(uint32_t ms);
