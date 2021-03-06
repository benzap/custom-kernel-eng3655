%ifndef __GlobalCFunctions_INC_INCLUDED__
%define __GlobalCFunctions_INC_INCLUDED__



bits 32

;==========================================================
;
; This is a division by zero
;
;==========================================================
global _DivZero

_DivZero:
	xor cx, cx
	mov ax, 0x1
	div cx
	ret


;==========================================================
;
; This will set up the GDT
; This is declared in C as 'extern void gdt_install();'
;
;==========================================================

global gdt_install   ; Allows the C code to link to this
extern _gdtr         ; Says that '_gdtr' is in another file

gdt_install:
    lgdt [_gdtr]     ; Load the GDT with our '_gdtr' which is a special pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:endgdt   ; 0x08 is the offset to our code segment: Far jump!
endgdt:
    ret               ; Returns back to the C code!
		

;==========================================================
;
; This will set up the IDT
; This is declared in C as 'extern void idt_install();'
;
;==========================================================
global idt_install   ; Allows the C code to link to this
extern _idtr         ; Says that '_idtr' is in another file


idt_install:
   lidt [_idtr]      ; Load the IDT pointer.
   ret


%endif ;__GlobalCFunctions_INC_INCLUDED__
