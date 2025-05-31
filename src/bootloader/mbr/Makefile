all:
	$(MAKE) -C stage0
	$(MAKE) -C stage1
	dd if=/dev/zero of=../../../media/floppy.img bs=512 count=2880
	mkfs.fat -F 12 ../../../media/floppy.img
	dd if=stage0/bootloader.bin of=../../../media/floppy.img bs=512 count=1 conv=notrunc
	mcopy -i ../../../media/floppy.img -s ../../../bin/* ::/