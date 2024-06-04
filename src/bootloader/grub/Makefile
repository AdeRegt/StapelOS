all: build_asm_files build_c_files

build_asm_files:
	nasm -felf32 boot.asm -o boot.o || exit

build_c_files:
	gcc -o ./../../../bin/32to64.sys boot.o loader.c -m32 -ffreestanding -mgeneral-regs-only -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Werror -ffreestanding -Xlinker -T linker.ld -nostdlib -ffreestanding
