/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the MX6Q Sabre Lite2 Freescale board.
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
#define CONFIG_MX6Q
#define CONFIG_MX6Q_SABRESD
#define CONFIG_FLASH_HEADER
#define CONFIG_FLASH_HEADER_OFFSET 0x400
#define CONFIG_MX6_CLK32	   32768

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

/*config the output device of display
  配置输出显示设备
  #define CONFIG_UBOOT_KERNEL_LVDS lvds屏幕输出
  #define CONFIG_UBOOT_KERNEL_MIPI mipi屏幕输出
  #define CONFIG_UBOOT_KERNEL_LCD  lcd 屏幕输出
 */
#ifndef CONFIG_UBOOT_KERNEL
   #define CONFIG_UBOOT_KERNEL_LVDS
   //#define CONFIG_UBOOT_KERNEL_MIPI
   //#define CONFIG_UBOOT_KERNEL_LCD
#endif


#define LVDS_MODE	 "ldb_mode=ldb=sin0\0"
#if defined(CONFIG_UBOOT_KERNEL_LVDS)
   #define MXC_FB0          "mxcfb0=video=mxcfb0:dev=ldb,LDB-WXGA,if=RGB24,bpp=32\0"
   #define MXC_FB1          "mxcfb1=video=mxcfb1:dev=hdmi,1920x1080M@60,if=RGB24,bpp=32\0"
#elif defined(CONFIG_UBOOT_KERNEL_MIPI)
   #define MXC_FB0          "mxcfb0=video=mxcfb0:dev=mipi_dsi,TRULY-EK79007-WVGA,if=RGB24,bpp=32\0"
   #define MXC_FB1          "mxcfb1=video=mxcfb1:dev=hdmi,1920x1080M@60,if=RGB24,bpp=32\0"
#elif defined(CONFIG_UBOOT_KERNEL_LCD)
   #define MXC_FB0          "mxcfb0=video=mxcfb0:dev=lcd,AT070-WVGA,if=RGB24,bpp=32\0"
   #define MXC_FB1          "mxcfb1=video=mxcfb1:dev=hdmi,1920x1080M@60,if=RGB24,bpp=32\0"
//#define MXC_FB0          "mxcfb0=video=mxcfb0:dev=mipi_dsi,TRULY-EK79007-WVGA,if=RGB24,bpp=32\0"
//#define MXC_FB0          "mxcfb0=video=mxcfb0:dev=lcd,AT070-WVGA,if=RGB24,bpp=32\0"
//#define MXC_FB0          "mxcfb0=video=mxcfb0:dev=ldb,LDB-WXGA,if=RGB24,bpp=32\0"
//#define MXC_FB0          "mxcfb0=video=mxcfb0:dev=hdmi,1920x1080M@60,if=RGB24,bpp=32\0"
//#define MXC_FB1          "mxcfb1=video=mxcfb1:dev=hdmi,1920x1080M@60,if=RGB24,bpp=32\0"
//#define MXC_FB1          "mxcfb1=video=mxcfb1:dev=lcd,AT070-WVGA,if=RGB24,bpp=32\0"
//#define MXC_FB1          "mxcfb1=video=mxcfb1:dev=ldb,LDB-WXGA,if=RGB24,bpp=32\0"
//#define MXC_FB1          "mxcfb1=video=mxcfb1:dev=mipi_dsi,TRULY-EK79007-WCGA,if=RGB24,bpp=32\0"
#endif

#define DEFAULT_CODEC 	 "codec_name=audio_codec=tef6635\0"

#define ETHADDR		"ethaddr=1E:ED:19:27:1A:B3\0"
#define FEC_MAC		"fec_mac=1E:ED:19:27:1A:B3\0"
#define NFS_ROOT	"nfsroot=/nfs_rootfs\0"


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
#define CONFIG_UART_BASE_ADDR   UART1_BASE_ADDR

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

/* Enable below configure when supporting nand */
#define CONFIG_CMD_SF
#define CONFIG_CMD_MMC
#define CONFIG_CMD_ENV
#define CONFIG_CMD_REGUL


#define CONFIG_CMD_CLOCK
#define CONFIG_REF_CLK_FREQ CONFIG_MX6_HCLK_FREQ

/* #define CONFIG_CMD_SATA */
#undef CONFIG_CMD_IMLS

#define CONFIG_CMD_IMX_DOWNLOAD_MODE

#define CONFIG_BOOTDELAY   3

#define CONFIG_PRIME	"FEC0"

#define CONFIG_LOADADDR		0x10800000	/* loadaddr env var */
#define CONFIG_RD_LOADADDR	(0x1300000)

#undef CONFIG_EXTRA_ENV_SETTINGS
#define	CONFIG_EXTRA_ENV_SETTINGS					\
		"netdev=eth0\0"						\
	 	LVDS_MODE						\
		MXC_FB0       						\
		MXC_FB1       						\
 		DEFAULT_CODEC  						\
 		ETHADDR  						\
 		FEC_MAC  						\
 		NFS_ROOT  						\
		"calibrate=Y\0"					\
		"ethprime=FEC0\0"					\
        "splashimage=0x30000000\0"              \
        "splashpos=m,m\0"                   \
		"uboot=u-boot.bin\0"			\
		"kernel=uImage\0"				\
		"nfsroot=/opt/eldk/arm\0"				\
		"bootargs_base=setenv bootargs console=ttymxc0,115200 ${mxcfb0} ${mxcfb1} ${ldb_mode} ${codec_name} video=mxcfb2:off calibrate=${calibrate} fec_mac=${fec_mac}\0"\
		"bootargs_nfs=setenv bootargs ${bootargs} root=/dev/nfs "\
			"ip=${ipaddr} nfsroot=${serverip}:${nfsroot},v3,tcp\0"\
		"bootcmd_net=run bootargs_base bootargs_nfs; "		\
			"tftpboot ${loadaddr} ${kernel}; bootm\0"	\
		"bootargs_mmc=setenv bootargs ${bootargs} ip=none "     \
			"root=/dev/mmcblk0p1 rootwait\0"                \
		"bootcmd_mmc=run bootargs_base bootargs_mmc; "   \
		"mmc dev 3; "	\
		"mmc read ${loadaddr} 0x800 0x2900; bootm\0"	\
		"bootcmd=run bootcmd_mmc\0"                      \
		"wdtenable=disable\0"        


#define CONFIG_ARP_TIMEOUT	200UL

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_PROMPT		"MX6Q SABRESD U-Boot > "
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
#define CONFIG_FEC0_PHY_ADDR		0xFF
#define CONFIG_DISCOVER_PHY
#define CONFIG_ETH_PRIME
#define CONFIG_RMII
#define CONFIG_CMD_MII
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_IPADDR			192.168.2.85
#define CONFIG_SERVERIP			192.168.2.51
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
	#define CONFIG_SYS_I2C_PORT             I2C2_BASE_ADDR
	#define CONFIG_SYS_I2C_SPEED            100000
	#define CONFIG_SYS_I2C_SLAVE            0x8
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
	#define CONFIG_MMC_8BIT_PORTS   0xC
	/* Setup target delay in DDR mode for each SD port */
	#define CONFIG_GET_DDR_TARGET_DELAY
#endif

/*
 * SATA Configs
 */
#ifdef CONFIG_CMD_SATA
	#define CONFIG_DWC_AHSATA
	#define CONFIG_SYS_SATA_MAX_DEVICE	1
	#define CONFIG_DWC_AHSATA_PORT_ID	0
	#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
	#define CONFIG_LBA48
	#define CONFIG_LIBATA

	#define CONFIG_DOS_PARTITION	1
	#define CONFIG_CMD_FAT		1
	#define CONFIG_CMD_EXT2		1
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
#define CONFIG_NR_DRAM_BANKS	1
#define PHYS_SDRAM_1		CSD0_DDR_BASE_ADDR
#define PHYS_SDRAM_1_SIZE	(1u * 1024 * 1024 * 1024)
#define iomem_valid_addr(addr, size) \
	(addr >= PHYS_SDRAM_1 && addr <= (PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE))

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
#define CONFIG_SYS_NO_FLASH

/* Monitor at beginning of flash */
#define CONFIG_FSL_ENV_IN_MMC
/* #define CONFIG_FSL_ENV_IN_NAND */
/* #define CONFIG_FSL_ENV_IN_SATA */

#define CONFIG_ENV_SECT_SIZE    (8 * 1024)
#define CONFIG_ENV_SIZE         CONFIG_ENV_SECT_SIZE

#if defined(CONFIG_FSL_ENV_IN_NAND)
	#define CONFIG_ENV_IS_IN_NAND 1
	#define CONFIG_ENV_OFFSET	0x100000
#elif defined(CONFIG_FSL_ENV_IN_MMC)
	#define CONFIG_ENV_IS_IN_MMC	1
	#define CONFIG_ENV_OFFSET	(768 * 1024)
#elif defined(CONFIG_FSL_ENV_IN_SATA)
	#define CONFIG_ENV_IS_IN_SATA   1
	#define CONFIG_SATA_ENV_DEV     0
	#define CONFIG_ENV_OFFSET       (768 * 1024)
#elif defined(CONFIG_FSL_ENV_IN_SF)
	#define CONFIG_ENV_IS_IN_SPI_FLASH	1
	#define CONFIG_ENV_SPI_CS		1
	#define CONFIG_ENV_OFFSET       (768 * 1024)
#else
	#define CONFIG_ENV_IS_NOWHERE	1
#endif

#define UBOOT_LOGO_BMP_ADDR 0x00900000


/*
 Note:
 if you define CONFIG_SPLASH_SCREEN the uboot use mipi screen to display the logo,
 but if you don't have macro define CONFIG_SPLASH_SCREEN,the uboot use another device to 
 display the logo.
 注意：
     如果使用mipi设备显示logo,就定义宏变量CONFIG_SPLASH_SCREEN,如果使用其他的例如hdmi,lvds,lcd显示设备那么就不定义宏变量CONFIG_SPLASH_SCREEN.
 */

#if defined(CONFIG_UBOOT_KERNEL_MIPI)
    #define CONFIG_SPLASH_SCREEN 
#endif

#ifdef CONFIG_SPLASH_SCREEN
	/*
	 * Framebuffer and LCD
	 */
	#define CONFIG_LCD
	#define CONFIG_IPU_V3H
	#define CONFIG_VIDEO_MX5
	#define CONFIG_IPU_CLKRATE	260000000
	#define CONFIG_SYS_CONSOLE_ENV_OVERWRITE
	#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
	#define CONFIG_SYS_CONSOLE_IS_IN_ENV
	#define LCD_BPP		LCD_COLOR16
	#define CONFIG_CMD_BMP
	#define CONFIG_BMP_16BPP
	#define CONFIG_FB_BASE	(TEXT_BASE + 0x300000)
	#define CONFIG_SPLASH_SCREEN_ALIGN
	#define CONFIG_SYS_WHITE_ON_BLACK
	
	#define MIPI_DSI 1
								//without this macro, the DI root clock is IPU internal clock.
#endif


	#define CONFIG_IMX_PWM
	#define IMX_PWM1_BASE    PWM1_BASE_ADDR
	#define IMX_PWM2_BASE    PWM2_BASE_ADDR
	#define IMX_PWM3_BASE	 PWM3_BASE_ADDR
	#define IMX_PWM4_BASE	 PWM4_BASE_ADDR

#endif

	


#ifndef CONFIG_SPLASH_SCREEN
#define CONFIG_UBOOT_LOGO_ENABLE

#ifdef CONFIG_UBOOT_LOGO_ENABLE

#if defined(CONFIG_UBOOT_KERNEL_LCD)
	#define IPU_OUTPUT_MODE_LCD
#elif defined(CONFIG_UBOOT_KERNEL_LVDS)
	#define IPU_OUTPUT_MODE_LVDS
#elif defined(CONFIG_UBOOT_KERNEL_HDMI)
	#define IPU_OUTPUT_MODE_HDMI
#endif

	#define CONFIG_FB_BASE	(TEXT_BASE + 0x300000)
	#define CONFIG_IMX_PWM
	#define IMX_PWM1_BASE	 PWM1_BASE_ADDR
	#define IMX_PWM2_BASE	 PWM2_BASE_ADDR
	#define IMX_PWM3_BASE	 PWM3_BASE_ADDR

#ifdef IPU_OUTPUT_MODE_HDMI
/*
	// For HDMI, 1280*720 resolution
	#define DISPLAY_WIDTH	1280
	#define DISPLAY_HEIGHT	720
	#define DISPLAY_BPP		32
	#define DISPLAY_IF_BPP	24  // RGB24 interface

	#define DISPLAY_HSYNC_START	220
	#define DISPLAY_HSYNC_END		110
	#define DISPLAY_HSYNC_WIDTH	40

	#define DISPLAY_VSYNC_START	20
	#define DISPLAY_VSYNC_END		5
	#define DISPLAY_VSYNC_WIDTH	5

	#define DISPLAY_PIX_CLOCK	74250000  //(DISPLAY_HSYNC_START + DISPLAY_HSYNC_END + DISPLAY_HSYNC_WIDTH + DISPLAY_WIDTH) * (DISPLAY_VSYNC_START + DISPLAY_VSYNC_END + DISPLAY_VSYNC_WIDTH + DISPLAY_HEIGHT) * refresh rate (60Hz)
*/
	// For HDMI, 1920*1080 resolution
	#define DISPLAY_WIDTH	1920
	#define DISPLAY_HEIGHT	1080
	#define DISPLAY_BPP		32
	#define DISPLAY_IF_BPP	24  // RGB24 interface

	#define DISPLAY_HSYNC_START	148
	#define DISPLAY_HSYNC_END		88
	#define DISPLAY_HSYNC_WIDTH	44

	#define DISPLAY_VSYNC_START	36
	#define DISPLAY_VSYNC_END		4
	#define DISPLAY_VSYNC_WIDTH	5

	#define DISPLAY_PIX_CLOCK	148500000  //(DISPLAY_HSYNC_START + DISPLAY_HSYNC_END + DISPLAY_HSYNC_WIDTH + DISPLAY_WIDTH) * (DISPLAY_VSYNC_START + DISPLAY_VSYNC_END + DISPLAY_VSYNC_WIDTH + DISPLAY_HEIGHT) * refresh rate (60Hz)

	#define DISPLAY_VSYNC_POLARITY			1
	#define DISPLAY_HSYNC_POLARITY			1
	#define DISPLAY_CLOCK_POLARITY			0
	#define DISPLAY_DATA_POLARITY				0
	#define DISPLAY_DATA_ENABLE_POLARITY		1

	#define IPU_NUM			2  // 1 for IPU1, 2 for IPU2.
	#define DI_NUM			0  // 0 for DI0, 1 for DI1.
	#define DI_CLOCK_EXTERNAL_MODE  //When clock external mode was defined, the DI clock root will be PLL5, 
								//without this macro, the DI root clock is IPU internal clock.
	#define CONFIG_IMX_HDMI
#endif

#ifdef IPU_OUTPUT_MODE_LVDS
	// For LVDS, 1280*800 resolution
	#define DISPLAY_WIDTH   1280
	#define DISPLAY_HEIGHT	800
	#define DISPLAY_BPP		16
	#define DISPLAY_IF_BPP	24  // RGB888 interface

	#define DISPLAY_HSYNC_START 48	
	#define DISPLAY_HSYNC_END	80	
	#define DISPLAY_HSYNC_WIDTH	32

	#define DISPLAY_VSYNC_START 9	
	#define DISPLAY_VSYNC_END	10
	#define DISPLAY_VSYNC_WIDTH 4	

	#define DISPLAY_PIX_CLOCK	71107200  //(DISPLAY_HSYNC_START + DISPLAY_HSYNC_END + DISPLAY_HSYNC_WIDTH + DISPLAY_WIDTH) * (DISPLAY_VSYNC_START + DISPLAY_VSYNC_END + DISPLAY_VSYNC_WIDTH + DISPLAY_HEIGHT) * refresh rate (60Hz)
/*
	// For LVDS, 1920*1080 resolution, dual channel
	#define DISPLAY_WIDTH	1920
	#define DISPLAY_HEIGHT	1080
	#define DISPLAY_BPP		32
	#define DISPLAY_IF_BPP	24	// RGB24 interface

	#define DISPLAY_HSYNC_START	100
	#define DISPLAY_HSYNC_END		40
	#define DISPLAY_HSYNC_WIDTH	10

	#define DISPLAY_VSYNC_START	20
	#define DISPLAY_VSYNC_END		3
	#define DISPLAY_VSYNC_WIDTH	2

	#define DISPLAY_PIX_CLOCK		135000000  //(DISPLAY_HSYNC_START + DISPLAY_HSYNC_END + DISPLAY_HSYNC_WIDTH + DISPLAY_WIDTH) * (DISPLAY_VSYNC_START + DISPLAY_VSYNC_END + DISPLAY_VSYNC_WIDTH + DISPLAY_HEIGHT) * refresh rate (60Hz)
	#define LVDS_SPLIT_MODE  // For dual channel split mode.
*/
	#define DISPLAY_VSYNC_POLARITY			1
	#define DISPLAY_HSYNC_POLARITY			1
	#define DISPLAY_CLOCK_POLARITY			1
	#define DISPLAY_DATA_POLARITY				0
	#define DISPLAY_DATA_ENABLE_POLARITY		1

	#define IPU_NUM			1  // 1 for IPU1, 2 for IPU2.
	#define DI_NUM			0  // 0 for DI0, 1 for DI1.
	#define LVDS_PORT		0  // 0 for LVDS0, 1 for LVDS1.
	#define DI_CLOCK_EXTERNAL_MODE  //When clock external mode was defined, the DI clock root will be PLL3 PFD1, 
								//without this macro, the DI root clock is IPU internal clock.
#endif

#ifdef IPU_OUTPUT_MODE_LCD
	//For LCD, 800*480 resolution
	#define DISPLAY_WIDTH	800
	#define DISPLAY_HEIGHT	480
	#define DISPLAY_BPP		16	
	#define DISPLAY_IF_BPP	24  // RGB565 interface

	#define DISPLAY_HSYNC_START	40
	#define DISPLAY_HSYNC_END		60
	#define DISPLAY_HSYNC_WIDTH	20

	#define DISPLAY_VSYNC_START	10
	#define DISPLAY_VSYNC_END		10
	#define DISPLAY_VSYNC_WIDTH	10

	#define DISPLAY_PIX_CLOCK	27000000  //(DISPLAY_HSYNC_START + DISPLAY_HSYNC_END + DISPLAY_HSYNC_WIDTH + DISPLAY_WIDTH) * (DISPLAY_VSYNC_START + DISPLAY_VSYNC_END + DISPLAY_VSYNC_WIDTH + DISPLAY_HEIGHT) * refresh rate (60Hz)

	#define DISPLAY_VSYNC_POLARITY			1
	#define DISPLAY_HSYNC_POLARITY			1
	#define DISPLAY_CLOCK_POLARITY			1
	#define DISPLAY_DATA_POLARITY				0
	#define DISPLAY_DATA_ENABLE_POLARITY		1

	#define IPU_NUM			1  // 1 for IPU1, 2 for IPU2.
	#define DI_NUM			0  // 0 for DI0, 1 for DI1.
	#define DI_CLOCK_EXTERNAL_MODE  //When clock external mode was defined, the DI clock root will be PLL5, 
								//without this macro, the DI root clock is IPU internal clock.
#endif  //CONFIG_UBOOT_LOGO_ENABLE
#endif  //CONFIG_SPLASH_SCREEN

#endif				/* __CONFIG_H */
