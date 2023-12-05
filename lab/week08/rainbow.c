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

  static uint8_t colors[] = {
      RGB_LED_CYAN,
      RGB_LED_YELLOW,
      RGB_LED_GREEN,
      RGB_LED_WHITE,
      RGB_LED_MAGENTA,
  };

  while (1)
  {
    PROCESS_YIELD();
    if (ev == button_hal_press_event)
    {
      printf("Button pressed!\n");
      rgb_led_set(colors[0]);
    }
    else if (ev == button_hal_release_event)
    {
      printf("Button released!\n");
    }
    else if (ev == button_hal_periodic_event)
    {
      printf("Button kept pressed!\n");
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
