#include "contiki.h"
#include "net/routing/routing.h"
#include "net/netstack.h"
#include "net/ipv6/simple-udp.h"

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

#define BLINK_INTERVAL (2 * CLOCK_SECOND)

static struct simple_udp_connection udp_conn;

PROCESS(udp_server_process, "UDP server");
AUTOSTART_PROCESSES(&udp_server_process);
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
  LOG_INFO("Received data from ");
  LOG_INFO_6ADDR(sender_addr);

  /* send back the same string to the client as an echo reply */
  LOG_INFO("Sending response to ");
  LOG_INFO_6ADDR(sender_addr);
  simple_udp_sendto(&udp_conn, data, datalen, sender_addr);
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_server_process, ev, data)
{
  static struct etimer blink_timer;
  static uint8_t led_status = 0;

  PROCESS_BEGIN();

  /* Initialize DAG root */
  NETSTACK_ROUTING.root_start();

  /* Initialize UDP connection */
  simple_udp_register(&udp_conn, SERVER_UDP_PORT, NULL, CLIENT_UDP_PORT, udp_rx_callback);

  etimer_set(&blink_timer, BLINK_INTERVAL);
  while (1)
  {
    PROCESS_WAIT_EVENT();

    if (etimer_expired(&blink_timer))
    {
      // Handle toggling the LED after a short while
#ifndef COOJA
      if (led_status)
      {
        rgb_led_off();
      }
      else
      {
        rgb_led_set(RGB_LED_GREEN);
      }

#else
      leds_single_toggle(LEDS_LED1);
#endif

      led_status = (led_status + 1) % 2;
    }

    /* Add some jitter */
    etimer_set(&blink_timer, BLINK_INTERVAL);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
