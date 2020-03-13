#include "../inc/gpio_hal.h"

#include <stm32f10x.h>

void gpio_init(GPIO_TypeDef *port,GPIO_CNF cnf,GPIO_SPEED speed,uint8_t pinNumber)
{
	//GPIO INIT FUNCTION
	enable_GPIO_clock(port);
	setOutputSpeed(port,pinNumber,speed);
	config_pin(port,pinNumber,cnf);

}


void config_pin(GPIO_TypeDef *port,uint8_t pinNumber,GPIO_CNF cnf)
{
	if(pinNumber <= 7)
	{
		if(cnf == OUT_PUSH_PULL)
		{
			CLEAR_BIT(port->CRL,CNF_BITS_1(pinNumber));
			CLEAR_BIT(port->CRL,CNF_BITS_0(pinNumber));
		}
		if(cnf == OUT_OPEN_DRAIN)
		{
			CLEAR_BIT(port->CRL,CNF_BITS_1(pinNumber));
			SET_BIT(port->CRL,CNF_BITS_0(pinNumber));
		}
		if(cnf == OUT_ALT_PUSH_PULL)
		{
			SET_BIT(port->CRL,CNF_BITS_1(pinNumber));
			CLEAR_BIT(port->CRL,CNF_BITS_0(pinNumber));
		}
		if(cnf == OUT_ALT_OPEN_DRAIN)
		{
			SET_BIT(port->CRL,CNF_BITS_1(pinNumber));
			SET_BIT(port->CRL,CNF_BITS_0(pinNumber));
		}
		if(cnf == IN_ANALOG)
		{
			CLEAR_BIT(port->CRL,CNF_BITS_1(pinNumber));
			CLEAR_BIT(port->CRL,CNF_BITS_0(pinNumber));
		}
		if(cnf == IN_FLOATING) // reset state
		{
			CLEAR_BIT(port->CRL,CNF_BITS_1(pinNumber));
			SET_BIT(port->CRL,CNF_BITS_0(pinNumber));
		}
		if(cnf == IN_PULLUP_PULLDOWN)
		{
			SET_BIT(port->CRL,CNF_BITS_1(pinNumber));
			CLEAR_BIT(port->CRL,CNF_BITS_0(pinNumber));
		}
	}

	else if(pinNumber >= 8)
	{
		if(cnf == OUT_PUSH_PULL)
			{
				CLEAR_BIT(port->CRH,CNF_BITS_1((pinNumber-8)));
				CLEAR_BIT(port->CRH,CNF_BITS_0((pinNumber-8)));
			}
			if(cnf == OUT_OPEN_DRAIN)
			{
				CLEAR_BIT(port->CRH,CNF_BITS_1((pinNumber-8)));
				SET_BIT(port->CRH,CNF_BITS_0((pinNumber-8)));
			}
			if(cnf == OUT_ALT_PUSH_PULL)
			{
				SET_BIT(port->CRH,CNF_BITS_1((pinNumber-8)));
				CLEAR_BIT(port->CRH,CNF_BITS_0((pinNumber-8)));
			}
			if(cnf == OUT_ALT_OPEN_DRAIN)
			{
				SET_BIT(port->CRH,CNF_BITS_1((pinNumber-8)));
				SET_BIT(port->CRH,CNF_BITS_0((pinNumber-8)));
			}
			if(cnf == IN_ANALOG)
			{
				CLEAR_BIT(port->CRH,CNF_BITS_1((pinNumber-8)));
				CLEAR_BIT(port->CRH,CNF_BITS_0((pinNumber-8)));
			}
			if(cnf == IN_FLOATING) // reset state
			{
				CLEAR_BIT(port->CRH,CNF_BITS_1((pinNumber-8)));
				SET_BIT(port->CRH,CNF_BITS_0((pinNumber-8)));
			}
			if(cnf == IN_PULLUP_PULLDOWN)
			{
				SET_BIT(port->CRH,CNF_BITS_1((pinNumber-8)));
				CLEAR_BIT(port->CRH,CNF_BITS_0((pinNumber-8)));
			}
	}
}

void enable_GPIO_clock(GPIO_TypeDef *gpio)
{
	if(gpio == GPIOA)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	if(gpio == GPIOB)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	if(gpio == GPIOC)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	if(gpio == GPIOD)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
	}
}

void setPin(GPIO_TypeDef *gpio, uint8_t pinNumber)
{
	gpio->BSRR = (1 << (pinNumber));
}

void clearPin(GPIO_TypeDef *gpio,uint8_t pinNumber)
{
	gpio->BSRR = (1 << (pinNumber+16));
}

void setOutputSpeed(GPIO_TypeDef *gpio,uint8_t pinNumber,GPIO_SPEED speed)
{
	if(pinNumber <= 7)
	{
		if(speed == SPEED_10MHZ)
		{
			CLEAR_BIT(gpio->CRL,MODE_BITS_1(pinNumber));
			SET_BIT(gpio->CRL,MODE_BITS_0(pinNumber));
		}
		if(speed == SPEED_2_MHZ)
		{
			SET_BIT(gpio->CRL,MODE_BITS_1(pinNumber));
			CLEAR_BIT(gpio->CRL,MODE_BITS_0(pinNumber));
		}
		if(speed == SPEED_50MHZ)
		{
			SET_BIT(gpio->CRL,MODE_BITS_1(pinNumber));
			SET_BIT(gpio->CRL,MODE_BITS_0(pinNumber));
		}
	}
	else if(pinNumber >= 8)
	{
		if(speed == SPEED_10MHZ)
		{
			CLEAR_BIT(gpio->CRH,MODE_BITS_1((pinNumber-8)));
			SET_BIT(gpio->CRH,MODE_BITS_0((pinNumber-8)));
		}
		if(speed == SPEED_2_MHZ)
		{
			SET_BIT(gpio->CRH,MODE_BITS_1((pinNumber-8)));
			CLEAR_BIT(gpio->CRH,MODE_BITS_0((pinNumber-8)));
		}
		if(speed == SPEED_50MHZ)
		{
			SET_BIT(gpio->CRH,MODE_BITS_1((pinNumber-8)));
			SET_BIT(gpio->CRH,MODE_BITS_0((pinNumber-8)));
		}
	}
}

