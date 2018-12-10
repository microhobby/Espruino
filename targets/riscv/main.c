#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"
#include "platform_config.h"

#include "jslex.h"
#include "jsvar.h"
#include "jsparse.h"
#include "jswrap_json.h"

#include "jsinteractive.h"
#include "jshardware.h"
#include "jswrapper.h"

int main(void)
{
	jshInit();
	jsvInit(0);
	jsiInit(true);

	while (1) {
   		jsiLoop();
  	}

	return 0;
}
