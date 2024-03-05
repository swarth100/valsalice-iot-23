/*
 * Copyright (c) 2014, TU Graz, Austria.
 * Copyright (c) 2010, Swedish Institute of Computer Science (SICS), Sweden.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are not permitted.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ''AS IS'' AND
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
 *         Thiemo Voigt <thiemo@sics.se>
 *
 * Description: Example on how to use JamLab's interference emulation.
 *
 *
 */

// Interference based on empirical data collected a priori
#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "contiki.h"
#include "node-id.h"
#include "dev/leds.h"
#include "dev/cc2420.h"
#include "dev/watchdog.h"

// Include custom libraries
// #include "settings_cc2420_interferer.h"
#include "settings_noisefloor_sampling.h" // To carry out the noise scanning
#include "settings_cc2420_rssi.h"		  // For the AGC setting
#include "settings_jamlab.h"			  // To activate the interferers

/*---------------------------------------------------------------------------*/

// Node addresses and their basic parameters
/* There can be up to 8 interferer nodes */
#ifndef AMOUNT_NODES_INVOLVED
#define AMOUNT_NODES_INVOLVED 1
#endif /* AMOUNT_NODES_INVOLVED */

static uint8_t address_scanners[AMOUNT_NODES_INVOLVED] = {0}; // Unused for Jamming
static uint8_t address_interferers[AMOUNT_NODES_INVOLVED] = {1};
static uint8_t radio_channels[AMOUNT_NODES_INVOLVED] = {26};
static uint8_t interference_power[AMOUNT_NODES_INVOLVED] = {CC2420_TXPOWER_MAX};
static uint8_t interference_type[AMOUNT_NODES_INVOLVED] = {JAMLAB_TYPE};

// For microwave: JL_MICRO

// Random seed
#define SRAND_SEED 19

// JamLab's carrier type
#define JAMLAB_CARRIER_TYPE JAMLAB_CARRIER_TYPE_MODULATED

// Generic constants
#define SCANNER_INITIAL_WAITING (CLOCK_SECOND * 10)
#define SCANNER_NEXT_ITERATION_WAITING (CLOCK_SECOND * 2)

// Global variables
uint8_t my_channel = 0;
uint8_t my_txpower = 0;
uint8_t my_interf_type = 0;
uint8_t my_role = 0; // 0 = inactive, 1 = interferer, 2 = scanner
uint32_t iteration_number = 0;

/*---------------------------------------------------------------------------*/

PROCESS(jamlab_example_process, "JamLab version 1.0");
AUTOSTART_PROCESSES(&jamlab_example_process);
PROCESS_THREAD(jamlab_example_process, ev, data)
{
	PROCESS_EXITHANDLER()
	PROCESS_BEGIN();

	leds_off(LEDS_ALL);

	// Fixing the AGC to enable better RSSI readings
	tune_AGC_radio();

	// Better randomization
	srand(SRAND_SEED);

	// Find the configuration for this node
	uint8_t temp = 0;
	for (temp = 0; temp < AMOUNT_NODES_INVOLVED; temp++)
	{
		// If I am a designated interferer
		if (node_id == address_interferers[temp])
		{
			my_channel = radio_channels[temp];
			my_txpower = interference_power[temp];
			my_interf_type = interference_type[temp];
			my_role = 1;
			leds_on(LEDS_RED);
			break;
		}
		// If I am a designated scanner
		else if (node_id == address_scanners[temp])
		{
			my_channel = radio_channels[temp];
			my_txpower = CC2420_TXPOWER_MAX;
			my_role = 2;
			leds_on(LEDS_BLUE);
			break;
		}
	}

	// I am an interferer
	if (my_role == 1)
	{

		// Ready
		printf("Node: %u, PHY channel: %u, power: %u, role (1 = jammer): %u\n", node_id, my_channel, my_txpower, my_role);

		// Start JamLab in emulation mode
		jamlab_emulation(my_channel, my_txpower, my_interf_type, JAMLAB_CARRIER_TYPE);
	}

	// I am a scanner node
	if (my_role == 2)
	{

		// Setting transmission power and radio channel
		cc2420_set_txpower(my_channel);
		cc2420_set_txpower(my_txpower);

		// Ready
		printf("Node: %u, PHY channel: %u, power: %u, role (2 = scanner): %u\n", node_id, my_channel, my_txpower, my_role);

		// Remain temporarily inactive to allow all interferers to start (in case of testbed parallel programming)
		static struct etimer et_initial;
		etimer_set(&et_initial, SCANNER_INITIAL_WAITING);
		PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et_initial));

		while (1)
		{

			iteration_number++;

			// Find the noise floor
			printf("\n\nNoise floor scanning, iteration %lu:\n", iteration_number);
			find_noise_floor(my_channel);

			// Just a small waiting time before next iteration
			static struct etimer et_initial;
			etimer_set(&et_initial, SCANNER_NEXT_ITERATION_WAITING);
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et_initial));
		}
	}

	// I remain inactive
	while (1)
	{
		PROCESS_WAIT_EVENT();
	}

	PROCESS_END();
}
