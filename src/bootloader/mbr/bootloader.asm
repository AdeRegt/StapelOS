;
; StapelOS bootloader
stapelos_bootloader_start:
        mov ax, 07C0h                   ; Set up 4K of stack space above buffer
        add ax, 544                     ; 8k buffer = 512 paragraphs + 32 paragraphs (loader)
        cli                             ; Disable interrupts while changing stack
        mov ss, ax
        mov sp, 4096
        sti                             ; Restore interrupts

        mov ax, 07C0h                   ; Set data segment to where we're loaded
        mov ds, ax

        call stapelos_bootloader_set_drive

        call stapelos_bootloader_welcome

        call stapelos_bootloader_reset_floppy

        mov al,14
        mov byte [write_sectors_count], al
        mov cl,2
        mov byte [write_sectors_sector],cl
        mov si,stage2
        mov word [write_sectors_location],si
        call stapelos_bootloader_read_sector

        jmp stage2 
        cli
        hlt

%INCLUDE "includes/graphics.asm"
%INCLUDE "includes/disk.asm"

%INCLUDE "includes/bootsignature.asm"

stage2:

        ;
        ; show welcome message 
        mov si,welcome_to_stage2
        call stapelos_bootloader_print_string

        ;
        ; try to get info about the dimensions
        call stapelos_bootloader_get_drive_parameters

        ;
        ; try loading the infodir of the filesystem
        call show_max_chs_info

        mov ah,0x41
        mov bx,0x55AA
        mov dl, byte [bootdev]
        stc 
        int 0x13
        jc stapelos_bootloader_show_error
        ; mov ax,cx 
        ; call os_print_4hex

        ; mov ax,word [partition_1_lba_start]
        ; call os_print_4hex
        ; mov ax,1
        ; mov word [write_sectors_lba], ax 

        mov si,filesysteminfo
        mov cx,512
        call stapelos_bootloader_print

        cli 
        hlt 

DAPACK:
	db	0x10
	db	0
blkcnt:	dw	1		; int 13 resets this to # of blocks actually read/written
db_add:	dw	filesysteminfo		; memory buffer destination address (0:7c00)
	dw	0		; in memory page zero
d_lba:	dd	2048		; put the lba to read in this spot
	dd	0		; more storage bytes only for big lba's ( > 4 bytes )

; CX = lba 
calculate_lba_to_chs:
        pusha 
        mov ax,0
        mov word[write_sectors_sector],ax  
        mov word[write_sectors_cylinder],ax
        mov word[write_sectors_head],ax
        .again:
        ; increate sector
        mov ax, word [write_sectors_sector]
        inc ax
        mov word [write_sectors_sector], ax
        cmp ax, word [logical_last_index_of_sectors_per_track]
        jne .skip1
        mov ax,0
        mov word [write_sectors_sector], ax
        mov ax, word [write_sectors_cylinder]
        inc ax
        mov word [write_sectors_cylinder], ax
        cmp ax, word [logical_last_index_of_cylinders]
        jne .skip1
        mov ax,0
        mov word [write_sectors_cylinder], ax
        mov ax, word [write_sectors_head]
        inc ax
        mov word [write_sectors_head], ax
        .skip1: 
        loop .again 
        popa 

show_max_chs_info:
        pusha 
        mov si, msg_chs_1
        call stapelos_bootloader_print_string
        mov ax,word [logical_last_index_of_sectors_per_track]
        call os_print_4hex
        mov si, msg_chs_2
        call stapelos_bootloader_print_string
        mov ax,word [logical_last_index_of_cylinders]
        call os_print_4hex
        mov si, msg_chs_3
        call stapelos_bootloader_print_string
        mov ax,word [logical_last_index_of_heads]
        call os_print_4hex
        popa 
        ret 



show_chs_info:
        pusha 
        mov si, msg_chs_4
        call stapelos_bootloader_print_string
        mov ax,word [write_sectors_cylinder]
        call os_print_4hex
        mov si, msg_chs_5
        call stapelos_bootloader_print_string
        mov ax,word [write_sectors_head]
        call os_print_4hex
        mov si, msg_chs_6
        call stapelos_bootloader_print_string
        mov ax,word [write_sectors_sector]
        call os_print_4hex
        popa 
        ret 

msg_chs_1 db " | logical_last_index_of_sectors_per_track=",0x00
msg_chs_2 db " | logical_last_index_of_cylinders=",0x00
msg_chs_3 db " | logical_last_index_of_heads=",0x00
msg_chs_4 db " | c=",0x00
msg_chs_5 db " | h=",0x00
msg_chs_6 db " | s=",0x00
welcome_to_stage2 db "Welcome to stage2! ",0x00
times 0x400-($-$$) db 0
filesysteminfo:
times 0x200 db 'g'
