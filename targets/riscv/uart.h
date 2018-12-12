
#ifndef UART_APP_H
#define UART_APP_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "platform.h"
#include "platform_config.h"
#include "encoding.h"
#include "sifive/devices/uart.h"
#include "irq.h"

enum {
  UART_RXBUF_SIZE = (1 << 3),
  UART_RXBUF_MASK = (UART_RXBUF_SIZE - 1)
};

volatile uint8_t rxbuf_head;
volatile uint8_t rxbuf_tail;
char rxbuf[UART_RXBUF_SIZE];

void UART_init(unsigned long baud, int stop_bits);
void UART_deinit();
void UART_set_baud(unsigned long baud);
void UART_set_stop_bits(int stop_bits);
int UART_put_char(char ch, int blocking);
int UART_get_char(char * ch, int blocking);
int UART_probe_rx();
int UART_write(char * msg, int blocking);
int UART_read_n(char * buffer, int max_chars, char terminator, int blocking);
void UART_on_rx(function_ptr_t callback);

#endif
