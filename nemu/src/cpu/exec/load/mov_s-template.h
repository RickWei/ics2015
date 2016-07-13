#include "cpu/exec/template-start.h"


make_helper(mov_rm2seg_w){
	uint32_t rm =instr_fetch(eip+1,1);
	int seg_n=(rm&0x38)>>3;
	int ins_len=1;
	decode_rm_w(eip+1);

	cpu.seg_r[seg_n].val=op_src->val;
	cpu.seg_c[seg_n].val=((uint64_t)lnaddr_read((cpu.GDTR.base+cpu.seg_r[seg_n].INDEX*8),4))+(((uint64_t)lnaddr_read((cpu.GDTR.base+cpu.seg_r[seg_n].INDEX*8+4),4))<<32);

	switch(seg_n){
		case 0:
			print_asm("mov %s,ES", op_src->str); break;
		case 1:
			print_asm("mov %s,CS", op_src->str); break; 
		case 2:
			print_asm("mov %s,SS", op_src->str); break; 
		case 3:
			print_asm("mov %s,DS", op_src->str); break; 
	}
	return 1+ins_len;
}

make_helper(mov_seg2rm_w){
	uint32_t rm =instr_fetch(eip+1,1);
	int seg_n=rm&0x3;
	int ins_len=1;
	decode_rm_w(eip+1);
	uint16_t seg=cpu.seg_r[seg_n].val;
	OPERAND_W(op_src,seg);
	switch(seg_n){
		case 0:
			print_asm("mov ES,%s", op_src->str); break;
		case 1:
			print_asm("mov CS,%s", op_src->str); break; 
		case 2:
			print_asm("mov SS,%s", op_src->str); break; 
		case 3:
			print_asm("mov DS,%s", op_src->str); break; 
	}
	return 1+ins_len;
}

#include "cpu/exec/template-end.h"
