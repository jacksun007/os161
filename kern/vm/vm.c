#include <types.h>
#include <kern/errno.h>
#include <lib.h>
#include <thread.h>
#include <curthread.h>
#include <addrspace.h>
#include <vm.h>
#include <machine/spl.h>
#include <machine/tlb.h>

/*
 * Note! If OPT_DUMBVM is set, as is the case until you start the VM
 * assignment, this file is not compiled or linked or in any way
 * used. The cheesy hack versions in dumbvm.c are used instead.
 */

void
vm_bootstrap(void)
{
	/* do nothing */
}

static
paddr_t
getppages(unsigned long npages)
{
	/*
	 * Write this.
	 */

	(void)npages;
	(void)getppages;
	return 0;
}

vaddr_t 
alloc_kpages(int npages)
{
	/*
	 * Write this.
	 */
	 
	(void)npages;
	return 0;
}

void 
free_kpages(vaddr_t addr)
{
	/*
	 * Write this.
	 */

	(void)addr;
}

int
vm_fault(int faulttype, vaddr_t faultaddress)
{
	/*
	 * Definitely write this.
	 */

	(void)faulttype;
	(void)faultaddress;
	return 0;
}
