#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "dev/etc/rgb-led/rgb-led.h"

#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(ping_process, "Ping Process");
AUTOSTART_PROCESSES(&ping_process);

static struct etimer blink_timer;

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
  /* DO NOT EDIT! */
  printf("Sending data: %d\n", data);
  nullnet_buf = (uint8_t *)&data;
  nullnet_len = sizeof(data);

  NETSTACK_NETWORK.output(NULL);
}

/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
  int data;
  memcpy(&data, bytes, len);

  printf("Data received: %d\n", data);
  /* EDIT Below this line */

  // TODO (1): Always turn the LED GREEN when you receive a message

  // TODO (2): Use `send_nullnet_data` to send back DOUBLE the amount received

  // TODO (3a): Reset the timer to allow for blinking!
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(ping_process, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set up a periodic event timer to poll the main process
  etimer_set(&blink_timer, BLINK_INTERVAL);

  while (true)
  {
    PROCESS_YIELD();

    // TODO (3b): Check if the timer is expired and turn the LEDs off
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
