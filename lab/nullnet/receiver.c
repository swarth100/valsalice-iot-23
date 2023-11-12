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

#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_receiver, "Remote Nullnet Receiver");
AUTOSTART_PROCESSES(&remote_led_demo_receiver);

/*---------------------------------------------------------------------------*/
void input_callback(const void *data, uint16_t len,
                    const linkaddr_t *src, const linkaddr_t *dest)
{

  char network_data[28];
  memcpy(network_data, data, len);
  LOG_INFO("Message received: %s\n", network_data);

#ifndef COOJA
  rgb_led_set(RGB_LED_CYAN);
#else
  leds_single_on(LEDS_LED1);
#endif
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(remote_led_demo_receiver, ev, data)
{
  static struct etimer periodic_timer;

  PROCESS_BEGIN();

  /* Initialize NullNet */
  nullnet_set_input_callback(input_callback);

  // Set up a periodic event timer to poll the main process
  etimer_set(&periodic_timer, CLOCK_SECOND);

  while (1)
  {
    PROCESS_WAIT_EVENT();

    LOG_INFO("Polling for messages...\n");

    if (etimer_expired(&periodic_timer))
    {
      // This event is triggered by the event timer
      // Check for incoming NullNet messages here if needed
      // You can also handle other periodic tasks here
      // Reset the timer for the next event
      etimer_reset(&periodic_timer);

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
