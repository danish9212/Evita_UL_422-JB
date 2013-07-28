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
#include <linux/i2c.h>
#include <linux/gpio.h>
#include <mach/board.h>
#include <mach/msm_bus_board.h>
#include <mach/gpiomux.h>
#include "devices.h"
#include "board-8930.h"
#include "board-operaul.h"
#include <asm/setup.h>

#include <linux/spi/spi.h>

#include "board-mahimahi-flashlight.h"
#ifdef CONFIG_MSM_CAMERA_FLASH
#include <linux/htc_flashlight.h>
#endif

#define CAM_PIN_GPIO_V_CAM_D1V8_EN	MSM_CAM_D1V8_EN


#define CAM_PIN_GPIO_V_RAW_1V2_EN	MSM_RAW_1V2_EN
#define CAM_PIN_GPIO_RAW_RSTN	MSM_RAW_RSTz
#define CAM_PIN_GPIO_RAW_INTR0	MSM_RAW_INTR0
#define CAM_PIN_GPIO_RAW_INTR1	MSM_RAW_INTR1
#define CAM_PIN_GPIO_CAM_MCLK0	MSM_RAW_MCLK
#define CAM_PIN_GPIO_CAM_MCLK1	MSM_CAM2_MCLK	

#define CAM_PIN_GPIO_CAM_I2C_DAT	MSM_CAM_I2C_SDA	
#define CAM_PIN_GPIO_CAM_I2C_CLK	MSM_CAM_I2C_SCL	

#define CAM_PIN_GPIO_MCAM_SPI_CLK	MSM_MCAM_SPI_CLK
#define CAM_PIN_GPIO_MCAM_SPI_CS0	MSM_MCAM_SPI_CS0
#define CAM_PIN_GPIO_MCAM_SPI_DI	MSM_MCAM_SPI_DI
#define CAM_PIN_GPIO_MCAM_SPI_DO	MSM_MCAM_SPI_DO


#define CAM_PIN_GPIO_CAM_PWDN		MSM_CAM_PWDN
#define CAM_PIN_GPIO_V_CAMIO_1V8_EN	MSM_CAMIO_1V8_EN
#define CAM_PIN_GPIO_CAM_VCM_PD		MSM_CAM1_VCM_PD

#define CAM_PIN_GPIO_CAM2_SEL		MSM_XB_CAM_SEL
#define CAM_PIN_GPIO_CAM2_RSTz		MSM_FRONT_CAM_RSTz
#define CAM_PIN_GPIO_CAM2_STANDBY	0

static struct gpiomux_setting cam_settings[] = {
	{
		.func = GPIOMUX_FUNC_GPIO, 
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
	},

	{
		.func = GPIOMUX_FUNC_1, 
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, 
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},

	{
		.func = GPIOMUX_FUNC_1, 
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_2, 
		.drv = GPIOMUX_DRV_8MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, 
		.drv = GPIOMUX_DRV_4MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
	},

	{
		.func = GPIOMUX_FUNC_2, 
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, 
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_IN,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, 
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_DOWN,
		.dir = GPIOMUX_IN,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, 
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_HIGH,
	},

	{
		.func = GPIOMUX_FUNC_GPIO, 
		.drv = GPIOMUX_DRV_2MA,
		.pull = GPIOMUX_PULL_NONE,
		.dir = GPIOMUX_OUT_LOW,
	},
};


static struct msm_gpiomux_config msm8930_cam_common_configs[] = {
	{
		.gpio = CAM_PIN_GPIO_CAM_MCLK0,	
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[1], 
			[GPIOMUX_SUSPENDED] = &cam_settings[2], 
		},
	},
	{
		.gpio = CAM_PIN_GPIO_CAM_MCLK1,	
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[4], 
			[GPIOMUX_SUSPENDED] = &cam_settings[2], 
		},
	},
	
	{
		.gpio = CAM_PIN_GPIO_CAM_I2C_DAT,	
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3], 
			[GPIOMUX_SUSPENDED] = &cam_settings[0],
		},
	},
	{
		.gpio = CAM_PIN_GPIO_CAM_I2C_CLK,	
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[3], 
			[GPIOMUX_SUSPENDED] = &cam_settings[0],
		},
	},
	{
		.gpio = CAM_PIN_GPIO_RAW_INTR0,	
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[7], 
			[GPIOMUX_SUSPENDED] = &cam_settings[8], 
		},
	},
	{
		.gpio = CAM_PIN_GPIO_RAW_INTR1,	
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_settings[7], 
			[GPIOMUX_SUSPENDED] = &cam_settings[8], 
		},
	},
	
	{
		.gpio      = CAM_PIN_GPIO_MCAM_SPI_CLK,
		.settings = {
			[GPIOMUX_ACTIVE] = &cam_settings[4], 
			[GPIOMUX_SUSPENDED] = &cam_settings[2], 
		},
	},
	{
		.gpio      = CAM_PIN_GPIO_MCAM_SPI_CS0,
		.settings = {
			[GPIOMUX_ACTIVE] = &cam_settings[6], 
			[GPIOMUX_SUSPENDED] = &cam_settings[10], 
		},
	},
	{
		.gpio      = CAM_PIN_GPIO_MCAM_SPI_DI,
		.settings = {
			[GPIOMUX_ACTIVE] = &cam_settings[4], 
			[GPIOMUX_SUSPENDED] = &cam_settings[0], 
		},
	},
	{
		.gpio      = CAM_PIN_GPIO_MCAM_SPI_DO,
		.settings = {
			[GPIOMUX_ACTIVE] = &cam_settings[4], 
			[GPIOMUX_SUSPENDED] = &cam_settings[2], 
		},
	},
};

static struct msm_bus_vectors cam_init_vectors[] = {
	{
		.src = MSM_BUS_MASTER_VFE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 0,
		.ib  = 0,
	},
	{
		.src = MSM_BUS_MASTER_VPE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 0,
		.ib  = 0,
	},
	{
		.src = MSM_BUS_MASTER_JPEG_ENC,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 0,
		.ib  = 0,
	},
};


static struct msm_bus_vectors cam_preview_vectors[] = {
	{
		.src = MSM_BUS_MASTER_VFE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 96215040,
		.ib  = 378224640,
	},
	{
		.src = MSM_BUS_MASTER_VPE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 0,
		.ib  = 0,
	},
	{
		.src = MSM_BUS_MASTER_JPEG_ENC,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 0,
		.ib  = 0,
	},
};

static struct msm_bus_vectors cam_video_vectors[] = {
	{
		.src = MSM_BUS_MASTER_VFE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 650000000,
		.ib  = 1361968128,
	},
	{
		.src = MSM_BUS_MASTER_VPE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 207747072,
		.ib  = 489756672,
	},
	{
		.src = MSM_BUS_MASTER_JPEG_ENC,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 60318720,
		.ib  = 150796800,
	},
};

static struct msm_bus_vectors cam_snapshot_vectors[] = {
	{
		.src = MSM_BUS_MASTER_VFE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 147045888,
		.ib  = 588183552,
	},
	{
		.src = MSM_BUS_MASTER_VPE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 0,
		.ib  = 0,
	},
	{
		.src = MSM_BUS_MASTER_JPEG_ENC,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 263678976,
		.ib  = 659197440,
	},
};

static struct msm_bus_vectors cam_zsl_vectors[] = {
	{
		.src = MSM_BUS_MASTER_VFE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 650000000,
		.ib  = 1271531520,
	},
	{
		.src = MSM_BUS_MASTER_VPE,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 0,
		.ib  = 0,
	},
	{
		.src = MSM_BUS_MASTER_JPEG_ENC,
		.dst = MSM_BUS_SLAVE_EBI_CH0,
		.ab  = 239708160,
		.ib  = 599270400,
	},
};

static struct msm_bus_paths cam_bus_client_config[] = {
	{
		ARRAY_SIZE(cam_init_vectors),
		cam_init_vectors,
	},
	{
		ARRAY_SIZE(cam_preview_vectors),
		cam_preview_vectors,
	},
	{
		ARRAY_SIZE(cam_video_vectors),
		cam_video_vectors,
	},
	{
		ARRAY_SIZE(cam_snapshot_vectors),
		cam_snapshot_vectors,
	},
	{
		ARRAY_SIZE(cam_zsl_vectors),
		cam_zsl_vectors,
	},
};

static struct msm_bus_scale_pdata cam_bus_client_pdata = {
		cam_bus_client_config,
		ARRAY_SIZE(cam_bus_client_config),
		.name = "msm_camera",
};


#if defined(CONFIG_OV5693) || defined(CONFIG_S5K6A2YA)
static struct regulator *reg_8038_l2;	
static struct regulator *reg_8038_l8;	

#ifdef CONFIG_S5K6A2YA
static struct regulator *reg_8038_l12;	
#endif

static struct regulator *reg_8038_l17;	


static int camera_sensor_power_enable(char *power, unsigned volt, struct regulator **sensor_power)
{
	int rc;

	if (power == NULL)
		return -ENODEV;

	*sensor_power = regulator_get(NULL, power);

	if (IS_ERR(*sensor_power)) {
		pr_err("%s: Unable to get %s\n", __func__, power);
		return -ENODEV;
	}

	if (strcmp(power, "8038_l17") == 0) {
		regulator_set_optimum_mode(*sensor_power, 10000);
	}

	if (volt != 1800000) {
		rc = regulator_set_voltage(*sensor_power, volt, volt);
		if (rc < 0) {
			pr_err("%s: unable to set %s voltage to %d rc:%d\n",
					__func__, power, volt, rc);
			regulator_put(*sensor_power);
			*sensor_power = NULL;
			return -ENODEV;
		}
	}

	rc = regulator_enable(*sensor_power);
	if (rc < 0) {
		pr_err("%s: Enable regulator %s failed\n", __func__, power);
		regulator_put(*sensor_power);
		*sensor_power = NULL;
		return -ENODEV;
	}

	return rc;
}

static int camera_sensor_power_disable(struct regulator *sensor_power)
{

	int rc;
	if (sensor_power == NULL)
		return -ENODEV;

	if (IS_ERR(sensor_power)) {
		pr_err("%s: Invalid requlator ptr\n", __func__);
		return -ENODEV;
	}

	rc = regulator_disable(sensor_power);
	if (rc < 0)
		pr_err("%s: disable regulator failed\n", __func__);

	regulator_put(sensor_power);
	sensor_power = NULL;
	return rc;
}
#endif

static int msm8930_csi_vreg_on(void)
{
	pr_info("%s\n", __func__);
	return camera_sensor_power_enable("8038_l2", 1200000, &reg_8038_l2);
}

static int msm8930_csi_vreg_off(void)
{
	pr_info("%s\n", __func__);
	return camera_sensor_power_disable(reg_8038_l2);
}

struct msm_camera_device_platform_data msm_camera_csi_device_data[] = {
	{
		.ioclk.mclk_clk_rate = 24000000,
		.ioclk.vfe_clk_rate  = 228570000,
		.csid_core = 0,
		.camera_csi_on = msm8930_csi_vreg_on,
		.camera_csi_off = msm8930_csi_vreg_off,
		.cam_bus_scale_table = &cam_bus_client_pdata,
		.csid_core = 0,
		.is_csiphy = 1,
		.is_csid   = 1,
		.is_ispif  = 1,
		.is_vpe    = 1,
	},
	{
		.ioclk.mclk_clk_rate = 24000000,
		.ioclk.vfe_clk_rate  = 228570000,
		.csid_core = 1,
		.camera_csi_on = msm8930_csi_vreg_on,
		.camera_csi_off = msm8930_csi_vreg_off,
		.cam_bus_scale_table = &cam_bus_client_pdata,
		.csid_core = 1,
		.is_csiphy = 1,
		.is_csid   = 1,
		.is_ispif  = 1,
		.is_vpe    = 1,
	},
};

#ifdef CONFIG_RAWCHIPII
static int msm8930_use_ext_1v2(void)
{
	return 1;
}

static int msm8930_rawchip_vreg_on(void)
{
	int rc = 0;
	pr_info("%s\n", __func__);

	
	rc = gpio_request(CAM_PIN_GPIO_V_CAM_D1V8_EN, "V_CAM_D1V8_EN");
	pr_info("rawchip 1v8 gpio_request, %d rc(%d)\n", CAM_PIN_GPIO_V_CAM_D1V8_EN, rc);
	if (rc < 0) {
		pr_err("rawchip on (\"gpio %d\", 1.8V) FAILED", CAM_PIN_GPIO_V_CAM_D1V8_EN);
		goto enable_rawchip_1v8_fail;
	}
	gpio_direction_output(CAM_PIN_GPIO_V_CAM_D1V8_EN, 1);
	gpio_free(CAM_PIN_GPIO_V_CAM_D1V8_EN);
	mdelay(1);

	
	rc = gpio_request(CAM_PIN_GPIO_V_RAW_1V2_EN, "_V_RAW_1V2_EN");
	pr_info("rawchip 1v2 gpio_request, %d rc(%d)\n", CAM_PIN_GPIO_V_RAW_1V2_EN, rc);
	if (rc < 0) {
		pr_err("rawchip on (\"gpio %d\", 1.2V) FAILED", CAM_PIN_GPIO_V_RAW_1V2_EN);
		goto enable_rawchip_1v2_fail;
	}
	gpio_direction_output(CAM_PIN_GPIO_V_RAW_1V2_EN, 1);
	gpio_free(CAM_PIN_GPIO_V_RAW_1V2_EN);

	return rc;

enable_rawchip_1v2_fail:
	rc = gpio_request(CAM_PIN_GPIO_V_CAM_D1V8_EN, "V_CAM_D1V8_EN");
	if (rc < 0)
		pr_err("rawchip off (\"gpio %d\", 1.8V) FAILED", CAM_PIN_GPIO_V_CAM_D1V8_EN);
	else {
		gpio_direction_output(CAM_PIN_GPIO_V_CAM_D1V8_EN, 0);
		gpio_free(CAM_PIN_GPIO_V_CAM_D1V8_EN);
	}
enable_rawchip_1v8_fail:
	return rc;

}

static int msm8930_rawchip_vreg_off(void)
{
	int rc = 0;
	pr_info("%s\n", __func__);

	rc = gpio_request(CAM_PIN_GPIO_V_RAW_1V2_EN, "V_RAW_1V2_EN");
	pr_info("rawchip 1v2 gpio_request, %d\n", CAM_PIN_GPIO_V_RAW_1V2_EN);
	if (rc < 0)
		pr_err("rawchip off (\"gpio %d\", 1.2V) FAILED", CAM_PIN_GPIO_V_RAW_1V2_EN);
	else {
		gpio_direction_output(CAM_PIN_GPIO_V_RAW_1V2_EN, 0);
		gpio_free(CAM_PIN_GPIO_V_RAW_1V2_EN);
	}
	udelay(50);

	rc = gpio_request(CAM_PIN_GPIO_V_CAM_D1V8_EN, "V_CAM_D1V8_EN");
	pr_info("rawchip 1v8 gpio_request, %d\n", CAM_PIN_GPIO_V_CAM_D1V8_EN);
	if (rc < 0)
		pr_err("rawchip off (\"gpio %d\", 1.8V) FAILED", CAM_PIN_GPIO_V_CAM_D1V8_EN);
	else {
		gpio_direction_output(CAM_PIN_GPIO_V_CAM_D1V8_EN, 0);
		gpio_free(CAM_PIN_GPIO_V_CAM_D1V8_EN);
	}

	return rc;
}

static struct msm_camera_rawchip_info operaul_msm_rawchip_board_info = {
	.rawchip_reset	= CAM_PIN_GPIO_RAW_RSTN,
	.rawchip_intr0	= MSM_GPIO_TO_INT(CAM_PIN_GPIO_RAW_INTR0),
	.rawchip_intr1	= MSM_GPIO_TO_INT(CAM_PIN_GPIO_RAW_INTR1),
	.rawchip_spi_freq = 27, 
	.rawchip_mclk_freq = 24, 
	.camera_rawchip_power_on = msm8930_rawchip_vreg_on,
	.camera_rawchip_power_off = msm8930_rawchip_vreg_off,
	.rawchip_use_ext_1v2 = msm8930_use_ext_1v2,
};

struct platform_device operaul_msm_rawchip_device = {
	.name	= "rawchip",
	.dev	= {
		.platform_data = &operaul_msm_rawchip_board_info,
	},
};
#endif

#if 0
static void mclk_switch(int camera_id)
{
	int rc = 0;

	rc = gpio_request(CAM_PIN_GPIO_CAM_MCLK1, "CAM_PIN_GPIO_CAM_MCLK1");
	if (rc == 0) {
		gpio_direction_output(CAM_PIN_GPIO_CAM_MCLK1, camera_id);
		gpio_free(CAM_PIN_GPIO_CAM_MCLK1);
		mdelay(5);
	}
	else {
		pr_err("mclk switch fail\n");
	}
}
#endif

static uint16_t msm_cam_gpio_tbl[] = {
	CAM_PIN_GPIO_CAM_MCLK0, 
	CAM_PIN_GPIO_CAM_MCLK1,
#if 0
	CAM_PIN_GPIO_CAM_I2C_DAT, 
	CAM_PIN_GPIO_CAM_I2C_CLK, 
#endif
	CAM_PIN_GPIO_RAW_INTR0,
	CAM_PIN_GPIO_RAW_INTR1,
	CAM_PIN_GPIO_MCAM_SPI_CLK,
	CAM_PIN_GPIO_MCAM_SPI_CS0,
	CAM_PIN_GPIO_MCAM_SPI_DI,
	CAM_PIN_GPIO_MCAM_SPI_DO,
};

static struct msm_camera_gpio_conf gpio_conf = {
	.cam_gpiomux_conf_tbl = NULL,
	.cam_gpiomux_conf_tbl_size = 0,
	.cam_gpio_tbl = msm_cam_gpio_tbl,
	.cam_gpio_tbl_size = ARRAY_SIZE(msm_cam_gpio_tbl),
};

#ifdef CONFIG_OV5693
static int msm8930_ov5693_vreg_on(void)
{
	int rc;
	pr_info("%s\n", __func__);

	
	rc = camera_sensor_power_enable("8038_l17", 2850000, &reg_8038_l17);
	pr_info("vcm sensor_power_enable(\"8038_l17\", 2.8V) == %d\n", rc);
	if (rc < 0) {
		pr_err("sensor_power_enable(\"8038_l17\", 2.8V) FAILED %d\n", rc);
		goto enable_ov5693_vcm_fail;
	}
	udelay(50);

	
	rc = camera_sensor_power_enable("8038_l8", 2800000, &reg_8038_l8);
	pr_info("analog sensor_power_enable(\"8038_l8\", 2.8V) == %d\n", rc);
	if (rc < 0) {
		pr_err("sensor_power_enable(\"8038_l8\", 2.8V) FAILED %d\n", rc);
		goto enable_ov5693_analog_fail;
	}
	udelay(50);

	
	rc = gpio_request(CAM_PIN_GPIO_V_CAMIO_1V8_EN, "V_CAMIO_1V8_EN");
	pr_info("cam io gpio_request, %d\n", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	if (rc < 0) {
		pr_err("GPIO(%d) request failed", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
		goto enable_ov5693_io_fail;
	}
	gpio_direction_output(CAM_PIN_GPIO_V_CAMIO_1V8_EN, 1);
	gpio_free(CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	udelay(50);

	
	rc = gpio_request(CAM_PIN_GPIO_CAM2_RSTz, "s5k6a2ya");
	pr_info(" reset pin gpio_request, %d\n", CAM_PIN_GPIO_CAM2_RSTz);
	if (rc < 0) {
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_CAM2_RSTz);
	}
	gpio_direction_output(CAM_PIN_GPIO_CAM2_RSTz, 0);
	gpio_free(CAM_PIN_GPIO_CAM2_RSTz);

	return rc;

enable_ov5693_io_fail:
	camera_sensor_power_disable(reg_8038_l8);
enable_ov5693_analog_fail:
	rc = gpio_request(CAM_PIN_GPIO_V_CAM_D1V8_EN, "V_CAM_D1V8_EN");
	if (rc < 0)
		pr_err("GPIO(%d) request failed", CAM_PIN_GPIO_V_CAM_D1V8_EN);
	else {
		gpio_direction_output(CAM_PIN_GPIO_V_CAM_D1V8_EN, 0);
		gpio_free(CAM_PIN_GPIO_V_CAM_D1V8_EN);
	}
enable_ov5693_vcm_fail:
	return rc;
}

static int msm8930_ov5693_vreg_off(void)
{
	int rc = 0;

	pr_info("%s\n", __func__);

	
	rc = camera_sensor_power_disable(reg_8038_l8);
	pr_info("sensor_power_disable(\"8038_l8\") == %d\n", rc);
	if (rc < 0)
		pr_err("sensor_power_disable\(\"8038_l8\") FAILED %d\n", rc);
	udelay(50);

	
	rc = gpio_request(CAM_PIN_GPIO_V_CAMIO_1V8_EN, "V_CAMIO_1V8_EN");
	pr_info("cam io gpio_request, %d\n", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	if (rc < 0)
		pr_err("GPIO(%d) request failed", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	else {
		gpio_direction_output(CAM_PIN_GPIO_V_CAMIO_1V8_EN, 0);
		gpio_free(CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	}
	udelay(50);

	
	if (reg_8038_l17 != NULL)
		regulator_set_optimum_mode(reg_8038_l17, 9000);
	rc = camera_sensor_power_disable(reg_8038_l17);
	pr_info("sensor_power_disable(\"8038_l17\") == %d\n", rc);
	if (rc < 0)
		pr_err("sensor_power_disable\(\"8038_l17\") FAILED %d\n", rc);

	return rc;
}

#ifdef CONFIG_OV5693_ACT
static struct i2c_board_info ov5693_actuator_i2c_info = {
	I2C_BOARD_INFO("ov5693_act", 0x0C),
};

static struct msm_actuator_info ov5693_actuator_info = {
	.board_info     = &ov5693_actuator_i2c_info,
	.bus_id         = MSM_8930_GSBI4_QUP_I2C_BUS_ID,
	.vcm_pwd        = CAM_PIN_GPIO_CAM_VCM_PD,
	.vcm_enable     = 1,
};
#endif

static struct msm_camera_csi_lane_params ov5693_csi_lane_params = {
	.csi_lane_assign = 0xE4,
	.csi_lane_mask = 0x3,
};

static struct msm_camera_sensor_platform_info sensor_ov5693_board_info = {
	.mount_angle = 90,
	.mirror_flip = CAMERA_SENSOR_FLIP,
	.sensor_reset_enable = 0,
	.sensor_reset	= 0,
	.sensor_pwd	= CAM_PIN_GPIO_CAM_PWDN,
	.vcm_pwd	= CAM_PIN_GPIO_CAM_VCM_PD,
	.vcm_enable	= 1,
	.csi_lane_params = &ov5693_csi_lane_params,
};

static struct camera_led_est msm_camera_sensor_ov5693_led_table[] = {
	{
		.enable = 1,
		.led_state = FL_MODE_FLASH_LEVEL2,
		.current_ma = 200,
		.lumen_value = 250,
		.min_step = 29,
		.max_step = 128
	},
	{
		.enable = 1,
		.led_state = FL_MODE_FLASH_LEVEL3,
		.current_ma = 300,
		.lumen_value = 350,
		.min_step = 27,
		.max_step = 28
	},
	{
		.enable = 1,
		.led_state = FL_MODE_FLASH_LEVEL4,
		.current_ma = 400,
		.lumen_value = 440,
		.min_step = 25,
		.max_step = 26
	},
	{
		.enable = 1,
		.led_state = FL_MODE_FLASH_LEVEL6,
		.current_ma = 600,
		.lumen_value = 625,
		.min_step = 23,
		.max_step = 24
	},

	{
		.enable = 1,
		.led_state = FL_MODE_FLASH,
		.current_ma = 750,
		.lumen_value = 745,
		.min_step = 0,
		.max_step = 22    
	},
	{
		.enable = 2,
		.led_state = FL_MODE_FLASH_LEVEL2,
		.current_ma = 200,
		.lumen_value = 250,
		.min_step = 0,
		.max_step = 270
	},
	{
		.enable = 0,
		.led_state = FL_MODE_OFF,
		.current_ma = 0,
		.lumen_value = 0,
		.min_step = 0,
		.max_step = 0
	},
	{
		.enable = 0,
		.led_state = FL_MODE_TORCH,
		.current_ma = 150,
		.lumen_value = 150,
		.min_step = 0,
		.max_step = 0
	},
	{
		.enable = 2,     
		.led_state = FL_MODE_FLASH,
		.current_ma = 750,
		.lumen_value = 745,
		.min_step = 271,
		.max_step = 317    
	},
	{
		.enable = 0,
		.led_state = FL_MODE_FLASH_LEVEL5,
		.current_ma = 500,
		.lumen_value = 500,
		.min_step = 25,
		.max_step = 26
	},
	{
		.enable = 0,
		.led_state = FL_MODE_FLASH,
		.current_ma = 750,
		.lumen_value = 750,
		.min_step = 271,
		.max_step = 325
	},
	{
		.enable = 0,
		.led_state = FL_MODE_TORCH_LEVEL_2,
		.current_ma = 200,
		.lumen_value = 75,
		.min_step = 0,
		.max_step = 40
	},
};


static struct camera_led_info msm_camera_sensor_ov5693_led_info = {
	.enable = 1,
	.low_limit_led_state = FL_MODE_TORCH,
	.max_led_current_ma = 750,  
	.num_led_est_table = ARRAY_SIZE(msm_camera_sensor_ov5693_led_table),
};

static struct camera_flash_info msm_camera_sensor_ov5693_flash_info = {
	.led_info = &msm_camera_sensor_ov5693_led_info,
	.led_est_table = msm_camera_sensor_ov5693_led_table,
};

static struct camera_flash_cfg msm_camera_sensor_ov5693_flash_cfg = {
	.low_temp_limit		= 5,
	.low_cap_limit		= 15,
	.flash_info			= &msm_camera_sensor_ov5693_flash_info,
};

#ifdef CONFIG_MSM_CAMERA_FLASH
int msm8930_flashlight_control_ov5693(int mode)
{
pr_info("%s, linear led, mode=%d", __func__, mode);
#ifdef CONFIG_FLASHLIGHT_TPS61310
	return tps61310_flashlight_control(mode);
#else
	return 0;
#endif
}

static struct msm_camera_sensor_flash_src msm_camera_flash_src_ov5693 = {
	.flash_sr_type = MSM_CAMERA_FLASH_SRC_CURRENT_DRIVER,
	.camera_flash = msm8930_flashlight_control_ov5693,
};
#endif

static struct msm_camera_sensor_flash_data flash_ov5693 = {
	.flash_type	= MSM_CAMERA_FLASH_LED,
#ifdef CONFIG_MSM_CAMERA_FLASH
	.flash_src	= &msm_camera_flash_src_ov5693,
#endif

};

static struct msm_camera_sensor_info msm_camera_sensor_ov5693_data = {
	.sensor_name	= "ov5693",
	.camera_power_on = msm8930_ov5693_vreg_on,
	.camera_power_off = msm8930_ov5693_vreg_off,
	.pdata	= &msm_camera_csi_device_data[0],
	.flash_data	= &flash_ov5693,
	.sensor_platform_info = &sensor_ov5693_board_info,
	.gpio_conf = &gpio_conf,
	.csi_if	= 1,
	.camera_type = BACK_CAMERA_2D,
	.sensor_type = BAYER_SENSOR,
#ifdef CONFIG_OV5693_ACT
	.actuator_info = &ov5693_actuator_info,
#endif
	.use_rawchip = RAWCHIP_ENABLE,
	.flash_cfg = &msm_camera_sensor_ov5693_flash_cfg, 
};

#endif	

#ifdef CONFIG_S5K6A2YA
static int msm8930_s5k6a2ya_vreg_on(void)
{
	int rc;
	pr_info(" %s\n", __func__);

	
	rc = camera_sensor_power_enable("8038_l17", 2850000, &reg_8038_l17);
	pr_info(" sensor_power_enable(\"8038_l17\", 2.8V) == %d\n", rc);
	if (rc < 0) {
		pr_err(" sensor_power_enable(\"8038_l17\", 2.8V) FAILED %d\n", rc);
		goto enable_s5k6a2ya_vcm_fail;
	}
	udelay(50);

	
	rc = camera_sensor_power_enable("8038_l8", 2800000, &reg_8038_l8);
	pr_info(" sensor_power_enable(\"8038_l8\", 2.8V) == %d\n", rc);
	if (rc < 0) {
		pr_err(" sensor_power_enable(\"8038_l8\", 2.8V) FAILED %d\n", rc);
		goto enable_s5k6a2ya_analog_fail;
	}
	udelay(50);

	
	rc = gpio_request(CAM_PIN_GPIO_V_CAMIO_1V8_EN, "V_CAMIO_1V8_EN");
	pr_info(" cam io gpio_request, %d\n", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	if (rc < 0) {
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
		goto enable_s5k6a2ya_io_fail;
	}
	gpio_direction_output(CAM_PIN_GPIO_V_CAMIO_1V8_EN, 1);
	gpio_free(CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	udelay(50);

	
	rc = gpio_request(CAM_PIN_GPIO_CAM2_RSTz, "s5k6a2ya");
	pr_info(" reset pin gpio_request, %d\n", CAM_PIN_GPIO_CAM2_RSTz);
	if (rc < 0) {
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_CAM2_RSTz);
		goto enable_s5k6a2ya_rst_fail;
	}
	gpio_direction_output(CAM_PIN_GPIO_CAM2_RSTz, 1);
	gpio_free(CAM_PIN_GPIO_CAM2_RSTz);
	mdelay(1);

	
	rc = camera_sensor_power_enable("8038_l12", 1200000, &reg_8038_l12);
	pr_info(" sensor_power_enable(\"8038_l12\", 1.2V) == %d\n", rc);
	if (rc < 0) {
		pr_err(" sensor_power_enable(\"8038_l12\", 1.2V) FAILED %d\n", rc);
		goto enable_s5k6a2ya_cam2_d1v2_fail;
	}
	udelay(50);

	
	rc = gpio_request(CAM_PIN_GPIO_CAM2_SEL, "CAM2_SEL");
	pr_info(" cam sel gpio_request, %d\n", CAM_PIN_GPIO_CAM2_SEL);
	if (rc < 0) {
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_CAM2_SEL);
		goto enable_s5k6a2ya_cam2_sel_fail;
	}
	gpio_direction_output(CAM_PIN_GPIO_CAM2_SEL, 1);
	gpio_free(CAM_PIN_GPIO_CAM2_SEL);
	udelay(50);


	udelay(500);

	return rc;

enable_s5k6a2ya_cam2_sel_fail:
	camera_sensor_power_disable(reg_8038_l12);
enable_s5k6a2ya_cam2_d1v2_fail:
	rc = gpio_request(CAM_PIN_GPIO_CAM2_RSTz, "s5k6a2ya");
	if (rc < 0)
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_CAM2_RSTz);
	else {
		gpio_direction_output(CAM_PIN_GPIO_CAM2_RSTz, 0);
		gpio_free(CAM_PIN_GPIO_CAM2_RSTz);
	}
enable_s5k6a2ya_rst_fail:
	rc = gpio_request(CAM_PIN_GPIO_V_CAMIO_1V8_EN, "V_CAMIO_1V8_EN");
	if (rc < 0)
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	else {
		gpio_direction_output(CAM_PIN_GPIO_V_CAMIO_1V8_EN, 0);
		gpio_free(CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	}
enable_s5k6a2ya_io_fail:
	camera_sensor_power_disable(reg_8038_l8);
enable_s5k6a2ya_analog_fail:
	camera_sensor_power_disable(reg_8038_l17);
enable_s5k6a2ya_vcm_fail:
	return rc;
}

static int msm8930_s5k6a2ya_vreg_off(void)
{
	int rc = 0;
	pr_info(" %s\n", __func__);



	
	rc = gpio_request(CAM_PIN_GPIO_CAM2_SEL, "CAM2_SEL");
	pr_info(" cam sel gpio_request, %d\n", CAM_PIN_GPIO_CAM2_SEL);
	if (rc < 0)
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_CAM2_SEL);
	else {
		gpio_direction_output(CAM_PIN_GPIO_CAM2_SEL, 0);
		gpio_free(CAM_PIN_GPIO_CAM2_SEL);
	}
	udelay(50);

	
	pr_info(" sensor_power_disable(\"8038_l12\") == %d\n", rc);
	rc = camera_sensor_power_disable(reg_8038_l12);
	if (rc < 0)
		pr_err(" sensor_power_disable(\"reg_8038_l12\") FAILED %d\n", rc);
	udelay(50);

	
	rc = gpio_request(CAM_PIN_GPIO_CAM2_RSTz, "s5k6a2ya");
	pr_info(" reset pin gpio_request, %d\n", CAM_PIN_GPIO_CAM2_RSTz);
	if (rc < 0)
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_CAM2_RSTz);
	else {
		gpio_direction_output(CAM_PIN_GPIO_CAM2_RSTz, 0);
		gpio_free(CAM_PIN_GPIO_CAM2_RSTz);
	}
	udelay(50);

	
	rc = gpio_request(CAM_PIN_GPIO_V_CAMIO_1V8_EN, "V_CAMIO_1V8_EN");
	pr_info(" cam io gpio_request, %d\n", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	if (rc < 0)
		pr_err(" GPIO(%d) request failed", CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	else {
		gpio_direction_output(CAM_PIN_GPIO_V_CAMIO_1V8_EN, 0);
		gpio_free(CAM_PIN_GPIO_V_CAMIO_1V8_EN);
	}
	udelay(50);

	
	pr_info(" sensor_power_disable(\"8038_l8\") == %d\n", rc);
	rc = camera_sensor_power_disable(reg_8038_l8);
	if (rc < 0)
		pr_err(" sensor_power_disable(\"reg_8038_l8\") FAILED %d\n", rc);
	udelay(50);

	
	pr_info(" sensor_power_disable(\"reg_8038_l17\") == %d\n", rc);
	rc = camera_sensor_power_disable(reg_8038_l17);
	if (rc < 0)
		pr_err(" sensor_power_disable(\"reg_8038_l17\") FAILED %d\n", rc);

	return rc;
}

static struct msm_camera_csi_lane_params s5k6a2ya_csi_lane_params = {
	.csi_lane_assign = 0xE4,
	.csi_lane_mask = 0x1,
};

static struct msm_camera_sensor_platform_info sensor_s5k6a2ya_board_info = {
	.mount_angle = 270,
	.mirror_flip = CAMERA_SENSOR_MIRROR_FLIP,
	.sensor_reset_enable = 1,
	.sensor_reset	= CAM_PIN_GPIO_CAM2_RSTz,
	.sensor_pwd	= CAM_PIN_GPIO_CAM2_STANDBY,
	.vcm_pwd	= CAM_PIN_GPIO_CAM_VCM_PD,
	.vcm_enable	= 0,
	.csi_lane_params = &s5k6a2ya_csi_lane_params,
};

static struct msm_camera_sensor_flash_data flash_s5k6a2ya = {
	.flash_type	= MSM_CAMERA_FLASH_NONE,
};

static struct msm_camera_sensor_info msm_camera_sensor_s5k6a2ya_data = {
	.sensor_name	= "s5k6a2ya",
	.sensor_reset	= CAM_PIN_GPIO_CAM2_RSTz,
	.sensor_pwd	= CAM_PIN_GPIO_CAM2_STANDBY,
	.vcm_pwd	= 0,
	.vcm_enable	= 0,
	.camera_power_on = msm8930_s5k6a2ya_vreg_on,
	.camera_power_off = msm8930_s5k6a2ya_vreg_off,
	.pdata	= &msm_camera_csi_device_data[0],
	.flash_data	= &flash_s5k6a2ya,
	.sensor_platform_info = &sensor_s5k6a2ya_board_info,
	.gpio_conf = &gpio_conf,
	.csi_if	= 1,
	.camera_type = FRONT_CAMERA_2D,
	.use_rawchip = RAWCHIP_ENABLE,
};
#endif	


static struct platform_device msm_camera_server = {
	.name = "msm_cam_server",
	.id = 0,
};

void __init operaul_init_cam(void)
{
	pr_info("msm8930_cam_common_configs");

	msm_gpiomux_install(msm8930_cam_common_configs,
			ARRAY_SIZE(msm8930_cam_common_configs));

	platform_device_register(&msm_camera_server);
	platform_device_register(&msm8960_device_csiphy0);
	platform_device_register(&msm8960_device_csiphy1);
	platform_device_register(&msm8960_device_csid0);
	platform_device_register(&msm8960_device_csid1);
	platform_device_register(&msm8960_device_ispif);
	platform_device_register(&msm8960_device_vfe);
	platform_device_register(&msm8960_device_vpe);

	if (system_rev >= 2) {
		sensor_s5k6a2ya_board_info.mirror_flip = CAMERA_SENSOR_NONE;
	}

}

#ifdef CONFIG_I2C
struct i2c_board_info operaul_camera_i2c_boardinfo[] = {
#ifdef CONFIG_OV5693
	{
	I2C_BOARD_INFO("ov5693", 0x20 >> 1),
	.platform_data = &msm_camera_sensor_ov5693_data,
	},
#endif
#ifdef CONFIG_S5K6A2YA
	{
	I2C_BOARD_INFO("s5k6a2ya", 0x6C >> 1),
	.platform_data = &msm_camera_sensor_s5k6a2ya_data,
	},
#endif
};

struct msm_camera_board_info operaul_camera_board_info= {
	.board_info = operaul_camera_i2c_boardinfo,
	.num_i2c_board_info = ARRAY_SIZE(operaul_camera_i2c_boardinfo),
};
#endif
