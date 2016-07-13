#include "common.h"
#include "memory.h"
#include <string.h>

#define VMEM_ADDR (0xa0000)
#define SCR_SIZE (320 * 200)

#define V_DIR 0
#define V_page 0xa0

/* Use the function to get the start address of user page directory. */
inline PDE* get_updir();

void create_video_mapping() {
	/* TODO: create an identical mapping from virtual memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) to physical memory area 
	 * [0xa0000, 0xa0000 + SCR_SIZE) for user program. You may define
	 * some page tables to create this mapping.
	 */
	//panic("please implement me");
	//PDE *my_pde;
//	PTE *my_pte;
//	my_pde=get_updir();
//	my_pde->present=1;	
//	my_pte=(PTE *)((my_pde->page_frame<<12)+V_page);
//	my_pte->val=make_pte(0xa0000);
//	my_pte->present=1;
}	

void video_mapping_write_test() {
	int i;
	int *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		buf[i] = i;
	}
}

void video_mapping_read_test() {
	int i;
	int *buf = (void *)VMEM_ADDR;
	for(i = 0; i < SCR_SIZE / 4; i ++) {
		assert(buf[i] == i);
	}
}

void video_mapping_clear() {
	memset((void *)VMEM_ADDR, 0, SCR_SIZE);
}

