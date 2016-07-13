#include "common.h"
#include "cpu/reg.h"
#include "memory/memory.h"

bool TLB_read(lnaddr_t addr, uint32_t *hwaddr_base);
bool TLB_write(uint32_t hwaddr_base, lnaddr_t addr);

hwaddr_t page_translate(lnaddr_t addr){
	if(cpu.cr0.protect_enable==1&&cpu.cr0.paging==1){

		if(addr>=0xa0000&&addr<0xafa00)
			return addr;
		uint32_t hwaddr_base;	
		PDE my_pde;
		PTE my_pte;
		hwaddr_t my_hwaddr;
		uint32_t dir=((addr>>22)&0x3ff)<<2;
		uint32_t page=((addr>>12)&0x3ff)<<2;
		uint32_t offset=addr&0xfff;

		if(TLB_read(addr,&hwaddr_base))
		{
			return (hwaddr_base<<12)+offset;
		}
		my_pde.val=hwaddr_read((cpu.cr3.page_directory_base<<12)+dir,4);//page directory
		
	if(my_pde.present==0){
			Log("%x",addr);
			Assert(0,"eip=%x",cpu.eip);
			return addr;
		}
		my_pte.val=hwaddr_read((my_pde.page_frame<<12)+page,4);//page table
		if(my_pte.present==0){
			Log("my_pte=%x",my_pde.page_frame);
			assert(0);
			return addr;
		}
		if(TLB_write(my_pte.page_frame, addr)==false)
			printf("fail to write\n");
		my_hwaddr=(my_pte.page_frame<<12)+offset;
		return my_hwaddr;
	}
	else
		return addr;
}
