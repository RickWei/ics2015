#include "cpu/exec/template-start.h"

#define instr call

#define CALL_REL(c) (c == 0xE8)
#define CALL_NEAR(c) (c == 0xff)

static void do_execute() {
	uint8_t opcode = instr_fetch(cpu.eip, 1);
	if (CALL_REL(opcode)) {
		DATA_TYPE imm = instr_fetch(cpu.eip + 1, DATA_BYTE);
		reg_l(R_ESP) -= DATA_BYTE;
#if DATA_BYTE == 2
		swaddr_write(reg_l(R_ESP), DATA_BYTE, (cpu.eip + 1 + DATA_BYTE) & 0x0000ffff,S_CS);
		cpu.eip += imm;
		cpu.eip &= 0x0000ffff;
#else
		swaddr_write(reg_l(R_ESP), DATA_BYTE, cpu.eip + 1 + DATA_BYTE,S_CS);
		cpu.eip += imm;
#endif
		print_asm("call %x",cpu.eip + 1 + DATA_BYTE);
	}
	else if (CALL_NEAR(opcode)) {	
		swaddr_t addr = op_src->val;
//	assert(1||(addr==0xc01008e0));
//	assert(0);
//	assert(addr==0xc01008e0);
		Operand temp_reg, temp_rm;
		temp_reg.size = DATA_BYTE;
		temp_rm.size = DATA_BYTE;
		extern int read_ModR_M(swaddr_t, Operand*, Operand*);
		int ins_len = read_ModR_M(cpu.eip + 1, &temp_rm, &temp_reg);
		reg_l(R_ESP) -= DATA_BYTE;
//Log("");
//panic("here");
//Log("%x",addr);

#if DATA_BYTE == 2
		swaddr_write(reg_l(R_ESP), DATA_BYTE, (cpu.eip + 1 + ins_len) & 0x0000ffff,S_CS);
		cpu.eip = (addr & 0x0000ffff) - 1 - ins_len;
#else 
		swaddr_write(reg_l(R_ESP), DATA_BYTE, cpu.eip + 1 + ins_len,S_CS);
		cpu.eip = addr - 1 - ins_len;
#endif
		if (op_src->type == OP_TYPE_REG) {
			print_asm("call %x",cpu.eip + 1 + ins_len);
		} 
		else {

		//	print_asm("call *%s",op_src->str);
		}

	}
	else { //Log("%x", opcode);
		assert(0); 
	}
}

make_instr_helper(i);
make_instr_helper(rm);
#include "cpu/exec/template-end.h"
