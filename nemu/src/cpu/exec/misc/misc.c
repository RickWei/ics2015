#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"
#include "raise-intr.h"

#define MEM_W(addr,data,sreg) swaddr_write(addr,4,data,sreg)

void raise_intr(uint8_t NO);

make_helper(nop) {
	print_asm("nop");
	return 1;
}

make_helper(int3) {
	void do_int3();
	do_int3();
	print_asm("int3");

	return 1;
}

make_helper(lea) {
	ModR_M m;
	m.val = instr_fetch(eip + 1, 1);
	int len = load_addr(eip + 1, &m, op_src);
	reg_l(m.reg) = op_src->addr;

	print_asm("leal %s,%%%s", op_src->str, regsl[m.reg]);
	return 1 + len;
}

make_helper(cltd) {
	if((int)cpu.eax<0)
		cpu.edx=0xffffffff;
	else
		cpu.edx=0;
	print_asm("cltd");
	return 1;
}

make_helper(cwtl){
	int temp=cpu.gpr[0]._16;
	cpu.eax=cpu.eax&0xFFFF;
	if(temp<0)
		cpu.eax=0xffff0000|cpu.eax;
	print_asm("cwtl");
	return 1;

}

make_helper(cld){
	cpu.DF=0;
	print_asm("cld");
	return 1;
}

make_helper(std) {
	cpu.DF=1;
	print_asm("std");
	return 1;
}

make_helper(int1){
	uint8_t NO=instr_fetch(cpu.eip+1,1);
	print_asm("int %d",NO);
	cpu.eip+=2;
	raise_intr(NO);
	return 2;
}

int cli(){
	cpu.IF=0;
	print_asm("cli");
	return 1;
}

int sti(){
	cpu.IF=1;
	print_asm("sti");
	return 1;
}

int hlt(){
	if(cpu.INTR) 
		return 1;	
	print_asm("hlt");	
	return 0;
}	
