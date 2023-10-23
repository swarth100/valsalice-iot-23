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

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_receiver, "Remote LED Demo Receiver");
AUTOSTART_PROCESSES(&remote_led_demo_receiver);

/*---------------------------------------------------------------------------*/
void input_callback(const void *data, uint16_t len,
                    const linkaddr_t *src, const linkaddr_t *dest)
{
  if (len == sizeof(unsigned))
  {
    unsigned count;
    memcpy(&count, data, sizeof(count));
    LOG_INFO("Message received %u from ", count);
    LOG_INFO_LLADDR(src);
    LOG_INFO_("\n");

    if (count % 2 == 0)
    {
      LOG_INFO("Setting LED off.\n");

#ifndef COOJA
      rgb_led_off();
#else
      leds_single_off(LEDS_LED1);
#endif
    }
    else
    {
      LOG_INFO("Setting LED on (to white).\n");

#ifndef COOJA
      rgb_led_set(RGB_LED_WHITE);
#else
      leds_single_on(LEDS_LED1);
#endif
    }
  }
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

    if (ev == PROCESS_EVENT_TIMER)
    {
      // This event is triggered by the event timer
      // Check for incoming NullNet messages here if needed
      // You can also handle other periodic tasks here
      // Reset the timer for the next event
      etimer_reset(&periodic_timer);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
