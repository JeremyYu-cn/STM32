.syntax unified
.cpu cortex-m3
.thumb


.global _start
.global Reset_Handler
.global Default_Handler

.extern main
.extern SystemInit

.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
.extern _estack


.section .isr_vector,"a",%progbits

_start:

    .word _estack
    .word Reset_Handler

    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler

    .word 0
    .word 0
    .word 0
    .word 0

    .word Default_Handler

    .word 0
    .word 0

    .word Default_Handler
    .word Default_Handler



.section .text


.thumb_func
Reset_Handler:

    /*
     * 初始化 MSP
     */
    ldr sp, =_estack


    /*
     * copy .data
     */
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata


copy_data:

    cmp r1, r2
    bcc copy_loop

    b zero_bss


copy_loop:

    ldr r3, [r0]
    str r3, [r1]

    adds r0, r0, #4
    adds r1, r1, #4

    b copy_data



zero_bss:

    ldr r0, =_sbss
    ldr r1, =_ebss

    movs r2, #0


zero_loop:

    cmp r0, r1
    bcc clear_loop

    b start_main


clear_loop:

    str r2, [r0]

    adds r0, r0, #4

    b zero_loop



start_main:

    bl SystemInit

    bl main


hang:

    b hang



.thumb_func
Default_Handler:

    b Default_Handler

    