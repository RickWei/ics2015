#include "common.h"

uint32_t dram_read(hwaddr_t, size_t);
void dram_write(hwaddr_t, size_t, uint32_t);
uint32_t cache_read_l1(hwaddr_t, size_t);
void cache_write_l1(hwaddr_t, size_t, uint32_t);
uint32_t cache_read_l2(hwaddr_t, size_t);
void cache_write_l2(hwaddr_t, size_t, uint32_t);
lnaddr_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg);
hwaddr_t page_translate(lnaddr_t addr);

/* Memory accessing interfaces */
extern int is_mmio(hwaddr_t);
extern uint32_t mmio_read(hwaddr_t,size_t,int);
extern void mmio_write(hwaddr_t,size_t,uint32_t,int);
uint32_t hwaddr_read(hwaddr_t addr, size_t len) {
	if(is_mmio(addr)!=-1)
		return mmio_read(addr,len,is_mmio(addr));
	else
		return cache_read_l1(addr, len) & (~0u >> ((4 - len) << 3));
	//return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
}

void hwaddr_write(hwaddr_t addr, size_t len, uint32_t data) {
	if(is_mmio(addr)!=-1)
	{
		mmio_write(addr,len,data,is_mmio(addr));
	}
	else{
		cache_write_l1(addr, len, data);
		cache_write_l2(addr, len, data);
	}//dram_write(addr, len, data);
}

uint32_t lnaddr_read(lnaddr_t addr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	/*if () {
		* this is a special case, you can handle it later. *
		assert(0);
	}*/
	//else 
	{
		hwaddr_t hwaddr = page_translate(addr);
		return hwaddr_read(hwaddr, len);
	}
}
void lnaddr_write(lnaddr_t addr, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
	/*if () {
		* this is a special case, you can handle it later. *
		assert(0);
	}*/
	//else 
	{
		hwaddr_t hwaddr=page_translate(addr);
		hwaddr_write(hwaddr, len, data);
		return;
	}
}

uint32_t swaddr_read(swaddr_t addr, size_t len,uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr=seg_translate(addr,len,sreg);
	return lnaddr_read(lnaddr, len);
}

void swaddr_write(swaddr_t addr, size_t len, uint32_t data,uint8_t sreg) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_t lnaddr=seg_translate(addr,len,sreg);
	lnaddr_write(lnaddr, len, data);
}

