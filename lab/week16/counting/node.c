#include "contiki.h"
#include "sys/ctimer.h"
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

static struct ctimer send_timer;
static message_t buffer;

/*---------------------------------------------------------------------------*/
/* Helper function to send data over nullnet */

void delayed_send_helper(void *ptr) { NETSTACK_NETWORK.output(NULL); }

void send_nullnet_data(int data)
{
      /* DO NOT EDIT! */
      LOG_INFO("Sending data from node_id '%d' for TEAM '%c'\n", node_id, TEAM_ID);

      buffer.team_id = TEAM_ID;
      buffer.node_id = node_id;
      buffer.data = data;

      nullnet_buf = (uint8_t *)&buffer;
      nullnet_len = sizeof(message_t);

      // We delay the send by one second to better visualise communication!
      ctimer_set(&send_timer, CLOCK_SECOND, delayed_send_helper, NULL);
}

/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
      message_t message;
      memcpy(&message, bytes, len);

      char msg_team_id = message.team_id;
      int msg_node_id = message.node_id;
      int msg_data = message.data;

      LOG_INFO("Received data from node_id '%d' for TEAM '%c': '%d'\n", msg_node_id, msg_team_id, msg_data);

      // We filter based on TEAM_ID to ignore messages from other teams
      if (msg_team_id == TEAM_ID)
      {
            // Turn the LED on ONLY IF we receive data
            leds_single_on(LEDS_LED1);

            // TODO: If sender is node 1 and I am node 2: reply
            // TODO: If sender is node 2 and I am node 3: reply
            // TODO: If sender is node 3 and I am node 1: reply
      }
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Node");
AUTOSTART_PROCESSES(&main_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
      static struct etimer blink_timer;
      static struct etimer beginning_timer;

      PROCESS_BEGIN();
      static bool has_sent = false;

      /* Initialize NullNet */
      nullnet_set_input_callback(receive_nullnet_data);

      /* Initialize the Timers */
      etimer_set(&blink_timer, BLINK_INTERVAL);
      etimer_set(&beginning_timer, BEGINNING_INTERVAL);

      while (true)
      {
            PROCESS_WAIT_EVENT();
            if (etimer_expired(&beginning_timer) && !has_sent)
            {
                  // Periodically send an empty message
                  if (node_id == ROOT_NODE_ID)
                  {
                        send_nullnet_data(1);
                  }

                  // We ensure that we can send the message only once
                  has_sent = true;
                  etimer_reset(&blink_timer);
            }
            else if (etimer_expired(&blink_timer))
            {
                  leds_single_off(LEDS_LED1);
            }
      }

      PROCESS_END();
}
/*---------------------------------------------------------------------------*/
