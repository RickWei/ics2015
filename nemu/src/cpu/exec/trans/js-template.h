#include "cpu/exec/template-start.h"

#define instr js

static void do_execute() {
	DATA_TYPE_S my_rel8=op_src->val;
	if(cpu.SF==1){
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

