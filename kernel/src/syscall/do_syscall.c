#include "irq.h"

#include <sys/syscall.h>

void add_irq_handle(int, void (*)(void));
void mm_brk(uint32_t);

static void sys_brk(TrapFrame *tf) {
#ifdef IA32_PAGE
	mm_brk(tf->ebx);
#endif
	tf->eax = 0;
}
extern void serial_printc(char);
extern int fs_write(int,uint32_t,int);
static void sys_write(TrapFrame *tf){
	if(tf->ebx==1||tf->ebx==2)
	{
		uint32_t buf=tf->ecx;
		uint32_t len=tf->edx;
		asm volatile (".byte 0xd6" : : "a"(2), "c"(buf), "d"(len));
		tf->eax=tf->edx;
		return;
//serial_printc('a');
	}
	else 
	{
		tf->eax=fs_write(tf->ebx,tf->ecx,tf->edx);
		return;	
	}
}
extern int fs_open(uint32_t, int );
static void sys_open(TrapFrame *tf){
	tf->eax=fs_open(tf->ebx,tf->ecx);
	return;
}
extern int fs_read(int, uint32_t, int);
static void sys_read(TrapFrame *tf){
	tf->eax=fs_read(tf->ebx,tf->ecx,tf->edx);
	return;
}
extern int fs_close(int);
static void sys_close(TrapFrame *tf){
	tf->eax=fs_close(tf->ebx);
	return;
}
extern int fs_lseek(int, int, int );
static void sys_lseek(TrapFrame *tf){
	tf->eax=fs_lseek(tf->ebx,tf->ecx,tf->edx);
}
void do_syscall(TrapFrame *tf) {

	switch(tf->eax) {
		/* The ``add_irq_handle'' system call is artificial. We use it to 
		 * let user program register its interrupt handlers. But this is 
		 * very dangerous in a real operating system. Therefore such a 
		 * system call never exists in GNU/Linux.
		 */
		case 0: 
			cli();
			add_irq_handle(tf->ebx, (void*)tf->ecx);
			sti();
			break;
		case SYS_brk: sys_brk(tf); break;
		/* TODO: Add more system calls. */
		case SYS_write:sys_write(tf);break;
		case 3:sys_read(tf);break;
		case 5:sys_open(tf);break;
		case 6:sys_close(tf);break;
		case 19:sys_lseek(tf);break;
		default: panic("Unhandled system call: id = %d", tf->eax);
	}
}

