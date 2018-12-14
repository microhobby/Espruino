
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "platform.h"
#include "platform_config.h"
#include "irq.h"
#include "gpio.h"
#include "uart.h"
#include "jshardware.h"
#include "jsutils.h"
#include "jsparse.h"
#include "jsinteractive.h"

static void NOP(const char * func)
{
	/*UART_write(func, 1);
	UART_write(" Not implemented\r\n", 1);*/
}

static void uart_irq_handle()
{
	char c;
	uint32_t uart_ip_reg = UART0_REG(UART_REG_IP);
	/* check the type of irq */
	uart_ip_reg &= UART0_REG(UART_REG_IE);

	if (uart_ip_reg & UART_IP_RXWM) {
		UART_get_char(&c, 1);
		/*UART_put_char(c, 1);*/
		jshPushIOCharEvent(EV_SERIAL1, c);
	}
}

void jshInit() 
{
	/* initialize irqs */
	init_plic();
	UART_init(115200, 0);
	UART_write("PLIC Initialized\r\n", 1);

	/* add rx irq callback */
	UART_on_rx(uart_irq_handle);

	/* set all Pins to output low */
	jshReset();
}

void jshReset()
{
	unsigned int i;
	for(i = 0; i < 19; i++) {
		if (i != 16 && i != 17) {
			jshPinSetState(i, JSHPINSTATE_GPIO_OUT);
			jshPinSetValue(i, false);
		}
	}

	/* set onboard led to high */
	jshPinSetValue(6, true);
	jshPinSetValue(3, true);
	jshPinSetValue(5, true);
}

/* stuff to do in idle */
void jshIdle() 
{
	jshUSARTKick(EV_SERIAL1);
}

bool jshSleep(JsSysTime timeUntilWake)
{
	//FIXME
	/* not really implemented */
	return true;
}

void jshKill()
{
	NOP(__func__);
}

int jshGetSerialNumber(unsigned char *data, int maxChars)
{
	NOP(__func__);
}

bool jshIsUSBSERIALConnected()
{
	NOP(__func__);
	return false;
}

/* https://miro.medium.com/max/754/1*snTXFElFuQLSFDnvZKJ6IA.png */
volatile JsSysTime baseSystemTime = 0;
volatile uint32_t lastSystemTime = 0;

JsSysTime jshGetSystemTime()
{
	volatile uint64_t * mtime = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
	uint64_t now = *mtime;
	return baseSystemTime + (JsSysTime)now;
}

void jshSetSystemTime(JsSysTime time)
{
	baseSystemTime = 0;
	baseSystemTime = time - jshGetSystemTime();
}

JsSysTime jshGetTimeFromMilliseconds(JsVarFloat ms)
{
	return (JsSysTime) ((ms * RTC_FREQ) / 1000);
}

JsVarFloat jshGetMillisecondsFromTime(JsSysTime time)
{
	return (time * 1000.0) / RTC_FREQ;
}

void jshFlashRead(void *buf, uint32_t addr, uint32_t len)
{
	/*NOP(__func__);*/
}

void jshFlashWrite(void *buf, uint32_t addr, uint32_t len) 
{
	/*NOP(__func__);*/
}

bool jshFlashGetPage(uint32_t addr, uint32_t *startAddr, uint32_t *pageSize) 
{
	return false;
}

void jshFlashErasePage(uint32_t addr)
{
	/*NOP(__func__);*/
}

size_t jshFlashGetMemMapAddress(size_t ptr)
{
	return 0;
}

void jshInterruptOff() 
{
	lock_irqs();
}

void jshInterruptOn() 
{
	enable_irqs();
}

/// Are we currently in an interrupt?
bool jshIsInInterrupt()
{
	return false; //FIXME
}

bool jshPinGetValue(Pin pin) 
{
	if(gpio_read_level(pin) == 1)
		return true;
	return false;
}

void jshPinSetState(Pin pin, JshPinState state)
{
	if(state == JSHPINSTATE_GPIO_OUT)
		gpio_output(pin);
	else if(state == JSHPINSTATE_GPIO_IN)
		gpio_input(pin);
}

JshPinState jshPinGetState(Pin pin) 
{
	unsigned int mux = gpio_read_mux(pin);

	if (mux == 1)
		return JSHPINSTATE_GPIO_IN | 
			(jshPinGetValue(pin) ? JSHPINSTATE_PIN_IS_ON : 0);
	if (mux == 2)
		return JSHPINSTATE_GPIO_OUT | 
			(jshPinGetValue(pin) ? JSHPINSTATE_PIN_IS_ON : 0);

	return JSHPINSTATE_UNDEFINED;
}

void jshPinSetValue(Pin pin, bool value) 
{
	gpio_level(pin, value ? 1 : 0);
}

void jshUSARTKick(IOEventFlags device) 
{
	/*NOP(__func__);*/
	
	// Get the next character to transmit.  We will have reached the end when
	// the value of the character to transmit is -1.
	int c = jshGetCharToTransmit(device);

	while (c >= 0) {
		UART_put_char(c, 1);
		c = jshGetCharToTransmit(device);
	}
}

bool jshIsDeviceInitialised(IOEventFlags device)
{
	//FIXME
	/* not really implemented */
	return true;
}

void jshUSARTSetup(IOEventFlags device, JshUSARTInfo *inf) 
{
	NOP(__func__);
}

IOEventFlags jshPinWatch(Pin pin, bool shouldWatch) 
{
	return 0;
}

bool jshIsEventForPin(IOEvent *event, Pin pin) 
{
	return false;
}

void jshKickWatchDog() 
{
	NOP(__func__);
}

bool jshGetWatchedPinState(IOEventFlags device)
{
	return false;
}

int jshPinAnalogFast(Pin pin) 
{
	return 0;
}

void jshUtilTimerReschedule(JsSysTime period) 
{
	NOP(__func__);
}

void jshUtilTimerDisable() 
{
	NOP(__func__);
}

void jshSetOutputValue(JshPinFunction func, int value) 
{
	NOP(__func__);
}

void jshUtilTimerStart(JsSysTime period) 
{
	NOP(__func__);
}

JshPinFunction jshGetCurrentPinFunction(Pin pin) 
{
	return 0;
}

void jshDelayMicroseconds(int microsec)
{
	volatile uint64_t * mtime = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
	uint64_t now = *mtime;
	uint64_t then = now + (microsec * RTC_FREQ / 10000);
	while (*mtime < then);
}

int jshSPISend(IOEventFlags device, int data) 
{
	NOP(__func__);
}

void jshSPISetup(IOEventFlags device, JshSPIInfo *inf) 
{
	NOP(__func__);
}

void jshSPIWait(IOEventFlags device) 
{
	NOP(__func__);
}

void jshSPISend16(IOEventFlags device, int data) 
{
	NOP(__func__);
}

JsVarFloat jshReadTemperature()
{
	return 0.0;
}

JsVarFloat jshReadVRef()  
{
	return 0.0;
}

void jshEnableWatchDog(JsVarFloat timeout) 
{
	NOP(__func__);
}

unsigned int jshSetSystemClock(JsVar *options) 
{
	return 0;
}

unsigned int jshGetRandomNumber() 
{
	return rand();
}

JsVarFloat jshPinAnalog(Pin pin) 
{
	return 0.0;
}

JsVar *jshFlashGetFree()
{
	return NULL;
}

JshPinFunction jshPinAnalogOutput(Pin pin, JsVarFloat value, JsVarFloat freq, JshAnalogOutputFlags flags)
{
	return 0;
}

void jshPinPulse(Pin pin, bool value, JsVarFloat time) 
{
	NOP(__func__);
}

bool jshCanWatch(Pin pin)
{
	return false;
}

void jshSPISetReceive(IOEventFlags device, bool isReceive) 
{
	NOP(__func__);
}

void jshSPISet16(IOEventFlags device, bool is16)
{
	NOP(__func__);
}

void jshI2CSetup(IOEventFlags device, JshI2CInfo *inf) 
{
	NOP(__func__);
}

void jshI2CWrite(IOEventFlags device, unsigned char address, int nBytes, const unsigned char *data, bool sendStop)
{
	NOP(__func__);
}

void jshI2CRead(IOEventFlags device, unsigned char address, int nBytes, unsigned char *data, bool sendStop)
{
	NOP(__func__);
}

void jshReboot() 
{
	NOP(__func__);
}

void jshDebug(int i1, int i2, int i3)
{
	/* this debug function appear to be reseting our core */
	char str[120];
	
	sprintf(str, "DEBUG::%d::%d::%d\r\n", i1, i2, i3);
	UART_write(str, 1);
}
