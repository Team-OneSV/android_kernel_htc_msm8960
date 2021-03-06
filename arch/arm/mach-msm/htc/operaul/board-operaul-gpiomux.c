/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <asm/mach-types.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>
#include <mach/socinfo.h>
#include "devices.h"
#include "board-8930.h"
#include <asm/setup.h>


static struct gpiomux_setting gsbi3_suspended_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi3_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi9 = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi10 = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi12 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting cdc_mclk = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting audio_auxpcm[] = {
	
	{
		.func = GPIOMUX_FUNC_GPIO,
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},
	
	{
		.func = GPIOMUX_FUNC_1,
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},
};

static struct gpiomux_setting audio_auxpcm_input[] = {
        
        {
                .func = GPIOMUX_FUNC_GPIO,
                .drv = GPIOMUX_DRV_2MA,
                .pull = GPIOMUX_PULL_DOWN,
                .dir = GPIOMUX_IN,
        },
        
        {
                .func = GPIOMUX_FUNC_1,
                .drv = GPIOMUX_DRV_2MA,
                .pull = GPIOMUX_PULL_NONE,
        },
};



static struct gpiomux_setting slimbus = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_KEEPER,
};

static struct gpiomux_setting wcnss_5wire_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wcnss_5wire_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv  = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting atmel_ldo_en_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting atmel_ldo_en_act_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#ifdef MSM8930_PHASE_2
static struct gpiomux_setting hsusb_sus_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};
static struct msm_gpiomux_config msm8930_hsusb_configs[] = {
	{
		.gpio = 63,     
		.settings = {
			[GPIOMUX_SUSPENDED] = &hsusb_sus_cfg,
		},
	},
	{
		.gpio = 97,     
		.settings = {
			[GPIOMUX_SUSPENDED] = &hsusb_sus_cfg,
		},
	},
};
#endif
#if 0
static struct gpiomux_setting hap_lvl_shft_suspended_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hap_lvl_shft_active_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};
#endif
static struct gpiomux_setting mdp_vsync_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdp_vsync_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};




static struct msm_gpiomux_config msm8960_gsbi_configs[] __initdata = {
#if 0
	{
		.gpio      = 6,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
		.gpio      = 7,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
		.gpio      = 8,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
	{
		.gpio      = 9,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &spi_suspended_config,
			[GPIOMUX_ACTIVE] = &spi_active,
		},
	},
#endif
	{
		.gpio      = 16,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi3_active_cfg,
		},
	},
	{
		.gpio      = 17,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3_suspended_cfg,
			[GPIOMUX_ACTIVE] = &gsbi3_active_cfg,
		},
	},
	{
		.gpio      = 44,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi12,
			[GPIOMUX_ACTIVE] = &gsbi12,
		},
	},
	{
		.gpio      = 95,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi9,
			[GPIOMUX_ACTIVE] = &gsbi9,
		},
	},
	{
		.gpio      = 96,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi9,
			[GPIOMUX_ACTIVE] = &gsbi9,
		},
	},
	{
		.gpio      = 45,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi12,
			[GPIOMUX_ACTIVE] = &gsbi12,
		},
	},
	{
		.gpio      = 73,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
			[GPIOMUX_ACTIVE] = &gsbi10,
		},
	},
	{
		.gpio      = 74,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
			[GPIOMUX_ACTIVE] = &gsbi10,
		},
	},
};

static struct gpiomux_setting  mi2s_active = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting  mi2s_suspend_pull_down = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct msm_gpiomux_config msm8930_mi2s_configs[] __initdata = {
	{
		.gpio	= 47,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &mi2s_suspend_pull_down,
			[GPIOMUX_ACTIVE] = &mi2s_active,
		},
	},
	{
		.gpio	= 48,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &mi2s_suspend_pull_down,
			[GPIOMUX_ACTIVE] = &mi2s_active,
		},
	},
	{
		.gpio	= 49,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &mi2s_suspend_pull_down,
			[GPIOMUX_ACTIVE] = &mi2s_active,
		},
	},
	{
		.gpio	= 52,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &mi2s_suspend_pull_down,
			[GPIOMUX_ACTIVE] = &mi2s_active,
		},
	},
};

static struct gpiomux_setting wcd9304_reset_suspend = {
        .func = GPIOMUX_FUNC_GPIO,
        .drv = GPIOMUX_DRV_2MA,
        .pull = GPIOMUX_PULL_NONE,
        .dir = GPIOMUX_OUT_HIGH,
};

static struct msm_gpiomux_config wcd9304_reset_configs[] __initdata = {
	{
		.gpio = 42,	
		.settings = {
			[GPIOMUX_SUSPENDED] = &wcd9304_reset_suspend,
		},
	},
};
static struct msm_gpiomux_config msm8930_slimbus_config[] __initdata = {
	{
		.gpio	= 60,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
	{
		.gpio	= 61,		
		.settings = {
			[GPIOMUX_SUSPENDED] = &slimbus,
		},
	},
};

static struct msm_gpiomux_config msm8930_audio_codec_configs[] __initdata = {
	{
		.gpio = 59,
		.settings = {
			[GPIOMUX_SUSPENDED] = &cdc_mclk,
		},
	},
};

static struct msm_gpiomux_config msm8930_audio_auxpcm_configs[] __initdata = {
	{
		.gpio = 63,
		.settings = {
			[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
			[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
	{
		.gpio = 64,
		.settings = {
			[GPIOMUX_SUSPENDED] = &audio_auxpcm_input[0],
			[GPIOMUX_ACTIVE] = &audio_auxpcm_input[1],
		},
	},
	{
		.gpio = 65,
		.settings = {
			[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
			[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
	{
		.gpio = 66,
		.settings = {
			[GPIOMUX_SUSPENDED] = &audio_auxpcm[0],
			[GPIOMUX_ACTIVE] = &audio_auxpcm[1],
		},
	},
};

static struct msm_gpiomux_config wcnss_5wire_interface[] = {
	{
		.gpio = 84,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 85,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 86,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 87,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
	{
		.gpio = 88,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wcnss_5wire_active_cfg,
			[GPIOMUX_SUSPENDED] = &wcnss_5wire_suspend_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8960_atmel_configs[] __initdata = {
	{	
		.gpio = 50,
		.settings = {
			[GPIOMUX_ACTIVE]    = &atmel_ldo_en_act_cfg,
			[GPIOMUX_SUSPENDED] = &atmel_ldo_en_sus_cfg,
		},
	},
};
#if 0
static struct msm_gpiomux_config hap_lvl_shft_config[] __initdata = {
	{
		.gpio = 47,
		.settings = {
			[GPIOMUX_SUSPENDED] = &hap_lvl_shft_suspended_config,
			[GPIOMUX_ACTIVE] = &hap_lvl_shft_active_config,
		},
	},
};
#endif

static struct msm_gpiomux_config msm8960_mdp_vsync_configs[] __initdata = {
	{
		.gpio = 0,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mdp_vsync_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdp_vsync_suspend_cfg,
		},
	}
};


#if 0
static struct gpiomux_setting haptics_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};
static struct gpiomux_setting haptics_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct msm_gpiomux_config msm8930_haptics_configs[] __initdata = {
	{
		.gpio = 77,
		.settings = {
			[GPIOMUX_ACTIVE] = &haptics_active_cfg,
			[GPIOMUX_SUSPENDED] = &haptics_suspend_cfg,
		},
	},
	{
		.gpio = 78,
		.settings = {
			[GPIOMUX_ACTIVE] = &haptics_active_cfg,
			[GPIOMUX_SUSPENDED] = &haptics_suspend_cfg,
		},
	},
};
#endif
int __init msm8930_init_gpiomux(void)
{
	int rc = msm_gpiomux_init(NR_GPIO_IRQS);
	if (rc) {
		pr_err(KERN_ERR "msm_gpiomux_init failed %d\n", rc);
		return rc;
	}

	msm_gpiomux_install(msm8960_gsbi_configs,
			ARRAY_SIZE(msm8960_gsbi_configs));

	msm_gpiomux_install(msm8960_atmel_configs,
			ARRAY_SIZE(msm8960_atmel_configs));

	msm_gpiomux_install(msm8930_slimbus_config,
			ARRAY_SIZE(msm8930_slimbus_config));

	msm_gpiomux_install(msm8930_audio_codec_configs,
			ARRAY_SIZE(msm8930_audio_codec_configs));

	msm_gpiomux_install(msm8930_mi2s_configs,
			ARRAY_SIZE(msm8930_mi2s_configs));
	msm_gpiomux_install(wcd9304_reset_configs,
            ARRAY_SIZE(wcd9304_reset_configs));

	msm_gpiomux_install(msm8930_audio_auxpcm_configs,
			ARRAY_SIZE(msm8930_audio_auxpcm_configs));

	msm_gpiomux_install(wcnss_5wire_interface,
			ARRAY_SIZE(wcnss_5wire_interface));

	if (machine_is_msm8930_mtp() || machine_is_msm8930_fluid() ||
		machine_is_msm8930_cdp()) {

#ifdef MSM8930_PHASE_2
		msm_gpiomux_install(msm8930_hsusb_configs,
			ARRAY_SIZE(msm8930_hsusb_configs));
#endif
	}


	msm_gpiomux_install(msm8960_mdp_vsync_configs,
			ARRAY_SIZE(msm8960_mdp_vsync_configs));
	return 0;
}
