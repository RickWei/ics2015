#include "cpu/exec/template-start.h"

make_helper(concat(leave_,SUFFIX)){
	if(DATA_BYTE==2){
		cpu.esp=cpu.esp&0xffff0000;
		cpu.esp=cpu.esp|(cpu.ebp&0xffff);
	}
	else if(DATA_BYTE==4){
		cpu.esp=cpu.ebp;
	}
	DATA_TYPE result=swaddr_read(cpu.esp,DATA_BYTE,S_SS);
	cpu.esp=cpu.esp+DATA_BYTE;
	cpu.ebp=result;
	print_asm("leave");
	return 1;
}


#include "cpu/exec/template-end.h"

