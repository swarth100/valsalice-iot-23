#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h> /* For printf() */
#include "dev/leds.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Configuration */
#define SEND_INTERVAL (5 * CLOCK_SECOND)
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
      LOG_INFO("Sending data %d\n", data);

      nullnet_buf = (uint8_t *)&data;
      nullnet_len = sizeof(data);

      NETSTACK_NETWORK.output(NULL);
      leds_single_on(LEDS_LED1);
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Multi Sender");
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

                  send_nullnet_data(datum);
                  datum++;

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
