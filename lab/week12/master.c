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

#define BLINK_INTERVAL (0.2 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_receiver, "Counter Process");
AUTOSTART_PROCESSES(&remote_led_demo_receiver);

static struct etimer blink_timer;

static message_t universe[30];
static int max_value = 0;

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(char team_id, int data)
{
  printf("Sending data to '%c': %d\n", team_id, data);

  message_t buffer = {
      .team_id = team_id, .data = data};
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

  char team_id = message.team_id;
  int data = message.data;

  int index = team_id - 'A';
  int cur_value = universe[index].data;

  if (team_id == 'Z')
  {
    // Always send -1 back to team 'Z', it's not allowed to be used!
    send_nullnet_data(team_id, -1);
    return;
  }

  if (data >= max_value)
  {
    max_value = data;
    printf("Team '%c' has new max value of %d\n", team_id, max_value);
  }

  if (data <= (cur_value + 1))
  {
    rgb_led_set(RGB_LED_GREEN);
    int new_value = data + 1;
    universe[index].data = new_value;
    send_nullnet_data(team_id, new_value);

    etimer_reset(&blink_timer);
  }
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(remote_led_demo_receiver, ev, data)
{
  PROCESS_BEGIN();

  for (char c = 'A'; c <= 'Z'; c++)
  {
    int index = c - 'A';
    message_t datum = {.team_id = c, .data = 0};
    universe[index] = datum;
  }

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set up a periodic event timer to poll the main process
  etimer_set(&blink_timer, BLINK_INTERVAL);

  while (1)
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
