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
#define TEAM_ID 'Z'

#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)
#define RETRY_INTERVAL (3 * CLOCK_SECOND)

/*---------------------------------------------------------------------------*/
PROCESS(counter_process, "Counter Process");
AUTOSTART_PROCESSES(&counter_process);

static struct etimer blink_timer;
static struct etimer retry_timer;

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
  /* DO NOT EDIT! */
  printf("Sending data: %d\n", data);

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

  int data = message.data;

  if (message.team_id == TEAM_ID)
  {
    printf("Data received: %d\n", data);
    /* EDIT inside this IF-statement */

    // Anytime you receive `data` you should `send_nullnet_data` with value `data + 1`.
    // If the `data` is above 20 you can turn on the CYAN light
  }
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(counter_process, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  // Set up a periodic event timer to poll the main process
  etimer_set(&blink_timer, BLINK_INTERVAL);
  etimer_set(&retry_timer, RETRY_INTERVAL);

  while (1)
  {
    PROCESS_WAIT_EVENT();

    // You can configure the blink timer to handle blinking.

    // You can configure the retry timer to restart counting from `0`.
    // This can be useful to handle missing data.
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
