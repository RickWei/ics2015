#include "cpu/exec/template-start.h"

make_helper(concat(stos_,SUFFIX)){
	if(DATA_BYTE==1){
		swaddr_write(cpu.edi,1,cpu.gpr[0]._8[0],S_DS);
		if(cpu.DF==0)
			cpu.edi++;
		else
			cpu.edi--;
	}
	else if(DATA_BYTE==2){
		swaddr_write(cpu.edi,2,cpu.gpr[0]._16,S_DS);
		if(cpu.DF==0)
			cpu.edi=cpu.edi+2;
		else
			cpu.edi=cpu.edi-2;
	}	
	else{
		swaddr_write(cpu.edi,4,cpu.eax,S_DS);
		if(cpu.DF==0)
			cpu.edi=cpu.edi+4;
		else
			cpu.edi=cpu.edi-4;
	}
	print_asm_template2();
	return 1;
}


#include "cpu/exec/template-end.h"

