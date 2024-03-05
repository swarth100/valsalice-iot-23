#ifndef CONFIG_H
#define CONFIG_H

/* ************************************************************************* */

/* Log configuration */
#include "sys/log.h"
#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

/* Timer Configuration */
#define BEGINNING_INTERVAL (10 * CLOCK_SECOND)
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

/* Message Configuration */
typedef struct
{
    char team_id;
    int node_id;
    int data;
} message_t;

// IMPORTANT!
// Change the `TEAM_ID` to be your specific team's!
#define TEAM_ID 'Z'
#define ROOT_NODE_ID 1

/* ************************************************************************* */

#endif // CONFIG_H