#include "cache.h"

#define L1_LINE 8	//8-way
#define L1_COL (1<<l1_OFFSET_WIDTH)//byte per block
#define L1_GROUP (1<<l1_INDEX_WIDTH)//blocks/3 3=8-way

#define COL_MASK (L1_COL-1)
#define HW_MEM_SIZE (1 << 27)
typedef struct{
	bool valid_byte;
	uint32_t tag;
	uint8_t Block[L1_COL];
} cache_line;
typedef struct{
	cache_line Line[L1_LINE];
} cache_Group;
typedef struct{
	cache_Group Group[L1_GROUP];
} cache_l1;

uint32_t cache_read_l2(hwaddr_t addr, size_t len);

static cache_l1 cache1;//define


static int is_hit(uint32_t index,uint32_t tag){
	uint32_t line;
	for(line=0;line<L1_LINE;line++){
		if(cache1.Group[index].Line[line].valid_byte)//valid
			if(cache1.Group[index].Line[line].tag==tag)//hit
				break;
	}
	return line;
}

static int is_full(uint32_t index){
	uint32_t line;
	for(line=0;line<L1_LINE;line++){
		if(cache1.Group[index].Line[line].valid_byte==false)
			break;
	}
	return line;
}

static void line_read_l1(hwaddr_t addr,void *data){
	Assert(addr < HW_MEM_SIZE, "physical address %x is outside of the physical memory!", addr);
	sram_addr temp;
	temp.addr = addr & ~BURST_MASK;
	uint32_t offset=temp.offset_1;
	uint32_t index=temp.index_1;
	uint32_t tag=temp.tag_1;	
	int line=is_hit(index,tag);	
	if(line<8){//hit
		memcpy(data, cache1.Group[index].Line[line].Block+offset, BURST_LEN);
	}
	else{//miss
		line=is_full(index);
		if(line>=8)//full
			line=replace_line(L1_LINE);//random replace
		cache1.Group[index].Line[line].valid_byte=true;
		cache1.Group[index].Line[line].tag=tag;
		int i;
		for(i=0;i<L1_COL;i++)
			cache1.Group[index].Line[line].Block[i]=cache_read_l2((addr&(~COL_MASK))+i,1);//search l2_cache
		memcpy(data, cache1.Group[index].Line[line].Block+offset, BURST_LEN);//replace
	}
}

static void line_write_l1(hwaddr_t addr, void *data, uint8_t *mask){
	Assert(addr < HW_MEM_SIZE, "physical address %x is outside of the physical memory!", addr);
	sram_addr temp;
	temp.addr = addr & ~BURST_MASK;
	uint32_t offset=temp.offset_1;
	uint32_t index=temp.index_1;
	uint32_t tag=temp.tag_1;
	int line=is_hit(index,tag);
	if(line<8){//hit
		memcpy_with_mask(cache1.Group[index].Line[line].Block + offset, data, BURST_LEN, mask);
	}
	return;//miss
}




//same as dram.c
uint32_t cache_read_l1(hwaddr_t addr,size_t len){
	uint32_t offset=addr&BURST_MASK;
	uint8_t temp[2*BURST_LEN];
	line_read_l1(addr,temp);
	if(offset+len>BURST_LEN){
		line_read_l1(addr+BURST_LEN,temp+BURST_LEN);
	}
	return unalign_rw(temp + offset, 4);
}

void cache_write_l1(hwaddr_t addr, size_t len, uint32_t data){
	uint32_t offset = addr & BURST_MASK;
	uint8_t temp[2 * BURST_LEN];
	uint8_t mask[2 * BURST_LEN];
	memset(mask, 0, 2 * BURST_LEN);
	*(uint32_t *)(temp + offset) = data;
	memset(mask + offset, 1, len);
	line_write_l1(addr,temp,mask);
	if(offset+len>BURST_LEN){
		line_write_l1(addr+BURST_LEN,temp+BURST_LEN,mask+BURST_LEN);
	}
}


void cache_init_l1(){
	int i,j;
	for(i=0;i<L1_GROUP;i++)
		for(j=0;j<L1_LINE;j++)
			cache1.Group[i].Line[j].valid_byte=false;
}
//same as dram.c
