/*
 * Hewlett-Packard Company Confidential (C) Copyright 2015 Hewlett-Packard Development Company, L.P.
 *
 * File:    hc-knet.h
 *
 */
#ifndef __HC_KNET_H__
#define __HC_KNET_H__ 1

#include <ovs/dynamic-string.h>
#include <netinet/ether.h>
#include <opennsl/types.h>

/* BCM KNET filter priorities.
 * Filters with priority 0 are applied only on RX channel 0.
 * Filters with priority 1 are applied only on RX channel 1.
 * Filters with priority 2 and above are applied to both RX channels.
 */
enum knet_filter_prio_e
{
    KNET_FILTER_PRIO_HIGHEST = 2,
    KNET_FILTER_PRIO_VLAN = 5,
    KNET_FILTER_PRIO_PORT,
    KNET_FILTER_PRIO_LOWEST = 255
};

typedef enum knet_debug_type_ {
    KNET_DEBUG_NETIF,
    KNET_DEBUG_FILTER,
    KNET_DEBUG_MAX
} knet_debug_type_t;

struct knet_user_data {
    struct ds *ds;
    int count;
};

extern int hc_knet_init(int unit);
extern int bcmsdk_knet_if_create(char *name, int unit, opennsl_port_t port,
                                 struct ether_addr *mac, int *knet_if_id);
extern int bcmsdk_knet_if_delete(char *name, int unit, int knet_if_id);

extern void bcmsdk_knet_filter_delete(char *name, int unit, int knet_filter_id);

extern int bcmsdk_knet_if_delete_by_name(char* name, int hw_unit);
extern void bcmsdk_knet_port_filter_create(char *name, int hw_unit, opennsl_port_t hw_port,
                                           int knet_if_id, int *knet_filter_id);
extern void bcmsdk_knet_vlan_interface_filter_create(char *name,  opennsl_vlan_t vid,
                                                     int *knet_filter_id);

extern void hc_knet_dump(struct ds *ds, knet_debug_type_t debug_type);

#endif /* __HC_KNET_H__ */
