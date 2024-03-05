/*
 * Copyright (c) 2010, University of Luebeck, Germany.
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

#ifndef __PROJECT_CONF_H__
#define __PROJECT_CONF_H__

#include <stdint.h>
#include "cc2420.h"

/* Redefine the channel and transmission power as required */
#undef CC2420_CONF_CHANNEL
#define CC2420_CONF_CHANNEL 26

#undef CC2420_CONF_CCA_THRESH
#define CC2420_CONF_CCA_THRESH -32

/* Disable IPv6 */
#undef UIP_CONF_IPV6
#define UIP_CONF_IPV6 0

/* Set the MAC and RDC drivers */
#undef NETSTACK_CONF_MAC
#define NETSTACK_CONF_MAC nullmac_driver

#undef NETSTACK_CONF_RDC
#define NETSTACK_CONF_RDC nullrdc_driver

/* WITH_SEND_CCA definition */
#ifndef WITH_SEND_CCA
#define WITH_SEND_CCA 0
#endif

/* Additional configurations can be added here */
// #undef CONF_SFD_TIMESTAMPS
// #define CONF_SFD_TIMESTAMPS 0

#undef CC2420_CONF_AUTOACK
#define CC2420_CONF_AUTOACK 0

#undef NULLRDC_802154_AUTOACK_HW
#define NULLRDC_802154_AUTOACK_HW 0

#undef NULLRDC_802154_AUTOACK
#define NULLRDC_802154_AUTOACK 0

/* Utility macros */
#define XSTR(x) STR(x)
#define STR(x) #x

#ifndef JAMLAB_TYPE
#define JAMLAB_TYPE JL_MICRO
#endif /* JAMLAB_TYPE */

#endif /* __PROJECT_CONF_H__ */
