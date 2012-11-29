%ifndef __INT_INC__
%define __INT_INC__

extern int_handler

int_common_stub:
	;Push all registers
    	pusha
    	push ds
	push es
	push fs
	push gs
	;cli
	; Load the kernel data segment descriptor
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	; Call the function
    	mov eax, esp
    	push eax
    	mov eax, int_handler
    	call eax
	pop eax

	; Pop all registers reverse order and far-return
	pop gs
	pop fs
	pop gs
	pop ds
	popa

    	add esp, 8
	sti
    	iret	

global int0

int0:
	;cli
	push byte 0
	push byte 0
	jmp int_common_stub

%endif