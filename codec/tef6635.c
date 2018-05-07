#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <sound/pcm.h>
#include <linux/clk.h>
#include <linux/platform_device.h>
#include <sound/pcm_params.h>
#include <sound/core.h>
#include <sound/soc.h>
#include <sound/initval.h>
#include <asm/io.h>



/* 1. 构造一个snd_soc_dai_driver   tef6635_dai
 * 2. 构造一个snd_soc_codec_driver  tef6635_codec_driver
 * 3. 注册它们
 */
/* tef6635 private structure in codec */
struct tef6635_priv {
	int sysclk;	/* sysclk rate */
	int master;	/* i2s master or not */
	int fmt;	/* i2s data format */
	
};

/* 设置全局的tef6635 操作结构体 */
struct tef6635_setting {
	bool playpack;		/* playback or callback */
	int i2s_ctl_params;	/* I2S控制参数 */
	int clk_ctl_params;	/* 时钟控制参数 */
}tef6635_setting;
 
static int uda1341_soc_probe(struct snd_soc_codec *codec)
{
	//通知MCU完成tef6635的初始化,包括芯片使能，设置I2S通道，mix的默认值等...
	tef6635_reg_init();
	return 0;	
}
 
static struct snd_soc_codec_driver tef6635_codec_driver = {
	.name  = "tef6635_codec", 
	.probe = tef6635_probe,	//对6635芯片做一些寄存器初始化设置
};



/* 需要在此实现与MCU通信函数 */
static void snd_soc_inform_mcu(struct tef6635_setting *setting){
	//解析setting
	//打包解析后的数据
	//通过uart口传输到mcu
	//确认对端完成设置及错误处理
	
}

/*
 * set clock according to i2s frame clock,
 */
static int tef6635_set_clock(struct snd_soc_codec *codec, int frame_rate)
{
	struct tef6635_priv *tef6635 = snd_soc_codec_get_drvdata(codec);
	struct tef6635_setting *seting = &tef6635_setting;	//指向全局变量tef6635_setting的指针
	int sys_fs;	/* sample freq */
	//将相关clk设置置0
	setting->clk_ctl_params = 0;
	
	/*
	 * sample freq should be divided by frame clock,
	 * if frame clock lower than 44.1khz, sample feq should set to
	 * 32khz or 44.1khz.
	 */
	switch (frame_rate) {
	case 8000:
	case 16000:
		sys_fs = 32000;
		break;
	case 11025:
	case 22050:
		sys_fs = 44100;
		break;
	default:
		sys_fs = frame_rate;
		break;
	}
	
	/* set divided factor of frame clock */
	switch (sys_fs / frame_rate) {
	case 4:
		//setting->clk_ctl_params = 
		break;
	case 2:
		//setting->clk_ctl_params = 
		break;
	case 1:
		//setting->clk_ctl_params = 
		break;
	default:
		return -EINVAL;
	}
	
	/* set the sys_fs according to frame rate */
	switch (sys_fs) {
	case 32000:
		//setting->clk_ctl_params =
		break;
	case 44100:
		//setting->clk_ctl_params =
		break;
	case 48000:
		//setting->clk_ctl_params =
		break;
	case 96000:
		//setting->clk_ctl_params =
		break;
	default:
		dev_err(codec->dev, "frame rate %d not supported\n",
			frame_rate);
		return -EINVAL;
	}
	
	/*
	 * calculate the divider of mclk/sample_freq,
	 * factor of freq =96k can only be 256, since mclk in range (12m,27m)
	 */
	switch (tef6635->sysclk / sys_fs) {
	case 256:
		//setting->clk_ctl_params =
		break;
	case 384:
		//setting->clk_ctl_params =
		break;
	case 512:
		//setting->clk_ctl_params =
		break;
	default:
		/* if mclk not satisify the divider, use pll */
		if (tef6635->master) {
			//setting->clk_ctl_params =
		} else {
			dev_err(codec->dev,
				"PLL not supported in slave mode\n");
			return -EINVAL;
		}
	}
	
	/* 如果有时钟相关的其他设置，在此处继续添加代码*/
	//将设置发送给mcu	
	//snd_soc_inform_mcu(setting); 
}

static int tef6635_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params,
	struct snd_soc_dai *dai)
{
    /* 根据params的值,设置TEF6635的寄存器 
	 * 主要是设置时钟、I2S格式
	 * 由于MCU完成实际的控制，这里只做参数解析，并根据协议将指令发送到MCU
	 */
	
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_codec *codec = rtd->codec;
	//引入结构体，返回的是声卡设备的priv_data的指针
	struct tef6635_priv *tef6635 = snd_soc_codec_get_drvdata(codec);
	struct tef6635_setting *seting = &tef6635_setting;	//指向全局变量tef6635_setting的指针
	int channels = params_channels(params);
	int ret;
	setting->playback = true;
	setting->i2s_ctl_params = 0;
	
	/* sysclk should already set*/
	if (!tef6635->sysclk) {
		dev_err(codec->dev, "%s: set sysclk first!\n", __func__);
		return -EFAULT;
	}
	
	/* tef6635仅用于playback */
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		seting->playpack = ture;
		
	/* set codec clock base on lrclk */
	ret = tef6635_set_clock(codec, params_rate(params));
	if (ret)
		return ret;
	
	/* set i2s data format */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		if (sgtl5000->fmt == SND_SOC_DAIFMT_RIGHT_J)
			tef6635 -EINVAL;
		/* 根据传输协议来定 */
		//seting->i2s_ctl_params = ;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		//seting->i2s_ctl_params = ;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		//seting->i2s_ctl_params = ;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		if (tef6635->fmt == SND_SOC_DAIFMT_RIGHT_J)
			return -EINVAL;
		//seting->i2s_ctl_params = ;
		break;
	default:
		return -EINVAL;
	}

	
	//将设置发送给mcu	
	//snd_soc_inform_mcu(setting); 
	
	 
    return 0;
	
}

static const struct snd_soc_dai_ops tef6635_ops = {
	.hw_params = tef6635_hw_params,
};

#define TEF6635_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE |\
			SNDRV_PCM_FMTBIT_S32_LE)

static struct snd_soc_dai_driver tef6635_dai = {
	.name = "tef6635_codec_dai",
	.playback = {
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		/*
		 * only support 8~48K + 96K,
		 * TODO modify hw_param to support more
		 */
		.rates = SNDRV_PCM_RATE_8000_48000 | SNDRV_PCM_RATE_96000,
		.formats = TEF6635_FORMATS,
	},
	/* pcm operations */
	.ops = &tef6635_ops,
	.symmetric_rates = 1,
};

/* 通过注册平台设备、平台驱动来实现对snd_soc_register_codec的调用
 *
 */

static int tef6635_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev,
			&tef6635_codec_driver, &tef6635_dai, 1);
}

static int tef6635_remove(struct platform_device *pdev)
{
    return snd_soc_unregister_codec(&pdev->dev);
}

struct platform_driver tef6635_drv = {
	.driver = {
	   .name = "imx-tef6635",
	   .owner = THIS_MODULE,
	},
	.probe = tef6635_probe,		
	.remove = tef6635_remove,	
	
};


/*设备注册放在单板中进行*/
/*
static void tef6635_dev_release(struct device * dev)
{
}

static struct platform_device tef6635_dev = {
    .name         = "tef6635_codec",
    .id       = -1,
    .dev = { 
    	.release = tef6635_dev_release, 
	},
};
*/

static int tef6635_init(void)
{
    /*设备注册放在单板中进行*/
	//platform_device_register(&tef6635_dev);
    platform_driver_register(&tef6635_drv);
    return 0;
}

static void tef6635_exit(void)
{
    /*设备注册放在单板中进行*/
	//platform_device_unregister(&tef6635_dev);		//device
    platform_driver_unregister(&tef6635_drv);		//driver
}

module_init(tef6635_init);
module_exit(tef6635_exit);
