#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/device.h>
#include <linux/fsl_devices.h>
#include <linux/clk.h>
#include <linux/gpio.h>

#include <sound/core.h>
#include <sound/soc.h>
#include <sound/pcm.h>
#include <asm/mach-types.h>

#include "imx-ssi.h"

/*
 * 1. 分配注册一个名为soc-audio的平台设备 imx_tef6635_snd_device
 * 2. 这个平台设备有一个私有数据 snd_soc_card imx_tef6635
 *    snd_soc_card里有一项snd_soc_dai_link imx_tef6635_dai
 *    snd_soc_dai_link被用来决定ASOC各部分的驱动
 */
 
static struct platform_device *imx_tef6635_snd_device;

static struct snd_soc_card imx_tef6635;

//tef6635私有数据
static struct imx_tef6635_priv {
	int sysclk;
	int hw;
	struct platform_device *pdev;
}card_priv ;


static struct snd_soc_ops imx_tef6635_hifi_ops = {
	//.hw_params = imx_tef6635_hw_params,
};


static struct snd_soc_dai_link imx_tef6635_dai[] = {
	{
		.name = "HiFi",
		.stream_name = "HiFi",
		.codec_name = "tef6635_codec",			//codec芯片的名称
		.codec_dai_name = "tef6635_codec_dai",	//使用的codec_dai的名字
		.cpu_dai_name = "imx-ssi.1",		//SOC侧的SSI接口，audmux内部端口2，使用SSI1
		.platform_name	= "imx-pcm-audio.1",	//soc侧的DMA设置
		.ops = &imx_tef6635_hifi_ops,			//硬件操作部分
	},
};

static struct snd_soc_card imx_tef6635 = {
	.name		= "tef6635-audio",
	.dai_link	= imx_tef6635_dai,
	.owner = THIS_MODULE,
	.num_links	= ARRAY_SIZE(imx_tef6635_dai),
};

/*设置ADUMUX的相关配置*/
static int imx_audmux_config(int slave, int master)
{
	unsigned int ptcr, pdcr;
	slave = slave - 1;
	master = master - 1;

	/* 对于slave端口的配置，也就是audmux的src_port */
	/* mx6的audio port设置为slave模式，由codec输出pcm clock*/
	ptcr = MXC_AUDMUX_V2_PTCR_SYN |
		MXC_AUDMUX_V2_PTCR_TFSDIR |
		MXC_AUDMUX_V2_PTCR_TFSEL(master) |	//I2S设置为slave模式，从ext_port获取时钟
		MXC_AUDMUX_V2_PTCR_TCLKDIR |
		MXC_AUDMUX_V2_PTCR_TCSEL(master);   //clk from master port(ext_port)
	pdcr = MXC_AUDMUX_V2_PDCR_RXDSEL(master);
	mxc_audmux_v2_configure_port(slave, ptcr, pdcr);

	ptcr = MXC_AUDMUX_V2_PTCR_SYN;
	pdcr = MXC_AUDMUX_V2_PDCR_RXDSEL(slave);
	mxc_audmux_v2_configure_port(master, ptcr, pdcr);
	
	return 0;
}



static int __devinit imx_tef6635_probe(struct platform_device *pdev)
{
	struct mxc_audio_platform_data *plat = pdev->dev.platform_data;

	int ret = 0;

	card_priv.pdev = pdev;

	imx_audmux_config(plat->src_port, plat->ext_port); 	//配置传输方向

	ret = -EINVAL;
	if (plat->init && plat->init())
		return ret;

	card_priv.sysclk = plat->sysclk;

	return 0;
}

static int imx_sgtl5000_remove(struct platform_device *pdev)
{
	struct mxc_audio_platform_data *plat = pdev->dev.platform_data;

	if (plat->finit)
		plat->finit();

	return 0;
}

static struct platform_driver imx_tef6635_audio_driver = {
	.probe = imx_tef6635_probe,
	.remove = imx_tef6635_remove,
	.driver = {
		   .name = "imx-tef6635",	//匹配该名称后调用probe设置端口时钟
		   },
};

static int __init imx_tef6635_init(void)
{
	int ret;

	ret = platform_driver_register(&imx_tef6635_audio_driver);
	if (ret)
		return -ENOMEM;
	
	imx_tef6635_snd_device = platform_device_alloc("soc-audio", -1);
	if (!imx_tef6635_snd_device)
		return -ENOMEM;
	platform_set_drvdata(imx_tef6635_snd_device, &imx_tef6635);
    ret = platform_device_add(imx_tef6635_snd_device);

	if (ret) {
		printk(KERN_ERR "ASoC: Platform device allocation failed\n");
		platform_device_put(imx_tef6635_snd_device);
    return 0;
}


static void __exit imx_tef6635_exit(void)
{
	platform_driver_unregister(&imx_tef6635_audio_driver);
	platform_device_unregister(imx_tef6635_snd_device);
}

module_init(imx_tef6635_init);
module_exit(imx_tef6635_exit);

MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_DESCRIPTION("PhyCORE ALSA SoC driver");
MODULE_LICENSE("GPL");
