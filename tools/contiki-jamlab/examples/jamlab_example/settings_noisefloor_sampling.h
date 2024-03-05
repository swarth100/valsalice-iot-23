/*
 * Copyright (c) 2012, University of Luebeck, Germany.
 * Copyright (c) 2013, TU Graz, Austria.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Author: Carlo Alberto Boano <cboano@tugraz.at>
 *
 */
 
#include <stdio.h> 
#include "dev/watchdog.h"

// Include custom libraries
#include "settings_cc2420_rssi.h"


/*---------------------------------------------------------------------------*/

// Definition of constants

#define NOISE_FLOOR_SAMPLES			((uint32_t) 2000000)		// Number of RSSI samples used to compute the noise floor
#define NOISE_FLOOR_ARRAYSIZE		((uint8_t) 60)				// We consider noise from -100 dBm to -100+XXX dBm

#define MODE_PERCENTAGE				0				// Does the function return the mode or the percentage? (0 = mode, !0 = percentage)
#define PERCENTAGE_VALUE			95				// The function return the mode corresponding to this cumulate percentage

#define DEBUG_PRINTINGS				1				// Do you want the printf to be printed? 0 = no, !0 = yes


/*---------------------------------------------------------------------------*/

// Prototype of functions
int8_t find_noise_floor(uint8_t channel);							// Returns the noise floor value in dBm for this specific mote

/*---------------------------------------------------------------------------*/
