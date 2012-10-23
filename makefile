KERNEL_CFLAGS = -Wall \
		-Wextra \
		-nostdlib \
		-nostartfiles \
		-nodefaultlibs \
	      	-fstrength-reduce \
	      	-fomit-frame-pointer \
	      	-nostdinc \
		-finline-functions \
	      	-fno-builtin \
		-std=c99 \
		-m32

KERNEL_LDFLAGS = -mi386linux

KERNEL_DEPS = asm/Kernel.asm \
	      asm/A20.inc \
	      asm/KernelDisplay.inc \
	      asm/FAT12.inc \
	      asm/Gdt.inc \
	      asm/PrintScreen.inc

KERNEL_OBJS = kernel.o mode7.o gdt.o hal.o\
              idt.o mem.o i86.o main.o 

ASM_BASE = asm
C_INCLUDES = includes

default: KERNEL.SYS

boot.bin: asm/BootLoader-Stage1wFAT.asm
	nasm -i$(ASM_BASE)/ $(ASM_BASE)/BootLoader-Stage1wFAT.asm -f bin -o boot.bin
	dd if=/dev/zero of=./boot.img bs=512 count=2880
	dd if=./boot.bin of=./boot.img bs=512 conv=notrunc

STAGE2.SYS: ./asm/Stage2.asm
	nasm -i$(ASM_BASE)/ $(ASM_BASE)/Stage2.asm -f bin -o STAGE2.SYS

KERNEL.SYS: $(KERNEL_DEPS) $(KERNEL_OBJS)
	ld -Tlink.ld -o KERNEL.SYS $(KERNEL_OBJS) $(KERNEL_LDFLAGS)

kernel.o : ./$(ASM_BASE)/Kernel.asm
	nasm -i./$(ASM_BASE)/ -f aout -o kernel.o ./$(ASM_BASE)/Kernel.asm

main.o : main.c
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES)/ -c -o main.o main.c

mode7.o : mode7.c
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES) -c -o mode7.o mode7.c

hal.o : hal.c
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES) -c -o hal.o hal.c

mem.o : mem.c
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES) -c -o mem.o mem.c

gdt.o : gdt.c
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES) -c -o gdt.o gdt.c

i86.o : i86.c
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES) -c -o i86.o i86.c

idt.o : idt.c
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES) -c -o idt.o idt.c

all: clean boot.bin STAGE2.SYS KERNEL.SYS

.phony: clean
clean:
	rm -f *.SYS
	rm -f *.bin
	rm -f *.o