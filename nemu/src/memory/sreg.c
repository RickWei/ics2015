#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"


uint32_t seg_base(uint8_t sreg){
	uint32_t temp;
	temp=cpu.seg_c[sreg].base_15_0+(cpu.seg_c[sreg].base_23_16<<16)+(cpu.seg_c[sreg].base_31_24<<24);
	return temp;	
}

lnaddr_t seg_translate(swaddr_t addr, size_t len, uint8_t sreg){
	if(cpu.cr0.protect_enable==0||cpu.cr0.paging==0)
		return addr;
	else{
		lnaddr_t lnaddr;
		uint32_t temp;
		temp=seg_base(sreg);
		lnaddr=temp+addr;	
		return lnaddr;
	}
}
										
