#include "headers/project.h"

//static uint32_t check_hello = 0;

void main()
{
	//Setup videocore
	init_V3D();
	
	// set up serial console
	uart_init();
	lfb_init();

	//Create mmu table on Core 0
	init_page_table();

	dynamic_memory_alloc_init();
	console_init();	
	clocks_init();

	//start_other_3_cores();
	mmu_init(); //Now turn on MMU on Core 0
	*core0_ready = true;

	render_quad(lfb_width, lfb_height, ARM_addr_to_GPU_addr((void*)(uintptr_t)lfb));

	// echo everything back
	while(1) 
	{
		uart_send(uart_getc());
	}
}
