.syntax unified
.cpu cortex-m3
.thumb


.global _start
.global Reset_Handler
.global main


.section .isr_vector
.type _start, %object

_start:

    .word 0x20005000        /* Initial MSP 20KB RAM */
    .word Reset_Handler     /* Reset Handler */


/* Exception vectors */

    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0


.section .text


Reset_Handler:

    bl main


hang:
    b hang