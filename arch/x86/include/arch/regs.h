#ifndef ARCH_X86_ASM_REGS_H
#define ARCH_X86_ASM_REGS_H

#include <zion/types.h>

/* Structure representing the stack frame during an interrupt */
struct regs {
	/* pushed the segs last */
	unsigned int gs, fs, es, ds;
	/* pushed by 'pusha' */
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
	/* these get pushed by the interrupt or we push it */
	unsigned int int_no, err_code;
	/* pushed by the processor automatically */ 
	unsigned int eip, cs, eflags, useresp, ss;
};

#endif
