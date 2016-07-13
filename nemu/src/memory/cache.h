#include "common.h"
#include "misc.h"
#include "burst.h"

#include <time.h>
#include <stdlib.h>

#define l1_OFFSET_WIDTH 6	//2^6=64B
#define l1_INDEX_WIDTH 7	//16-6-3=7	2^3=8 way
#define l1_TAG_WIDTH (32-l1_OFFSET_WIDTH-l1_INDEX_WIDTH)
// 32-(n+m)
#define l2_OFFSET_WIDTH 6
#define l2_INDEX_WIDTH 12	//22-6-4=12	2^4=16 way
#define l2_TAG_WIDTH (32-l2_OFFSET_WIDTH-l2_INDEX_WIDTH)

typedef union{
	struct{
		uint32_t offset_1:l1_OFFSET_WIDTH;
		uint32_t index_1:l1_INDEX_WIDTH;
		uint32_t tag_1:l1_TAG_WIDTH;
	};
	struct{
		uint32_t offset_2:l2_OFFSET_WIDTH;
		uint32_t index_2:l2_INDEX_WIDTH;
		uint32_t tag_2:l2_TAG_WIDTH;
	};
	uint32_t addr;
} sram_addr;

static inline uint32_t replace_line(uint32_t num_line){
	srand(time(0));
	return rand()%num_line;
}
