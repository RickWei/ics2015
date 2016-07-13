#include "cpu/exec/template-start.h"

#define instr adc

static void do_execute() {
	DATA_TYPE my_src=op_src->val;
	DATA_TYPE my_dest=op_dest->val;
	OPERAND_W(op_dest,my_dest+my_src+cpu.CF);
	uint64_t my_test=(uint64_t)my_dest+my_src+cpu.CF;
	DATA_TYPE my_test4=my_dest+my_src+cpu.CF;
	DATA_TYPE_S my_test2=my_dest+my_src+cpu.CF;
	cpu.CF=!!(my_test>>(DATA_BYTE*8));
	my_test^=(my_test>>4);
	my_test^=(my_test>>2);
	my_test^=(my_test>>1);
	my_test=my_test&1;
	cpu.PF=!my_test;
	uint8_t my_test3=(my_dest&0xf)+(my_src&0xf)+cpu.CF;
	cpu.AF=!!(my_test3>>4);
	cpu.ZF=!my_test2;
	cpu.SF=(my_test2<0);
	cpu.OF=((my_dest^my_test4)&((my_src+cpu.CF)^my_dest))>>((DATA_BYTE<<3)-1);
	print_asm_template2();
}

make_instr_helper(r2rm)
#if DATA_BYTE==2||DATA_BYTE==4
make_instr_helper(si2rm)
#endif
#include "cpu/exec/template-end.h"

