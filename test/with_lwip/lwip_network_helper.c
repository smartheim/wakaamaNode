#if defined(LWIP)

#include <sys/socket.h>

#include "lwip/init.h"
#include "lwip/debug.h"
#include "lwip/mem.h"
#include "lwip/memp.h"
#include "lwip/sys.h"
#include "lwip/timeouts.h"
#include "lwip/ethip6.h"
#include "lwip/netif.h"
#include "netif/etharp.h"
#include "lwipopts.h"

#include "client_debug.h" // for lwm2m_printf
#include "network_helper.h"
#include "internals.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#define DEVTAP "/dev/net/tun"

/* (manual) host IP configuration */
static ip4_addr_t ipaddr, netmask, gw;

/* nonstatic debug cmd option, exported in lwipopts.h */
unsigned char debug_flags;

struct netif netifs[2];
const char* tapNames[2] = {TAP_CLIENT_DEVIDE, TAP_SERVER_DEVICE};
const char* tapIP[2] = {TAP_CLIENT_ADDR, TAP_SERVER_ADDR};

err_t low_level_output(struct netif *netif, struct pbuf *p)
{
  char buf[1514];
  ssize_t written;

  /* initiate transfer(); */
  pbuf_copy_partial(p, buf, p->tot_len, 0);

  /* signal that packet should be sent(); */
  written = write((intptr_t)netif->state, buf, p->tot_len);
  if (written == -1) {
    perror("tapif: write");
  }
  return ERR_OK;
}

static void tapif_input(struct netif *netif)
{
    struct pbuf *p;
    u16_t len;
    char buf[1514];

    /* Obtain the size of the packet and put it into the "len"
       variable. */
    len = read((intptr_t)netif->state, buf, sizeof(buf));
    if (len == (u16_t)-1) {
      perror("read returned -1");
      exit(1);
    }

    /* We allocate a pbuf chain of pbufs from the pool. */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
    if (p != NULL) {
      pbuf_take(p, buf, len);
      /* acknowledge that packet has been read(); */
    } else {
      /* drop packet(); */
      LWIP_DEBUGF(NETIF_DEBUG, ("tapif_input: could not allocate pbuf\n"));
    }

  if (p == NULL) {
    LWIP_DEBUGF(TAPIF_DEBUG, ("tapif_input: low_level_input returned NULL\n"));
    return;
  }

  if (netif->input(p, netif) != ERR_OK) {
    LWIP_DEBUGF(NETIF_DEBUG, ("tapif_input: netif input error\n"));
    pbuf_free(p);
  }
}

void network_close()
{
    //close((intptr_t)netifs[0].state);
    //close((intptr_t)netifs[1].state);
    //netif_remove(&netifs[0]);
    //netif_remove(&netifs[1]);
}

err_t tapif_init(struct netif *netif) {
    return ERR_OK;
}

err_t tapif_real_init(int netIfNo)
{
    struct netif *netif = &netifs[netIfNo];

    netif->state = (void*)(intptr_t)netIfNo;
    netif->name[0] = 't';
    netif->name[1] = netIfNo+'0';
    netif->output = etharp_output;
    netif->output_ip6 = ethip6_output;
    netif->linkoutput = low_level_output;
    netif->mtu = 1500;

    /* Obtain MAC address from network interface. */

    /* (We just fake an address...) */
    netif->hwaddr[0] = 0x02;
    netif->hwaddr[1] = 0x12;
    netif->hwaddr[2] = 0x34;
    netif->hwaddr[3] = 0x56;
    netif->hwaddr[4] = 0x78;
    netif->hwaddr[5] = 0xab + netIfNo;
    netif->hwaddr_len = 6;

    /* device capabilities */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_IGMP;

    netif->state = (void*)(intptr_t)open(DEVTAP, O_RDWR);
    LWIP_DEBUGF(TAPIF_DEBUG, ("tapif_init: fd %c%c\n", netif->name[0], netif->name[1]));
    if ((intptr_t)netif->state == -1) {
      perror("tapif_init: try running \"modprobe tun\" or rebuilding your kernel with CONFIG_TUN; cannot open "DEVTAP);
      exit(1);
    }

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));

    strncpy(ifr.ifr_name, tapNames[netIfNo], sizeof(ifr.ifr_name));

    ifr.ifr_flags = IFF_TAP|IFF_NO_PI;
    if (ioctl((intptr_t)netif->state, TUNSETIFF, (void *) &ifr) < 0) {
        perror("tapif_init: "DEVTAP" ioctl TUNSETIFF");
        return ERR_ABRT;
    }

    netif_set_link_up(netif);
    return ERR_OK;
}

bool network_init()
{
    // LwIP can only be initialited once
    static bool lwip_init_done = false;
    if (lwip_init_done) {
        sys_restart_timeouts();
        return true;
    }
    lwip_init_done = true;

  /* use debug flags defined by debug.h */
  debug_flags = LWIP_DBG_OFF;
  debug_flags |= (LWIP_DBG_ON|LWIP_DBG_TRACE|LWIP_DBG_STATE|LWIP_DBG_FRESH|LWIP_DBG_HALT);

  lwip_init();

  for (int tapDevices = 0; tapDevices < 2; ++tapDevices)
  {
      IP4_ADDR(&gw, 192,168,7,10);
      ipaddr.addr = ipaddr_addr(tapIP[tapDevices]);
      IP4_ADDR(&netmask, 255,255,255,0);

      char ip_str[16] = {0}, nm_str[16] = {0}, gw_str[16] = {0};
      strncpy(ip_str, ip4addr_ntoa(&ipaddr), sizeof(ip_str));
      strncpy(nm_str, ip4addr_ntoa(&netmask), sizeof(nm_str));
      strncpy(gw_str, ip4addr_ntoa(&gw), sizeof(gw_str));

      lwm2m_printf("Host at %s mask %s gateway %s\n", ip_str, nm_str, gw_str);

        netif_add(&netifs[tapDevices], &ipaddr, &netmask, &gw, NULL, tapif_init, ethernet_input);
      err_t tapIfOK = tapif_real_init(tapDevices);
      if (tapIfOK != ERR_OK) {
        lwm2m_printf("tapif_real_init failed with %i\n", tapIfOK);
        lwip_init_done = false;
        return false;
      }
      netif_set_up(&netifs[tapDevices]);
      netif_create_ip6_linklocal_address(&netifs[tapDevices], 1);
  }
  return true;
  //netif_set_default(&netifs[tapDevices]);
}

void* network_get_interface(int id)
{
     struct netif* n = netif_list;
     for (int c = 1;c>=0 && n;--c)
     {
         if (c==id)
             return n;
         n = n->next;
     }
     return NULL;
}

uint8_t network_step_blocking(lwm2m_context_t * lwm2mH, int bound_sockets) {
    time_t max_wait_sec = 5;
    uint8_t result = lwm2m_step(lwm2mH, &max_wait_sec);
    if (result != 0 && result != COAP_503_SERVICE_UNAVAILABLE)
    {
        fprintf(stderr, "lwm2m_step() failed: 0x%X\r\n", result);
    }

    fd_set fdset;
    int ret;
    struct timeval tv;
    u32_t msecs = sys_timeouts_sleeptime();

    tv.tv_sec = msecs / 1000;
    if (tv.tv_sec > max_wait_sec) tv.tv_sec = max_wait_sec;
    tv.tv_usec = (msecs % 1000) * 1000;

    struct netif* netifP = &netifs[bound_sockets];

    FD_ZERO(&fdset);
    FD_SET((intptr_t)netifP->state, &fdset);

    ret = select((intptr_t)netifP->state + 1, &fdset, NULL, NULL, &tv);
    if (ret > 0) {
      tapif_input(netifP);
    }

#if NO_SYS==1
    sys_check_timeouts();
#endif
    return result;
}

#endif
