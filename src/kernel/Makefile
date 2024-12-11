all: build_asm_files build_c_files

build_asm_files:
	nasm memory/gdt_ep.asm -f elf64 -o memory/gdt_ep.bin

CSOURCES := $(wildcard */*.c */*/*.c *.c)
build_c_files: $(CSOURCES)
	gcc -o ./../../bin/kernel64.sys $(CSOURCES) ../interpeter/src/main.c memory/gdt_ep.bin -D STAPELOS -m64 -ffreestanding -mgeneral-regs-only -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Werror -ffreestanding -Xlinker -T ./linker.ld -nostdlib -lgcc -ffreestanding -g -no-pie
