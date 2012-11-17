%ifndef __IRQ_INC__
%define __IRQ_INC__

extern irq_handler

irq_common_stub:
	;Push all registers
    	pusha
    	push ds
	push es
	push fs
	push gs

	; Load the kernel data segment descriptor
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	; Call the function
    	mov eax, esp
    	push eax
    	mov eax, irq_handler
    	call eax
	pop eax

	; Pop all registers reverse order and far-return
	pop gs
	pop fs
	pop gs
	pop ds
	popa

    	add esp, 8
    	iret	


global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
	push byte 0
        push byte 32            ; 32 + 0
        jmp irq_common_stub
irq1:
	push byte 1
        push byte 33            ; 32 + 1
        jmp irq_common_stub
irq2:
        push byte 34            ; 32 + 2
        jmp irq_common_stub
irq3:
        push byte 35            ; 32 + 3
        jmp irq_common_stub
irq4:
        push byte 36            ; 32 + 4
        jmp irq_common_stub
irq5:
        push byte 37            ; 32 + 5
        jmp irq_common_stub
irq6:
        push byte 38            ; 32 + 6
        jmp irq_common_stub
irq7:
        push byte 39            ; 32 + 7
        jmp irq_common_stub
irq8:
        push byte 40            ; 32 + 8
        jmp irq_common_stub
irq9:
        push byte 41            ; 32 + 9
        jmp irq_common_stub
irq10:
        push byte 42            ; 32 + 10
        jmp irq_common_stub
irq11:
        push byte 43            ; 32 + 11
        jmp irq_common_stub
irq12:
        push byte 44            ; 32 + 12
        jmp irq_common_stub
irq13:
        push byte 45            ; 32 + 13
        jmp irq_common_stub
irq14:
        push byte 46            ; 32 + 14
        jmp irq_common_stub
irq15:
        push byte 47            ; 32 + 15
        jmp irq_common_stub

%endif
