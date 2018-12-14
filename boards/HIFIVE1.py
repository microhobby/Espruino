#!/bin/false
# This file is part of Espruino, a JavaScript interpreter for Microcontrollers
#
# Copyright (C) 2018 Matheus Castello <matheus@castello.eng.br>
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
# ----------------------------------------------------------------------------------------
# This file contains information for a specific board - the available pins, and where LEDs,
# Buttons, and other in-built peripherals are. It is used to build documentation as well
# as various source and header files for Espruino.
# ----------------------------------------------------------------------------------------

import pinutils;
info = {
 'name' : "HiFive1",
 'default_console' : "EV_SERIAL1",
 'variables' :  300,
 'binary_name' : 'espruino_%v_hifive',
 'build' : {
   'optimizeflags' : '-O2',
   'libraries' : [
   ],
   'makefile' : [
     'RISCV=1',
     'DEFINES += -DHIFIVE1 -DEMBEDDED',
   ]
 }
};
chip = {
  'part' : "Freedom E300",
  'family' : "RISCV",
  'package' : "",
  'ram' : 16,
  'flash' : 128000, # size in (kb)
  'speed' : -1,
  'usart' : 1,
  'spi' : 1,
  'i2c' : 1,
  'adc' : 0,
  'dac' : 0,
};

devices = {
	'LED1' : { 'pin' : 'D6' }, # red
	'LED2' : { 'pin' : 'D3' }, # green
	'LED3' : { 'pin' : 'D5' }, # blue
};

def get_pins():
	pins = pinutils.generate_pins(0,19)
	return pins
