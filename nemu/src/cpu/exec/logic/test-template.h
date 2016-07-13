#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	DATA_TYPE my_dest=op_dest->val;
	DATA_TYPE my_src=op_src->val;
	DATA_TYPE my_test1=my_dest&my_src;
	DATA_TYPE_S my_test=my_test1;
	cpu.CF=0;
	cpu.OF=0;
	my_test1^=(my_test1>>4);
	my_test1^=(my_test1>>2);
	my_test1^=(my_test1>>1);
	my_test1=my_test1&1;
	cpu.PF=!my_test1;
	cpu.ZF=!my_test;
	cpu.SF=(my_test<0);
	print_asm_template2();
}
make_instr_helper(i2a)
make_instr_helper(r2rm)
make_instr_helper(i2rm)
#include "cpu/exec/template-end.h"
