/**************************************************************
CAUTION : This file is Auto Generated by VBA based on *.xls.
          So, don't modify this file manually!
***************************************************************/
#ifndef UDP_IOS_AO_CONFIG_H_
#define UDP_IOS_AO_CONFIG_H_

/*配置管脚复用关系、内部上下拉以及驱动能力*/
#define UDP_IOS_AO_CONFIG \
do{\
\
/*配置PMU(13个PIN)*/\
    /*pmu_auxdac0_ssi管脚复用配置*/\
    OUTSET_IOS_AO_IOM_CTRL4;\
\
    /*pmu_auxdac1_ssi管脚复用配置*/\
    SET_IOS_PMU_AUXDAC1_SSI_CTRL1_1;\
    OUTSET_IOS_AO_IOM_CTRL5;\
    CLR_IOS_GPIO0_1_CTRL1_1;\
    /*pmu_auxdac1_ssi管脚上下拉配置*/\
    NASET_IOS_AO_IOM_CTRL5;\
\
\
/*配置USIM0（3个PIN）*/\
\
/*配置USIM1(3个PIN）*/\
    /*gpio0[12]管脚上下拉配置*/\
    PUSET_IOS_AO_IOM_CTRL16;\
\
\
/*配置UART0（2个PIN）*/\
\
/*配置GPIO(5个PIN）*/\
    /*gpio0[16]管脚上下拉配置*/\
    NASET_IOS_AO_IOM_CTRL20;\
\
    /*gpio0[17]管脚上下拉配置*/\
    PUSET_IOS_AO_IOM_CTRL21;\
\
    /*gpio0[18]管脚上下拉配置*/\
    NASET_IOS_AO_IOM_CTRL22;\
\
    /*gpio0[19]管脚上下拉配置*/\
    NASET_IOS_AO_IOM_CTRL23;\
\
\
/*配置MMC1(6个PIN）*/\
    /*mmc1_clk管脚复用配置*/\
    SET_IOS_MMC1_CLK_CTRL1_1;\
    OUTSET_IOS_AO_IOM_CTRL24;\
    CLR_IOS_GPIO0_20_CTRL1_1;\
    /*mmc1_clk管脚上下拉配置*/\
    NASET_IOS_AO_IOM_CTRL24;\
\
    /*mmc1_cmd管脚复用配置*/\
    SET_IOS_MMC1_CTRL1_1;\
    CLR_IOS_GPIO0_21_CTRL1_1;\
    /*mmc1_cmd管脚上下拉配置*/\
    PUSET_IOS_AO_IOM_CTRL25;\
\
    /*mmc1_data[0]管脚复用配置*/\
    SET_IOS_MMC1_CTRL1_1;\
    CLR_IOS_GPIO0_22_CTRL1_1;\
    /*mmc1_data[0]管脚上下拉配置*/\
    PUSET_IOS_AO_IOM_CTRL26;\
\
    /*mmc1_data[1]管脚复用配置*/\
    SET_IOS_MMC1_CTRL1_1;\
    CLR_IOS_GPIO0_23_CTRL1_1;\
    /*mmc1_data[1]管脚上下拉配置*/\
    PUSET_IOS_AO_IOM_CTRL27;\
\
    /*mmc1_data[2]管脚复用配置*/\
    SET_IOS_MMC1_CTRL1_1;\
    CLR_IOS_GPIO0_24_CTRL1_1;\
    /*mmc1_data[2]管脚上下拉配置*/\
    PUSET_IOS_AO_IOM_CTRL28;\
\
    /*mmc1_data[3]管脚复用配置*/\
    SET_IOS_MMC1_CTRL1_1;\
    CLR_IOS_GPIO0_25_CTRL1_1;\
    /*mmc1_data[3]管脚上下拉配置*/\
    PUSET_IOS_AO_IOM_CTRL29;\
\
\
/*配置JTAG_DFM_MODE(1个PIN）*/\
\
/*配置HSIC（2个PIN）*/\
\
}while(0)

/*管脚配置宏for drv*/
#define UDP_IOS_CONFIG \
do{\
    UDP_IOS_AO_CONFIG;\
    UDP_IOS_PD_CONFIG;\
}while(0)

#endif

