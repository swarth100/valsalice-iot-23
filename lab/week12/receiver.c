#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "dev/etc/rgb-led/rgb-led.h"

#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(receiver_process, "Receiver Process");
AUTOSTART_PROCESSES(&receiver_process);

static struct etimer blink_timer;

/*---------------------------------------------------------------------------*/
/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
  int data;
  memcpy(&data, bytes, len);

  printf("Color received: %d\n", data);

  // TODO (1): Set the RGB to the receiver color!

  // TODO (2a): Reset the timer to allow for blinking!
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(receiver_process, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set up a periodic event timer to poll the main process
  etimer_set(&blink_timer, CLOCK_SECOND);

  while (true)
  {
    PROCESS_YIELD();

    // TODO (2b): Check if the timer is expired and turn the LEDs off
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
