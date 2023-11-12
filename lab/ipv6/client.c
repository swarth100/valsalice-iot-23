#include "contiki.h"
#include "net/routing/routing.h"
#include "random.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"
#include <stdint.h>
#include <inttypes.h>

#include "sys/log.h"

#ifndef COOJA
#include "dev/etc/rgb-led/rgb-led.h"
#else
#include "dev/leds.h"
#endif

#define LOG_MODULE "App"
#define LOG_LEVEL LOG_LEVEL_INFO

#define WITH_SERVER_REPLY 1
#define SERVER_UDP_PORT 8765
#define CLIENT_UDP_PORT 4321

#define SEND_INTERVAL (10 * CLOCK_SECOND)
#define BLINK_INTERVAL (0.5 * CLOCK_SECOND)

static struct simple_udp_connection udp_conn;

/*---------------------------------------------------------------------------*/
PROCESS(udp_client_process, "UDP client");
AUTOSTART_PROCESSES(&udp_client_process);
/*---------------------------------------------------------------------------*/
static void
udp_rx_callback(struct simple_udp_connection *c,
                const uip_ipaddr_t *sender_addr,
                uint16_t sender_port,
                const uip_ipaddr_t *receiver_addr,
                uint16_t receiver_port,
                const uint8_t *data,
                uint16_t datalen)
{

  LOG_INFO("Received response from ");
  LOG_INFO_6ADDR(sender_addr);
  LOG_INFO_("\n");
  LOG_INFO("Response has data '%s'\n", data);
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_client_process, ev, data)
{
  static struct etimer periodic_timer;
  static struct etimer blink_timer;
  static char str[32];
  uip_ipaddr_t dest_ipaddr;
  static uint8_t tx_count;

  PROCESS_BEGIN();

  /* Initialize UDP connection */
  simple_udp_register(&udp_conn, CLIENT_UDP_PORT, NULL, SERVER_UDP_PORT, udp_rx_callback);

  etimer_set(&periodic_timer, random_rand() % SEND_INTERVAL);
  while (1)
  {
    PROCESS_WAIT_EVENT();

    if (etimer_expired(&periodic_timer))
    {
      if (NETSTACK_ROUTING.node_is_reachable() &&
          NETSTACK_ROUTING.get_root_ipaddr(&dest_ipaddr))
      {

        /* Send to DAG root */
        snprintf(str, sizeof(str), "hello %d", tx_count);

        LOG_INFO("Sending request to ");
        LOG_INFO_6ADDR(&dest_ipaddr);
        LOG_INFO_("\n");
        LOG_INFO("Request has data '%s'\n", str);

        simple_udp_sendto(&udp_conn, str, strlen(str), &dest_ipaddr);
        tx_count++;

#ifndef COOJA
        rgb_led_set(RGB_LED_CYAN);
#else
        leds_single_on(LEDS_LED1);
#endif
        etimer_set(&blink_timer, BLINK_INTERVAL);
      }
      else
      {
        LOG_INFO("Cannot send packet as root node is not reachable yet.\n");
      }
    }
    else if (etimer_expired(&blink_timer))
    {
      // Handle toggling the LED after a short while
#ifndef COOJA
      rgb_led_off();
#else
      leds_single_off(LEDS_LED1);
#endif
    }

    /* Add some jitter */
    etimer_set(&periodic_timer, SEND_INTERVAL - CLOCK_SECOND + (random_rand() % (2 * CLOCK_SECOND)));
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
