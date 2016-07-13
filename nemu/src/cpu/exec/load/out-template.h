#include "cpu/exec/template-start.h"

#define instr out
extern uint32_t pio_read(ioaddr_t,size_t);
extern void pio_write(ioaddr_t,size_t,uint32_t);
#if DATA_BYTE==1
int out_a_b(){
	pio_write(cpu.edx,1,(uint32_t)cpu.gpr[0]._8[0]);
	return 1;
}
int in_a_b(){
	cpu.gpr[0]._8[0]=(uint8_t)pio_read(cpu.edx,1);
	return 1;
}

#endif
#if DATA_BYTE==4
int out_a_w(){
	pio_write(cpu.edx,4,cpu.eax);
	return 1;
}
int in_a_w(){
	cpu.eax=pio_read(cpu.edx,4);
	return 1;
}
#endif
#include "cpu/exec/template-end.h"
