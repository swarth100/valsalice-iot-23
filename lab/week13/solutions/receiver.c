#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "dev/etc/rgb-led/rgb-led.h"

#define BLINK_INTERVAL (1 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(receiver_process, "Receiver Process");
AUTOSTART_PROCESSES(&receiver_process);

/*---------------------------------------------------------------------------*/
/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
  char data;
  memcpy(&data, bytes, len);

  // Add custom code BELOW this line

  printf("Data received: '%c'\n", data);
  if (data == 'F')
  {
    rgb_led_set(RGB_LED_CYAN);
  }
  else
  {
    rgb_led_set(RGB_LED_GREEN);
  }
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(receiver_process, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set the interval for the timer ONCE so we do not need to set it again
  static struct etimer blink_timer;
  etimer_set(&blink_timer, BLINK_INTERVAL);

  while (true)
  {
    PROCESS_WAIT_EVENT();

    // This is a cyclic timer that keeps turning off the LED after a fixed time.
    if (etimer_expired(&blink_timer))
    {
      rgb_led_off();

      etimer_reset(&blink_timer);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
