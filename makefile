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

ASM_BASE = asm
C_INCLUDES = includes

default: KERNEL.SYS

boot.bin: asm/BootLoader-Stage1wFAT.asm
	nasm -i$(ASM_BASE)/ $(ASM_BASE)/BootLoader-Stage1wFAT.asm -f bin -o boot.bin
	dd if=/dev/zero of=./boot.img bs=512 count=2880
	dd if=./boot.bin of=./boot.img bs=512 conv=notrunc

STAGE2.SYS: ./asm/Stage2.asm
	nasm -i$(ASM_BASE)/ $(ASM_BASE)/Stage2.asm -f bin -o STAGE2.SYS

KERNEL.SYS: $(KERNEL_DEPS)
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES)/ -c -o main.o main.c
	gcc $(KERNEL_CFLAGS) -I./$(C_INCLUDES)/ -c -o mode7.o mode7.c
	nasm -i./$(ASM_BASE)/ -f aout -o kernel.o ./$(ASM_BASE)/Kernel.asm
	ld -Tlink.ld -o KERNEL.SYS kernel.o mode7.o main.o $(KERNEL_LDFLAGS)

all: boot.bin STAGE2.SYS KERNEL.SYS

.phony: clean
clean:
	rm KERNEL.SYS STAGE2.SYS boot.bin main.o kernel.o mode7.o