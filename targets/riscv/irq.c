
#include "irq.h"
#include "uart.h"

void no_interrupt_handler (void) {}

void handle_m_time_interrupt() 
{
	clear_csr(mie, MIP_MTIP);

	/* reset and clear */
	volatile uint64_t * mtimecmp = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
	*mtimecmp = 0xffffffff;

	set_csr(mie, MIP_MTIP);
}

void handle_m_ext_interrupt() 
{
	plic_source int_num = PLIC_claim_interrupt (&g_plic);
	if ((int_num >= 1) && (int_num < PLIC_NUM_INTERRUPTS)) {
		if (g_ext_interrupt_handlers [int_num]) {
			g_ext_interrupt_handlers [int_num] ();
		}
	} else {
		exit(1 + (uintptr_t) int_num);
	}
	PLIC_complete_interrupt(&g_plic, int_num);
}

void init_plic()
{
	PLIC_init(&g_plic,
	    PLIC_CTRL_ADDR,
	    PLIC_NUM_INTERRUPTS,
	    PLIC_NUM_PRIORITIES);
}

void lock_irqs() 
{
	/* clear machine irq */
	clear_csr(mie, MIP_MEIP);
	/* clear time irq */
  	clear_csr(mie, MIP_MTIP);
	/* clear general */
	/*clear_csr(mstatus, MSTATUS_MIE);*/
}

void enable_general()
{
	/* enable general */
	set_csr(mstatus, MSTATUS_MIE);
}

void enable_irqs()
{
	/* enable machine irq */
	set_csr(mie, MIP_MEIP);
	/* enable time irq */
	set_csr(mie, MIP_MTIP);
}
