#ifndef _NETINET_IN_H
#define _NETINET_IN_H 1

#include <stdint.h>

typedef uint32_t in_addr_t;

struct in_addr {
	in_addr_t s_addr;
};

#endif
