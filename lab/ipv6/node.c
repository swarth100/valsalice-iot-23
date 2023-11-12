#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"

#include "sys/log.h"

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define BLINK_INTERVAL (2 * CLOCK_SECOND)

PROCESS(udp_node_process, "UDP node");
AUTOSTART_PROCESSES(&udp_node_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_node_process, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize DAG root */
  NETSTACK_ROUTING.init();

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
