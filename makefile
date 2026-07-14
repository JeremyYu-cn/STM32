CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g \
         -Wall -ffreestanding -nostdlib \
         -Iinclude

LDFLAGS = -T linker.ld -Wl,-Map=firmware.map -nostdlib

SRCS = \
core/lib/sys.c \
core/lib/uart.c \
core/system.c \
core/main.c \
include/freeRTOS/include/timers.c \
include/freeRTOS/include/tasks.c \
include/freeRTOS/include/list.c \
include/freeRTOS/include/queue.c \
include/freeRTOS/include/port.c \
include/freeRTOS/include/heap_4.c \
startup.s

OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.s=.o)

all: firmware.bin

firmware.elf: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $@

firmware.bin: firmware.elf
	$(OBJCOPY) -O binary $< $@

flash:
	openocd \
	-f interface/stlink.cfg \
	-f target/stm32f1x.cfg \
	-c "program firmware.bin 0x08000000 verify reset exit"

clean:
	rm -f *.o *.elf *.bin *.map