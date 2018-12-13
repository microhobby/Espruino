/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2018 Matheus Castello <matheus@castello.eng.br>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * Platform Specific entry point
 * ----------------------------------------------------------------------------
 */

#include <stdint.h>
#include <math.h>
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encoding.h"
#include <unistd.h>
#include "stdatomic.h"
#include "irq.h"
#include "uart.h"

#include "jslex.h"
#include "jsvar.h"
#include "jsparse.h"
#include "jswrap_json.h"

#include "jsinteractive.h"
#include "jshardware.h"
#include "jswrapper.h"

void addNativeFunction(const char *name, void (*callbackPtr)(void)) {
  jsvObjectSetChildAndUnLock(execInfo.root, name, jsvNewNativeFunction(callbackPtr, JSWAT_VOID));
}

static void clearScreen()
{
	jsiConsolePrint("\033[2J");
	jsiConsolePrint("\033[H");
}

int main (void)
{
	jshInit();
	jsvInit(0);
	jsiInit(true);

	addNativeFunction("clear", clearScreen);

	while(1)
		jsiLoop();
}
