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
 
 
/*---------------------------------------------------------------------------*/

#include "settings_noisefloor_sampling.h"


/*---------------------------------------------------------------------------*/

// Global variables 
static uint32_t total_amount_samples = 0;				// Keep the total amount of samples that were carried out so far
static int8_t last_rssi_sample = 0;					// Used to read the CC2420 register

static int8_t mode_rssi_value = 0;					// To store the RSSI value with the maximum amount of occurrences 
static uint32_t max_occurrencies = 0;					// To store the RSSI value with the maximum amount of occurrences 
static int8_t perc_rssi_value = 0;					// To store the RSSI value with the percentage required amount of occurrences

static uint32_t rssi_occurrences[NOISE_FLOOR_ARRAYSIZE + 1]; 		// Array to understand the occurrence of the RSSI samples (in the last position I show the samples that are out of range
	

/*---------------------------------------------------------------------------*/

// FIND_NOISE_FLOOR: Find the noise floor value for this specific mote
int8_t find_noise_floor(uint8_t channel) {

	// Setting physical channel
	cc2420_set_channel(channel);	
		
	// Initial operations
	watchdog_stop();		// Avoiding the watchdog to cause problems
	dint();				// Disable interrupts
	boost_cpu(); 			// Temporarily boost CPU speed
	CC2420_SPI_ENABLE(); 		// Enable SPI

	// Defining and initializing some variables
	uint8_t temp = 0;	
	total_amount_samples = 0;
	max_occurrencies = 0;
	mode_rssi_value = 0;	
	for(temp=0; temp<=NOISE_FLOOR_ARRAYSIZE; temp++){
		rssi_occurrences[temp] = 0;
	}
		
	// Fast RSSI sampling
	while(total_amount_samples < NOISE_FLOOR_SAMPLES){
		
		// Getting one RSSI sample		
		FASTSPI_GETRSSI(last_rssi_sample);
		
		// Correcting the RSSI reading to go higher than 0
		last_rssi_sample = (last_rssi_sample + 55);
		
		// Increasing counter
		total_amount_samples++;
		
		// Inside the array I store the occurrencies of the RSSI values in-range
		if((last_rssi_sample >= 0)&&(last_rssi_sample < NOISE_FLOOR_ARRAYSIZE)){
			rssi_occurrences[last_rssi_sample]++;
			// Compute the maximum occurrency value among the RSSI values in-range
			if(rssi_occurrences[last_rssi_sample] > max_occurrencies) {
				max_occurrencies = rssi_occurrences[last_rssi_sample];
				mode_rssi_value = last_rssi_sample;
			}
		}	
		// In the last position of the array I store the files that were out-of-range		
		else{
			rssi_occurrences[NOISE_FLOOR_ARRAYSIZE]++;
		}
	}	
	
	// Closing the fast RSSI sampling operations
	CC2420_SPI_DISABLE();		// Disable SPI
	restore_cpu();			// Restore CPU speed
	eint(); 			// Re-enable interrupts
	watchdog_start();		// Make sure the watchdog is running again

	// Required percentage
	uint32_t perce = (NOISE_FLOOR_SAMPLES / 100 * PERCENTAGE_VALUE);
	uint32_t sum_c = 0;
	perc_rssi_value = 0;
	
	// Final printings	
	printf("\nNoise on channel %u:\n", channel);
	
	// Compute the RSSI value for the required percentage
	for(temp=0; temp<NOISE_FLOOR_ARRAYSIZE; temp++){
		sum_c += rssi_occurrences[temp];
		printf("%4d: %6lu (%lu)\n", (temp - 100), rssi_occurrences[temp], sum_c);
		if((perc_rssi_value == 0)&&(sum_c >= perce)){
			perc_rssi_value = temp;			
		}	
	}
	// If the value is not found yet, it means that the RSSI noise floor is higher than NOISE_FLOOR_ARRAYSIZE
	if(perc_rssi_value == 0){
		perc_rssi_value = temp;
	}
	
	#if DEBUG_PRINTINGS
		printf("MORE: %6lu\n", rssi_occurrences[NOISE_FLOOR_ARRAYSIZE]);
		printf("MAX : %6d (%lu)\n", (mode_rssi_value - 100), max_occurrencies);
		printf("PERC: %6d (%lu)\n", (perc_rssi_value - 100), perce);
	#endif
	
	#if MODE_PERCENTAGE
		return (perc_rssi_value - 100);
	#else
		return (mode_rssi_value - 100);
	#endif
}

/*---------------------------------------------------------------------------*/
