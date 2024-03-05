#ifndef CONFIG_H
#define CONFIG_H

/* ************************************************************************* */

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Timer Configuration */
#define SEND_INTERVAL (5 * CLOCK_SECOND)
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/* Message Configuration */
typedef struct
{
    char team_id;
    int source_node_id;
    int target_node_id;
    int payload;
} message_t;

// IMPORTANT!
// Change the `TEAM_ID` to be your specific team's!
#define TEAM_ID 'Z'

// IMPORTANT!
// Change this if you add or reduce the number of nodes in the network, or if the IDs change.
#define N_NODES 4
int NODE_IDS[N_NODES] = {3, 4, 5, 6};

/* ************************************************************************* */

#endif // CONFIG_H