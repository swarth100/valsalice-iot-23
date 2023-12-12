/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "sys/etimer.h"
#include "dev/button-hal.h"
#include "dev/etc/rgb-led/rgb-led.h"

#include <stdio.h>
#include <stdbool.h>
/*---------------------------------------------------------------------------*/
PROCESS(simple_timer_process, "Timer Process");
AUTOSTART_PROCESSES(&simple_timer_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(simple_timer_process, ev, data)
{
  PROCESS_BEGIN();

  while (1)
  {
    PROCESS_YIELD();
    if (ev == button_hal_press_event)
    {
      rgb_led_set(RGB_LED_BLUE);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
