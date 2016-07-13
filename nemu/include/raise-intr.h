#ifndef __RAISE__
#define __RAISE__
#include <setjmp.h>
extern void swaddr_write(swaddr_t,size_t,uint32_t,uint8_t);
extern jmp_buf jbuf;
extern uint32_t seg_base(uint8_t);
void raise_intr(uint8_t NO) {
	/* TODO: Trigger an interrupt/exception with ``NO''.
	 * *	 * That is, use ``NO'' to index the IDT.
	 * *		 */
	uint32_t *temp=(uint32_t *)(&cpu.eip)+1;
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,*temp,S_SS); 
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,(uint32_t)cpu.seg_r[S_CS].val,S_SS); 
	cpu.esp-=4;
	swaddr_write(cpu.esp,4,cpu.eip,S_SS);
	uint32_t IDT=cpu.IDTR.base;
	uint64_t IG=IDT+8*NO;
	uint32_t low=lnaddr_read(IG,4);
	uint32_t high=lnaddr_read(IG+4,4);
	uint16_t PC=(low>>16)&0xFFFF;
	uint32_t IP=(low&0xFFFF)|(((high>>16)&0xFFFF)<<16);
	cpu.eip=seg_base(PC)+IP;
	/* Jump back to cpu_exec() */
	longjmp(jbuf, 1);
}
#endif
