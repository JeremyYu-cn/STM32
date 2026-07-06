.syntax unified
.cpu cortex-m3
.thumb

.global _start
.global main

_start:
    bl main

loop:
    b loop