  /*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the MX6DL SabreSD Freescale board.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/arch/mx6.h>

 /* High Level Configuration Options */
#define CONFIG_ARMV7	/* This is armv7 Cortex-A9 CPU core */
#define CONFIG_MXC
#define CONFIG_MX6DL
#define CONFIG_MX6DL_DDR3
#define CONFIG_MX6DL_UDOO

 /* for DDR 64bit */
#define CONFIG_FLASH_HEADER
#define CONFIG_FLASH_HEADER_OFFSET 0x400
#define CONFIG_MX6_CLK32	   32768

/* CONFIG_DDR_SIZE:
		0 ->  512M,  bus size 32, active CS = 1 (256Mx2);
		1 ->  1Giga, bus size 32, active CS = 1 (512Mx2);
		2 ->  1Giga, bus size 64, active CS = 1 (256Mx4);
		3 ->  2Giga, bus size 64, active CS = 1 (512Mx4);
		4 ->  4Giga, bus size 64, active CS = 2 (512Mx8);
*/

/* CONFIG_DDR_TYPE:     
		0 ->  DDR3
		1 ->  LDDR3
*/
#define CONFIG_DDR_SIZE	DDR_SIZE_CONF
#define CONFIG_DDR_TYPE DDR_TYPE_CONF

#if(CONFIG_DDR_SIZE == 0)
	#define CONFIG_DDR_32BIT
#elif(CONFIG_DDR_SIZE > 0)
	#define CONFIG_DDR_64BIT
#endif


/* Disable secure boot feature in default, if you want to enable this
 * feature, please carefully read related documents, you may needs to
 * change u-boot.lds */
#undef CONFIG_SECURE_BOOT

#define CONFIG_SKIP_RELOCATE_UBOOT

#define CONFIG_ARCH_CPU_INIT
#undef CONFIG_ARCH_MMU /* disable MMU first */
#define CONFIG_L2_OFF  /* disable L2 cache first*/

#define CONFIG_MX6_HCLK_FREQ	24000000

#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_SYS_64BIT_VSPRINTF

#define BOARD_LATE_INIT

#define CONFIG_CMDLINE_TAG	/* enable passing of ATAGs */
#define CONFIG_SERIAL_TAG
#define CONFIG_REVISION_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_MXC_GPIO
#define CONFIG_BOARD_REVISION_ATAG
#define CONFIG_BOARD_REVISION_TAG

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(2 * 1024 * 1024)
/* size in bytes reserved for initial data */
#define CONFIG_SYS_GBL_DATA_SIZE	128

/*
 * Hardware drivers
 */
#define CONFIG_MXC_UART
#define CONFIG_UART_BASE_ADDR   UART2_BASE_ADDR


/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX		1
#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{9600, 19200, 38400, 57600, 115200}

/***********************************************************
 * Command definition
 ***********************************************************/

#include <config_cmd_default.h>

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_CMD_NET
#define CONFIG_NET_RETRY_COUNT  100
#define CONFIG_NET_MULTI 1
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_DNS

#define CONFIG_CMD_SPI
#define CONFIG_CMD_I2C
#define CONFIG_CMD_IMXOTP
#define CONFIG_CMD_UDOOCONFIG
#define CONFIG_TIMESTAMP
#define CONFIG_CMD_RTC
#define CONFIG_RTC_PCF2123
#define CONFIG_RTC_SNVS

#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_HUSH_PARSER		1 /* Use the HUSH parser */
#ifdef	CONFIG_SYS_HUSH_PARSER
#define	CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#endif

/* Enable below configure when supporting nand */
#define CONFIG_CMD_SF
#define CONFIG_CMD_MMC
#define CONFIG_CMD_ENV
#define CONFIG_CMD_REGUL

#define CONFIG_CMD_CLOCK
#define CONFIG_REF_CLK_FREQ CONFIG_MX6_HCLK_FREQ

#undef CONFIG_CMD_IMLS

#define CONFIG_CMD_IMX_DOWNLOAD_MODE

#define CONFIG_BOOTDELAY 3

#define CONFIG_PRIME	"FEC0"

#define CONFIG_INITRD_TAG

#if (CONFIG_DDR_SIZE == 1) || (CONFIG_DDR_SIZE == 2)
#define MEMORY_SIZE_PARAM	"mem=1024M"
#elif (CONFIG_DDR_SIZE == 3)
#define MEMORY_SIZE_PARAM	"mem=2048M"
#endif

#ifdef OS_TYPE_ANDROID
#define CONFIG_LOADADDR		0x10800000
#define CONFIG_RD_LOADADDR      0x11000000
#define	CONFIG_EXTRA_ENV_SETTINGS					\
		"netdev=eth0\0"						\
		"ethprime=FEC0\0"					\
		"fastboot_dev=mmc2\0"					\
		"bootcmd=booti mmc2\0"					\
		"splashimage=0x30000000\0"				\
		"splashpos=m,m\0"					\
		"lvds_num=1\0"                   \
		"bootargs=console=ttymxc1,115200 init=/init video=mxcfb0:dev=hdmi,1920x1080M@60,if=RGB24,bpp=32 video=mxcfb1:off video=mxcfb2:off fbmem=28M vmalloc=400M androidboot.console=ttymxc1 androidboot.hardware=freescale " MEMORY_SIZE_PARAM "\0"
#endif

#ifdef OS_TYPE_LINUX
#define CONFIG_LOADADDR		0x10800000
#define CONFIG_RD_LOADADDR      (0x10800000 + 0x300000)
#define	CONFIG_EXTRA_ENV_SETTINGS					\
	"uboot=u-boot.bin\0"			\
	"kernel=uImage\0"			\
	"bootargs=console=ttymxc1,115200 root=/dev/mmcblk0p1 rootwait rw fixrtc rootflags=barrier=1 arm_freq=996 video=mxcfb0:dev=hdmi,1920x1080M@60,if=RGB24 " MEMORY_SIZE_PARAM "\0"	\
	"bootcmd=mmc dev 0; ext2load mmc 0:1 10800000 /boot/uImage; bootm 10800000\0"
#endif 


#define CONFIG_ARP_TIMEOUT	200UL

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */

#define CONFIG_SYS_PROMPT		"MX6DL UDOO U-Boot > "

#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size */
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS	16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE /* Boot Argument Buffer Size */

#define CONFIG_SYS_MEMTEST_START	0x10000000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x10010000

#undef	CONFIG_SYS_CLKS_IN_HZ		/* everything, incl board info, in Hz */

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR

#define CONFIG_SYS_HZ			1000

#define CONFIG_CMDLINE_EDITING

#define CONFIG_FEC0_IOBASE	ENET_BASE_ADDR
#define CONFIG_FEC0_PINMUX	-1
#define CONFIG_FEC0_MIIBASE	-1
#define CONFIG_GET_FEC_MAC_ADDR_FROM_IIM
#define CONFIG_MXC_FEC
#define CONFIG_FEC0_PHY_ADDR		1
#define CONFIG_ETH_PRIME
#define CONFIG_RMII
#define CONFIG_CMD_MII
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_IPADDR			192.168.1.103
#define CONFIG_SERVERIP			192.168.1.101
#define CONFIG_NETMASK			255.255.255.0

/*
 * OCOTP Configs
 */
#ifdef CONFIG_CMD_IMXOTP
	#define CONFIG_IMX_OTP
	#define IMX_OTP_BASE			OCOTP_BASE_ADDR
	#define IMX_OTP_ADDR_MAX		0x7F
	#define IMX_OTP_DATA_ERROR_VAL	0xBADABADA
#endif

/*
 * I2C Configs
 */
#ifdef CONFIG_CMD_I2C
	#define CONFIG_HARD_I2C         1
	#define CONFIG_I2C_MXC          1
	#define CONFIG_SYS_I2C_PORT             I2C1_BASE_ADDR
	#define CONFIG_SYS_I2C_SPEED            100000
	#define CONFIG_SYS_I2C_SLAVE            0x8
	#define CONFIG_MX6_INTER_LDO_BYPASS	0
#endif

/*
 * SPI Configs
 */
#ifdef CONFIG_CMD_SF
	#define CONFIG_FSL_SF		1
	#define CONFIG_SPI_FLASH_IMX_M25PXX	1
	#define CONFIG_SPI_FLASH_CS	0
	#define CONFIG_IMX_ECSPI
	#define IMX_CSPI_VER_2_3	1
	#define MAX_SPI_BYTES		(64 * 4)
#endif

/* Regulator Configs */
#ifdef CONFIG_CMD_REGUL
	#define CONFIG_ANATOP_REGULATOR
	#define CONFIG_CORE_REGULATOR_NAME "vdd1p1"
	#define CONFIG_PERIPH_REGULATOR_NAME "vdd1p1"
#endif

/*
 * MMC Configs
 */
#ifdef CONFIG_CMD_MMC
	#define CONFIG_MMC
	#define CONFIG_GENERIC_MMC
	#define CONFIG_IMX_MMC
	#define CONFIG_SYS_FSL_USDHC_NUM        4
	#define CONFIG_SYS_FSL_ESDHC_ADDR       0
	#define CONFIG_SYS_MMC_ENV_DEV  2
	#define CONFIG_DOS_PARTITION	1
	#define CONFIG_CMD_FAT		1
	#define CONFIG_CMD_EXT2		1

	/* detect whether SD1, 2, 3, or 4 is boot device */
	#define CONFIG_DYNAMIC_MMC_DEVNO

	/* SD3 and SD4 are 8 bit */
	#define CONFIG_MMC_8BIT_PORTS		0xC
	/* Setup target delay in DDR mode for each SD port */
	#define CONFIG_GET_DDR_TARGET_DELAY
#endif

/*
 * GPMI Nand Configs
 */
/* #define CONFIG_CMD_NAND */

#ifdef CONFIG_CMD_NAND
	#define CONFIG_NAND_GPMI
	#define CONFIG_GPMI_NFC_SWAP_BLOCK_MARK
	#define CONFIG_GPMI_NFC_V2

	#define CONFIG_GPMI_REG_BASE	GPMI_BASE_ADDR
	#define CONFIG_BCH_REG_BASE	BCH_BASE_ADDR

	#define NAND_MAX_CHIPS		8
	#define CONFIG_SYS_NAND_BASE		0x40000000
	#define CONFIG_SYS_MAX_NAND_DEVICE	1

	/* NAND is the unique module invoke APBH-DMA */
	#define CONFIG_APBH_DMA
	#define CONFIG_APBH_DMA_V2
	#define CONFIG_MXS_DMA_REG_BASE	ABPHDMA_BASE_ADDR
#endif

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128 * 1024)	/* regular stack */

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
 
/* RAM Settings*/
/* DDR_TYPE: 0 ->  512M,  bus size 32, active CS = 1 (256Mx2);
	     1 ->  1Giga, bus size 32, active CS = 1 (512Mx2);
	     2 ->  1Giga, bus size 64, active CS = 1 (256Mx4) only for DL;
             3 ->  2Giga, bus size 64, active CS = 1 (512Mx4) only for DL;
             4 ->  4Giga, bus size 64, active CS = 2 (512Mx8) only for DL;
*/

#define CONFIG_NR_DRAM_BANKS	1
#define PHYS_SDRAM_1		CSD0_DDR_BASE_ADDR

#if (CONFIG_DDR_SIZE == 0)
#define PHYS_SDRAM_1_SIZE	(512u * 1024 * 1024)
#endif

#if (CONFIG_DDR_SIZE == 1 || CONFIG_DDR_SIZE == 2)
#define PHYS_SDRAM_1_SIZE	(1u * 1024 * 1024 * 1024)
#endif

#if (CONFIG_DDR_SIZE == 3)
#define PHYS_SDRAM_1_SIZE	(2u * 1024 * 1024 * 1024)
#endif

#if (CONFIG_DDR_SIZE == 4)
#define PHYS_SDRAM_1_SIZE	(4u * 1024 * 1024 * 1024 - 256u * 1024 * 1024)
#endif

#define iomem_valid_addr(addr, size) \
	(addr >= PHYS_SDRAM_1 && addr <= (PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_SYS_NO_FLASH

#ifdef ENV_MMC
	#define CONFIG_FSL_ENV_IN_MMC
#elif defined(ENV_SPI)
	#define CONFIG_FSL_ENV_IN_SF
#else
	#define CONFIG_FSL_ENV_IN_MMC
#endif

#define CONFIG_ENV_SECT_SIZE    (8 * 1024)
#define CONFIG_ENV_SIZE         CONFIG_ENV_SECT_SIZE

#if defined(CONFIG_FSL_ENV_IN_NAND)
	#define CONFIG_ENV_IS_IN_NAND 1
	#define CONFIG_ENV_OFFSET	0x100000
#elif defined(CONFIG_FSL_ENV_IN_MMC)
	#define CONFIG_ENV_IS_IN_MMC	1
	#define CONFIG_ENV_OFFSET	(768 * 1024)
#elif defined(CONFIG_FSL_ENV_IN_SF)
	#define CONFIG_ENV_IS_IN_SPI_FLASH	1
	#define CONFIG_ENV_SPI_CS		1
	#define CONFIG_ENV_OFFSET       (768 * 1024)
#else
	#define CONFIG_ENV_IS_NOWHERE	1
#endif

/* #define CONFIG_SPLASH_SCREEN */
/* #define CONFIG_MXC_EPDC */

/*
 * SPLASH SCREEN Configs
 */
//#define CONFIG_SPLASH_SCREEN
#ifdef CONFIG_SPLASH_SCREEN
	/*
	 * Framebuffer and LCD
	 */
	#define CONFIG_LCD
	#define CONFIG_FB_BASE				(TEXT_BASE + 0x300000)
	#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#ifdef CONFIG_MXC_EPDC
	#undef LCD_TEST_PATTERN
	/* #define CONFIG_SPLASH_IS_IN_MMC			1 */
	#define LCD_BPP					LCD_MONOCHROME
	/* #define CONFIG_SPLASH_SCREEN_ALIGN		1 */

	#define CONFIG_WORKING_BUF_ADDR			(TEXT_BASE + 0x100000)
	#define CONFIG_WAVEFORM_BUF_ADDR		(TEXT_BASE + 0x200000)
	#define CONFIG_WAVEFORM_FILE_OFFSET		0x600000
	#define CONFIG_WAVEFORM_FILE_SIZE		0xF0A00
	#define CONFIG_WAVEFORM_FILE_IN_MMC

#ifdef CONFIG_SPLASH_IS_IN_MMC
	#define CONFIG_SPLASH_IMG_OFFSET		0x4c000
	#define CONFIG_SPLASH_IMG_SIZE			0x19000
#endif
#else /* !CONFIG_MXC_EPDC */
	#define CONFIG_IPU_V3H
	#define CONFIG_VIDEO_MX5
	#define CONFIG_IPU_CLKRATE	260000000
	#define CONFIG_SYS_CONSOLE_ENV_OVERWRITE
	#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
	#define LCD_BPP		LCD_COLOR16
	#define CONFIG_CMD_BMP
	#define CONFIG_BMP_8BPP
	#define CONFIG_SPLASH_SCREEN_ALIGN
	#define CONFIG_SYS_WHITE_ON_BLACK

	#define CONFIG_IMX_PWM
	#define IMX_PWM1_BASE    PWM1_BASE_ADDR
	#define IMX_PWM2_BASE    PWM2_BASE_ADDR
#endif
#endif /* CONFIG_SPLASH_SCREEN */
#endif				/* __CONFIG_H */

#define CONFIG_USB_DEVICE
#define CONFIG_IMX_UDC		       1
#define CONFIG_FASTBOOT		       1
#define CONFIG_FASTBOOT_STORAGE_EMMC_SATA
#define CONFIG_FASTBOOT_VENDOR_ID      0x18d1
#define CONFIG_FASTBOOT_PRODUCT_ID     0x0d02
#define CONFIG_FASTBOOT_BCD_DEVICE     0x311
#define CONFIG_FASTBOOT_MANUFACTURER_STR  "Freescale"
#define CONFIG_FASTBOOT_PRODUCT_NAME_STR "i.mx6dl UDOO SmartDevice"
#define CONFIG_FASTBOOT_INTERFACE_STR	 "Android fastboot"
#define CONFIG_FASTBOOT_CONFIGURATION_STR  "Android fastboot"
#define CONFIG_FASTBOOT_SERIAL_NUM	"12345"
#define CONFIG_FASTBOOT_SATA_NO		 0

/*  For system.img growing up more than 256MB, more buffer needs
*   to receive the system.img*/
#define CONFIG_FASTBOOT_TRANSFER_BUF	0x2c000000
#define CONFIG_FASTBOOT_TRANSFER_BUF_SIZE 0x14000000 /* 320M byte */


#define CONFIG_CMD_BOOTI
//#define CONFIG_ANDROID_RECOVERY
/* which mmc bus is your main storage ? */
#define CONFIG_ANDROID_MAIN_MMC_BUS 3

#define CONFIG_ANDROID_BOOT_PARTITION_MMC 1
#define CONFIG_ANDROID_SYSTEM_PARTITION_MMC 5
#define CONFIG_ANDROID_RECOVERY_PARTITION_MMC 2
#define CONFIG_ANDROID_CACHE_PARTITION_MMC 6


#define CONFIG_ANDROID_RECOVERY_BOOTARGS_MMC NULL
#define CONFIG_ANDROID_RECOVERY_BOOTCMD_MMC  \
	"booti mmc2 recovery"
#define CONFIG_ANDROID_RECOVERY_CMD_FILE "/recovery/command"
#define CONFIG_INITRD_TAG
