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

#include "platform_config.h"
#include "jsinteractive.h"
#include "jshardware.h"


int main (void)
{
	jshInit();
	jsvInit(0);
	jsiInit(true);

	while(1)
		jsiLoop();
}
