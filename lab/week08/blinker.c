#include "contiki.h"
#include <string.h>
#include <stdio.h> /* For printf() */

#include "dev/etc/rgb-led/rgb-led.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Configuration */
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(simple_led_program, "Simple LED");
AUTOSTART_PROCESSES(&simple_led_program);

/*---------------------------------------------------------------------------*/

void use_rgb(int counter)
{
      if (counter % 2 == 0)
      {
            rgb_led_off();
      }
      else
      {
            rgb_led_set(RGB_LED_GREEN);
      }
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(simple_led_program, ev, data)
{
      static struct etimer blink_timer;
      static int counter = 0;

      PROCESS_BEGIN();
      etimer_set(&blink_timer, BLINK_INTERVAL);

      while (true)
      {
            PROCESS_WAIT_EVENT();
            if (etimer_expired(&blink_timer))
            {
                  use_rgb(counter);
                  etimer_set(&blink_timer, BLINK_INTERVAL);
            }

            counter++;
      }

      PROCESS_END();
}
/*---------------------------------------------------------------------------*/
