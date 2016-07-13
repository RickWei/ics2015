#include "cpu/exec/template-start.h"

make_helper(concat(cmps_,SUFFIX)){
	DATA_TYPE src;
	DATA_TYPE dest;
	int32_t incdec;	
	src=swaddr_read(cpu.esi,DATA_BYTE,S_DS);
	dest=swaddr_read(cpu.edi,DATA_BYTE,S_DS);
	if(cpu.DF==0)
		incdec=DATA_BYTE;
	else
		incdec=-DATA_BYTE;
	cpu.esi=cpu.esi+incdec;
	cpu.edi=cpu.edi+incdec;
	uint64_t my_test=(uint64_t)src-dest;
	DATA_TYPE my_test4=src-dest;
	DATA_TYPE_S my_test2=src-dest;
	cpu.CF=dest>src;
	my_test^=(my_test>>4);
	my_test^=(my_test>>2);
	my_test^=(my_test>>1);
	my_test=my_test&1;
	cpu.PF=!my_test;
	uint8_t my_test3=(src&0xf)+((-dest)&0xf);
	cpu.AF=!!(my_test3>>4);
	cpu.ZF=!my_test2;
	cpu.SF=(my_test2<0);
	cpu.OF=((src^my_test4)&(dest^src))>>((DATA_BYTE<<3)-1);
	print_asm_template2();
	return 1;
}


#include "cpu/exec/template-end.h"

