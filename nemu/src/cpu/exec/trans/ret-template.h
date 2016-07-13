#include "cpu/exec/template-start.h"

extern uint32_t seg_base(uint8_t);

make_helper(concat(ret_,SUFFIX)){
		if(DATA_BYTE==2){
			cpu.eip=swaddr_read(cpu.esp,2,S_SS)-1;
			cpu.esp=cpu.esp+2;
			cpu.eip=cpu.eip&0xffff;
		}
		else{
			cpu.eip=swaddr_read(cpu.esp,4,S_SS)-1;
			cpu.esp=cpu.esp+4;		
		}	
		if(ops_decoded.opcode==0xC2||ops_decoded.opcode==0xCA){
			DATA_TYPE_S temp=op_src->val;
			cpu.esp=cpu.esp+temp;
			
		}	
		print_asm("ret");
		return 1;
}
#if DATA_BYTE==4
int iret(){
	uint32_t temp=swaddr_read(cpu.esp,4,S_SS);
	cpu.esp=cpu.esp+4;	
	cpu.eip=seg_base(swaddr_read(cpu.esp,4,S_SS))+temp;
	cpu.esp=cpu.esp+4;
	*(&cpu.eip+1)=swaddr_read(cpu.esp,4,S_SS);
	cpu.esp=cpu.esp+4;
	print_asm("iret");
	return 0;
}

#endif

#include "cpu/exec/template-end.h"

