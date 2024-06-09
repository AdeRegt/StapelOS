#pragma once
#include <stdint.h>

#define CAPLENGTH ((uint8_t*)base_xhci_address)[0]
#define HCIVERSION ((uint16_t*)( base_xhci_address + 0x02 ))[0]
#define HCSPARAMS1 ((uint32_t*)( base_xhci_address + 0x04 ))[0]
#define HCSPARAMS2 ((uint32_t*)( base_xhci_address + 0x08 ))[0]
#define HCSPARAMS3 ((uint32_t*)( base_xhci_address + 0x0C ))[0]
#define HCCPARAMS1 ((uint32_t*)( base_xhci_address + 0x10 ))[0]
#define DBOFF ((uint32_t*)( base_xhci_address + 0x14 ))[0]
#define RTSOFF ((uint32_t*)( base_xhci_address + 0x18 ))[0]
#define HCCPARAMS2 ((uint32_t*)( base_xhci_address + 0x1C ))[0]
#define VTIOSOFF ((uint32_t*)( base_xhci_address + 0x20 ))[0]

#define HCSPARAMS1_MASK_MaxSlots 0xFF
#define HCSPARAMS1_MaxSlots ( HCSPARAMS1 & HCSPARAMS1_MASK_MaxSlots )

#define HCSPARAMS1_MASK_MaxIntrs 0x7FF00
#define HCSPARAMS1_SHIFT_MaxIntrs 8
#define HCSPARAMS1_MaxIntrs ((HCSPARAMS1 & HCSPARAMS1_MASK_MaxIntrs)>>HCSPARAMS1_SHIFT_MaxIntrs)

#define HCSPARAMS1_MASK_MaxPorts 0xFF000000
#define HCSPARAMS1_SHIFT_MaxPorts 24
#define HCSPARAMS1_MaxPorts ((HCSPARAMS1 & HCSPARAMS1_MASK_MaxPorts)>>HCSPARAMS1_SHIFT_MaxPorts)

#define HCSPARAMS2_MASK_IST 0xF
#define HCSPARAMS2_IST ( HCSPARAMS2 & HCSPARAMS2_MASK_IST )

#define HCSPARAMS2_MASK_ERST_Max 0xF0
#define HCSPARAMS2_SHIFT_ERST_Max 4
#define HCSPARAMS2_ERST_Max ( ( HCSPARAMS2 & HCSPARAMS2_MASK_ERST_Max ) >> HCSPARAMS2_SHIFT_ERST_Max )

#define HCSPARAMS2_MASK_Scratchpad_Bufs_Hi 0x3E00000
#define HCSPARAMS2_SHIFT_Scratchpad_Bufs_Hi 21
#define HCSPARAMS2_Scratchpad_Bufs_Hi ( ( HCSPARAMS2 & HCSPARAMS2_MASK_Scratchpad_Bufs_Hi ) >> HCSPARAMS2_SHIFT_Scratchpad_Bufs_Hi )

#define HCSPARAMS2_MASK_SPR 0x4000000
#define HCSPARAMS2_SHIFT_SPR 26
#define HCSPARAMS2_SPR ( ( HCSPARAMS2 & HCSPARAMS2_MASK_SPR ) >> HCSPARAMS2_SHIFT_SPR )

#define HCSPARAMS2_MASK_Scratchpad_Bufs_Lo 0x4000000
#define HCSPARAMS2_SHIFT_Scratchpad_Bufs_Lo 27
#define HCSPARAMS2_Scratchpad_Bufs_Lo ( ( HCSPARAMS2 & HCSPARAMS2_MASK_Scratchpad_Bufs_Lo ) >> HCSPARAMS2_SHIFT_Scratchpad_Bufs_Lo )

#define HCSPARAMS3_MASK_U1 0xFF
#define HCSPARAMS3_SHIFT_U1 0
#define HCSPARAMS3_U1 ( ( HCSPARAMS3 & HCSPARAMS3_MASK_U1 ) >> HCSPARAMS3_SHIFT_U1 )

#define HCSPARAMS3_MASK_U2 0xFFFF0000
#define HCSPARAMS3_SHIFT_U2 16
#define HCSPARAMS3_U2 ( ( HCSPARAMS3 & HCSPARAMS3_MASK_U2 ) >> HCSPARAMS3_SHIFT_U2 )

#define HCCPARAMS1_AC64       ( ( HCCPARAMS1 & 0b00000000000000000000000000000001 ) >> 0 )
#define HCCPARAMS1_BNC        ( ( HCCPARAMS1 & 0b00000000000000000000000000000010 ) >> 1 )
#define HCCPARAMS1_CSZ        ( ( HCCPARAMS1 & 0b00000000000000000000000000000100 ) >> 2 )
#define HCCPARAMS1_PPC        ( ( HCCPARAMS1 & 0b00000000000000000000000000001000 ) >> 3 )
#define HCCPARAMS1_PIND       ( ( HCCPARAMS1 & 0b00000000000000000000000000010000 ) >> 4 )
#define HCCPARAMS1_LHRC       ( ( HCCPARAMS1 & 0b00000000000000000000000000100000 ) >> 5 )
#define HCCPARAMS1_LTC        ( ( HCCPARAMS1 & 0b00000000000000000000000001000000 ) >> 6 )
#define HCCPARAMS1_NSS        ( ( HCCPARAMS1 & 0b00000000000000000000000010000000 ) >> 7 )
#define HCCPARAMS1_PAE        ( ( HCCPARAMS1 & 0b00000000000000000000000100000000 ) >> 8 )
#define HCCPARAMS1_SPC        ( ( HCCPARAMS1 & 0b00000000000000000000001000000000 ) >> 9 )
#define HCCPARAMS1_SEC        ( ( HCCPARAMS1 & 0b00000000000000000000010000000000 ) >> 10 )
#define HCCPARAMS1_CFC        ( ( HCCPARAMS1 & 0b00000000000000000000100000000000 ) >> 11 )
#define HCCPARAMS1_MaxPSASize ( ( HCCPARAMS1 & 0b00000000000000001111000000000000 ) >> 12 )
#define HCCPARAMS1_xECP       ( ( HCCPARAMS1 & 0b11111111111111110000000000000000 ) >> 16 )

void initialise_xhci(uint8_t bus, uint8_t slot, uint8_t func);
