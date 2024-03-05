#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "contiki.h"
#include "net/netstack.h"
#include "net/nullnet/nullnet.h"
#include "dev/leds.h"
#include "sys/node-id.h"

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

// IMPORTANT: The config.h file contains common configuration!
#include "config.h"

/*---------------------------------------------------------------------------*/
// Generates the response payload for a given request
int generate_response(int request)
{
  srand(node_id + request);
  int response = rand();

  LOG_INFO("Generated payload '%d'.\n", response);
  return response;
}

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */
void send_nullnet_data(int target_node_id, int payload)
{
  /* DO NOT EDIT! */
  LOG_INFO(
      "Sending '%d', TEAM '%c', to '%d', payload '%d'\n",
      node_id, TEAM_ID, target_node_id, payload);

  message_t buffer = {
      .team_id = TEAM_ID,
      .source_node_id = node_id,
      .target_node_id = target_node_id,
      .payload = payload,
  };
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

  char msg_team_id = message.team_id;
  int msg_source_node_id = message.source_node_id;
  int msg_target_node_id = message.target_node_id;
  int msg_payload = message.payload;

  LOG_INFO("Received message from node_id '%d' for TEAM '%c' for target node '%d'.\n",
           msg_source_node_id, msg_team_id, msg_target_node_id);

  // TODO(1): Change `true` to a different condition
  if (true)
  {
    // Turn the LED on ONLY IF we receive data
    leds_single_on(LEDS_LED1);

    // Generate payload
    int payload = generate_response(msg_payload);
    LOG_INFO("Replying to source node '%d' with payload: %d\n", msg_source_node_id, payload);

    // TODO(2): Reply using `send_nullnet_data` to send the payload back!
  }

  // TODO(3): What if the target node is not the current node?

  // TODO(4): What can you try to do to increase the network's reliability?

  // TODO(5): Should you try to do anything to prevent duplicate messages?
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
