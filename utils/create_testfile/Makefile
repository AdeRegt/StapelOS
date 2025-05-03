all:
	cc test.c -c -o ./testexec.o -m64  -Werror -ffreestanding
	ld ./testexec.o -nostdlib  -o ./testexec
	./../file_to_c_variable/file_to_c_variable ./testexec ./testfile.c
	rm ./testexec.o 
	