#include "cache.h"

#define L2_LINE 16//16 way

#define L2_COL (1<<l2_OFFSET_WIDTH)
#define L2_GROUP (1<<l2_INDEX_WIDTH)

#define COL_MASK (L2_COL-1)

#define HW_MEM_SIZE (1 << 27)

uint32_t dram_read(hwaddr_t addr, size_t len);
uint32_t dram_write(hwaddr_t addr, size_t len, uint32_t data);

typedef struct{
	bool valid_byte;
	bool dirty_byte;
	uint32_t tag;
	uint8_t Block[L2_COL];
} cache_line;
typedef struct{
	cache_line Line[L2_LINE];
} cache_group;
typedef struct{
	cache_group Group[L2_GROUP];
} cache_l2;

static cache_l2 cache2;

static int is_hit(uint32_t index,uint32_t tag){
	uint32_t line;
	for(line=0;line<L2_LINE;line++){				
		if(cache2.Group[index].Line[line].valid_byte)		
		if(cache2.Group[index].Line[line].tag==tag)
			break;
	}
	return line;
}

static int is_full(uint32_t index){
	uint32_t line;
	for(line=0;line<L2_LINE;line++){
		if(cache2.Group[index].Line[line].valid_byte==false)
			break;
	}
	return line;
}

static void write_back(uint32_t index,int line,hwaddr_t addr){
	if(cache2.Group[index].Line[line].dirty_byte){
		uint32_t i;
		for(i=0;i<L2_COL;i++)
			dram_write(addr,1,cache2.Group[index].Line[line].Block[i]);
	}
}

static void line_read_l2(hwaddr_t addr,void *data){
	Assert(addr < HW_MEM_SIZE, "physical address %x is outside of the physical memory!", addr);
	sram_addr temp;
	temp.addr = addr & ~BURST_MASK;
	uint32_t offset=temp.offset_2;
	uint32_t index=temp.index_2;
	uint32_t tag=temp.tag_2;
	int line=is_hit(index,tag);
	if(line<16){//hit
		memcpy(data, cache2.Group[index].Line[line].Block+offset, BURST_LEN);
	}
	else{//miss
		line=is_full(index);
		if(line>=8){
			line=replace_line(L2_LINE);
			write_back(index,line,addr);
		}
		cache2.Group[index].Line[line].valid_byte=true;
		cache2.Group[index].Line[line].dirty_byte=false;
		cache2.Group[index].Line[line].tag=tag;
		int i;
		for(i=0;i<L2_COL;i++)
			cache2.Group[index].Line[line].Block[i]=dram_read((addr&(~COL_MASK))+i,1);
		memcpy(data, cache2.Group[index].Line[line].Block + offset, BURST_LEN);
	}
}


//write-allocate
static void line_write_l2(hwaddr_t addr, void *data, uint8_t *mask){
	Assert(addr < HW_MEM_SIZE, "physical address %x is outside of the physical memory!", addr);
	sram_addr temp;
	temp.addr = addr & ~BURST_MASK;
	uint32_t offset=temp.offset_2;
	uint32_t index=temp.index_2;
	uint32_t tag=temp.tag_2;
	int line=is_hit(index,tag);
	if(line<16){//hit
		memcpy_with_mask(cache2.Group[index].Line[line].Block + offset, data, BURST_LEN, mask);//write-allocate
		cache2.Group[index].Line[line].dirty_byte=true;
	}
	else{//miss
		line=is_full(index);
		if(line>=8){//miss
			line=replace_line(L2_LINE);
			write_back(index,line,addr);//write back
		}
		cache2.Group[index].Line[line].valid_byte=true;
		cache2.Group[index].Line[line].dirty_byte=true;
		cache2.Group[index].Line[line].tag=tag;
		int i;
		for(i=0;i<L2_COL;i++)
			cache2.Group[index].Line[line].Block[i]=dram_read((addr&(~COL_MASK))+i,1);
		memcpy_with_mask(cache2.Group[index].Line[line].Block + offset, data, BURST_LEN, mask);
	}
}

uint32_t cache_read_l2(hwaddr_t addr,size_t len){
	uint32_t offset=addr&BURST_MASK;
	uint8_t temp[2*BURST_LEN];
	line_read_l2(addr,temp);
	if(offset+len>BURST_LEN){
		line_read_l2(addr+BURST_LEN,temp+BURST_LEN);
	}
	return unalign_rw(temp + offset, 4);
}

void cache_write_l2(hwaddr_t addr, size_t len, uint32_t data){
	uint32_t offset = addr & BURST_MASK;
	uint8_t temp[2 * BURST_LEN];
	uint8_t mask[2 * BURST_LEN];
	memset(mask, 0, 2 * BURST_LEN);
	*(uint32_t *)(temp + offset) = data;
	memset(mask + offset, 1, len);
	line_write_l2(addr,temp,mask);
	if(offset+len>BURST_LEN){
		line_write_l2(addr+BURST_LEN,temp+BURST_LEN,mask+BURST_LEN);
	}
}

void cache_init_l2(){
	int i,j;
	for(i=0;i<L2_GROUP;i++)
		for(j=0;j<L2_LINE;j++)
			cache2.Group[i].Line[j].valid_byte=false;
}

