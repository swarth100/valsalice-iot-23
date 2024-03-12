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

#define STATS_INTERVAL (30 * CLOCK_SECOND)

static int reception_stats[N_NODES];
static int send_stats[N_NODES];
static int cur_node = 0;

/*---------------------------------------------------------------------------*/
// Map node IDs to indices in the array
int get_index_for_node_id(int target_node_id)
{
      int index = 0;
      for (int i = 0; i < N_NODES; i++)
      {
            if (NODE_IDS[i] == target_node_id)
            {
                  index = i;
                  break;
            }
      }
      return index;
}

// Generate a request value for a given node.
int get_request_value(int source_node_id)
{
      /* DO NOT EDIT! */
      return reception_stats[get_index_for_node_id(source_node_id)] + 1;
}

// Given a payload received from a given node, the sender can verify if the payload was indeed sent
// from the correct node.
bool verify_response(int source_node_id, int payload)
{
      /* DO NOT EDIT! */
      int request_value = get_request_value(source_node_id);

      srand(source_node_id + request_value);
      bool is_valid = rand() == payload;

      if (is_valid)
      {
            LOG_INFO("Payload '%d' from node '%d' is valid\n", payload, source_node_id);
      }
      else
      {
            LOG_INFO("Payload '%d' from node '%d' is NOT valid\n", payload, source_node_id);
      }

      return is_valid;
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

      // Track send stats
      send_stats[get_index_for_node_id(target_node_id)]++;

      NETSTACK_NETWORK.output(NULL);
}

/* Helper function to receive data over nullnet */
void receive_nullnet_data(const void *bytes, uint16_t len,
                          const linkaddr_t *src, const linkaddr_t *dest)
{
      /* DO NOT EDIT! */
      message_t message;
      memcpy(&message, bytes, len);

      char msg_team_id = message.team_id;
      int msg_source_node_id = message.source_node_id;
      int msg_target_node_id = message.target_node_id;
      int msg_payload = message.payload;

      // The source of a message will be the node sending the response.
      // This may not be the node the message has originated from!
      int cur_node_id = NODE_IDS[cur_node];

      LOG_INFO("Received message from node_id '%d' for TEAM '%c' for target node '%d'.\n",
               msg_source_node_id, msg_team_id, msg_target_node_id);

      // HINT: Change `true` to a different condition
      if (msg_team_id == TEAM_ID &&
          msg_target_node_id == node_id)
      {
            // Turn the LED on ONLY IF we receive data
            leds_single_on(LEDS_LED1);

            // Verify the received response
            if (verify_response(cur_node_id, msg_payload))
            {
                  reception_stats[cur_node]++;
            }
      }
}

/*---------------------------------------------------------------------------*/

// Print stats on how the network is performing
void print_stats()
{
      /* DO NOT EDIT! */
      LOG_INFO("RECEPTION STATS:\n");
      for (int i = 0; i < N_NODES; i++)
      {
            if (send_stats[i] > 0)
            {
                  LOG_INFO(
                      "[STATS] ID '%d'. Sent: '%d'. Received: '%d'. Success Rate: '%d%%'\n",
                      NODE_IDS[i], send_stats[i], reception_stats[i], (int)((float)reception_stats[i] / send_stats[i] * 100));
            }
      }
}

/*---------------------------------------------------------------------------*/
PROCESS(main_process, "Sender Process");
AUTOSTART_PROCESSES(&main_process);

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(main_process, ev, data)
{
      static struct etimer blink_timer;
      static struct etimer periodic_timer;
      static struct etimer stats_timer;

      PROCESS_BEGIN();

      /* Initialize NullNet */
      nullnet_set_input_callback(receive_nullnet_data);

      /* Initialize the Timers */
      etimer_set(&blink_timer, BLINK_INTERVAL);
      etimer_set(&periodic_timer, SEND_INTERVAL);
      etimer_set(&stats_timer, STATS_INTERVAL);

      // Initialise the reception stats
      for (int i = 0; i < N_NODES; i++)
      {
            reception_stats[i] = 0;
            send_stats[i] = 0;
      }

      while (true)
      {
            PROCESS_WAIT_EVENT();

            if (etimer_expired(&stats_timer))
            {
                  etimer_reset(&stats_timer);

                  // Print reception stats
                  print_stats();
            }

            if (etimer_expired(&periodic_timer))
            {
                  // Determine the next target node.
                  // `target_node_id` holds the ID of the node you must get input from.
                  cur_node = (cur_node + 1) % N_NODES;
                  int target_node_id = NODE_IDS[cur_node];

                  // Generate a request value
                  int request_value = get_request_value(target_node_id);

                  // Periodically send a message
                  // TODO(1): Use `send_nullnet_data` to actually send the message
                  send_nullnet_data(target_node_id, request_value);

                  etimer_reset(&blink_timer);
                  etimer_reset(&periodic_timer);
            }

            if (etimer_expired(&blink_timer))
            {
                  leds_single_off(LEDS_LED1);
            }
      }

      PROCESS_END();
}
/*---------------------------------------------------------------------------*/
