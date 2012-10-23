; ENGI 3655 - Lab 3->5
; Feb 4, 2010
;
; BootLoader-Stage1wFAT.asm

[BITS 16]					; we are in 16 bit real mode
[ORG 0]						; we will set regisers later

start:	jmp	main				; jump to start of bootloader

;*********************************************
;	BIOS Parameter Block
;*********************************************

; BPB Begins 3 bytes from start. We do a far jump, which is 3 bytes in size.
; If you use a short jump, add a "nop" after it to offset the 3rd byte.

bpbOEM					db "ENGI3655"			; OEM identifier (Cannot exceed 8 bytes!)
bpbBytesPerSector:  	DW 512
bpbSectorsPerCluster: 	DB 1
bpbReservedSectors: 	DW 1
bpbNumberOfFATs: 		DB 2
bpbRootEntries: 		DW 224
bpbTotalSectors: 		DW 2880
bpbMedia: 				DB 0xf0
bpbSectorsPerFAT: 		DW 9
bpbSectorsPerTrack: 	DW 18
bpbHeadsPerCylinder: 	DW 2
bpbHiddenSectors: 		DD 0
bpbTotalSectorsBig:     DD 0
bsDriveNumber: 	        DB 0
bsUnused: 				DB 0
bsExtBootSignature: 	DB 0x29
bsSerialNumber:	        DD 0xa0a1a2a3
bsVolumeLabel: 	        DB "OUR FLOPPY "
bsFileSystem: 	        DB "FAT12   "

;************************************************;
;	Prints a string
;	DS=>SI: 0 terminated string
;************************************************;
Print:
			push ax				; remember state of AX (AH/AL)
    PrintLoop:
			lodsb				; load next byte from string from SI to AL
			or	al, al			; Does AL=0?
			jz	PrintDone		; Yep, null terminator found-bail out
			mov	ah, 0eh			; Nope-Print the character
			int	10h
			jmp	PrintLoop		; Repeat until null terminator found
	PrintDone:
			pop ax
			ret				; we are done, so return

;************************************************;
; Reads a series of sectors
; CX=>Number of sectors to read
; AX=>Starting sector
; ES:BX=>Buffer to read to
;************************************************;

ReadSectors:
     .MAIN:
          mov     di, 0x0005                          ; five retries for error
     .SECTORLOOP:
          push    ax
          push    bx
          push    cx
          call    LBACHS                              ; convert starting sector to CHS
          mov     ah, 0x02                            ; BIOS read sector
          mov     al, 0x01                            ; read one sector
          mov     ch, BYTE [absoluteTrack]            ; track
          mov     cl, BYTE [absoluteSector]           ; sector
          mov     dh, BYTE [absoluteHead]             ; head
          mov     dl, BYTE [bsDriveNumber]            ; drive
          int     0x13                                ; invoke BIOS
          jnc     .SUCCESS                            ; test for read error
          xor     ax, ax                              ; BIOS reset disk
          int     0x13                                ; invoke BIOS
          dec     di                                  ; decrement error counter
          pop     cx
          pop     bx
          pop     ax
          jnz     .SECTORLOOP                         ; attempt to read again
          int     0x18
     .SUCCESS:
          mov     si, msgProgress
          call    Print
          pop     cx
          pop     bx
          pop     ax
          add     bx, WORD [bpbBytesPerSector]        ; queue next buffer
          inc     ax                                  ; queue next sector
          loop    .MAIN                               ; read next sector
          ret

;************************************************;
; Convert CHS to LBA
; AX  = cluster number
; LBA = (cluster - 2) * sectors per cluster
;************************************************;

ClusterLBA:
          sub     ax, 0x0002                          ; zero base cluster number
          xor     cx, cx
          mov     cl, BYTE [bpbSectorsPerCluster]     ; convert byte to word
          mul     cx
          add     ax, WORD [datasector]               ; base data sector
          ret
     
;************************************************;
; Convert LBA to CHS
; AX=>LBA Address to convert
;
; absolute sector = (logical sector / sectors per track) + 1
; absolute head   = (logical sector / sectors per track) MOD number of heads
; absolute track  = logical sector / (sectors per track * number of heads)
;
;************************************************;

LBACHS:
          xor     dx, dx                              ; prepare dx:ax for operation
          div     WORD [bpbSectorsPerTrack]           ; calculate
          inc     dl                                  ; adjust for sector 0
          mov     BYTE [absoluteSector], dl
          xor     dx, dx                              ; prepare dx:ax for operation
          div     WORD [bpbHeadsPerCylinder]          ; calculate
          mov     BYTE [absoluteHead], dl
          mov     BYTE [absoluteTrack], al
          ret

;*********************************************
;	Bootloader Entry Point
;*********************************************

main:

     ;----------------------------------------------------
     ; code located at 0000:7C00, adjust segment registers
     ;----------------------------------------------------
     
          cli						; disable interrupts
          mov     ax, 0x07C0				; setup registers to point to our segment
          mov     ds, ax
          mov     es, ax
          mov     fs, ax
          mov     gs, ax

     ;----------------------------------------------------
     ; create stack
     ;----------------------------------------------------
     
          mov     ax, 0x0000				; set the stack
          mov     ss, ax
          mov     sp, 0xFFFF
          sti						; restore interrupts

     ;----------------------------------------------------
     ; Display loading message
     ;----------------------------------------------------
     
          ;mov     si, msgLoading
          ;call    Print
          
     ;----------------------------------------------------
     ; Read the Root Directory Table into Memory
     ; 
     ; Get the size of the RDT in sectors
     ; Get the start of the RDT
     ; Save the end of the RDT
     ; Read from disk into memory
     ;----------------------------------------------------

     LOAD_ROOT:
		  mov     si, msgRDT
          call    Print
          
     ;----------------------------------------------------
     ; Get the size of the Root Directory Table
     ;----------------------------------------------------
     
          mov     ax, 0x020					; 32-bytes per directory entry
          mul     WORD [bpbRootEntries]		; ... * the number of entries
          div     WORD [bpbBytesPerSector]	; ... / the number of bytes per sector
          xchg    ax, cx					; Save result in cx
			
     ;----------------------------------------------------
     ; Get the start of the Root Directory Table
     ;----------------------------------------------------
     
     	  xor     ax, ax
          mov     al, [bpbNumberOfFATs]				; Get the number of 
          mul WORD [bpbSectorsPerFAT]				; ...sectors occupied by FATs
          add     ax, [bpbReservedSectors]			; + reserved sectors
		  
     ;----------------------------------------------------
     ; Save the end of the RDT
     ;----------------------------------------------------      
     
          mov    [datasector], ax
          add    [datasector], cx		; [datasector] is now the LBA of the data sector on the disk
          
     ;----------------------------------------------------
     ; Read Root Directory Table into memory
     ;----------------------------------------------------

          mov    bx, 0x0200
          ; ax is the sector of the start of the RDT (from above)
          ; cx is the number of sectors of RDT (from above)
          call   ReadSectors

     ;----------------------------------------------------
     ; Search the Root Directory Table
     ; 
     ; Set loop counter
     ; Start at the beginning of the RDT
     ; Get the first 11 bytes of the directory entry
     ; Get the file name
     ; Compare SI and DI
     ; If they match, load FAT
     ; If they don't match, loop to next directory entry
     ; If we're out of entries, the file doesn't exist
     ;----------------------------------------------------

          mov    cx, WORD [bpbRootEntries]		; Set loop counter
          mov    di, 0x0200
          .loop:
              push   di							; Save start of RDT entry
              mov    cx, 0x000B
              mov    si, ImageName
              rep cmpsb							; Compare cx bytes of ES:SI and DS:DI
              pop    di							; Return to start of RDT entry
              je     LOAD_FAT
              add    di, 0x0020					; Go to next entry
              loop   .loop						; ... and try again
              jmp    FAILURE
          
     ;----------------------------------------------------
     ; Read the FAT into Memory
     ; 
     ; Get the size of the FAT in sectors
     ; Get the start of the FAT
     ; Read from disk into memory
     ;----------------------------------------------------

     LOAD_FAT:
     	 mov     si, msgFAT
         call    Print
         
     ;----------------------------------------------------
     ; Save the position of the first cluster of our file
     ;----------------------------------------------------
     
         mov    dx, WORD [di + 0x001A]		; put cluster # into dx
         mov    WORD [cluster], dx			; put cluster # dx->memory
     
     ;----------------------------------------------------
     ; Get the size of the FAT in sectors
     ;----------------------------------------------------
     
         xor    ax, ax
         mov    al, [bpbNumberOfFATs]
         mul WORD [bpbSectorsPerFAT]
         mov    cx, ax
     
     ;----------------------------------------------------
     ; Get the start of the FAT
     ;----------------------------------------------------
     
         mov   ax, [bpbReservedSectors]
     
     ;----------------------------------------------------
     ; Read the FAT into memory
     ;----------------------------------------------------
     
         ; ax contains the first sector of the FAT
         ; cx contains the size of the FAT in sectors
         mov    bx, 0x0200
         call   ReadSectors						; overwrites RDT
          
     ;----------------------------------------------------
     ; Search the FAT
     ; 
     ; Put the current cluster number in ax
     ; Convert the current cluster info into LogicalSector and read
     ; Put the current cluster address word in dx
     ; Load next cluster, alternating between even and odd
     ; Test for end of file indicator
     ;----------------------------------------------------
         
         ; We'll be copying stage 2 to ES:BX => 0500:0000
         mov    ax, 0x0050
         mov    es, ax
         mov    bx, 0x0000
         push   bx								  ; initial push of bx
         
         mov     si, msgImage
         call    Print
         
     LOAD_IMAGE:
         
     ;----------------------------------------------------
     ; Put the current cluster number in ax
     ;----------------------------------------------------

         mov    ax, WORD [cluster]
         
     ;----------------------------------------------------
     ; Convert the current cluster info into LogicalSector and read
     ;----------------------------------------------------

         call   ClusterLBA
         
     ;----------------------------------------------------
     ; Read the image file into memory (0050:0000)
     ;----------------------------------------------------
	     
	     pop    bx								; recall copy position
	     xor    cx, cx
         mov    cl, [bpbSectorsPerCluster]
         call   ReadSectors						; read cluster into memory
         push   bx								; save copy position
         
     ;----------------------------------------------------
     ; Put the current cluster address word in dx
     ;----------------------------------------------------
         
         mov    ax, WORD [cluster]
         
         mov    cx, ax
         mov    dx, ax
         shr    dx, 0x0001		; dx = ax/2
         add    cx, dx			; cx = 1.5 * ax
         mov    bx, 0x0200
         add    bx, cx			; bx = 0x0200 + 1.5*ax
         
         mov    dx, WORD [bx]
         
     ;----------------------------------------------------
     ; Load next cluster, alternating between even and odd
     ;----------------------------------------------------
    
         ; ax now contains our cluster number
         ; dx now contains our next cluster address
         
         ; Since FAT addresses are 12-bit (not 8 or 16), 
         ; what we do depends on whether the cluster is odd or even...
         
         test ax, 0x0001
         jnz .OddCluster
         .EvenCluster:
             and dx, 0x0FFF		; Remove first 4 bits of 16 to make 12
             jmp .Done
         .OddCluster:
             shr dx, 0x0004		; Remove last 4 bits of 16 to make 12
         .Done:
             mov WORD [cluster], dx

     ;----------------------------------------------------
     ; Test for end of file indicator
     ;----------------------------------------------------
     
         cmp    dx, 0x0FF0
         jb     LOAD_IMAGE
     
     ;----------------------------------------------------
     ; Final executable code and data
     ;----------------------------------------------------

     DONE:
          mov     si, msgLoaded
          call    Print
          
          push    WORD 0x0050		; changes CS
          push    WORD 0x0000		; changes IP
          
          retf
          
     FAILURE:
          mov     si, msgFailure
          call    Print
          
          mov     ah, 0x00
          int     0x16                                ; await keypress
          int     0x19                                ; warm boot computer
     
     absoluteSector db 0x00
     absoluteHead   db 0x00
     absoluteTrack  db 0x00
     
     datasector  dw 0x0000
     cluster     dw 0x0000
     ImageName   db "STAGE2  SYS"
     

     msgProgress db "*", 0x00
     msgRDT      db "Loading RDT: ", 0x00
     msgFAT      db 0x0D, 0x0A, "Loading FAT: ", 0x00
     msgImage    db 0x0D, 0x0A, "Loading next stage: ", 0x00
     msgLoaded   db 0x0D, 0x0A, "All done.", 0x0D, 0x0A, 0x0D, 0x0A, 0x00
     msgFailure  db 0x0D, 0x0A, "Failed.", 0x0D, 0x0A, 0x00
     
          TIMES 510-($-$$) DB 0
          DW 0xAA55