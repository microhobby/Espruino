
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "plic/plic_driver.h"
#include "encoding.h"

#include "platform.h"
#include "platform_config.h"
#include "uart.h"
#include "jshardware.h"
#include "jsutils.h"
#include "jsparse.h"
#include "jsinteractive.h"

plic_instance_t g_plic;

static void NOP(const char * func)
{
	/*_puts(func);
	_puts(" Not implemented\r\n");*/
}

void jshInit() 
{
	_puts("Serial ok\r\n");

	/* initialize irqs */
	PLIC_init(&g_plic,
	    PLIC_CTRL_ADDR,
	    PLIC_NUM_INTERRUPTS,
	    PLIC_NUM_PRIORITIES);

	_puts("PLIC Initialized\r\n");
}

void jshReset()
{
	NOP(__func__);
}

void jshIdle() 
{
	NOP(__func__);
}

bool jshSleep(JsSysTime timeUntilWake)
{
	NOP(__func__);
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

JsSysTime jshGetSystemTime()
{
	NOP(__func__);
	return 0;
}

void jshSetSystemTime(JsSysTime time)
{
	NOP(__func__);
}

JsSysTime jshGetTimeFromMilliseconds(JsVarFloat ms)
{
	NOP(__func__);
	return 0;
}

JsVarFloat jshGetMillisecondsFromTime(JsSysTime time)
{
	NOP(__func__);
	return 0;
}

void jshFlashRead(void *buf, uint32_t addr, uint32_t len)
{
	NOP(__func__);
}

void jshFlashWrite(void *buf, uint32_t addr, uint32_t len) 
{
	NOP(__func__);
}

bool jshFlashGetPage(uint32_t addr, uint32_t *startAddr, uint32_t *pageSize) 
{
	return false;
}

void jshFlashErasePage(uint32_t addr)
{
	NOP(__func__);
}

size_t jshFlashGetMemMapAddress(size_t ptr)
{
	return 0;
}

void jshInterruptOff() 
{
	/*NOP(__func__);*/
	clear_csr(mie, MIP_MEIP);
  	clear_csr(mie, MIP_MTIP);
}

void jshInterruptOn() 
{
	/*NOP(__func__);*/
	set_csr(mie, MIP_MEIP);
	set_csr(mie, MIP_MTIP);
	set_csr(mstatus, MSTATUS_MIE);
}

bool jshIsInInterrupt()
{
	return false;
}

bool jshPinGetValue(Pin pin) 
{
	return false;
}

void jshPinSetState(Pin pin, JshPinState state)
{
	NOP(__func__);
}

JshPinState jshPinGetState(Pin pin) 
{
	return JSHPINSTATE_UNDEFINED;
}

void jshPinSetValue(Pin pin, bool value) 
{
	NOP(__func__);
}

void jshUSARTKick(IOEventFlags device) 
{
	/*NOP(__func__);*/
	
	// Get the next character to transmit.  We will have reached the end when
	// the value of the character to transmit is -1.
	int c = jshGetCharToTransmit(device);

	while (c >= 0) {
		_putc(c);
		c = jshGetCharToTransmit(device);
	}
}

bool jshIsDeviceInitialised(IOEventFlags device)
{
	return false;
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
	NOP(__func__);
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
	return 0;
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
	_puts(str);
}
