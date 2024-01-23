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
#define SEND_INTERVAL (10 * CLOCK_SECOND)
#define BUFFER_INTERVAL (0.3 * CLOCK_SECOND)

#define START_ID 'D'
#define END_ID 'N'
#define UNIVERSE_LEN (END_ID - START_ID) + 1

/*---------------------------------------------------------------------------*/
PROCESS(remote_led_demo_receiver, "Counter Process");
AUTOSTART_PROCESSES(&remote_led_demo_receiver);

static struct etimer blink_timer;
static struct etimer send_timer;
static struct etimer buffer_timer;

static message_t universe[UNIVERSE_LEN];
static int command = 1;
static char send_team_id = START_ID;

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
  rgb_led_set(RGB_LED_GREEN);
}

/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
  message_t message;
  memcpy(&message, bytes, len);

  char team_id = message.team_id;
  int data = message.data;

  int index = team_id - START_ID;

  if (team_id == 'Z')
  {
    // Do not reply to team 'Z', it's not allowed to be used!
    return;
  }

  rgb_led_set(RGB_LED_CYAN);
  if (data == 42)
  {
    universe[index].data += 1;
    send_nullnet_data(team_id, 3);
    printf("Correct message from '%c'\n", team_id);
  }
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(remote_led_demo_receiver, ev, data)
{
  PROCESS_BEGIN();

  for (char c = START_ID; c <= END_ID; c++)
  {
    int index = c - START_ID;
    message_t datum = {.team_id = c, .data = 0};
    universe[index] = datum;
  }

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set up a periodic event timer to poll the main process
  etimer_set(&blink_timer, BLINK_INTERVAL);
  etimer_set(&send_timer, SEND_INTERVAL);
  etimer_set(&buffer_timer, BUFFER_INTERVAL);

  while (1)
  {
    PROCESS_WAIT_EVENT();

    if (etimer_expired(&blink_timer))
    {
      etimer_restart(&blink_timer);

      rgb_led_off();
    }
    if (etimer_expired(&buffer_timer))
    {
      if (send_team_id != (END_ID + 1))
      {
        send_nullnet_data(send_team_id, command);
        send_team_id = (char)(send_team_id + 1);

        etimer_restart(&buffer_timer);
      }
    }
    if (etimer_expired(&send_timer))
    {
      send_team_id = START_ID;
      command = ((command + 1) % 3);

      etimer_restart(&send_timer);
      etimer_restart(&buffer_timer);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
