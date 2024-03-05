/*
 * Copyright (c) 2012, University of Luebeck, Germany.
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
 * Author: Carlo Alberto Boano <cboano@iti.uni-luebeck.de>
 *
 */

#include "settings_cc2420_rssi.h"
#include "cc2420.h"
#include "cc2420_const.h"

/*---------------------------------------------------------------------------*/

// CPU Boosting: temporarily boost CPU speed
static uint16_t boost_cpu_var1, boost_cpu_var2;
void boost_cpu()
{
	boost_cpu_var1 = DCOCTL;
	boost_cpu_var2 = BCSCTL1;
	DCOCTL = 0xff;
	BCSCTL1 |= 0x07;
}
// CPU Boosting: restore CPU speed
void restore_cpu()
{
	DCOCTL = boost_cpu_var1;
	BCSCTL1 = boost_cpu_var2;
}

/*---------------------------------------------------------------------------*/

// TUNING AGC to enable better RSSI readings
void tune_AGC_radio()
{
	// Get the content of the CC2420 AGCTST1 register
	// uint16_t reg_agctst = getreg(CC2420_AGCTST1);
	// Write the CC2420 AGCTST1 register
	// setreg(CC2420_AGCTST1, (reg_agctst + (1 << 8) + (1 << 13)));
}

/*---------------------------------------------------------------------------*/
