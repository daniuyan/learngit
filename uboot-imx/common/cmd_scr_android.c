
#include <common.h>
#include <net.h>
#include <command.h>
//#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <config_cmd_default.h>

int mxcfb0()
{
	char c;

	do
	{
		printf("mxcfb0 current screen is `%s`\n",getenv("screensize0"));
		printf("AAAxAAA-B means Binch screen with AAAxAAA pixels\n");
		printf("---------------------screen type----------------------\n");
		printf("0 -- exit to upper menu\n");
        	printf("1 -- 480x272-4-LCD\n");
		printf("2 -- 800x480-7-LCD\n");
		printf("3 -- 1024x600-7-mipi\n");
		printf("4 -- 1280x800-10-LVDS\n");
	    	printf("5 -- 1920x1080M@60-HDMI\n");
	    	printf("6 -- 1280x720M@60-HDMI\n");
		printf("7 -- 1024x768-X-LVDS\n");
		printf("8 -- 1920x1080-X-LVDS\n");
		printf("9 -- off\n");
		printf("------------------------------------------------------\n");

	HERE:
		printf(":");
		c = getc();

		printf("%c\n",c);
		
		switch(c)
		{
		case '0':
			return 0;
			break;
		case '1':
			setenv("mxcfb0","video=mxcfb0:dev=lcd,NHD-4.3-ATXI,if=RGB24,bpp=32");
			setenv("screensize0","480x272-4-LCD");
			break;
		case '2':
			setenv("mxcfb0","video=mxcfb0:dev=lcd,AT070-WVGA,if=RGB24,bpp=32");
			setenv("screensize0","800x480-7-LCD");
		    	break;
		case '3':
			setenv("mxcfb0","video=mxcfb0:dev=mipi_dsi,TRULY-EK79007-WVGA,if=RGB24,bpp=32");
			setenv("screensize0","1024x600-7-mipi");
		    	break;
		case '4':
			setenv("mxcfb0","video=mxcfb0:dev=ldb,LDB-WXGA,if=RGB24,bpp=32");
			setenv("screensize0","1280x800-10-LVDS");
			break;
		case '5':
			setenv("mxcfb0","video=mxcfb0:dev=hdmi,1920x1080@60,if=RGB24,bpp=32");
			setenv("screensize0","1920x1080M@60-HDMI");
			break;
		case '6':
			setenv("mxcfb0","video=mxcfb0:dev=hdmi,1280x720M@60,if=RGB24,bpp=32");
			setenv("screensize0","1280x720M@60-HDMI");
			break;
		case '7':
			setenv("mxcfb0","video=mxcfb0:dev=ldb,LDB-XGA,if=RGB24,bpp=32");
			setenv("screensize0","1024x768-X-LVDS");
			break;
		case '8':
			setenv("mxcfb0","video=mxcfb0:dev=ldb,LDB-1080P60,if=RGB24,bpp=32");
			setenv("screensize0","1920x1080-X-LVDS");
			break;
		case '9':
			setenv("mxcfb0","video=mxcfb0:off");
			setenv("screensize0","off");
			break;
        default:
			printf("incorrect number\n");
			goto HERE;
		}	

		if(saveenv())
			printf("something error occured, please check the nand device!");

	}while(1);
}

int mxcfb1()
{
	char c;

	do
	{
		printf("mxcfb1 current screen is `%s`\n",getenv("screensize1"));
		printf("AAAxAAA-B means Binch screen with AAAxAAA pixels\n");
		printf("---------------------screen type----------------------\n");
		printf("0 -- exit to upper menu\n");
        	printf("1 -- 480x272-4-LCD\n");
		printf("2 -- 800x480-7-LCD\n");
		printf("3 -- 1024x600-7-mipi\n");
		printf("4 -- 1280x800-10-LVDS\n");
	    	printf("5 -- 1920x1080M@60-HDMI\n");
	    	printf("6 -- 1280x720M@60-HDMI\n");
		printf("7 -- 1024x768-X-LVDS\n");
		printf("8 -- 1920x1080-X-LVDS\n");
		printf("9 -- off\n");
		printf("------------------------------------------------------\n");

	HERE:
		printf(":");
		c = getc();

		printf("%c\n",c);
		
		switch(c)
		{
		case '0':
			return 0;
			break;
		case '1':
			setenv("mxcfb1","video=mxcfb1:dev=lcd,NHD-4.3-ATXI,if=RGB24,bpp=32");
			setenv("screensize1","480x272-4-LCD");
			break;
		case '2':
			setenv("mxcfb1","video=mxcfb1:dev=lcd,AT070-WVGA,if=RGB24,bpp=32");
			setenv("screensize1","800x480-7-LCD");
		    	break;
		case '3':
			setenv("mxcfb1","video=mxcfb1:dev=mipi_dsi,TRULY-EK79007-WVGA,if=RGB24,bpp=32");
			setenv("screensize1","1024x600-7-mipi");
		    	break;
		case '4':
			setenv("mxcfb1","video=mxcfb1:dev=ldb,LDB-WXGA,if=RGB24,bpp=32");
			setenv("screensize1","1280x800-10-LVDS");
			break;
		case '5':
			setenv("mxcfb1","video=mxcfb1:dev=hdmi,1920x1080@60,if=RGB24,bpp=32");
			setenv("screensize1","1920x1080M@60-HDMI");
			break;
		case '6':
			setenv("mxcfb1","video=mxcfb1:dev=hdmi,1280x720M@60,if=RGB24,bpp=32");
			setenv("screensize1","1280x720M@60-HDMI");
			break;
		case '7':
			setenv("mxcfb1","video=mxcfb1:dev=ldb,LDB-XGA,if=RGB24,bpp=32");
			setenv("screensize1","1024x768-X-LVDS");
			break;
		case '8':
			setenv("mxcfb1","video=mxcfb1:dev=ldb,LDB-1080P60,if=RGB24,bpp=32");
			setenv("screensize1","1920x1080-X-LVDS");
			break;
		case '9':
			setenv("mxcfb1","video=mxcfb1:off");
			setenv("screensize1","off");
			break;
        default:
			printf("incorrect number\n");
			goto HERE;
		}	

		if(saveenv())
			printf("something error occured, please check the nand device!");

	}while(1);
}
int lvds_mode()
{
        char c;
        do
        {
                printf("----------------------LVDS MODE Menu-----------------------\n");
		printf("lvds mode current value is `%s`\n",getenv("ldb_mode"));
                printf("0 -- exit to upper menu\n");
                printf("1 -- sin0\n");
                printf("2 -- sin1\n");
                printf("3 -- sep0\n");
                printf("4 -- sep1\n");
                printf("5 -- spl0\n");
                printf("6 -- spl1\n");
                printf("7 -- dul0\n");
                printf("8 -- dul1\n");
                printf("------------------------------------------------------\n");

        HERE:
                printf(":");
                c = getc();

                printf("%c\n",c);

                switch(c)
                {
                case '0':
                        return 0;
                        break;
                case '1':
			setenv("ldb_mode","ldb=sin0");
                        break;
                case '2':
			setenv("ldb_mode","ldb=sin1");
                        break;
                case '3':
			setenv("ldb_mode","ldb=sep0");
                        break;
                case '4':
			setenv("ldb_mode","ldb=sep1");
                        break;
                case '5':
			setenv("ldb_mode","ldb=spl0");
                        break;
                case '6':
			setenv("ldb_mode","ldb=spl1");
                        break;
                case '7':
			setenv("ldb_mode","ldb=dul0");
                        break;
                case '8':
			setenv("ldb_mode","ldb=dul1");
                        break;
                default:
                        printf("incorrect number\n");
                        goto HERE;

                }
		if(saveenv())
			printf("something error occured, please check the nand device!");
        }while(1);
}



int boot_mode()
{
        char c;
        do
        {
                printf("----------------------BOOT MODE Menu-----------------------\n");
                printf("0 -- exit to upper menu\n");
                printf("1 -- boot from emmc\n");
                printf("2 -- boot from net\n");
                printf("------------------------------------------------------\n");

        HERE:
                printf(":");
                c = getc();

                printf("%c\n",c);

                switch(c)
                {
                case '0':
                        return 0;
                        break;
                case '1':
			setenv("bootcmd","run bootcmd_mmc");
                        break;
                case '2':
			setenv("bootcmd","run bootcmd_net");
                        break;
                default:
                        printf("incorrect number\n");
                        goto HERE;

                }
		if(saveenv())
			printf("something error occured, please check the nand device!");
        }while(1);
}
int enable_wdt()
{
        char c;
        do
        {
                printf("----------------------Watchdog Enable Menu-----------------------\n");
		printf("watchdog current  is `%s`\n",getenv("wdtenable"));
                printf("0 -- exit to upper menu\n");
                printf("1 -- enable watchdog\n");
                printf("2 -- disable watchdog\n");
                printf("------------------------------------------------------\n");

        HERE:
                printf(":");
                c = getc();

                printf("%c\n",c);

                switch(c)
                {
                case '0':
                        return 0;
                        break;
                case '1':
			setenv("wdtenable","enable");
                        break;
                case '2':
			setenv("wdtenable","disable");
                        break;
                default:
                        printf("incorrect number\n");
                        goto HERE;

                }
		if(saveenv())
			printf("something error occured, please check the nand device!");
        }while(1);
}

int select_codec()
{
        char c;
        do
        {
                printf("----------------------Select Codec Menu-----------------------\n");
                printf("0 -- exit to upper menu\n");
                printf("1 -- set audio codec tef6635\n");
                printf("------------------------------------------------------\n");

        HERE:
                printf(":");
                c = getc();

                printf("%c\n",c);

                switch(c)
                {
                case '0':
                        return 0;
                        break;
                case '1':
			setenv("codec_name","audio_codec=tef6635-12M");
                        break;
                default:
                        printf("incorrect number\n");
                        goto HERE;

                }
		if(saveenv())
			printf("something error occured, please check the nand device!");
        }while(1);
}

int calibrate()
{
	char c;
	do
	{
		printf("current calibrate mode is `%s`\n",getenv("calibrate"));
		printf("Y means calibrate,N means not calibrate\n");
		printf("-------------------Calibrate Menu---------------------\n");
		printf("0 -- exit to upper menu\n");
		printf("1 -- set Yes Calibrate\n");
		printf("2 -- set No Calibrate\n");
		printf("------------------------------------------------------\n");

	HERE:
		printf(":");
		c = getc();

		printf("%c\n",c);
		
		switch(c)
		{
		case '0':
			return 0;
			break;
		case '1':
			setenv("calibrate","Y");	
			break;
		case '2':
			setenv("calibrate","N");
			break;
		default:
			printf("incorrect number\n");
			goto HERE;

		}	
		if(saveenv())
			printf("something error occured, please check the nand device!");
	}while(1);
}

 int generate_mac()
{
        int c = 0;
	char mac[6];
        char ethaddr[24];
	
	memset(ethaddr, sizeof(ethaddr), 0);
        do
        {
                printf("------------------------------------------------------\n");
                printf("-- press any key to get a random char used for mac!\n");
                printf("------------------------------------------------------\n");

                getc();
		mac[c] = get_ticks() % 256;
		if(c == 0) {
		}
                printf("get a char: %02X\n",mac[c]);
		c++;

        }while(c < 6);

	mac[0] &= 0xFE;
	mac[0] |= 0x02;
	sprintf(ethaddr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	setenv("ethaddr",ethaddr);
	setenv("fec_mac",ethaddr);
			printf("set the ethaddr as %s\n", ethaddr);

	if(saveenv())
			printf("something error occured, please check the nand device!");
		
	
}

int do_scr_android(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])  
{ 
	char c;

	if(argc >1)
		goto err;
	
	do
	{
		printf("----------------------Main Menu-----------------------\n");
		printf("0 -- exit to uboot shell\n");
		printf("1 -- set mxcfb0 parameters\n");
		printf("2 -- set mxcfb1 parameters\n");
		printf("3 -- set lvds mode\n");
		printf("4 -- set watdog enable\n");
		printf("5 -- select the audio codec\n");
		printf("6 -- select calibrate mode\n");
		printf("7 -- select boot mode\n");
		printf("8 -- generate a random of MAC\n");
		printf("------------------------------------------------------\n");
		
	HERE:
		printf(":");
		c = getc();

		printf("%c\n",c);
		

		switch(c)
		{
		case '0':
			return 0;
			break;
		case '1':
			mxcfb0();
			break;
		case '2':
			mxcfb1();
			break;
		case '3':
			lvds_mode();
			break;
		case '4':
			enable_wdt();
			break;
		case '5':
			select_codec();
			break;
		case '6':
			calibrate();
			break;
		case '7':
			boot_mode();
			break;
		case '8':
			generate_mac();
			break;
		default:
			printf("incorrect number\n");
			goto HERE;
		}
	}while(1);
	
err:
	printf ("wrong argv, see help scr!\n");
	return 1;
}

U_BOOT_CMD(
         scr_android ,      1,      1,      do_scr_android,
       "set extra parameters\n",
        ""
);
