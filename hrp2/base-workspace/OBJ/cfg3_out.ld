OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm","elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
	ROM : ORIGIN = 0xc0008000, LENGTH = 0x100000
	RAM : ORIGIN = 0xc0108000, LENGTH = 0x3ef8000
}

PROVIDE(_gp = 0);
PROVIDE(hardware_init_hook = 0);
PROVIDE(software_init_hook = 0);
PROVIDE(software_term_hook = 0);

SECTIONS {
	vector : {
		__start_text_kernel = .;
		__start_text_kernel__std = .;
		*(.vector)
	} > ROM

	.rodata_kernel : {
		__start_rodata_kernel = .;
		__start_rodata_kernel__std = .;
		kernel_cfg.o(.text) kernel_cfg.o(.rodata .rodata.str1.4) kernel_mem3.o(.text) kernel_mem3.o(.rodata .rodata.str1.4) libkernel.a(.text) libkernel.a(.rodata .rodata.str1.4) syslog.o(.text) syslog.o(.rodata .rodata.str1.4) banner.o(.text) banner.o(.rodata .rodata.str1.4) serial.o(.text) serial.o(.rodata .rodata.str1.4) logtask.o(.text) logtask.o(.rodata .rodata.str1.4) fatfs_dri.o(.text) fatfs_dri.o(.rodata .rodata.str1.4) fatfs_syscall.o(.text) fatfs_syscall.o(.rodata .rodata.str1.4) diskio.o(.text) diskio.o(.rodata .rodata.str1.4) ff.o(.text) ff.o(.rodata .rodata.str1.4) mmcsd.o(.text) mmcsd.o(.rodata .rodata.str1.4) mmcsdlib.o(.text) mmcsdlib.o(.rodata .rodata.str1.4) mmcsd_dri.o(.text) mmcsd_dri.o(.rodata .rodata.str1.4) mmcsd_proto.o(.text) mmcsd_proto.o(.rodata .rodata.str1.4) mmcsd_rw.o(.text) mmcsd_rw.o(.rodata .rodata.str1.4) soc_cache.o(.text) soc_cache.o(.rodata .rodata.str1.4) soc_edma.o(.text) soc_edma.o(.rodata .rodata.str1.4) edma.o(.text) edma.o(.rodata .rodata.str1.4) uart.o(.text) uart.o(.rodata .rodata.str1.4) cp15.o(.text) cp15.o(.rodata .rodata.str1.4) psc.o(.text) psc.o(.rodata .rodata.str1.4) usb.o(.text) usb.o(.rodata .rodata.str1.4) usbphyGS60.o(.text) usbphyGS60.o(.rodata .rodata.str1.4) cppi41dma.o(.text) cppi41dma.o(.rodata .rodata.str1.4) evmAM1808_usb.o(.text) evmAM1808_usb.o(.rodata .rodata.str1.4) soc_interrupt.o(.text) soc_interrupt.o(.rodata .rodata.str1.4) bluetooth_dri.o(.text) bluetooth_dri.o(.rodata .rodata.str1.4) libBTstack.a(.text) libBTstack.a(.rodata .rodata.str1.4) usbmsc_dri.o(.text) usbmsc_dri.o(.rodata .rodata.str1.4) usbmsc_media_functions.o(.text) usbmsc_media_functions.o(.rodata .rodata.str1.4) usb_dev_msc.o(.text) usb_dev_msc.o(.rodata .rodata.str1.4) usb_msc_structs.o(.text) usb_msc_structs.o(.rodata .rodata.str1.4) libusblib.a(.text) libusblib.a(.rodata .rodata.str1.4) mbed_dri.o(.text) mbed_dri.o(.rodata .rodata.str1.4) libmbed.a(.text) libmbed.a(.rodata .rodata.str1.4) app.o(.text) app.o(.rodata .rodata.str1.4) apploader.o(.text) apploader.o(.rodata .rodata.str1.4) cli_main.o(.text) cli_main.o(.rodata .rodata.str1.4) *(.text_kernel) *(.rodata_kernel) *(.page_table) 
		__end_rodata_kernel__std = .;
		__end_rodata_kernel = .;
	} > ROM
	. = ALIGN(4K);
	__limit_rodata_kernel__std = .;
	__limit_rodata_kernel = .;

	.rodata_kernel_ffffffff ALIGN(4) : {
		__start_rodata_kernel_ffffffff = .;
		__start_rodata_kernel__ffffffff_0 = .;
		brick_dri.o(.text) brick_dri.o(.rodata .rodata.str1.4) analog_dri.o(.text) analog_dri.o(.rodata .rodata.str1.4) lcd_dri.o(.text) lcd_dri.o(.rodata .rodata.str1.4) lcd_font.o(.text) lcd_font.o(.rodata .rodata.str1.4) motor_dri.o(.text) motor_dri.o(.rodata .rodata.str1.4) i2c_dri.o(.text) i2c_dri.o(.rodata .rodata.str1.4) davinci_iic_dri.o(.text) davinci_iic_dri.o(.rodata .rodata.str1.4) uart_dri.o(.text) uart_dri.o(.rodata .rodata.str1.4) pru.o(.text) pru.o(.rodata .rodata.str1.4) suart_utils.o(.text) suart_utils.o(.rodata .rodata.str1.4) suart_api.o(.text) suart_api.o(.rodata .rodata.str1.4) pru_suart.o(.text) pru_suart.o(.rodata .rodata.str1.4) sound_dri.o(.text) sound_dri.o(.rodata .rodata.str1.4) ev3main.o(.text) ev3main.o(.rodata .rodata.str1.4) driver_interface_bluetooth.o(.text) driver_interface_bluetooth.o(.rodata .rodata.str1.4) driver_interface_brick.o(.text) driver_interface_brick.o(.rodata .rodata.str1.4) driver_interface_sound.o(.text) driver_interface_sound.o(.rodata .rodata.str1.4) driver_interface_filesys.o(.text) driver_interface_filesys.o(.rodata .rodata.str1.4) dmloader.o(.text) dmloader.o(.rodata .rodata.str1.4) elf32.o(.text) elf32.o(.rodata .rodata.str1.4) 
		__end_rodata_kernel__ffffffff_0 = .;
		__end_rodata_kernel_ffffffff = .;
	} > ROM
	. = ALIGN(4K);
	__limit_rodata_kernel__ffffffff_0 = .;
	__limit_rodata_kernel_ffffffff = .;

	.rodata_TDOM_APP ALIGN(4) : {
		__start_rodata_TDOM_APP = .;
		__start_rodata_TDOM_APP__std = .;
		*(.text_TDOM_APP) *(.rodata_TDOM_APP) 
		__end_rodata_TDOM_APP__std = .;
		__end_rodata_TDOM_APP = .;
	} > ROM
	. = ALIGN(4K);
	__limit_rodata_TDOM_APP__std = .;
	__limit_rodata_TDOM_APP = .;

	.rodata_shared ALIGN(4) : {
		__start_rodata_shared = .;
		__start_rodata_shared__0 = .;
		zmodem-toppers.o(.text) zmodem-toppers.o(.rodata .rodata.str1.4) crc16.o(.text) crc16.o(.rodata .rodata.str1.4) crc32.o(.text) crc32.o(.rodata .rodata.str1.4) 
		__end_rodata_shared__0 = .;
		. = ALIGN(4);
		__limit_rodata_shared__0 = .;

		__start_rodata_shared__std = .;
		*(.text) *(.rodata .rodata.str1.4) *(.text.*) *(.rodata.*) *(.text_shared) *(.rodata_shared) 
	} > ROM
	.preinit_array ALIGN(4) : {
		PROVIDE_HIDDEN (__preinit_array_start = .);
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN (__preinit_array_end = .);
	} > ROM
	.init_array ALIGN(4) : {
		PROVIDE_HIDDEN (__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN (__init_array_end = .);
	} > ROM
	.fini_array ALIGN(4) : {
		PROVIDE_HIDDEN (__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array))
		PROVIDE_HIDDEN (__fini_array_end = .);
	} > ROM
	.ARM.exidx ALIGN(4) : {
		__exidx_start = .;
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		__exidx_end = .;
	} > ROM
	__end_rodata_shared__std = .;
	__end_rodata_shared = .;
	. = ALIGN(4K);
	__limit_rodata_shared__std = .;
	__limit_rodata_shared = .;

	.ROM_align ALIGN(4) : {
		__ROM_align = .;
	} > ROM

	.bss_kernel_ffffffff_ffffffff (NOLOAD) : {
		__start_ram_kernel_ffffffff_ffffffff = .;
		__start_bss_kernel_ffffffff_ffffffff = .;
		__start_bss_kernel__ffffffff_ffffffff_ffffffff = .;
		*(.appheap) *(.lcd_vmem) 
		__end_bss_kernel__ffffffff_ffffffff_ffffffff = .;
		__end_bss_kernel_ffffffff_ffffffff = .;
	} > RAM
	. = ALIGN(4K);
	__limit_bss_kernel__ffffffff_ffffffff_ffffffff = .;
	__limit_bss_kernel_ffffffff_ffffffff = .;
	__limit_ram_kernel_ffffffff_ffffffff = .;

	.data_kernel ALIGN(4) : ALIGN(4) {
		__start_ram_kernel = .;
		__start_data_kernel = .;
		__start_data_kernel__std = .;
		kernel_cfg.o(.data) kernel_mem3.o(.data) libkernel.a(.data) syslog.o(.data) banner.o(.data) serial.o(.data) logtask.o(.data) fatfs_dri.o(.data) fatfs_syscall.o(.data) diskio.o(.data) ff.o(.data) mmcsd.o(.data) mmcsdlib.o(.data) mmcsd_dri.o(.data) mmcsd_proto.o(.data) mmcsd_rw.o(.data) soc_cache.o(.data) soc_edma.o(.data) edma.o(.data) uart.o(.data) cp15.o(.data) psc.o(.data) usb.o(.data) usbphyGS60.o(.data) cppi41dma.o(.data) evmAM1808_usb.o(.data) soc_interrupt.o(.data) bluetooth_dri.o(.data) libBTstack.a(.data) usbmsc_dri.o(.data) usbmsc_media_functions.o(.data) usb_dev_msc.o(.data) usb_msc_structs.o(.data) libusblib.a(.data) mbed_dri.o(.data) libmbed.a(.data) app.o(.data) apploader.o(.data) cli_main.o(.data) *(.data_kernel) 
		__end_data_kernel__std = .;
		__end_data_kernel = .;
	} > RAM AT > ROM
	__start_idata_kernel = LOADADDR(.data_kernel);
	. = ALIGN(4);
	__limit_data_kernel__std = .;
	__limit_data_kernel = .;

	.bss_kernel ALIGN(4) (NOLOAD) : {
		__start_bss_kernel = .;
		__start_bss_kernel__std = .;
		kernel_cfg.o(.bss COMMON) kernel_mem3.o(.bss COMMON) libkernel.a(.bss COMMON) syslog.o(.bss COMMON) banner.o(.bss COMMON) serial.o(.bss COMMON) logtask.o(.bss COMMON) fatfs_dri.o(.bss COMMON) fatfs_syscall.o(.bss COMMON) diskio.o(.bss COMMON) ff.o(.bss COMMON) mmcsd.o(.bss COMMON) mmcsdlib.o(.bss COMMON) mmcsd_dri.o(.bss COMMON) mmcsd_proto.o(.bss COMMON) mmcsd_rw.o(.bss COMMON) soc_cache.o(.bss COMMON) soc_edma.o(.bss COMMON) edma.o(.bss COMMON) uart.o(.bss COMMON) cp15.o(.bss COMMON) psc.o(.bss COMMON) usb.o(.bss COMMON) usbphyGS60.o(.bss COMMON) cppi41dma.o(.bss COMMON) evmAM1808_usb.o(.bss COMMON) soc_interrupt.o(.bss COMMON) bluetooth_dri.o(.bss COMMON) libBTstack.a(.bss COMMON) usbmsc_dri.o(.bss COMMON) usbmsc_media_functions.o(.bss COMMON) usb_dev_msc.o(.bss COMMON) usb_msc_structs.o(.bss COMMON) libusblib.a(.bss COMMON) mbed_dri.o(.bss COMMON) libmbed.a(.bss COMMON) app.o(.bss COMMON) apploader.o(.bss COMMON) cli_main.o(.bss COMMON) *(.bss.g_bytesWritten .bss.intStatus .bss.g_bytesRead .bss.gDMAflag .bss.g_sSCSICSW .bss.ulSOFDivide.* .bss.g_eUSBMode .bss.g_pucDataBufferIn .bss.g_bUSBTimerInitialized .bss.g_ulCurrentUSBTick .bss.g_ulUSBSOFCount .bss._PathLocale .bss.__nlocale_changed .bss.__mlocale_changed) *(.bss_kernel) 
		__end_bss_kernel__std = .;
		__end_bss_kernel = .;
	} > RAM AT > RAM
	. = ALIGN(4);
	__limit_bss_kernel__std = .;
	__limit_bss_kernel = .;

	.prsv_kernel ALIGN(4) (NOLOAD) : {
		__start_prsv_kernel = .;
		__start_prsv_kernel__std = .;
		kernel_cfg.o(.prsv) kernel_mem3.o(.prsv) libkernel.a(.prsv) syslog.o(.prsv) banner.o(.prsv) serial.o(.prsv) logtask.o(.prsv) fatfs_dri.o(.prsv) fatfs_syscall.o(.prsv) diskio.o(.prsv) ff.o(.prsv) mmcsd.o(.prsv) mmcsdlib.o(.prsv) mmcsd_dri.o(.prsv) mmcsd_proto.o(.prsv) mmcsd_rw.o(.prsv) soc_cache.o(.prsv) soc_edma.o(.prsv) edma.o(.prsv) uart.o(.prsv) cp15.o(.prsv) psc.o(.prsv) usb.o(.prsv) usbphyGS60.o(.prsv) cppi41dma.o(.prsv) evmAM1808_usb.o(.prsv) soc_interrupt.o(.prsv) bluetooth_dri.o(.prsv) libBTstack.a(.prsv) usbmsc_dri.o(.prsv) usbmsc_media_functions.o(.prsv) usb_dev_msc.o(.prsv) usb_msc_structs.o(.prsv) libusblib.a(.prsv) mbed_dri.o(.prsv) libmbed.a(.prsv) app.o(.prsv) apploader.o(.prsv) cli_main.o(.prsv) *(.prsv_kernel) 
		__end_prsv_kernel__std = .;
		__end_prsv_kernel = .;
	} > RAM
	. = ALIGN(4K);
	__limit_prsv_kernel__std = .;
	__limit_prsv_kernel = .;
	__limit_ram_kernel = .;

	.ustack_BRICK_BTN_TSK ALIGN(4) (NOLOAD) : {
		__start_ustack_BRICK_BTN_TSK = .;
		kernel_cfg.o(.ustack_BRICK_BTN_TSK) 
		__end_ustack_BRICK_BTN_TSK = .;
	} > RAM
	. = ALIGN(4K);
	__limit_ustack_BRICK_BTN_TSK = .;

	.data_TDOM_APP ALIGN(4) : ALIGN(4) {
		__start_ram_TDOM_APP = .;
		__start_data_TDOM_APP = .;
		__start_data_TDOM_APP__std = .;
		*(.data_TDOM_APP) 
		__end_data_TDOM_APP__std = .;
		__end_data_TDOM_APP = .;
	} > RAM AT > ROM
	__start_idata_TDOM_APP = LOADADDR(.data_TDOM_APP);
	. = ALIGN(4);
	__limit_data_TDOM_APP__std = .;
	__limit_data_TDOM_APP = .;

	.bss_TDOM_APP ALIGN(4) (NOLOAD) : {
		__start_bss_TDOM_APP = .;
		__start_bss_TDOM_APP__std = .;
		*(.bss_TDOM_APP) 
		__end_bss_TDOM_APP__std = .;
		__end_bss_TDOM_APP = .;
	} > RAM AT > RAM
	. = ALIGN(4);
	__limit_bss_TDOM_APP__std = .;
	__limit_bss_TDOM_APP = .;

	.prsv_TDOM_APP ALIGN(4) (NOLOAD) : {
		__start_prsv_TDOM_APP = .;
		__start_prsv_TDOM_APP__std = .;
		*(.prsv_TDOM_APP) 
		__end_prsv_TDOM_APP__std = .;
		__end_prsv_TDOM_APP = .;
	} > RAM
	. = ALIGN(4K);
	__limit_prsv_TDOM_APP__std = .;
	__limit_prsv_TDOM_APP = .;
	__limit_ram_TDOM_APP = .;

	.data_shared_0_ffffffff ALIGN(4) : ALIGN(4) {
		__start_ram_shared_0_ffffffff = .;
		__start_data_shared_0_ffffffff = .;
		__start_data_shared__0_ffffffff_0 = .;
		zmodem-toppers.o(.data) crc16.o(.data) crc32.o(.data) 
		__end_data_shared__0_ffffffff_0 = .;
		__end_data_shared_0_ffffffff = .;
	} > RAM AT > ROM
	__start_idata_shared_0_ffffffff = LOADADDR(.data_shared_0_ffffffff);
	. = ALIGN(4);
	__limit_data_shared__0_ffffffff_0 = .;
	__limit_data_shared_0_ffffffff = .;

	.bss_shared_0_ffffffff ALIGN(4) (NOLOAD) : {
		__start_bss_shared_0_ffffffff = .;
		__start_bss_shared__0_ffffffff_0 = .;
		zmodem-toppers.o(.bss COMMON) crc16.o(.bss COMMON) crc32.o(.bss COMMON) *(.app_text_mempool) 
		__end_bss_shared__0_ffffffff_0 = .;
		__end_bss_shared_0_ffffffff = .;
	} > RAM AT > RAM
	. = ALIGN(4);
	__limit_bss_shared__0_ffffffff_0 = .;
	__limit_bss_shared_0_ffffffff = .;

	.prsv_shared_0_ffffffff ALIGN(4) (NOLOAD) : {
		__start_prsv_shared_0_ffffffff = .;
		__start_prsv_shared__0_ffffffff_0 = .;
		zmodem-toppers.o(.prsv) crc16.o(.prsv) crc32.o(.prsv) 
		__end_prsv_shared__0_ffffffff_0 = .;
		__end_prsv_shared_0_ffffffff = .;
	} > RAM
	. = ALIGN(4K);
	__limit_prsv_shared__0_ffffffff_0 = .;
	__limit_prsv_shared_0_ffffffff = .;
	__limit_ram_shared_0_ffffffff = .;

	.data_kernel_0_ffffffff ALIGN(4) : ALIGN(4) {
		__start_srpw_all = .;
		__start_ram_kernel_0_ffffffff = .;
		__start_data_kernel_0_ffffffff = .;
		__start_data_kernel__0_ffffffff_0 = .;
		brick_dri.o(.data) analog_dri.o(.data) lcd_dri.o(.data) lcd_font.o(.data) motor_dri.o(.data) i2c_dri.o(.data) davinci_iic_dri.o(.data) uart_dri.o(.data) pru.o(.data) suart_utils.o(.data) suart_api.o(.data) pru_suart.o(.data) sound_dri.o(.data) ev3main.o(.data) driver_interface_bluetooth.o(.data) driver_interface_brick.o(.data) driver_interface_sound.o(.data) driver_interface_filesys.o(.data) dmloader.o(.data) elf32.o(.data) 
		__end_data_kernel__0_ffffffff_0 = .;
		__end_data_kernel_0_ffffffff = .;
	} > RAM AT > ROM
	__start_idata_kernel_0_ffffffff = LOADADDR(.data_kernel_0_ffffffff);
	. = ALIGN(4);
	__limit_data_kernel__0_ffffffff_0 = .;
	__limit_data_kernel_0_ffffffff = .;

	.bss_kernel_0_ffffffff ALIGN(4) (NOLOAD) : {
		__start_bss_kernel_0_ffffffff = .;
		__start_bss_kernel__0_ffffffff_0 = .;
		brick_dri.o(.bss COMMON) analog_dri.o(.bss COMMON) lcd_dri.o(.bss COMMON) lcd_font.o(.bss COMMON) motor_dri.o(.bss COMMON) i2c_dri.o(.bss COMMON) davinci_iic_dri.o(.bss COMMON) uart_dri.o(.bss COMMON) pru.o(.bss COMMON) suart_utils.o(.bss COMMON) suart_api.o(.bss COMMON) pru_suart.o(.bss COMMON) sound_dri.o(.bss COMMON) ev3main.o(.bss COMMON) driver_interface_bluetooth.o(.bss COMMON) driver_interface_brick.o(.bss COMMON) driver_interface_sound.o(.bss COMMON) driver_interface_filesys.o(.bss COMMON) dmloader.o(.bss COMMON) elf32.o(.bss COMMON) 
		__end_bss_kernel__0_ffffffff_0 = .;
		__end_bss_kernel_0_ffffffff = .;
	} > RAM AT > RAM
	. = ALIGN(4);
	__limit_bss_kernel__0_ffffffff_0 = .;
	__limit_bss_kernel_0_ffffffff = .;

	.prsv_kernel_0_ffffffff ALIGN(4) (NOLOAD) : {
		__start_prsv_kernel_0_ffffffff = .;
		__start_prsv_kernel__0_ffffffff_0 = .;
		brick_dri.o(.prsv) analog_dri.o(.prsv) lcd_dri.o(.prsv) lcd_font.o(.prsv) motor_dri.o(.prsv) i2c_dri.o(.prsv) davinci_iic_dri.o(.prsv) uart_dri.o(.prsv) pru.o(.prsv) suart_utils.o(.prsv) suart_api.o(.prsv) pru_suart.o(.prsv) sound_dri.o(.prsv) ev3main.o(.prsv) driver_interface_bluetooth.o(.prsv) driver_interface_brick.o(.prsv) driver_interface_sound.o(.prsv) driver_interface_filesys.o(.prsv) dmloader.o(.prsv) elf32.o(.prsv) 
		__end_prsv_kernel__0_ffffffff_0 = .;
		__end_prsv_kernel_0_ffffffff = .;
		__end_srpw_all = .;
	} > RAM
	. = ALIGN(4K);
	__limit_prsv_kernel__0_ffffffff_0 = .;
	__limit_prsv_kernel_0_ffffffff = .;
	__limit_ram_kernel_0_ffffffff = .;
	__limit_srpw_all = .;

	.data_shared ALIGN(4) : ALIGN(4) {
		__start_ram_shared = .;
		__start_data_shared = .;
		__start_data_shared__std = .;
		*(.data) *(.data.*) *(.data_shared) 
		__end_data_shared__std = .;
		__end_data_shared = .;
	} > RAM AT > ROM
	__start_idata_shared = LOADADDR(.data_shared);
	. = ALIGN(4);
	__limit_data_shared__std = .;
	__limit_data_shared = .;

	.bss_shared ALIGN(4) (NOLOAD) : {
		__start_bss_shared = .;
		__start_bss_shared__0 = .;
		*(.app_data_mempool) 
		__end_bss_shared__0 = .;
		. = ALIGN(4);
		__limit_bss_shared__0 = .;

		__start_bss_shared__std = .;
		*(.bss COMMON) *(.bss_shared) 
		__end_bss_shared__std = .;
		__end_bss_shared = .;
	} > RAM AT > RAM
	. = ALIGN(4);
	__limit_bss_shared__std = .;
	__limit_bss_shared = .;

	.prsv_shared ALIGN(4) (NOLOAD) : {
		__start_prsv_shared = .;
		__start_prsv_shared__std = .;
		*(.prsv) *(.prsv_shared) 
		__end_prsv_shared__std = .;
		__end_prsv_shared = .;
	} > RAM
	. = ALIGN(4K);
	__limit_prsv_shared__std = .;
	__limit_prsv_shared = .;
	__limit_ram_shared = .;

	.RAM_align ALIGN(4) : {
		__RAM_align = .;
	} > RAM

	/DISCARD/ : {
		*(.rel.dyn)
	}

	/* DWARF debug sections.
	Symbols in the DWARF debugging sections are relative to 
	the beginning of the section so we begin them at 0.  */

	/* DWARF 1 */
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }

	/* GNU DWARF 1 extensions */
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }

	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }

	/* DWARF 2 */
	.debug_info     0 : { *(.debug_info) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }
	.debug_ranges   0 : { *(.debug_ranges) }

	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }

}
