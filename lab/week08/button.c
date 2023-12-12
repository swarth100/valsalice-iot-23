/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "dev/button-hal.h"
#include "dev/etc/rgb-led/rgb-led.h"

#include <stdio.h>
#include <stdbool.h>
/*---------------------------------------------------------------------------*/
PROCESS(button_hal_example, "Button HAL Example");
AUTOSTART_PROCESSES(&button_hal_example);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(button_hal_example, ev, data)
{
  PROCESS_BEGIN();
  static int press_seconds = 0;

  while (1)
  {
    PROCESS_YIELD();

    if (ev == button_hal_press_event)
    {
      printf("Button pressed!\n");
      rgb_led_set(RGB_LED_GREEN);
    }
    else if (ev == button_hal_release_event)
    {
      printf("Button released!\n");
      rgb_led_off();
    }

    if (ev == button_hal_periodic_event)
    {
      press_seconds = press_seconds + 1;
      printf("Button pressed for %d seconds!\n", press_seconds);

      if (press_seconds >= 5)
      {
        rgb_led_set(RGB_LED_CYAN);
      }
    }
    else
    {
      press_seconds = 0;
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
