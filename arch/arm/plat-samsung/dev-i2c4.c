/* linux/arch/arm/plat-samsung/dev-i2c4.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * S5P series device definition for i2c device 3
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/gfp.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/platform_device.h>

#include <mach/irqs.h>
#include <mach/map.h>

#include <plat/regs-iic.h>
#include <plat/iic.h>
#include <plat/devs.h>
#include <plat/cpu.h>

static struct resource s3c_i2c_resource[] = {
	[0] = {
		.start	= S3C_PA_IIC4,
		.end	= S3C_PA_IIC4 + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= IRQ_IIC4,
		.end	= IRQ_IIC4,
		.flags	= IORESOURCE_IRQ,
	},
};

struct platform_device s3c_device_i2c4 = {
	.name		= "s3c2440-i2c",
	.id		= 4,
	.num_resources	= ARRAY_SIZE(s3c_i2c_resource),
	.resource	= s3c_i2c_resource,
};

//kaixian@cellon set IIC frequency as 400KHZ for es305 running at high speed
#ifdef CONFIG_ANC_ES305
struct s3c2410_platform_i2c i2c4_i2c_data __initdata = {
	.flags		= 0,
	.slave_addr	= 0x10,
	.frequency	= 400*1000,
	.sda_delay	= 100,
};
#endif /* CONFIG_ANC_ES305 */
void __init s3c_i2c4_set_platdata(struct s3c2410_platform_i2c *pd)
{
	struct s3c2410_platform_i2c *npd;


#ifdef CONFIG_ANC_ES305
	if (!pd) {
		pd = &i2c4_i2c_data;
		pd->bus_num = 4;
	}
#else/* CONFIG_ANC_ES305 */
	if (!pd) {
		pd = &default_i2c_data;
		pd->bus_num = 4;
	}
#endif /* CONFIG_ANC_ES305 */
	
	npd = s3c_set_platdata(pd, sizeof(struct s3c2410_platform_i2c),
			       &s3c_device_i2c4);

	if (!npd->cfg_gpio)
		npd->cfg_gpio = s3c_i2c4_cfg_gpio;
}