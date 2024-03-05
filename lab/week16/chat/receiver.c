#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include <string.h>
#include <stdio.h>
#include "dev/leds.h"
#include "sys/node-id.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

// IMPORTANT: The config.h file contains common configuration!
#include "config.h"

/*---------------------------------------------------------------------------*/
/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
  message_t message;
  memcpy(&message, bytes, len);

  char msg_team_id = message.team_id;
  int msg_node_id = message.node_id;

  LOG_INFO("Received message from node_id '%d' for TEAM: '%c'\n", msg_node_id, msg_team_id);

  // TODO: Change `false` to check for `TEAM_ID`
  if (false)
  {
    // Turn the LED on ONLY IF we receive data
    leds_single_on(LEDS_LED1);
    // TODO: Print the node ID the message is coming from
    LOG_INFO("Got message from node_id: %d\n", ___________);
  }
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Receiver process");
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
