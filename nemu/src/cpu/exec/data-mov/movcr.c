#include "cpu/exec/helper.h"


make_helper(mov_cr2r){
	uint32_t mod_rm=instr_fetch(eip+1,1);
	uint32_t reg_g=mod_rm&0x7;
	uint32_t reg_c=(mod_rm&0x38)>>3;
	if(reg_c==0)
		reg_l(reg_g)=cpu.cr0.val;
	else if(reg_c==3)
		reg_l(reg_g)=cpu.cr3.val;
	else
		assert(0);
	print_asm("mov cr0 %%%s",regsl[reg_g]);
	return 2;
}

make_helper(mov_r2cr){
	uint32_t mod_rm=instr_fetch(eip+1,1);
	uint32_t reg_g=mod_rm&0x7;
	uint32_t reg_c=(mod_rm&0x38)>>3;
	if(reg_c==0)
		cpu.cr0.val=reg_l(reg_g);
	else if(reg_c==3){
		cpu.cr3.val=reg_l(reg_g);
	}
	else
		assert(0);
	print_asm("mov %%%s cr0",regsl[reg_g]);
	return 2;
}

