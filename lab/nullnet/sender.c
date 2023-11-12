#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h> /* For printf() */

#ifndef COOJA
#include "dev/etc/rgb-led/rgb-led.h"
#else
#include "dev/leds.h"
#endif

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Configuration */
#define SEND_INTERVAL (5 * CLOCK_SECOND)
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_sender, "Remote Nullnet Sender");
AUTOSTART_PROCESSES(&remote_led_demo_sender);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(remote_led_demo_sender, ev, data)
{
      static struct etimer periodic_timer;
      static struct etimer blink_timer;
      static char network_data[28] = " user: DonBosco; pwd: Valsa ";

      PROCESS_BEGIN();

      /* Initialize NullNet */
      nullnet_buf = (uint8_t *)&network_data[0];
      nullnet_len = strlen(network_data);

      etimer_set(&periodic_timer, SEND_INTERVAL);
      while (1)
      {
            PROCESS_WAIT_EVENT();
            if (etimer_expired(&periodic_timer))
            {
                  // Handle sending packages every 20 seconds
                  LOG_INFO("Broadcasting packet of size %d", strlen(network_data));
                  LOG_INFO_("\n");

                  NETSTACK_NETWORK.output(NULL);
                  etimer_reset(&periodic_timer);

#ifndef COOJA
                  rgb_led_set(RGB_LED_GREEN);
#else
                  leds_single_on(LEDS_LED1);
#endif
                  etimer_set(&blink_timer, BLINK_INTERVAL);
            }
            else if (etimer_expired(&blink_timer))
            {
                  // Handle toggling the LED after a short while
#ifndef COOJA
                  rgb_led_off();
#else
                  leds_single_off(LEDS_LED1);
#endif
            }
      }

      PROCESS_END();
}
/*---------------------------------------------------------------------------*/
