all:
	$(MAKE) -C origin
	$(MAKE) -C origin/apps
	$(MAKE) -C origin/gnuefi
	$(MAKE) -C origin/inc
	$(MAKE) -C origin/lib
	$(MAKE) -C src
	$(MAKE) -C src clean
	$(MAKE) -C origin clean
	$(MAKE) -C origin/apps clean
	$(MAKE) -C origin/gnuefi clean
	$(MAKE) -C origin/inc clean
	$(MAKE) -C origin/lib clean
	rm origin/x86_64/gnuefi/gnu-efi.pc
	rm origin/gnuefi/gnu-efi.pc
	