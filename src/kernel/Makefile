all: build_asm_files build_c_files

build_asm_files:

CSOURCES := $(wildcard */*.c */*/*.c *.c)
build_c_files: $(CSOURCES)
	gcc -o ./../../bin/kernel64.sys $(CSOURCES) -m64 -ffreestanding -mgeneral-regs-only -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -Werror -ffreestanding -Xlinker -T ./linker.ld -nostdlib -lgcc -ffreestanding
