#ifndef GPIO_APP_H
#define GPIO_APP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "plic/plic_driver.h"
#include "encoding.h"

void gpio_output(unsigned int pin);
void gpio_input(unsigned int pin);
void gpio_pulled(unsigned int pin, unsigned int level);
void gpio_level(unsigned int pin, unsigned int level);
unsigned int gpio_read_level(unsigned int pin);
unsigned int gpio_read_mux(unsigned int pin);

#endif