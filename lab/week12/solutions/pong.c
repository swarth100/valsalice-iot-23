#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h> /* For printf() */

#include "dev/etc/rgb-led/rgb-led.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Configuration */
#define SEND_INTERVAL (3 * CLOCK_SECOND)
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_sender, "Pong Process");
AUTOSTART_PROCESSES(&remote_led_demo_sender);

/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
      nullnet_buf = (uint8_t *)&data;
      nullnet_len = sizeof(data);

      NETSTACK_NETWORK.output(NULL);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(remote_led_demo_sender, ev, data)
{
      static struct etimer send_timer;
      static struct etimer blink_timer;

      static int message = 15;

      PROCESS_BEGIN();

      etimer_set(&send_timer, SEND_INTERVAL);
      while (1)
      {
            PROCESS_YIELD();
            if (etimer_expired(&send_timer))
            {
                  // Send package on interval
                  LOG_INFO("Sending message %d\n", message);

                  send_nullnet_data(message);
                  etimer_reset(&send_timer);

                  rgb_led_set(RGB_LED_GREEN);
                  etimer_set(&blink_timer, BLINK_INTERVAL);

                  message = (message + 7) % 33;
            }
            else if (etimer_expired(&blink_timer))
            {
                  // Handle toggling the LED after a short while
                  rgb_led_off();
            }
      }

      PROCESS_END();
}
/*---------------------------------------------------------------------------*/
