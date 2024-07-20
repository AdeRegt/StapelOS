;
; print_string prints a string to the screen at the text cursor
stapelos_bootloader_print_string:                           ; Output string in SI to screen
        pusha

        mov ah, 0Eh                     ; int 10h teletype function

.repeat:
        lodsb                           ; Get char from string
        cmp al, 0
        je .done                        ; If char is zero, end of string
        int 10h                         ; Otherwise, print it
        jmp short .repeat

.done:
        popa
        ret

stapelos_bootloader_print:                           ; Output string in SI to screen, CX loop
        pusha

        mov ah, 0Eh                     ; int 10h teletype function

.repeat:
        lodsb                           ; Get char from string
        int 10h                         ; Otherwise, print it
        loop .repeat

.done:
        popa
        ret

stapelos_bootloader_welcome:
        push si
        mov si,helloworldstring 
        call stapelos_bootloader_print_string 
        pop si
        ret 

stapelos_bootloader_show_error:
        mov si,errormessage
        call stapelos_bootloader_print_string
        cli 
        hlt 

errormessage db "Diskerror",0x00
helloworldstring db "Welcome to the StapelOS bootloader",0x00

os_print_digit:
	pusha

	cmp ax, 9			; There is a break in ASCII table between 9 and A
	jle .digit_format

	add ax, 'A'-'9'-1		; Correct for the skipped punctuation

.digit_format:
	add ax, '0'			; 0 will display as '0', etc.	

	mov ah, 0Eh			; May modify other registers
	int 10h

	popa
	ret


; ------------------------------------------------------------------
; os_print_1hex -- Displays low nibble of AL in hex format
; IN: AL = number to format and print

os_print_1hex:
	pusha

	and ax, 0Fh			; Mask off data to display
	call os_print_digit

	popa
	ret


; ------------------------------------------------------------------
; os_print_2hex -- Displays AL in hex format
; IN: AL = number to format and print

os_print_2hex:
	pusha

	push ax				; Output high nibble
	shr ax, 4
	call os_print_1hex

	pop ax				; Output low nibble
	call os_print_1hex

	popa
	ret

os_print_4hex:
	pusha

	push ax				; Output high byte
	mov al, ah
	call os_print_2hex

	pop ax				; Output low byte
	call os_print_2hex

	popa
	ret