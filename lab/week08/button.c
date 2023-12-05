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

  while (1)
  {
    PROCESS_YIELD();

    if (ev == button_hal_press_event)
    {
      printf("Button pressed!\n");
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
