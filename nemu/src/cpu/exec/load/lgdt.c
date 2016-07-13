#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"

make_helper(lgdt){
	int instr_len=decode_rm_l(eip+1);
	cpu.GDTR.limit=lnaddr_read(op_src->addr,2);
	cpu.GDTR.base=lnaddr_read(op_src->addr+2,4);
	print_asm("lgdt %s",op_src->str);
	return 1+instr_len;
}

make_helper(lidt){
	int instr_len=decode_rm_l(eip+1);
	cpu.IDTR.limit=lnaddr_read(op_src->addr,2);
	cpu.IDTR.base=lnaddr_read(op_src->addr+2,4);
	print_asm("lidt %s",op_src->str);
	return 1+instr_len;
}


