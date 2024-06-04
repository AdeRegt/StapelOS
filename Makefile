all:
	$(MAKE) -C src
	grub-mkrescue -o ./media/cdrom.iso ./bin

clean:
	rm -f test1

# Builder will call this to install the application before running.
install:
	cp ./bin/32to64.sys /srv/tftp/32to64.sys
	cp ./bin/kernel64.sys /srv/tftp/kernel64.sys

# Builder uses this target to run your application.
run:
	qemu-system-x86_64 --cdrom ./media/cdrom.iso
