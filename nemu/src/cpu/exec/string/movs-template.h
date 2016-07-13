#include "cpu/exec/template-start.h"

make_helper(concat(movs_,SUFFIX)){
	int32_t incdec;
	swaddr_write(cpu.edi,DATA_BYTE,swaddr_read(cpu.esi,DATA_BYTE,S_DS),S_DS);
	if(cpu.DF==0)
		incdec=DATA_BYTE;
	else
		incdec=-DATA_BYTE;
	cpu.edi=cpu.edi+incdec;
	cpu.esi=cpu.esi+incdec;
	print_asm_template2();
	return 1;
}


#include "cpu/exec/template-end.h"

