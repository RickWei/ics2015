#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	DATA_TYPE my_src;
	if(ops_decoded.opcode==0x1bf)
		my_src=(((DATA_TYPE_S)op_src->val)<<16)>>16;
	else{
		int temp=(DATA_BYTE<<3)-8;
		my_src=(((DATA_TYPE_S)op_src->val)<<temp)>>temp;
	}
	OPERAND_W(op_dest,my_src);
	print_asm_template2();
}
make_instr_helper(rmb2r)

make_instr_helper(rml2r)


#include "cpu/exec/template-end.h"

