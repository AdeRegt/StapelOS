; note: this code is for 64-bit long mode only.
;       it is unknown if it works in protected mode.
;       using intel assembly style
global jump_usermode
extern uprogstart
extern usermode_eflags
jump_usermode:

	mov rcx, qword [uprogstart] ; to be loaded into RIP
	mov r11, qword [usermode_eflags] ; to be loaded into EFLAGS
	o64 sysret ;use "o64 sysret" if you assemble with NASM