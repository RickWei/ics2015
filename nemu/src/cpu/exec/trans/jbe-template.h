#include "cpu/exec/template-start.h"

#define instr jbe

static void do_execute() {
	DATA_TYPE_S my_rel8=op_src->val;
	uint32_t my_rel = my_rel8;
	if(cpu.ZF==1||cpu.CF==1){
		cpu.eip=cpu.eip+my_rel;
		if(DATA_BYTE==2){
			cpu.eip=cpu.eip&0xffff;
		}
	}
	print_asm_template1();
}


#if DATA_BYTE==1 
	make_instr_helper(si)
#endif
make_instr_helper(i)

#include "cpu/exec/template-end.h"

