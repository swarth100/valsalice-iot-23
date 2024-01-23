#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "dev/etc/rgb-led/rgb-led.h"

typedef struct
{
  char team_id;
  int data;
} message_t;

// IMPORTANT!
// Change the `TEAM_ID` to be your specific team's!
#define TEAM_ID 'L'

#define BLINK_INTERVAL (5 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(contiki_process, "Repeat Process");
AUTOSTART_PROCESSES(&contiki_process);

static struct etimer blink_timer;

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
  /* DO NOT EDIT! */
  printf("Sending data from '%c': %d\n", TEAM_ID, data);

  message_t buffer = {
      .team_id = TEAM_ID, .data = data};
  nullnet_buf = (uint8_t *)&buffer;
  nullnet_len = sizeof(message_t);

  NETSTACK_NETWORK.output(NULL);
}

/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
  message_t message;
  memcpy(&message, bytes, len);

  char team = message.team_id;
  int data = message.data;

  printf("Received instruction for TEAM: '%c'\n", team);

  if (team == TEAM_ID)
  {
    printf("Data received: %d\n", data);
    /* EDIT inside this IF-statement */
    if (data == 0)
    {
      send_nullnet_data(42);
    }
    else if (data == 1)
    {
      rgb_led_set(RGB_LED_GREEN);
    }
    else if (data == 2)
    {
      rgb_led_set(RGB_LED_MAGENTA);
    }
    else if (data == 3)
    {
      rgb_led_set(RGB_LED_BLUE);
    }
  }
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(contiki_process, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set up a periodic event timer to poll the main process
  etimer_set(&blink_timer, BLINK_INTERVAL);

  while (true)
  {
    PROCESS_WAIT_EVENT();

    if (etimer_expired(&blink_timer))
    {
      etimer_reset(&blink_timer);

      rgb_led_off();
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
