times 0x1B8-($-$$) db 0 ; fill rest of bootloader
; 0x1B8	4	Optional "Unique Disk ID / Signature
unique_disk_id dd 0
; 0x1BC	2	Optional, reserved 0x00003
reserved dw 0
; 0x1BE	16	First partition table entry
partition_1_drive_attr: 
    db 0
partition_1_chs: 
    times 3 db 0
partition_1_type:
    db 0
partition_1_chs_end:
    times 3 db 0
partition_1_lba_start:
    dd 0
partition_1_number_of_sector:
    dd 0
; 0x1CE	16	Second partition table entry
partition_2_drive_attr: 
    db 0
partition_2_chs: 
    times 3 db 0
partition_2_type:
    db 0
partition_2_chs_end:
    times 3 db 0
partition_2_lba_start:
    dd 0
partition_2_number_of_sector:
    dd 0
; 0x1DE	16	Third partition table entry
partition_3_drive_attr: 
    db 0
partition_3_chs: 
    times 3 db 0
partition_3_type:
    db 0
partition_3_chs_end:
    times 3 db 0
partition_3_lba_start:
    dd 0
partition_3_number_of_sector:
    dd 0
; 0x1EE	16	Fourth partition table entry
partition_4_drive_attr: 
    db 0
partition_4_chs: 
    times 3 db 0
partition_4_type:
    db 0
partition_4_chs_end:
    times 3 db 0
partition_4_lba_start:
    dd 0
partition_4_number_of_sector:
    dd 0
; 0x1FE	2	(0x55, 0xAA) "Valid bootsector" signature bytes
dw 0AA55h