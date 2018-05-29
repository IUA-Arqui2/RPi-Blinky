
;@-------------------------------------------------------------------------
;@-------------------------------------------------------------------------

.globl _start
_start:
    ldr pc,reset_handler
    ldr pc,undefined_handler
    ldr pc,swi_handler
    ldr pc,prefetch_handler
    ldr pc,data_handler
    ldr pc,hyp_handler
    ldr pc,irq_handler
    ldr pc,fiq_handler
reset_handler:      .word reset
undefined_handler:  .word undefined_instruction_vector
swi_handler:        .word smc
prefetch_handler:   .word prefetch_abort_vector
data_handler:       .word data_abort_vector
hyp_handler:        .word hang
irq_handler:        .word interrupt_vector
fiq_handler:        .word fast_interrupt_vector

reset:

    ;@ b skip
    mrs r0,cpsr
    bic r0,r0,#0x1F
    orr r0,r0,#0x13
    msr spsr_cxsf,r0
    add r0,pc,#4
    msr ELR_hyp,r0
    eret
skip:

    mrc p15, 0, r1, c12, c0, 0 ;@ get vbar
    mov r0,#0x8000
    ;@ mov r1,#0x0000
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}

    mov r12,#0
    mcr p15, 0, r12, c7, c10, 1
    dsb
    mov r12, #0
    mcr p15, 0, r12, c7, c5, 0
    mov r12, #0
    mcr p15, 0, r12, c7, c5, 6
    dsb
    isb
    smc #0

    mrc p15,0,r2,c1,c0,0
    bic r2,#0x1000
    bic r2,#0x0004
    mcr p15,0,r2,c1,c0,0


    mov r0,#0x8000
    mcr p15, 0, r0, c12, c0, 0

    ;@ mov r0,#0x8000
    ;@ mov r1,#0x0000
    ;@ ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    ;@ stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
    ;@ ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    ;@ stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
    
    ;@ Enable Advanced SIMD & Vector Floating Point Calculations (NEON MPE)
   ;@ mrc p15,0,r0,c1,c0,2 ;@ R0 = Access Control Register
   ;@ orr r0,$300000 + $C00000 ;@ Enable Single & Double Precision
   ;@ mcr p15,0,r0,c1,c0,2 ;@ Access Control Register = R0
   ;@ mov r0,$40000000 ;@ R0 = Enable VFP
   ;@ vmsr fpexc,r0 ;@ FPEXC = R0
    

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

    bl notmain
hang: b hang

smc:
    mrc p15, 0, r1, c1, c1, 0
    bic r1, r1, #1
    mcr p15, 0, r1, c1, c1, 0
    movs    pc, lr


.globl __enable_interrupts
__enable_interrupts:
    mrs r0,cpsr
    bic r0,r0,#0x80
    msr cpsr_c,r0
    bx lr

#irq:
#    push {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
#    bl c_irq_handler
#    pop  {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12,lr}
#    subs pc,lr,#4
