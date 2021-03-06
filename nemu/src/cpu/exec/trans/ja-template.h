#include "cpu/exec/template-start.h"

#define instr ja

static void do_execute() {
	DATA_TYPE_S my_rel8=op_src->val;
	if(cpu.ZF==0&&cpu.CF==0){
		cpu.eip=cpu.eip+my_rel8;
		if(DATA_BYTE==2){
			cpu.eip=cpu.eip&0xffff;
		}
	}
	print_asm_template1();
}

make_instr_helper(i)
#if DATA_BYTE==1 
	make_instr_helper(si)
#endif

#include "cpu/exec/template-end.h"
	
