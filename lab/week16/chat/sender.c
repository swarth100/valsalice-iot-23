#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "dev/leds.h"
#include "sys/node-id.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

// IMPORTANT: The config.h file contains common configuration!
#include "config.h"

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data()
{
      /* DO NOT EDIT! */
      LOG_INFO("Sending data from '%d' for TEAM '%c'\n", node_id, TEAM_ID);

      message_t buffer = {.team_id = TEAM_ID, .node_id = node_id};
      nullnet_buf = (uint8_t *)&buffer;
      nullnet_len = sizeof(message_t);

      NETSTACK_NETWORK.output(NULL);
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Sender Process");
AUTOSTART_PROCESSES(&main_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
      static struct etimer blink_timer;
      static struct etimer periodic_timer;

      PROCESS_BEGIN();

      /* Initialize the Timers */
      etimer_set(&blink_timer, BLINK_INTERVAL);
      etimer_set(&periodic_timer, SEND_INTERVAL);

      while (true)
      {
            PROCESS_WAIT_EVENT();
            if (etimer_expired(&periodic_timer))
            {
                  // Periodically send an empty message
                  // TODO: Send an empty message

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
