/*
 * Copyright (c) 2019 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <device.h>
#include <init.h>
#include <drivers/pinmux.h>
#include <sys/sys_io.h>

#include <pinmux/stm32/pinmux_stm32.h>

/* pin assignments for NUCLEO-L452RE board */
static const struct pin_config pinconf[] = {
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(usart1))
	{STM32_PIN_PA9,  STM32L4X_PINMUX_FUNC_PA9_USART1_TX},
	{STM32_PIN_PA10, STM32L4X_PINMUX_FUNC_PA10_USART1_RX},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(usart2))
	{STM32_PIN_PA2, STM32L4X_PINMUX_FUNC_PA2_USART2_TX},
	{STM32_PIN_PA3, STM32L4X_PINMUX_FUNC_PA3_USART2_RX},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(i2c1))
	{STM32_PIN_PB6, STM32L4X_PINMUX_FUNC_PB6_I2C1_SCL},
	{STM32_PIN_PB7, STM32L4X_PINMUX_FUNC_PB7_I2C1_SDA},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(pwm2))
	{STM32_PIN_PA0, STM32L4X_PINMUX_FUNC_PA0_PWM2_CH1},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(spi1))
#ifdef CONFIG_SPI_STM32_USE_HW_SS
	{STM32_PIN_PA4, STM32L4X_PINMUX_FUNC_PA4_SPI1_NSS},
#endif /* CONFIG_SPI_STM32_USE_HW_SS */
	{STM32_PIN_PA5, STM32L4X_PINMUX_FUNC_PA5_SPI1_SCK},
	{STM32_PIN_PA6, STM32L4X_PINMUX_FUNC_PA6_SPI1_MISO},
	{STM32_PIN_PA7, STM32L4X_PINMUX_FUNC_PA7_SPI1_MOSI},
#endif
#if DT_HAS_NODE_STATUS_OKAY(DT_NODELABEL(can1))
	{STM32_PIN_PA11, STM32L4X_PINMUX_FUNC_PA11_CAN_RX},
	{STM32_PIN_PA12, STM32L4X_PINMUX_FUNC_PA12_CAN_TX},
#endif
};

static int pinmux_stm32_init(struct device *port)
{
	ARG_UNUSED(port);

	stm32_setup_pins(pinconf, ARRAY_SIZE(pinconf));

	return 0;
}

SYS_INIT(pinmux_stm32_init, PRE_KERNEL_1,
	 CONFIG_PINMUX_STM32_DEVICE_INITIALIZATION_PRIORITY);