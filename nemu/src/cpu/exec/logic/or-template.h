#include "cpu/exec/template-start.h"

#define instr or

static void do_execute () {
	DATA_TYPE result = op_dest->val | op_src->val;
	OPERAND_W(op_dest, result);

	/* TODO: Update EFLAGS. */
	//panic("please implement me");
	DATA_TYPE my_test=result;
	my_test^=(my_test>>4);
	my_test^=(my_test>>2);
	my_test^=(my_test>>1);
	my_test=my_test&1;
	cpu.PF=!my_test;
	DATA_TYPE_S my_test1=result;
	cpu.OF=0;cpu.CF=0;
	cpu.ZF=!result;
	cpu.SF=(my_test1<0);

	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(i2rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"