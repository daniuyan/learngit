/*单板部分修改内容，添加mxc单板的tef设备*/
static struct platform_device mxc_tef6635_device = {
    .name = "imx-tef6635",
};
static struct mxc_audio_platform_data tef6635_data = {
    .ssi_num = 1,
    .src_port = 2,
    .ext_port = 5,
    .init = mxc_tef6635_init,
};
static int mxc_tef6635_init(void)
{
    struct clk *ssi_ext1;
    struct clk *ssi_sys_clk;

    u32 rate;

    ssi_ext1 = clk_get(NULL, "ssi_ext1_clk"); //外部时钟
    if (IS_ERR(ssi_ext1))
            return -1;
    rate = clk_round_rate(ssi_ext1, 3000000);
    if (rate < 2000000 || rate > 24000000) {
            printk(KERN_ERR "Error: UDA134x mclk freq %d out of range!\n",
                   rate);
            clk_put(ssi_ext1);
            return -1;
    }
    clk_set_rate(ssi_ext1, rate);
    clk_enable(ssi_ext1);

    tef6635_data.sysclk = rate;  //I2S的数据时钟

    return 0;
}
