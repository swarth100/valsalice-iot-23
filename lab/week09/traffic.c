/*---------------------------------------------------------------------------*/
#include "contiki.h"
#include "sys/etimer.h"
#include "dev/button-hal.h"
#include "dev/etc/rgb-led/rgb-led.h"

#include <stdio.h>
#include <stdbool.h>
/*---------------------------------------------------------------------------*/
PROCESS(traffic_process, "Traffic Light Process");
AUTOSTART_PROCESSES(&traffic_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(traffic_process, ev, data)
{
  static struct etimer timer1;
  static struct etimer timer2;
  static struct etimer timer3;

  PROCESS_BEGIN();
  while (1)
  {
    PROCESS_YIELD();
    if (ev == button_hal_press_event)
    {
      printf("Button pressed!\n");
    }
    else if (ev == PROCESS_EVENT_TIMER)
    {
      printf("Timer expired!\n");
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
