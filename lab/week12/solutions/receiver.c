#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "dev/etc/rgb-led/rgb-led.h"

#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_receiver, "Remote Nullnet Receiver");
AUTOSTART_PROCESSES(&remote_led_demo_receiver);

static struct etimer periodic_timer;

/*---------------------------------------------------------------------------*/
/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
  int data;
  memcpy(&data, bytes, len);

  printf("Color received: %d\n", data);
  rgb_led_set(data);

  etimer_reset(&periodic_timer);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(remote_led_demo_receiver, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set up a periodic event timer to poll the main process
  etimer_set(&periodic_timer, CLOCK_SECOND);

  while (1)
  {
    PROCESS_WAIT_EVENT();

    printf("Polling for messages...\n");

    if (etimer_expired(&periodic_timer))
    {
      etimer_reset(&periodic_timer);

      rgb_led_off();
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
