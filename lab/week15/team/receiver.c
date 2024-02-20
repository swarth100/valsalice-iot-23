#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h> /* For printf() */
#include "dev/leds.h"

// IMPORTANT: The config.h file contains common configuration!
#include "config.h"

static int last_received_data = 0;

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int data)
{
  /* DO NOT EDIT! */
  printf("Sending data from '%c': %d\n", TEAM_ID, data);

  message_t buffer = {.team_id = TEAM_ID, .data = data};
  nullnet_buf = (uint8_t *)&buffer;
  nullnet_len = sizeof(message_t);

  NETSTACK_NETWORK.output(NULL);
}

/*---------------------------------------------------------------------------*/
/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
  message_t message;
  memcpy(&message, bytes, len);

  char team = message.team_id;
  int data = message.data;

  printf("Received data for TEAM: '%c': %d\n", team, data);

  /* TODO(1): ONLY IF the team matches: repeat the message! */
  /* TODO(2): ONLY IF `data` is different from `last_received_data`: repeat the message! */
  // HINT: Change `true` to a different condition
  if (true)
  {
    send_nullnet_data(data);

    // Turn the LED on ONLY IF we receive data
    leds_single_on(LEDS_LED1);
  }

  // Important! We need to remember the last datum we received!
  last_received_data = data;
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Team Receiver");
AUTOSTART_PROCESSES(&main_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
  static struct etimer blink_timer;

  /* Initialize NullNet */
  nullnet_set_input_callback(receive_nullnet_data);

  PROCESS_BEGIN();

  /* Initialize the Timers */
  etimer_set(&blink_timer, BLINK_INTERVAL);

  while (true)
  {
    PROCESS_WAIT_EVENT();
    if (etimer_expired(&blink_timer))
    {
      leds_single_off(LEDS_LED1);
      etimer_reset(&blink_timer);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
