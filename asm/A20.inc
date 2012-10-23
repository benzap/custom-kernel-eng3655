
%ifndef __A20_INC__
%define __A20_INC__

bits	16

;--------------------------------------------
; Enables a20 line through output port
;--------------------------------------------

EnableA20_KKbrd_Out:

	cli
	pusha
	
 	; disable keyboard
        call    waitForInputBuffer
        mov     al,0xAD
        out     0x64,al


	; read output port
        call    waitForInputBuffer
        mov     al,0xD0
        out     0x64,al

	; grab keyboard bits and store for later
        call    waitForOutputBuffer
        in      al,0x60
        push    ax

	; write input port
        call    waitForInputBuffer
        mov     al,0xD1
        out     0x64,al

	; enable A20 bit, send to input port
        call    waitForInputBuffer
        pop     ax
        or      al,2
        out     0x60,al

	;; enable keyboard
        call    waitForInputBuffer
        mov     al,0xAE
        out     0x64,al
 
        call    waitForInputBuffer

	popa
        sti
        ret
	
	;; when bit 2 is 0, the input buffer is empty and can be written to
waitForInputBuffer:
        in      al,0x64
        test    al,2
        jnz     waitForInputBuffer
        ret
 
	;; when bit 1 is 1, the output buffer is full and can be read from.
waitForOutputBuffer:
        in      al,0x64
        test    al,1
        jz      waitForOutputBuffer
        ret


%endif ;__A20_INC__
