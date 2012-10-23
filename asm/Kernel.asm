;org 0x100000   ; Kernel starts at 1 MB

bits 32    ; 32 bit code

global start
start:

jmp KernelCode   ; jump to entry point
%include "KernelDisplay.inc"
%include "GlobalCFunctions.inc"
	
%define VIDMEM 0xB8000

msgGoodbye db 0x0A, 0x0A, "It is now safe to turn off your computer.", 0x0A, 0

KernelCode:
 ;-------------------------------;
 ;   Set registers   
 ;-------------------------------;

 mov ax, 0x10  ; set data segments to data selector (0x10)
 mov ds, ax
 mov ss, ax
 mov es, ax
 mov esp, 90000h  ; stack begins from 90000h

 ;---------------------------------------;
 ;   Jump to our C Kernel
 ;---------------------------------------;

 extern KernelMain
 call KernelMain 

 mov ebx, msgGoodbye
 call DisplayString

 ;---------------------------------------;
 ;   Stop execution    
 ;---------------------------------------;

 jmp $	; Infinite loop


