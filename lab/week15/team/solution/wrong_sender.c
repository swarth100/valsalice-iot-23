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

typedef struct
{
      char team_id;
      int data;
} message_t;

/* Configuration */
#define SEND_INTERVAL (0.95 * CLOCK_SECOND)
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
      /* DO NOT EDIT! */
      printf("Sending wrong data value: %d\n", data);

      message_t buffer = {.team_id = 'Z', .data = data};
      nullnet_buf = (uint8_t *)&buffer;
      nullnet_len = sizeof(message_t);

      NETSTACK_NETWORK.output(NULL);
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Wrong Sender");
AUTOSTART_PROCESSES(&main_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
      static struct etimer periodic_timer;
      static struct etimer blink_timer;

      /* We send a single piece of data over the network */
      static int datum = 1000;

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
