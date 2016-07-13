#include "TLB.h"

tlb TLB[TLB_NUM];

uint32_t TLB_index(lnaddr_t addr){
	return (addr>>12)&TLB_MASK;
}

uint32_t TLB_tag(lnaddr_t addr){
	return (addr>>12)>>6;
}

bool TLB_check(uint32_t index, uint32_t tag){
	if(TLB[index].VA==0)
		return false;
	else if(TLB[index].tag==tag)
		return true;
	else
		return false;
}

bool TLB_read(lnaddr_t addr, uint32_t *hwaddr_base){
	uint32_t index=TLB_index(addr);
	uint32_t tag=TLB_tag(addr);
	if(TLB_check(index,tag)){
		*hwaddr_base=TLB[index].hwaddr_base;
		return true;
	}
	else
		return false;
}

bool TLB_write(uint32_t hwaddr_base, lnaddr_t addr){
	uint32_t index=TLB_index(addr);
	uint32_t tag=TLB_tag(addr);
	TLB[index].hwaddr_base=hwaddr_base;
	TLB[index].tag=tag;
	TLB[index].VA=1;
	return true;
}

void TLB_init(){
	int i;
	for(i=0;i<TLB_NUM;i++)
		TLB[i].VA=0;
}
