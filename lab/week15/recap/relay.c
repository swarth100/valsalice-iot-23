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
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/* If the data has not changed we do not re-repeat it */
static int last_received_datum = 0;

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

/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
      int data;
      memcpy(&data, bytes, len);

      LOG_INFO("Received data: '%d'\n", data);

      /* Only relay when the data has changed! */
      if (data != last_received_datum)
      {
            last_received_datum = data;
            send_nullnet_data(data);
            leds_single_on(LEDS_LED1);
      }
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Multi Relay");
AUTOSTART_PROCESSES(&main_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
      static struct etimer blink_timer;

      /* Initialize NullNet */
      nullnet_set_input_callback(receive_nullnet_data);

      PROCESS_BEGIN();

      /* Initialize the Timers */
      etimer_set(&blink_timer, BLINK_INTERVAL);

      while (true)
      {
            PROCESS_WAIT_EVENT();
            if (etimer_expired(&blink_timer))
            {
                  leds_single_off(LEDS_LED1);
            }
      }

      PROCESS_END();
}
/*---------------------------------------------------------------------------*/
