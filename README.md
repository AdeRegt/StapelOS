# StapelOS
## Building
``` make all ```

## Features
### Filesystems
Filesystem | Read | Write
---------- | ---- | ----- 
File allocation table (FAT) 32 | :white_check_mark: | :x: 

### Supported USB Classes
Class | Protocol | EHCI | XHCI 
----- | -------- | ---- | ---- 
MSD | USB 2.0 | :white_check_mark: | :white_check_mark:
MSD | USB 3.0 | :white_check_mark: | :bug:

### Devices

Devicename | VirtualBox | Qemu | Bochs | Real hardware
---------- | ---------- | ---- | ----- | -------------
devices - pci | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 
devices - ps2 - keyboard | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 
devices - serial | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 
devices - stapel | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 
devices - timer | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 
devices - echi | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 
devices - xhci | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 
devices - apic | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 
devices - pic | :white_check_mark: | :white_check_mark: | :white_check_mark: | :white_check_mark: 