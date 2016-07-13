#include "cpu/exec/template-start.h"

#define instr jmp

static void do_execute() {
	if(ops_decoded.opcode==0xeb||ops_decoded.opcode==0xe9){
		cpu.eip+=(uint32_t)(DATA_TYPE_S)op_src->val;
		if(DATA_BYTE==2){
			cpu.eip=cpu.eip&0xffff;
		}
	}
	else if(ops_decoded.opcode==0xff){
		if(DATA_BYTE==2)
			cpu.eip=op_src->val&0xffff;
		else if(DATA_BYTE==4)
			cpu.eip=op_src->val;
	}
	print_asm_template1();
}

make_helper(concat(jmp_inter_, SUFFIX)){
	cpu.seg_r[S_CS].val=instr_fetch(cpu.eip+1+DATA_BYTE,2);
	int offset=cpu.seg_r[S_CS].INDEX*8;
	cpu.seg_c[S_CS].val=lnaddr_read(cpu.GDTR.base+offset,4)+(((long long)(lnaddr_read(cpu.GDTR.base+offset+4,4)))<<32);
	swaddr_t dest;
	dest=instr_fetch(cpu.eip+1,DATA_BYTE);
#if DATA_BYTE==2
	cpu.eip=(dest&0xffff)-5;
#else
	cpu.eip=dest-7;
#endif
	print_asm("ljmp $0x%x,$0x%x", cpu.seg_r[S_CS].val,dest);	
	return 1+2+DATA_BYTE;
}
make_instr_helper(i)
make_instr_helper(rm)
make_instr_helper(jrm)
#include "cpu/exec/template-end.h"
