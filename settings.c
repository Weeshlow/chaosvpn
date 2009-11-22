#include <stdlib.h>
#include <string.h>

#include "chaosvpn.h"

// NOTE: *must* assign NULL here to string values; initialize those in
// settings_init_defaults(). All numerics may be initialized here.

char* s_my_peerid = NULL;
char* s_my_vpn_ip = NULL;
char* s_my_vpn_ip6 = NULL;
char* s_my_password = NULL;
char* s_my_ip = NULL;
char* s_networkname = NULL;
char* s_tincd_bin = NULL;
char* s_ip_bin = NULL;
char* s_ifconfig = NULL;
char* s_ifconfig6 = NULL;
char* s_master_url = NULL;
char* s_base = NULL;
char* s_pidfile = NULL;
char* s_interface = NULL;
char* s_my_vpn_netmask = NULL;
int s_tincd_debuglevel = 0;


// Note: all settings *must* be strdupped!
void
settings_init_defaults(void)
{
    s_interface = strdup("eth0");
    s_my_vpn_netmask = strdup("255.255.255.0");
}