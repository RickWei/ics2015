#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
	DATA_TYPE my_src=op_src->val;
	OPERAND_W(op_dest,my_src);
	print_asm_template2();
}
make_instr_helper(rmb2r)

make_instr_helper(rml2r)


#include "cpu/exec/template-end.h"

