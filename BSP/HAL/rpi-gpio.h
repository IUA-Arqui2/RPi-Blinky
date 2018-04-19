#ifndef RPI_GPIO_H
#define RPI_GPIO_H

typedef struct{
    uint8_t func;
    uint8_t num;
}gpio_t;

inline void gpio_init(gpio_t pin);
inline void gpio_on(gpio_t pin);
inline void gpio_off(gpio_t pin);



/***/
#define RPI_GPIO_FSEL0_00_INPUT     ( 0 )
#define RPI_GPIO_FSEL0_00_OUTPUT    ( 1 )

#endif
