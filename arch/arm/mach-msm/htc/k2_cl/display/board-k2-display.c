/* linux/arch/arm/mach-msm/board-k2-panel.c
 *
 * Copyright (c) 2011 HTC.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/bootmem.h>
#include <asm/mach-types.h>
#include <mach/msm_bus_board.h>
#include <mach/msm_memtypes.h>
#include <mach/board.h>
#include <mach/gpio.h>
#include <mach/gpiomux.h>
#include <mach/socinfo.h>
#include <linux/ion.h>
#include <mach/ion.h>
#include <linux/regulator/consumer.h>

#include "../devices.h"
#include "../board-k2_cl.h"
#include <mach/panel_id.h>
#include <mach/debug_display.h>
#include <asm/system_info.h>
#include <linux/leds.h>
#include "../../../../drivers/video/msm/msm_fb.h"
#include "../../../../drivers/video/msm/mipi_dsi.h"
#include "../../../../drivers/video/msm/mdp4.h"

#define RESOLUTION_WIDTH 480
#define RESOLUTION_HEIGHT 800

#ifdef CONFIG_FB_MSM_TRIPLE_BUFFER
#define MSM_FB_PRIM_BUF_SIZE \
		(roundup((RESOLUTION_WIDTH * RESOLUTION_HEIGHT * 4), 4096) * 3) 
#else
#define MSM_FB_PRIM_BUF_SIZE \
		(roundup((RESOLUTION_WIDTH * RESOLUTION_HEIGHT * 4), 4096) * 2) 
#endif

#define MSM_FB_SIZE roundup(MSM_FB_PRIM_BUF_SIZE, 4096)

#ifdef CONFIG_FB_MSM_OVERLAY0_WRITEBACK
#define MSM_FB_OVERLAY0_WRITEBACK_SIZE roundup((1376 * 768 * 3 * 2), 4096)
#else
#define MSM_FB_OVERLAY0_WRITEBACK_SIZE (0)
#endif

#ifdef CONFIG_FB_MSM_OVERLAY1_WRITEBACK
#define MSM_FB_OVERLAY1_WRITEBACK_SIZE roundup((1920 * 1088 * 3 * 2), 4096)
#else
#define MSM_FB_OVERLAY1_WRITEBACK_SIZE (0)
#endif

#define MDP_VSYNC_GPIO 0
#define MIPI_VIDEO_NOVATEK_WVGA_PANEL_NAME	"mipi_video_novatek_wvga"
#define HDMI_PANEL_NAME	"hdmi_msm"
#define TVOUT_PANEL_NAME	"tvout_msm"

static struct resource msm_fb_resources[] = {
	{
		.flags = IORESOURCE_DMA,
	},
};

static struct msm_fb_platform_data msm_fb_pdata;

static struct platform_device msm_fb_device = {
	.name   = "msm_fb",
	.id     = 0,
	.num_resources     = ARRAY_SIZE(msm_fb_resources),
	.resource          = msm_fb_resources,
	.dev.platform_data = &msm_fb_pdata,
};

void __init k2_allocate_fb_region(void)
{
	void *addr;
	unsigned long size;

	size = MSM_FB_SIZE;
	addr = alloc_bootmem_align(size, 0x1000);
	msm_fb_resources[0].start = __pa(addr);
	msm_fb_resources[0].end = msm_fb_resources[0].start + size - 1;
	pr_info("allocating %lu bytes at %p (%lx physical) for fb\n",
			size, addr, __pa(addr));
}

#ifdef CONFIG_MSM_BUS_SCALING

static struct msm_bus_vectors mdp_init_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 0,
		.ib = 0,
	},
};

static struct msm_bus_vectors mdp_ui_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 216000000 * 2,
		.ib = 270000000 * 2,
	},
};

static struct msm_bus_vectors mdp_vga_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 216000000 * 2,
		.ib = 270000000 * 2,
	},
};

static struct msm_bus_vectors mdp_720p_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 230400000 * 2,
		.ib = 288000000 * 2,
	},
};

static struct msm_bus_vectors mdp_1080p_vectors[] = {
	{
		.src = MSM_BUS_MASTER_MDP_PORT0,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab = 334080000 * 2,
		.ib = 417600000 * 2,
	},
};

static struct msm_bus_paths mdp_bus_scale_usecases[] = {
	{
		ARRAY_SIZE(mdp_init_vectors),
		mdp_init_vectors,
	},
	{
		ARRAY_SIZE(mdp_ui_vectors),
		mdp_ui_vectors,
	},
	{
		ARRAY_SIZE(mdp_ui_vectors),
		mdp_ui_vectors,
	},
	{
		ARRAY_SIZE(mdp_vga_vectors),
		mdp_vga_vectors,
	},
	{
		ARRAY_SIZE(mdp_720p_vectors),
		mdp_720p_vectors,
	},
	{
		ARRAY_SIZE(mdp_1080p_vectors),
		mdp_1080p_vectors,
	},
};

static struct msm_bus_scale_pdata mdp_bus_scale_pdata = {
	mdp_bus_scale_usecases,
	ARRAY_SIZE(mdp_bus_scale_usecases),
	.name = "mdp",
};

#endif

static struct msm_panel_common_pdata mdp_pdata = {
	.gpio = MDP_VSYNC_GPIO,
	.mdp_max_clk = 200000000,
	.mdp_max_bw = 2000000000,
	.mdp_bw_ab_factor = 115,
	.mdp_bw_ib_factor = 150,
#ifdef CONFIG_MSM_BUS_SCALING
	//.mdp_bus_scale_table = &mdp_bus_scale_pdata,
#endif
	.mdp_rev = MDP_REV_42,
#ifdef CONFIG_MSM_MULTIMEDIA_USE_ION
	.mem_hid = BIT(ION_CP_MM_HEAP_ID),
#else
	.mem_hid = MEMTYPE_EBI1,
#endif
	.mdp_iommu_split_domain = 0,
	.cont_splash_enabled = 0x00,
	.splash_screen_addr = 0x00,
	.splash_screen_size = 0x00,
};

void __init k2_mdp_writeback(struct memtype_reserve* reserve_table)
{
	mdp_pdata.ov0_wb_size = MSM_FB_OVERLAY0_WRITEBACK_SIZE;
	mdp_pdata.ov1_wb_size = MSM_FB_OVERLAY1_WRITEBACK_SIZE;
#if defined(CONFIG_ANDROID_PMEM) && !defined(CONFIG_MSM_MULTIMEDIA_USE_ION)
	reserve_table[mdp_pdata.mem_hid].size +=
		mdp_pdata.ov0_wb_size;
	reserve_table[mdp_pdata.mem_hid].size +=
		mdp_pdata.ov1_wb_size;
#endif
}

static bool dsi_power_on;
static bool first_inited = true;
static int mipi_dsi_panel_power(int on)
{
	static struct regulator *reg_l2;
	int rc;

	PR_DISP_INFO("%s: power %s.\n", __func__, on ? "on" : "off");

	if (!dsi_power_on) {
		
		gpio_tlmm_config(GPIO_CFG(MSM_LCD_ID0, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, 0), GPIO_CFG_ENABLE);
		gpio_tlmm_config(GPIO_CFG(MSM_LCD_ID1, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, 0), GPIO_CFG_ENABLE);

		
		reg_l2 = regulator_get(&msm_mipi_dsi1_device.dev,
				"dsi_vdda");
		if (IS_ERR(reg_l2)) {
			pr_err("could not get 8038_l2, rc = %ld\n",
				PTR_ERR(reg_l2));
			return -ENODEV;
		}
		rc = regulator_set_voltage(reg_l2, 1200000, 1200000);
		if (rc) {
			pr_err("set_voltage l2 failed, rc=%d\n", rc);
			return -EINVAL;
		}

		dsi_power_on = true;

		if (first_inited) {
			first_inited = false;

			rc = regulator_set_optimum_mode(reg_l2, 100000);
			if (rc < 0) {
				pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
				return -EINVAL;
			}
			rc = regulator_enable(reg_l2);
			if (rc) {
				pr_err("enable l2 failed, rc=%d\n", rc);
				return -ENODEV;
			}
			return 0;
		}
	}

	if (on) {
		if (panel_type == PANEL_ID_K2_WL_AUO || panel_type == PANEL_ID_K2_WL_AUO_C2) {
			rc = regulator_set_optimum_mode(reg_l2, 100000);
			if (rc < 0) {
				pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
				return -EINVAL;
			}

			gpio_set_value(MSM_V_LCMIO_1V8_EN, 1);
			//hr_msleep(1);
			gpio_set_value(MSM_V_LCM_3V3_EN, 1);

			rc = regulator_enable(reg_l2);
			if (rc) {
				pr_err("enable l2 failed, rc=%d\n", rc);
				return -ENODEV;
			}

			//hr_msleep(55);
			gpio_set_value(MSM_LCD_RSTz, 1);
			usleep(20);
			gpio_set_value(MSM_LCD_RSTz, 0);
			usleep(30);
			gpio_set_value(MSM_LCD_RSTz, 1);
			//hr_msleep(120);
		} else if (panel_type == PANEL_ID_K2_WL_JDI_NT) {
			rc = regulator_set_optimum_mode(reg_l2, 100000);
			if (rc < 0) {
				pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
				return -EINVAL;
			}

			gpio_set_value(MSM_V_LCMIO_1V8_EN, 1);
			//hr_msleep(1);
			gpio_set_value(MSM_V_LCM_3V3_EN, 1);

			rc = regulator_enable(reg_l2);
			if (rc) {
				pr_err("enable l2 failed, rc=%d\n", rc);
				return -ENODEV;
			}

			//hr_msleep(50);
			gpio_set_value(MSM_LCD_RSTz, 1);
			//hr_msleep(10);
			gpio_set_value(MSM_LCD_RSTz, 0);
			//hr_msleep(10);
			gpio_set_value(MSM_LCD_RSTz, 1);
			//hr_msleep(120);
        }
	} else {
		if (panel_type == PANEL_ID_K2_WL_AUO || panel_type == PANEL_ID_K2_WL_AUO_C2) {
			rc = regulator_disable(reg_l2);
			if (rc) {
				pr_err("disable reg_l2 failed, rc=%d\n", rc);
				return -ENODEV;
			}
			rc = regulator_set_optimum_mode(reg_l2, 100);
				if (rc < 0) {
					pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
				return -EINVAL;
			}

			gpio_set_value(MSM_LCD_RSTz, 0);
			//hr_msleep(1);
			gpio_set_value(MSM_V_LCM_3V3_EN, 0);
			//hr_msleep(5);
			gpio_set_value(MSM_V_LCMIO_1V8_EN, 0);
		} else if (panel_type == PANEL_ID_K2_WL_JDI_NT) {
			rc = regulator_disable(reg_l2);
			if (rc) {
				pr_err("disable reg_l2 failed, rc=%d\n", rc);
				return -ENODEV;
			}
			rc = regulator_set_optimum_mode(reg_l2, 100);
				if (rc < 0) {
					pr_err("set_optimum_mode l2 failed, rc=%d\n", rc);
				return -EINVAL;
			}
			//hr_msleep(10);
			gpio_set_value(MSM_LCD_RSTz, 0);
			//hr_msleep(10);
			gpio_set_value(MSM_V_LCM_3V3_EN, 0);
			//hr_msleep(10);
			gpio_set_value(MSM_V_LCMIO_1V8_EN, 0);
        }
	}
	return 0;
}

static struct mipi_dsi_platform_data mipi_dsi_pdata = {
	.vsync_gpio = MDP_VSYNC_GPIO,
	.dsi_power_save = mipi_dsi_panel_power,
};

static struct dsi_cmd_desc k2_jdi_display_off_cmds[] = {
	{DTYPE_PERIPHERAL_OFF, 1, 0, 1, 70, sizeof(k2_jdi_peripheral_off), k2_jdi_peripheral_off},
};

static struct dsi_cmd_desc k2_auo_display_off_cmds[] = {
	{DTYPE_PERIPHERAL_OFF, 1, 0, 1, 70, sizeof(k2_peripheral_off), k2_peripheral_off},
};

#ifdef CONFIG_MSM_ACL_ENABLE
static struct dsi_cmd_desc novatek_cabc_on_cmds[] = {
	{DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(led_cabc_pwm_on), led_cabc_pwm_on},
};

static struct dsi_cmd_desc novatek_cabc_off_cmds[] = {
	{DTYPE_DCS_LWRITE, 1, 0, 0, 1, sizeof(led_cabc_pwm_off), led_cabc_pwm_off},
};
#endif

#ifdef CONFIG_MSM_CABC_VIDEO_ENHANCE
static struct dsi_cmd_desc novatek_cabc_UI_cmds[] = {
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e3), k2_e3},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_1), k2_ff_1},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f5), k2_f5},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
};
static struct dsi_cmd_desc novatek_cabc_video_cmds[] = {
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_e3_video), k2_e3_video},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_1), k2_ff_1},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_f5_video), k2_f5_video},
	{DTYPE_DCS_LWRITE, 1, 0, 0, 0, sizeof(k2_ff_2), k2_ff_2},
};
#endif

static int k2_lcd_on(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	struct mipi_panel_info *mipi;
	struct msm_panel_info *pinfo;

	mfd = platform_get_drvdata(pdev);
	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	pinfo = &mfd->panel_info;
	mipi  = &mfd->panel_info.mipi;

	if (mfd->init_mipi_lcd == 0) {
		PR_DISP_DEBUG("Display On - 1st time\n");

		mfd->init_mipi_lcd = 1;
		return 0;
	}

	PR_DISP_INFO("Display On.\n");

	mipi_dsi_cmds_tx(&k2_panel_tx_buf, init_on_cmds,
		init_on_cmds_count);

	atomic_set(&lcd_power_state, 1);

	PR_DISP_DEBUG("Init done!\n");

	return 0;
}

static int k2_lcd_off(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;

	mfd = platform_get_drvdata(pdev);

	if (!mfd)
		return -ENODEV;
	if (mfd->key != MFD_KEY)
		return -EINVAL;

	atomic_set(&lcd_power_state, 0);

	return 0;
}

static int __devinit k2_lcd_probe(struct platform_device *pdev)
{
	struct msm_fb_data_type *mfd;
	struct mipi_panel_info *mipi;
	struct platform_device *current_pdev;
	static struct mipi_dsi_phy_ctrl *phy_settings;
	static char dlane_swap;

	if (pdev->id == 0) {
		mipi_k2_pdata = pdev->dev.platform_data;

		if (mipi_k2_pdata
			&& mipi_k2_pdata->phy_ctrl_settings) {
			phy_settings = (mipi_k2_pdata->phy_ctrl_settings);
		}

		if (mipi_k2_pdata
			&& mipi_k2_pdata->dlane_swap) {
			dlane_swap = (mipi_k2_pdata->dlane_swap);
		}

		return 0;
	}

	current_pdev = msm_fb_add_device(pdev);

	if (current_pdev) {
		mfd = platform_get_drvdata(current_pdev);
		if (!mfd)
			return -ENODEV;
		if (mfd->key != MFD_KEY)
			return -EINVAL;

		mipi  = &mfd->panel_info.mipi;

		if (phy_settings != NULL)
			mipi->dsi_phy_db = phy_settings;

		if (dlane_swap)
			mipi->dlane_swap = dlane_swap;
	}
	return 0;
}

DEFINE_LED_TRIGGER(bkl_led_trigger);
static void k2_display_off(struct msm_fb_data_type *mfd)
{
	
#ifdef NOVATEK_CABC
	atomic_set(&lcd_backlight_off, 1);
#endif
#ifdef CONFIG_BACKLIGHT_WLED_CABC
	if (wled_trigger_initialized) {
		led_trigger_event(bkl_led_trigger, 0);
	}
#endif
	

	cmdreq.cmds = display_off_cmds;
	cmdreq.cmds_cnt = display_off_cmds_count;
	cmdreq.flags = CMD_REQ_COMMIT;
	cmdreq.rlen = 0;
	cmdreq.cb = NULL;

	mipi_dsi_cmdlist_put(&cmdreq);

	PR_DISP_INFO("%s\n", __func__);
}
#ifdef NOVATEK_CABC
static void k2_dim_on(struct msm_fb_data_type *mfd)
{
	if (atomic_read(&lcd_backlight_off)) {
		PR_DISP_DEBUG("%s: backlight is off. Skip dimming setting\n", __func__);
		return;
	}

	PR_DISP_DEBUG("%s\n",  __FUNCTION__);

	cmdreq.cmds = novatek_dim_on_cmds;
	cmdreq.cmds_cnt = ARRAY_SIZE(novatek_dim_on_cmds);
	cmdreq.flags = CMD_REQ_COMMIT;
	cmdreq.rlen = 0;
	cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&cmdreq);
}

#ifdef CONFIG_MSM_ACL_ENABLE
static void k2_cabc_on(int on, struct msm_fb_data_type *mfd)
{
	static int first_time = 1;

	PR_DISP_DEBUG("%s: ON=%d\n",  __FUNCTION__, on);

	if (on == 8 && !first_time) {
		cmdreq.cmds = novatek_cabc_off_cmds;
		cmdreq.cmds_cnt = ARRAY_SIZE(novatek_cabc_off_cmds);
	} else {
		cmdreq.cmds = novatek_cabc_on_cmds;
		cmdreq.cmds_cnt = ARRAY_SIZE(novatek_cabc_on_cmds);
	}
	cmdreq.flags = CMD_REQ_COMMIT;
	cmdreq.rlen = 0;
	cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&cmdreq);

	first_time = 0;
}
#endif

#ifdef CONFIG_MSM_CABC_VIDEO_ENHANCE
static void k2_set_cabc(struct msm_fb_data_type *mfd, int mode)
{
	PR_DISP_DEBUG("%s: mode=%d\n",  __FUNCTION__, mode);

	if (mode == 0) {
		cmdreq.cmds = novatek_cabc_UI_cmds;
		cmdreq.cmds_cnt = ARRAY_SIZE(novatek_cabc_UI_cmds);
	} else {
		cmdreq.cmds = novatek_cabc_video_cmds;
		cmdreq.cmds_cnt = ARRAY_SIZE(novatek_cabc_video_cmds);
	}
	cmdreq.flags = CMD_REQ_COMMIT;
	cmdreq.rlen = 0;
	cmdreq.cb = NULL;
	mipi_dsi_cmdlist_put(&cmdreq);
}
#endif
#endif

#define BRI_SETTING_MIN                 30
#define BRI_SETTING_DEF                 143
#define BRI_SETTING_MAX                 255

static unsigned char k2_shrink_pwm(int val)
{
	unsigned int pwm_min, pwm_default, pwm_max;
	unsigned char shrink_br = BRI_SETTING_MAX;

        if (system_rev >= 0x80) 
           pwm_min = 7;
        else
           pwm_min = 17;

        pwm_default = 99;
        pwm_max = 255;

	if (val <= 0) {
		shrink_br = 0;
	} else if (val > 0 && (val < BRI_SETTING_MIN)) {
			shrink_br = pwm_min;
	} else if ((val >= BRI_SETTING_MIN) && (val <= BRI_SETTING_DEF)) {
			shrink_br = (val - BRI_SETTING_MIN) * (pwm_default - pwm_min) /
		(BRI_SETTING_DEF - BRI_SETTING_MIN) + pwm_min;
	} else if (val > BRI_SETTING_DEF && val <= BRI_SETTING_MAX) {
			shrink_br = (val - BRI_SETTING_DEF) * (pwm_max - pwm_default) /
		(BRI_SETTING_MAX - BRI_SETTING_DEF) + pwm_default;
	} else if (val > BRI_SETTING_MAX)
			shrink_br = pwm_max;

	PR_DISP_INFO("brightness orig=%d, transformed=%d\n", val, shrink_br);

	return shrink_br;
}

static void k2_set_backlight(struct msm_fb_data_type *mfd)
{
	struct mipi_panel_info *mipi;
	led_pwm1[1] = k2_shrink_pwm((unsigned char)(mfd->bl_level));

	if (mipi_k2_pdata && (mipi_k2_pdata->enable_wled_bl_ctrl)
	    && (wled_trigger_initialized)) {
		led_trigger_event(bkl_led_trigger, led_pwm1[1]);
		return;
	}
	mipi  = &mfd->panel_info.mipi;


	
	if (atomic_read(&lcd_power_state) == 0) {
		PR_DISP_DEBUG("%s: LCD is off. Skip backlight setting\n", __func__);
		return;
	}

	if (mdp4_overlay_dsi_state_get() <= ST_DSI_SUSPEND) {
		return;
	}

#ifdef NOVATEK_CABC
        
        if (led_pwm1[1] == 0) {
                atomic_set(&lcd_backlight_off, 1);
				cmdreq.cmds = novatek_dim_off_cmds;
				cmdreq.cmds_cnt = ARRAY_SIZE(novatek_dim_off_cmds);
				cmdreq.flags = CMD_REQ_COMMIT;
				cmdreq.rlen = 0;
				cmdreq.cb = NULL;

				mipi_dsi_cmdlist_put(&cmdreq);
        } else
                atomic_set(&lcd_backlight_off, 0);
#endif
	cmdreq.cmds = novatek_cmd_backlight_cmds;
	cmdreq.cmds_cnt = ARRAY_SIZE(novatek_cmd_backlight_cmds);
	cmdreq.flags = CMD_REQ_COMMIT;
	cmdreq.rlen = 0;
	cmdreq.cb = NULL;

	mipi_dsi_cmdlist_put(&cmdreq);

#ifdef CONFIG_BACKLIGHT_WLED_CABC
	
	if (wled_trigger_initialized) {
		led_trigger_event(bkl_led_trigger, mfd->bl_level);
	}
#endif
	return;
}

static struct mipi_dsi_panel_platform_data k2_pdata = {
#ifdef CONFIG_MACH_K2_WL
	.dlane_swap = 0,
#else
	.dlane_swap = 1,
#endif
#ifdef CONFIG_BACKLIGHT_WLED_CABC
	.enable_wled_bl_ctrl = 0x0,
#else
	.enable_wled_bl_ctrl = 0x1,
#endif
};

static struct platform_device mipi_dsi_k2_panel_device = {
	.name = "mipi_k2",
	.id = 0,
	.dev = {
		.platform_data = &k2_pdata,
	}
};

static struct platform_driver this_driver = {
	.probe  = k2_lcd_probe,
	.driver = {
		.name   = "mipi_k2",
	},
};

static struct msm_fb_panel_data k2_panel_data = {
	.on		= k2_lcd_on,
	.off		= k2_lcd_off,
	//.display_on = k2_display_on,
	//.display_off = k2_display_off,
	.set_backlight = k2_set_backlight,
#ifdef NOVATEK_CABC
	//.dimming_on	= k2_dim_on,
#ifdef CONFIG_MSM_ACL_ENABLE
	//.acl_enable	= k2_cabc_on,
#endif
#ifdef CONFIG_MSM_CABC_VIDEO_ENHANCE
	//.set_cabc	= k2_set_cabc,
#endif
#endif
};

static struct msm_panel_info pinfo;
static int ch_used[3];

int mipi_k2_device_register(struct msm_panel_info *pinfo,
					u32 channel, u32 panel)
{
	struct platform_device *pdev = NULL;
	int ret;

	if ((channel >= 3) || ch_used[channel])
		return -ENODEV;

	ch_used[channel] = TRUE;

	pdev = platform_device_alloc("mipi_k2", (panel << 8)|channel);
	if (!pdev)
		return -ENOMEM;

	k2_panel_data.panel_info = *pinfo;

	ret = platform_device_add_data(pdev, &k2_panel_data,
		sizeof(k2_panel_data));
	if (ret) {
		printk(KERN_ERR
		  "%s: platform_device_add_data failed!\n", __func__);
		goto err_device_put;
	}

	ret = platform_device_add(pdev);
	if (ret) {
		printk(KERN_ERR
		  "%s: platform_device_register failed!\n", __func__);
		goto err_device_put;
	}

	return 0;

err_device_put:
	platform_device_put(pdev);
	return ret;
}

static struct mipi_dsi_phy_ctrl dsi_video_mode_phy_db = {
       
       
       {0x09, 0x08, 0x05, 0x00, 0x20},
       
       {0xA9, 0x18, 0x1A, 0x00, 0x34, 0x38, 0x14,
       0x1B, 0x15, 0x03, 0x04, 0x00},
       
       {0x5F, 0x00, 0x00, 0x10},
       
       {0xFF, 0x00, 0x06, 0x00},
       
       {0x00, 0x37, 0x30, 0xC4, 0x00, 0x20, 0x0A, 0x62,
       0x71, 0x88, 0x99,
       0x00, 0x14, 0x03, 0x00, 0x02, 0x00, 0x20, 0x00, 0x01 },
};

static struct mipi_dsi_reg_set dsi_video_mode_reg_db[] = {
	
	{0x0340, 0xC0},	
	{0x0344, 0xEF},	
	{0x0358, 0x00},	
	
	{0x0380, 0xC0},	
	{0x0384, 0xEF},	
	{0x0398, 0x00},	

	{0x0400, 0x80},	
	{0x0404, 0x23},	
	{0x0408, 0x00},	

	{0x040c, 0x00},	
	{0x0414, 0x01},	
	{0x0418, 0x00}	
};

static int __init mipi_video_novatek_wvga_pt_init(void)
{
	int ret;

	pinfo.xres = 480;
	pinfo.yres = 800;
	pinfo.type = MIPI_VIDEO_PANEL;
	pinfo.pdest = DISPLAY_1;
	pinfo.wait_cycle = 0;
	pinfo.bpp = 24;
	pinfo.width = 56;
	pinfo.height = 93;
	pinfo.camera_backlight = 200;

#if defined (CONFIG_MACH_K2_CL)
    pinfo.lcdc.h_back_porch = 14;
    pinfo.lcdc.h_front_porch = 16;
    pinfo.lcdc.h_pulse_width = 4;
    pinfo.lcdc.v_back_porch = 16;
    pinfo.lcdc.v_front_porch = 20;
    pinfo.lcdc.v_pulse_width = 4;
    pinfo.clk_rate = 312000000;
#else
    pinfo.lcdc.h_back_porch = 10;
    pinfo.lcdc.h_front_porch = 14;
    pinfo.lcdc.h_pulse_width = 4;
    pinfo.lcdc.v_back_porch = 10;
    pinfo.lcdc.v_front_porch = 8;
    pinfo.lcdc.v_pulse_width = 2;
    pinfo.clk_rate = 300000000;
#endif

	pinfo.lcdc.border_clr = 0;	
	pinfo.lcdc.underflow_clr = 0xff;	
	pinfo.lcdc.hsync_skew = 0;
	pinfo.bl_max = 255;
	pinfo.bl_min = 1;
	pinfo.fb_num = 2;

	pinfo.mipi.mode = DSI_VIDEO_MODE;
	pinfo.mipi.pulse_mode_hsa_he = TRUE;
	pinfo.mipi.hfp_power_stop = FALSE;
	pinfo.mipi.hbp_power_stop = FALSE;
	pinfo.mipi.hsa_power_stop = FALSE;
	pinfo.mipi.eof_bllp_power_stop = TRUE;
	pinfo.mipi.bllp_power_stop = TRUE;
	pinfo.mipi.traffic_mode = DSI_NON_BURST_SYNCH_PULSE;
	pinfo.mipi.dst_format = DSI_VIDEO_DST_FORMAT_RGB888;
	pinfo.mipi.vc = 0;
	pinfo.mipi.rgb_swap = DSI_RGB_SWAP_BGR;
	pinfo.mipi.data_lane0 = TRUE;
	pinfo.mipi.data_lane1 = TRUE;
	pinfo.mipi.esc_byte_ratio = 3;

	pinfo.mipi.tx_eot_append = TRUE;
	pinfo.mipi.t_clk_post = 0x04;
	pinfo.mipi.t_clk_pre = 0x1c;
	pinfo.mipi.stream = 0; 
	pinfo.mipi.mdp_trigger = DSI_CMD_TRIGGER_SW;
	pinfo.mipi.dma_trigger = DSI_CMD_TRIGGER_SW;
	pinfo.mipi.frame_rate = 60;

	pinfo.mipi.dsi_phy_db = &dsi_video_mode_phy_db;

	pinfo.mipi.dsi_reg_db = dsi_video_mode_reg_db;
	pinfo.mipi.dsi_reg_db_size = ARRAY_SIZE(dsi_video_mode_reg_db);

	ret = mipi_k2_device_register(&pinfo, MIPI_DSI_PRIM,
						MIPI_DSI_PANEL_WVGA_PT);
	if (ret)
		pr_err("%s: failed to register device!\n", __func__);

	if (panel_type == PANEL_ID_K2_WL_AUO) {
		PR_DISP_INFO("%s: panel_type=PANEL_ID_K2_WL_AUO\n", __func__);
		init_on_cmds = k2_auo_display_on_cmds;
		init_on_cmds_count = ARRAY_SIZE(k2_auo_display_on_cmds);
		display_off_cmds = k2_auo_display_off_cmds;
		display_off_cmds_count = ARRAY_SIZE(k2_auo_display_off_cmds);
	} else if (panel_type == PANEL_ID_K2_WL_AUO_C2) {
		PR_DISP_INFO("%s: panel_type=PANEL_ID_K2_WL_AUO_C2\n", __func__);
		init_on_cmds = k2_auo_display_on_cmds_c2;
		init_on_cmds_count = ARRAY_SIZE(k2_auo_display_on_cmds_c2);
		display_off_cmds = k2_auo_display_off_cmds;
		display_off_cmds_count = ARRAY_SIZE(k2_auo_display_off_cmds);
	} else if (panel_type == PANEL_ID_K2_WL_JDI_NT) {
		PR_DISP_INFO("%s: panel_type=PANEL_ID_K2_WL_JDI\n", __func__);
		init_on_cmds = k2_jdi_display_on_cmds;
		init_on_cmds_count = ARRAY_SIZE(k2_jdi_display_on_cmds);
		display_off_cmds = k2_jdi_display_off_cmds;
		display_off_cmds_count = ARRAY_SIZE(k2_jdi_display_off_cmds);
	} else if (panel_type == PANEL_ID_K2_WL_JDI_NT_T02) {
		PR_DISP_INFO("%s: panel_type=PANEL_ID_K2_WL_JDI_T02\n", __func__);
		init_on_cmds = k2_jdi_display_on_cmds;
		init_on_cmds_count = ARRAY_SIZE(k2_jdi_display_on_cmds);
		display_off_cmds = k2_jdi_display_off_cmds;
		display_off_cmds_count = ARRAY_SIZE(k2_jdi_display_off_cmds);
	}

	return ret;
}

void __init k2_init_fb(void)
{
	platform_device_register(&msm_fb_device);

	if(panel_type != PANEL_ID_NONE && board_mfg_mode() != 5) {
		if (board_mfg_mode() == 4) mdp_pdata.cont_splash_enabled = 0x0;
		platform_device_register(&mipi_dsi_k2_panel_device);
		msm_fb_register_device("mdp", &mdp_pdata);
		msm_fb_register_device("mipi_dsi", &mipi_dsi_pdata);
	}
}

static int __init k2_init_panel(void)
{
	if(panel_type == PANEL_ID_NONE || board_mfg_mode() == 5) {
		PR_DISP_INFO("%s panel ID = PANEL_ID_NONE\n", __func__);
		return 0;
	}

	led_trigger_register_simple("bkl_trigger", &bkl_led_trigger);
	pr_info("%s: SUCCESS (WLED TRIGGER)\n", __func__);
	wled_trigger_initialized = 1;
	atomic_set(&lcd_power_state, 1);

	mipi_dsi_buf_alloc(&k2_panel_tx_buf, DSI_BUF_SIZE);
	mipi_dsi_buf_alloc(&k2_panel_rx_buf, DSI_BUF_SIZE);

	mipi_video_novatek_wvga_pt_init();

	return platform_driver_register(&this_driver);
}

device_initcall_sync(k2_init_panel);
