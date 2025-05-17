all:
	nm -n -g --defined-only ./../../bin/kernel64.sys | grep ' [Tt] ' | awk '{print $$3}' > symbols.txt
	gcc -o symftoc symftoc.c 
	./symftoc symbols.txt ./../../src/kernel/utils/reflection.c
	rm symbols.txt