#include "uart.h"

extern void _config_hifive_uart()
{
	volatile int i=0;

	while(i < 10000){i++;}

	// Make sure the HFROSC is on before the next line:
	PRCI_REG(PRCI_HFROSCCFG) |= ROSC_EN(1);
	// Run off 16 MHz Crystal for accuracy. Note that the
	// first line is 
	PRCI_REG(PRCI_PLLCFG) = (PLL_REFSEL(1) | PLL_BYPASS(1));
	PRCI_REG(PRCI_PLLCFG) |= (PLL_SEL(1));
	// Turn off HFROSC to save power
	PRCI_REG(PRCI_HFROSCCFG) &= ~(ROSC_EN(1));

	// Configure UART to print
	GPIO_REG(GPIO_OUTPUT_VAL) |= IOF0_UART0_MASK;
	GPIO_REG(GPIO_OUTPUT_EN)  |= IOF0_UART0_MASK;
	GPIO_REG(GPIO_IOF_SEL)    &= ~IOF0_UART0_MASK;
	GPIO_REG(GPIO_IOF_EN)     |= IOF0_UART0_MASK;

	// 115200 Baud Rate
	UART0_REG(UART_REG_DIV) = 138;
	UART0_REG(UART_REG_TXCTRL) = UART_TXEN;
	UART0_REG(UART_REG_RXCTRL) = UART_RXEN;

	i = 0;
	while(i < 10000){i++;}
}

extern void _putc(char c) {
	while ((int32_t) UART0_REG(UART_REG_TXFIFO) < 0);
	UART0_REG(UART_REG_TXFIFO) = c;
}

extern int _getc(char * c){
	int32_t val = (int32_t) UART0_REG(UART_REG_RXFIFO);

	if (val > 0) {
		*c =  val & 0xFF;
		return 1;
	}

	return 0;
}

extern void _puts(const char * s) {
	while (*s != '\0'){
		_putc(*s++);
	}
}
