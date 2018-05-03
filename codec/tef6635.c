
/* 1. 构造一个snd_soc_dai_driver   tef6635_dai
 * 2. 构造一个snd_soc_codec_driver  tef6635_codec_driver
 * 3. 注册它们
 */
 
 static struct snd_soc_codec_driver tef6635_codec_driver = {
};

static int tef6635_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params,
	struct snd_soc_dai *dai)
{
    /* 根据params的值,设置TEF6635的寄存器 */
    return 0;
}

static const struct snd_soc_dai_ops tef6635_ops = {
	.hw_params = tef6635_hw_params,
};

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
	   .name = "tef6635_codec",
	   .owner = THIS_MODULE,
	},
	.probe = tef6635_probe,		//待补充
	.remove = tef6635_remove,	//待补充
	
};



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

static int tef6635_init(void)
{
    platform_device_register(&tef6635_dev);
    platform_driver_register(&tef6635_drv);
    return 0;
}

static void tef6635_exit(void)
{
    platform_device_unregister(&tef6635_dev);		//device
    platform_driver_unregister(&tef6635_drv);		//driver
}

module_init(tef6635_init);
module_exit(tef6635_exit);
