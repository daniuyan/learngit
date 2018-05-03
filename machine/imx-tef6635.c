#include <linux/clk.h>
#include <linux/gpio.h>
#include <linux/module.h>

#include <sound/soc.h>

/*
 * 1. 分配注册一个名为soc-audio的平台设备 imx_tef6635_snd_device
 * 2. 这个平台设备有一个私有数据 snd_soc_card imx_tef6635
 *    snd_soc_card里有一项snd_soc_dai_link imx_tef6635_dai
 *    snd_soc_dai_link被用来决定ASOC各部分的驱动
 */
 
static struct platform_device *imx_tef6635_snd_device;

static struct snd_soc_card imx_tef6635;



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


static int __init imx_tef6635_init(void)
{

	imx_tef6635_snd_device = platform_device_alloc("soc-audio", 1);
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
	platform_device_unregister(imx_tef6635_snd_device);
}

module_init(imx_tef6635_init);
module_exit(imx_tef6635_exit);

MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_DESCRIPTION("PhyCORE ALSA SoC driver");
MODULE_LICENSE("GPL");
