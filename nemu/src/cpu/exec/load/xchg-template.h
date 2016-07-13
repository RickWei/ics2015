#include "cpu/exec/template-start.h"

#define instr xchg

static void do_execute(){
	DATA_TYPE my_src=op_src->val;
	DATA_TYPE my_dest=op_dest->val;
	OPERAND_W(op_dest,my_src);
	OPERAND_W(op_src,my_dest);
	print_asm_template2();

}

make_instr_helper(rm2rm)

#include "cpu/exec/template-end.h"
