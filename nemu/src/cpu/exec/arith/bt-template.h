#include "cpu/exec/template-start.h"

#define instr bt

static void do_execute() {
	DATA_TYPE my_src=op_src->val;
	DATA_TYPE my_dest=op_dest->val;
	cpu.CF=((my_dest>>my_src)&0x1);
	print_asm_template2();
}

make_instr_helper(r2rm)

#include "cpu/exec/template-end.h"
