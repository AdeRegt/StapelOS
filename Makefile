all:
	$(MAKE) -C src

clean:
	rm -f test1

# Builder will call this to install the application before running.
install:
	grub-mkrescue -o ./media/efi_grub_cdrom.iso ./bin
	xorrisofs -o ./media/efi_custom_cdrom.iso -eltorito-platform efi --efi-boot efi/boot/bootx64.efi ./bin
	if [ -d /media/$(USER)/TEST ]; then cp -r ./bin/* /media/$(USER)/TEST ; fi

# Builder uses this target to run your application.
run:
	# qemu-system-x86_64 --cdrom ./media/cdrom.iso
