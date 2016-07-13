#include "cpu/exec/template-start.h"

#define instr push

static void do_execute() {
	if(DATA_BYTE==2){
		cpu.esp=cpu.esp-2;
		MEM_W(cpu.esp,op_src->val,S_SS);
	}
	else{
		cpu.esp=cpu.esp-4;
		swaddr_write(cpu.esp,4,op_src->val,S_SS);
	}
	print_asm_template1();
}
make_instr_helper(i)
make_instr_helper(r)
make_instr_helper(rm)
#if DATA_BYTE==1 || DATA_BYTE==4
	make_instr_helper(si)
#endif

#if DATA_BYTE==4
int pusha(){
	uint32_t temp=cpu.esp;
	cpu.esp=cpu.esp-4;
	MEM_W(cpu.esp,cpu.eax,S_SS);
	cpu.esp=cpu.esp-4;
	MEM_W(cpu.esp,cpu.ecx,S_SS);	
	cpu.esp=cpu.esp-4;
	MEM_W(cpu.esp,cpu.edx,S_SS);
	cpu.esp=cpu.esp-4;
	MEM_W(cpu.esp,cpu.ebx,S_SS);
	cpu.esp=cpu.esp-4;
	MEM_W(cpu.esp,temp,S_SS);
	cpu.esp=cpu.esp-4;
	MEM_W(cpu.esp,cpu.ebp,S_SS);
	cpu.esp=cpu.esp-4;
	MEM_W(cpu.esp,cpu.esi,S_SS);
	cpu.esp=cpu.esp-4;
	MEM_W(cpu.esp,cpu.edi,S_SS);
	print_asm("pusha");
	return 1;
}
#endif
#include "cpu/exec/template-end.h"

