.section .eight
.global _eightstart
_eightstart:
	//
	// Set up the reset and other vectors (at 0x0000).
	//
	ldr pc, reset_handler
	ldr pc, undefined_handler
	ldr pc, swi_handler
	ldr pc, prefetch_handler
	ldr pc, data_handler
	ldr pc, unused_handler
	ldr pc, irq_handler
	ldr pc, fiq_handler

reset_handler:      .word reset
undefined_handler:  .word undefined
swi_handler:        .word swi
prefetch_handler:   .word prefetch
data_handler:       .word data
unused_handler:     .word hang
irq_handler:        .word irq
fiq_handler:        .word fiq

reset:
	//
	// Copy the eight ldr instructions from 0x8000 (_eightstart) to 0x0000.
	//
    mov r0,#0x8000
    mov r1,#0x0000
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}

    ;@ (PSR_IRQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD2
    msr cpsr_c,r0
    mov sp,#0x8000

    ;@ (PSR_FIQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD1
    msr cpsr_c,r0
    mov sp,#0x4000

    ;@ (PSR_SVC_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD3
    msr cpsr_c,r0
    mov sp,#0x8000000

    ;@ SVC MODE, IRQ ENABLED, FIQ DIS
    ;@mov r0,#0x53
    ;@msr cpsr_c, r0

	//
	// Enable VFP
	//
	mrc p15, #0, r1, c1, c0, #2 // r1 = Access Control Register
	orr r1, r1, #(0xf << 20)    // enable full access for p10,11
	mcr p15, #0, r1, c1, c0, #2 // ccess Control Register = r1
	mov r1, #0
	mcr p15, #0, r1, c7, c5, #4 // flush prefetch buffer because of FMXR below
	                            // and CP 10 & 11 were only just enabled
	mov r0,#0x40000000          // Enable VFP itself
	fmxr FPEXC, r0              // FPEXC = r0

    bl _start

    b hang



.globl enable_irq
enable_irq:
    mrs r0,cpsr
    bic r0,r0,#0x80
    msr cpsr_c,r0
    bx lr

undefined:
    bl c_undefined_handler

swi:
    bl c_swi_handler

prefetch:
    bl c_prefetch_handler

data:
    bl c_data_handler

hang:
    b hang

irq:
    push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    bl c_irq_handler
    pop  {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
    subs pc,lr,#4

fiq: b hang


