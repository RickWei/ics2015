#include "cpu/exec/template-start.h"

#define instr movcc

static void do_execute(){
	switch(ops_decoded.opcode&0xff){
		case 0x47:
			if(cpu.CF==0&&cpu.ZF==0)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x43:
			if(cpu.CF==0)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x42:
			if(cpu.CF==1)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x46:
			if(cpu.CF==1||cpu.ZF==1)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x44:		
			if(cpu.ZF==1)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x4F:
			if(cpu.ZF==0&&cpu.SF==cpu.OF)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x4D:
			if(cpu.SF==cpu.OF)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x4C:
			if(cpu.SF!=cpu.OF)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x4E:
			if(cpu.ZF==1||cpu.SF!=cpu.OF)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x45:
			if(cpu.ZF==0)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x41:
			if(cpu.OF==0)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x4B:
			if(cpu.PF==0)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x49:
			if(cpu.SF==0)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x40:
			if(cpu.OF==1)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x4A:
			if(cpu.PF==1)
				OPERAND_W(op_dest, op_src->val);
			break;
		case 0x48:
			if(cpu.SF==1)
				OPERAND_W(op_dest, op_src->val);
			break;
		default:
			panic("wrong");
	}
	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

