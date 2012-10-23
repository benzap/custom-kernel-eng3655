%ifndef __GDT_INC__
%define __GDT_INC__

[bits 16]

;*******************************************
; Install our GDT
;*******************************************

InstallGDT:

	cli                  ; clear interrupts
	pusha                ; save registers
	lgdt 	[toc]        ; load GDT into GDTR
	sti	             ; enable interrupts
	popa                 ; restore registers
	ret	             ; All done!

;*******************************************
; Global Descriptor Table (GDT)
;*******************************************

gdt_data: 
	dd 0                ; null descriptor
	dd 0 

;gdt_kernel_code:            ; code descriptor
	dw 0FFFFh           ; limit low
	dw 0                ; base low
	db 0                ; base middle
	db 10011010b        ; access
	db 11001111b        ; granularity
	db 0                ; base high

;gdt_kernel_data:            ; data descriptor
	dw 0FFFFh           ; limit low (Same as code)
	dw 0                ; base low
	db 0                ; base middle
	db 10010010b        ; access
	db 11001111b        ; granularity
	db 0                ; base high


;User mode descriptors go here

;gdt_user_code:
	dw 0FFFFh           ; limit low
	dw 0                ; base low
	db 0                ; base middle
	db 11110010b        ; access
	db 11001111b        ; granularity
	db 0                ; base high

;gdt_user_data:
	dw 0FFFFh           ; limit low (Same as code)
	dw 0                ; base low
	db 0                ; base middle
	db 11110010b        ; access
	db 11001111b        ; granularity
	db 0                ; base high

end_of_gdt:
toc: 
	dw end_of_gdt - gdt_data - 1 	; limit (Size of GDT)
	dd gdt_data 			; base of GDT

; give the descriptor offsets names
; (offsets of toc in bytes)
%define NULL_DESC 		0x00
%define CODE_DESC 		0x08
%define DATA_DESC		0x10
%define USER_CODE_DESC 		0x18
%define USER_DATA_DESC 		0x20

%endif ;__GDT_INC__
