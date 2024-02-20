#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h> /* For printf() */
#include "dev/leds.h"

// IMPORTANT: The config.h file contains common configuration!
#include "config.h"

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
      /* DO NOT EDIT! */
      printf("Sending data from '%c': %d\n", TEAM_ID, data);

      message_t buffer = {.team_id = TEAM_ID, .data = data};
      nullnet_buf = (uint8_t *)&buffer;
      nullnet_len = sizeof(message_t);

      NETSTACK_NETWORK.output(NULL);
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Team Sender");
AUTOSTART_PROCESSES(&main_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
      static struct etimer periodic_timer;
      static struct etimer blink_timer;

      /* We send a single piece of data over the network */
      static int datum = 1;

      PROCESS_BEGIN();

      /* Initialize the Timers */
      etimer_set(&blink_timer, BLINK_INTERVAL);
      etimer_set(&periodic_timer, SEND_INTERVAL);

      while (true)
      {
            PROCESS_WAIT_EVENT();
            if (etimer_expired(&periodic_timer))
            {

                  // TODO (1): Send `datum` over nullnet
                  send_nullnet_data(datum);
                  datum++;

                  // TODO (2): Also reset the `periodic_timer`
                  etimer_reset(&blink_timer);
                  etimer_reset(&periodic_timer);
            }
            else if (etimer_expired(&blink_timer))
            {
                  leds_single_off(LEDS_LED1);
            }
      }

      PROCESS_END();
}
/*---------------------------------------------------------------------------*/
