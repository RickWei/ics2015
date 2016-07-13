#include "common.h"

#include <time.h>

#define TLB_NUM 64
#define TLB_MASK 0x3f

typedef struct{
	uint32_t VA:1;
	uint32_t tag;
	hwaddr_t hwaddr_base;
} tlb;

