CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g \
         -Wall -ffreestanding -nostdlib \
         -Iinclude

LDFLAGS = -T linker.ld -nostdlib

SRCS = \
core/lib/sys.c \
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
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program firmware.elf verify reset exit"

clean:
	rm -f *.o *.elf *.bin