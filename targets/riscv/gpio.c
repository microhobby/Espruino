
#include "gpio.h"

uint32_t gpio_offsets[20] = {
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	0,
	1,
	2,
	3,
	4,
	5,
	8, /* pin14 appear not be connected on HiFive1 */
	9,
	10,
	11,
	12,
	13
};

void gpio_output(unsigned int pin)
{
	GPIO_REG(GPIO_INPUT_EN) &= ~(0x1 << gpio_offsets[pin]);
	GPIO_REG(GPIO_OUTPUT_EN) |= (0x1 << gpio_offsets[pin]);
}

void gpio_input(unsigned int pin) 
{
	GPIO_REG(GPIO_OUTPUT_EN) &= ~(0x1 << gpio_offsets[pin]);
	GPIO_REG(GPIO_INPUT_EN) |= (0x1 << gpio_offsets[pin]);
}

void gpio_pulled(unsigned int pin, unsigned int level)
{
	/* not implemented yet */
	// TODO
}

void gpio_level(unsigned int pin, unsigned int level)
{
	/* check if pin is input */
	if (GPIO_REG(GPIO_INPUT_EN) & (0x1 << gpio_offsets[pin]))
		return; /* input nop */

	if (level)
		GPIO_REG(GPIO_OUTPUT_VAL) |= (0x1 << gpio_offsets[pin]);
	else
		GPIO_REG(GPIO_OUTPUT_VAL) &= ~(0x1 << gpio_offsets[pin]);
}

unsigned int gpio_read_level(unsigned int pin)
{
	/* check if pin is input */
	if (GPIO_REG(GPIO_INPUT_EN) & (0x1 << gpio_offsets[pin]))
		return !!(GPIO_REG(GPIO_INPUT_VAL) & (0x1 << gpio_offsets[pin]));
	else
		return !!(GPIO_REG(GPIO_OUTPUT_VAL) & (0x1 << gpio_offsets[pin]));

	return 0;
}

unsigned int gpio_read_mux(unsigned int pin)
{
	/* check if is input */
	if (GPIO_REG(GPIO_INPUT_EN) & (0x1 << gpio_offsets[pin]))
		return 1;
	else if (GPIO_REG(GPIO_OUTPUT_EN) & (0x1 << gpio_offsets[pin]))
		return 2;

	return 0;
}
