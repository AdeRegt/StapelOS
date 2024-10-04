all:
	$(MAKE) -C src
	grub-mkrescue -o ./media/cdrom.iso ./bin

clean:
	rm -f test1

# Builder will call this to install the application before running.
install:
	cp -r ./bin/* /media/$(USER)/TEST

# Builder uses this target to run your application.
run:
	# qemu-system-x86_64 --cdrom ./media/cdrom.iso
