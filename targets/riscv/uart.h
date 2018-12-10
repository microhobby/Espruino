#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "platform.h"
#include "platform_config.h"

extern void _config_hifive_uart(void);
extern void _putc(char c);
extern void _puts(const char * s);
