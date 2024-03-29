#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h> /* For printf() */

#include "dev/etc/rgb-led/rgb-led.h"

/* Configuration */
#define SEND_INTERVAL (2 * CLOCK_SECOND)
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_sender, "Remote Nullnet Sender");
AUTOSTART_PROCESSES(&remote_led_demo_sender);

static int n_colors = 4;
static int colors[] = {
    RGB_LED_BLUE, RGB_LED_GREEN, RGB_LED_MAGENTA, RGB_LED_CYAN};

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
      static int epoch = 0;
      static int selected_color = RGB_LED_BLUE;

      PROCESS_BEGIN();

      etimer_set(&send_timer, SEND_INTERVAL);
      while (1)
      {
            PROCESS_YIELD();
            if (etimer_expired(&send_timer))
            {
                  // Send package on interval
                  printf("Sending color %d\n", selected_color);

                  send_nullnet_data(selected_color);
                  etimer_reset(&send_timer);

                  rgb_led_set(RGB_LED_GREEN);
                  etimer_set(&blink_timer, BLINK_INTERVAL);

                  epoch++;
                  selected_color = colors[epoch % n_colors];
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
