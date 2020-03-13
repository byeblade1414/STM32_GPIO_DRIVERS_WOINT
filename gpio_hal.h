#ifndef _GPIO_HAL_INCLUDED
#define _GPIO_HAL_INCLUDED

#ifndef __STM32F10x_H
#include <stm32f10x.h> // in case the device header file is not included.
#endif

//macros for determining for both corresponding cnf and mode bits.
#define MODE_BITS_0(x) 	(1 << 4*x)
#define MODE_BITS_1(x) 	(1 << ((4*x)+1))
#define CNF_BITS_0(x) 	(1 << ((4*x)+2))
#define CNF_BITS_1(x) 	(1 << ((4*x)+3))

//macros for both setting and clearing two equal size numbers (they are equal in bit size)

#ifdef SET_BIT
#undef SET_BIT
#define SET_BIT(x,y) (x |= y)
#endif

#ifdef CLEAR_BIT
#undef CLEAR_BIT
#define CLEAR_BIT(x,y) (x &= ~y)
#endif

typedef enum{
	SPEED_2_MHZ,
	SPEED_10MHZ,
	SPEED_50MHZ
}GPIO_SPEED;


typedef enum{
	// output mode
	OUT_PUSH_PULL,
	OUT_OPEN_DRAIN,
	OUT_ALT_PUSH_PULL,
	OUT_ALT_OPEN_DRAIN,
	//input mode
	IN_ANALOG,
	IN_FLOATING,
	IN_PULLUP_PULLDOWN
}GPIO_CNF;

typedef enum{
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE
}edge_select;

void gpio_init(GPIO_TypeDef *port,GPIO_CNF cnf,GPIO_SPEED speed,uint8_t pinNumber);
void config_pin(GPIO_TypeDef *port,uint8_t pinNumber,GPIO_CNF cnf);
void enable_GPIO_clock(GPIO_TypeDef *gpio);
void setPin(GPIO_TypeDef *gpio,uint8_t pinNumber);
void clearPin(GPIO_TypeDef *gpio,uint8_t pinNumber);
void setOutputSpeed(GPIO_TypeDef *gpio,uint8_t pinNumber,GPIO_SPEED speed);
#endif
