
#ifndef IRQ_APP_H
#define IRQ_APP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "plic/plic_driver.h"
#include "encoding.h"

plic_instance_t g_plic;
typedef void (*function_ptr_t) (void);
void no_interrupt_handler (void);
function_ptr_t g_ext_interrupt_handlers[PLIC_NUM_INTERRUPTS];

void init_plic();
void lock_irqs();
void enable_irqs();

#endif