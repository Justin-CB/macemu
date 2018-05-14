#include <stdint.h>
#include "cpu/ppc/OLDOPS.H"
#define MAKE_RD(op) ((op >> 21) & 0x1F)
#define MAKE_RA(op) ((op >> 16) & 0x1F)
void bcctr(regpointer regs, uint32 op)
{
	uint32 rd = MAKE_RD(op);
	uint32 ra = MAKE_RA(op);
	if (op & 1) {
		*(regs.lr) = *(regs.pc);
	}
	if (!(rd & 4)) {
		*(regs.ctr)--;
		if (rd & 2) {
			if (*(regs.ctr)) {
				return;
			}
		} 
		else {
			if (!(*(regs.ctr))) {
				return;
			}
		}
	}
	if (!(rd & 0x10)) {
		if (rd & 8) {
			if (!((*(regs.cr)) & (0x80000000 >> ra))) {
				return;
			}
		} 
		else {
			if ((*(regs.cr)) & (0x80000000 >> ra)) {
				return;
			}
		}
	}
	*(regs.pc) = ((*(regs.ctr)) & 0xfffffffc);
}