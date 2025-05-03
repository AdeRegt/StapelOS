; note: this code is for 64-bit long mode only.
;       it is unknown if it works in protected mode.
;       using intel assembly style
global jump_usermode
extern uprogstart
jump_usermode:

	mov ecx, 0x401000 ; to be loaded into RIP
	mov r11, 0x202 ; to be loaded into EFLAGS
	o64 sysret ;use "o64 sysret" if you assemble with NASM