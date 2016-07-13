#include "cpu/exec/template-start.h"

#define instr pop

static void do_execute() {
	OPERAND_W(op_src,MEM_R(REG(R_ESP),S_SS));
	cpu.esp=cpu.esp+DATA_BYTE;
	print_asm_template1();
}
#if DATA_BYTE==4
int popa(){
	cpu.edi=MEM_R(REG(R_ESP),S_SS);
	cpu.esp=cpu.esp+DATA_BYTE;
	cpu.esi=MEM_R(REG(R_ESP),S_SS);
	cpu.esp=cpu.esp+DATA_BYTE;
	cpu.ebp=MEM_R(REG(R_ESP),S_SS);
	cpu.esp=cpu.esp+DATA_BYTE;
//throw away	
	cpu.esp=cpu.esp+DATA_BYTE;
	cpu.ebx=MEM_R(REG(R_ESP),S_SS);
	cpu.esp=cpu.esp+DATA_BYTE;
	cpu.edx=MEM_R(REG(R_ESP),S_SS);
	cpu.esp=cpu.esp+DATA_BYTE;
	cpu.ecx=MEM_R(REG(R_ESP),S_SS);
	cpu.esp=cpu.esp+DATA_BYTE;
	cpu.eax=MEM_R(REG(R_ESP),S_SS);
	cpu.esp=cpu.esp+DATA_BYTE;
	print_asm("POPA");
	return 1;	
}
#endif
make_instr_helper(r)
make_instr_helper(rm)
#include "cpu/exec/template-end.h"

