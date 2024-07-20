stapelos_bootloader_reset_floppy:		; IN: [bootdev] = boot device; OUT: carry set on error
	push ax
	push dx
	mov ax, 0
	mov dl, byte [bootdev]
	stc
	int 13h
	jc stapelos_bootloader_show_error
	pop dx
	pop ax
	ret

; CL = sector to read
stapelos_bootloader_read_sector:
	pusha 
	mov ch, byte [write_sectors_cylinder]
	mov cl, byte [write_sectors_sector]
	mov dx,0
	mov dh, byte [write_sectors_head]
	mov dl, byte [bootdev]
	mov si, word [write_sectors_location]
	mov bx, ds
	mov es, bx
	mov bx, si

	mov ah, 2			; Params for int 13h: read floppy sectors
	mov al, byte [write_sectors_count]
	stc 
	int 13h
	jc stapelos_bootloader_show_error
	popa 
	ret 

stapelos_bootloader_set_drive:
    push dx
    mov byte[bootdev], dl 
    pop dx 
    ret

stapelos_bootloader_get_drive_parameters:
	pusha
	mov ah,0x8
	mov dl,byte [bootdev]
	stc 
	int 0x13 
	jc stapelos_bootloader_show_error
	dec dh
	mov byte [logical_last_index_of_heads], dh
	push cx 
	and cx, 3Fh
	mov byte [logical_last_index_of_sectors_per_track], cl
	pop cx 
	and cx, 0xFFC0
	shr cx, 6
	mov word [logical_last_index_of_cylinders], cx
	popa 
	ret 

bootdev db 0x00
logical_last_index_of_sectors_per_track dw 0x00
logical_last_index_of_cylinders dw 0x00
logical_last_index_of_heads dw 0x00
write_sectors_location dw 0
write_sectors_sector dw 0
write_sectors_count dw 0
write_sectors_cylinder dw 0
write_sectors_head dw 0
write_sectors_lba dd 0