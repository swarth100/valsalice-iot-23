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

/* Configuration */
#define SAY_INTERVAL (5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Hello Process");
AUTOSTART_PROCESSES(&main_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
      static struct etimer periodic_timer;

      PROCESS_BEGIN();

      /* Initialize the Timers */
      etimer_set(&periodic_timer, SAY_INTERVAL);

      while (true)
      {
            PROCESS_WAIT_EVENT();
            if (etimer_expired(&periodic_timer))
            {
                  // TODO: Print the Node ID
                  LOG_INFO("Node ID: %d\n", _________);
                  etimer_reset(&periodic_timer);
            }
      }

      PROCESS_END();
}
/*---------------------------------------------------------------------------*/
