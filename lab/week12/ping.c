#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "dev/etc/rgb-led/rgb-led.h"

#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_receiver, "Ping Process");
AUTOSTART_PROCESSES(&remote_led_demo_receiver);

static struct etimer blink_timer;

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
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

  rgb_led_set(RGB_LED_GREEN);
  send_nullnet_data(data * 2);

  etimer_reset(&blink_timer);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(remote_led_demo_receiver, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set up a periodic event timer to poll the main process
  etimer_set(&blink_timer, BLINK_INTERVAL);

  while (1)
  {
    PROCESS_WAIT_EVENT();

    printf("Polling for messages...\n");

    if (etimer_expired(&blink_timer))
    {
      etimer_reset(&blink_timer);

      rgb_led_off();
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
