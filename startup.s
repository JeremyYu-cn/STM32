.syntax unified
.cpu cortex-m3
.thumb


.global _start
.global Reset_Handler
.global Default_Handler


.extern main
.extern SystemInit


/* FreeRTOS handlers */
.extern vPortSVCHandler
.extern xPortPendSVHandler
.extern xPortSysTickHandler


/* linker symbols */
.extern _sidata
.extern _sdata
.extern _edata
.extern _sbss
.extern _ebss
.extern _estack



/* ============================= */
/* Vector Table                   */
/* ============================= */

.section .isr_vector,"a",%progbits
.align 2


_start:

    /* Initial Stack Pointer */
    .word _estack


    /* Reset Handler */
    .word Reset_Handler


    /* Cortex-M3 Exceptions */

    .word Default_Handler       /* NMI */
    .word Default_Handler       /* HardFault */
    .word Default_Handler       /* MemManage */
    .word Default_Handler       /* BusFault */
    .word Default_Handler       /* UsageFault */


    .word 0                    /* Reserved */
    .word 0                    /* Reserved */
    .word 0                    /* Reserved */
    .word 0                    /* Reserved */


    .word vPortSVCHandler       /* SVC */


    .word Default_Handler       /* DebugMon */


    .word 0                    /* Reserved */


    .word xPortPendSVHandler    /* PendSV */


    .word xPortSysTickHandler   /* SysTick */



/* ============================= */
/* Code Section                   */
/* ============================= */

.section .text
.align 2



/* ============================= */
/* Reset Handler                  */
/* ============================= */

.thumb_func
Reset_Handler:


    /* Set MSP */
    ldr sp, =_estack



    /*
     * Copy .data
     *
     * FLASH:
     *     _sidata
     *
     * RAM:
     *     _sdata -> _edata
     */

    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata


copy_data_loop:


    cmp r1, r2
    bcc copy_data


    b clear_bss



copy_data:


    ldr r3, [r0]

    str r3, [r1]


    adds r0, r0, #4
    adds r1, r1, #4


    b copy_data_loop




/* ============================= */
/* Clear BSS                      */
/* ============================= */


clear_bss:


    ldr r0, =_sbss
    ldr r1, =_ebss


    movs r2, #0



clear_bss_loop:


    cmp r0, r1

    bcc clear_bss_write


    b system_init



clear_bss_write:


    str r2, [r0]


    adds r0, r0, #4


    b clear_bss_loop





/* ============================= */
/* System Init                    */
/* ============================= */


system_init:


    bl SystemInit


    bl main



/* main 不应该返回 */

hang:


    b hang




/* ============================= */
/* Default Exception Handler      */
/* ============================= */


.thumb_func
Default_Handler:


    b Default_Handler
    