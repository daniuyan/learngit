
因做BT录音，需要把mx6的audio port设置为master模式，让mx6输出pcm clock。

配置流程：

1. arch/arm/mach-mx6/booard_mx6_groove.c

配置ssi的id和内部外部口

 static struct mxc_audio_platform_data mx6_t6_mic_data = {
  .ssi_num = 0,
     .src_port = 1,
     .ext_port = 4,
 };

加载ssi 0 的驱动

imx6q_add_imx_ssi(0, &mx6_mic_board_ssi_pdata)

2. 驱动配置：

配置audio port的clock方向

static int imx_audmux_config(int slave, int master)
{
     unsigned int ptcr, pdcr;
     slave = slave - 1;  //slave =2 ;master =5
     master = master - 1;
 
     /* SSI0 mastered by port 5 */
     ptcr =  MXC_AUDMUX_V2_PTCR_SYN;
     
     pdcr = MXC_AUDMUX_V2_PDCR_RXDSEL(master);
     mxc_audmux_v2_configure_port(slave, ptcr, pdcr);
     
     ptcr =MXC_AUDMUX_V2_PTCR_SYN    |
      MXC_AUDMUX_V2_PTCR_TFSDIR |    
      MXC_AUDMUX_V2_PTCR_TFSEL(slave) |
           MXC_AUDMUX_V2_PTCR_TCLKDIR |
                 MXC_AUDMUX_V2_PTCR_TCSEL(slave);
     pdcr = MXC_AUDMUX_V2_PDCR_RXDSEL(slave);
     mxc_audmux_v2_configure_port(master, ptcr, pdcr);
     return 0;
}

配置驱动所以的cpu dai

static struct snd_soc_dai_link imx_wm7210_dai[] = {
     {
        .name       = "HiFi",
         .stream_name    = "HiFi",
         .codec_dai_name = "mxc-wm7210",
         .codec_name = "mxc_wm7210.0",
         .cpu_dai_name   = "imx-ssi.0",
         .platform_name  = "imx-pcm-audio.0",
         .init       = imx_3stack_wm7210_init,
         .ops        = &imx_wm7210_hifi_ops,
     },
};

配置ssi 为master模式和相关的clock的方向

static int wm7210_params(struct snd_pcm_substream *substream,
      struct snd_pcm_hw_params *params)
  {
      struct snd_soc_pcm_runtime *rtd = substream->private_data;
      struct snd_soc_dai *codec_dai = rtd->codec_dai;
      struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
      u32 dai_format;
      int ret;
      unsigned int channels = params_channels(params);
       dai_format =  SND_SOC_DAIFMT_NB_IF |
          SND_SOC_DAIFMT_CBS_CFS| SND_SOC_DAIFMT_I2S;
      ret = snd_soc_dai_set_fmt(cpu_dai, dai_format);
      ret = snd_soc_dai_set_sysclk(cpu_dai, IMX_SSP_SYS_CLK,0,1);
      if (ret < 0)
          return ret;
  
      return 0;
 }