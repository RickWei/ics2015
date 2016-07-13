#include "cpu/exec/template-start.h"

#define instr set

static void do_execute() {
	DATA_TYPE my_zero=0;
	DATA_TYPE my_one=1;
//	cpu.eax=ops_decoded.opcode;
	if(ops_decoded.opcode==0x195){
		if(cpu.ZF==0)
			OPERAND_W(op_src,my_one);
		else
			OPERAND_W(op_src,my_zero);
	}
	else if(ops_decoded.opcode==0x194){
		if(cpu.ZF==1)
			OPERAND_W(op_src,my_one);
		else
			OPERAND_W(op_src,my_zero);
	}
	else if(ops_decoded.opcode==0x19e){
		if(cpu.ZF==1 || cpu.SF!=cpu.OF)
			OPERAND_W(op_src,my_one);
		else
			OPERAND_W(op_src,my_zero);
	}
	else if(ops_decoded.opcode==0x19d){
		if(cpu.SF==cpu.OF)
			OPERAND_W(op_src,my_one);
		else
			OPERAND_W(op_src,0);
	}
	else if(ops_decoded.opcode==0x19c){
		if(cpu.SF!=cpu.OF)
			OPERAND_W(op_src,my_one);
		else
			OPERAND_W(op_src,0);
	}
//	else{
//		assert(0);
//	}
	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"



