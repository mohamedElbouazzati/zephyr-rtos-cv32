/*
 * Copyright (c) 2018 - 2021 Antmicro <www.antmicro.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT cv32e41p_intc0

#include <zephyr/kernel.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/irq.h>
#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/arch/riscv/irq.h>
#include<soc.h>

// #define CONFIG_UART_INTERRUPT_DRIVEN  1
#define IRQ_MASK		DT_INST_REG_ADDR_BY_NAME(0, irq_mask)
#define IRQ_PENDING		DT_INST_REG_ADDR_BY_NAME(0, irq_pending)

#define TIMER0_IRQ		DT_IRQN(DT_INST(0, litex_timer0))
#define UART0_IRQ		DT_IRQN(DT_INST(0, litex_uart0))

#define ETH0_IRQ		DT_IRQN(DT_INST(0, litex_eth0))

#define I2S_RX_IRQ		DT_IRQN(DT_NODELABEL(i2s_rx))
#define I2S_TX_IRQ		DT_IRQN(DT_NODELABEL(i2s_tx))

#define GPIO_IRQ		DT_IRQN(DT_NODELABEL(gpio_in))
#define FIRQ_OFFSET     16

static inline void cv32e41p_litex_irq_setmask(uint32_t mask)
{
	__asm__ volatile ("csrw %0, %1" :: "i"(IRQ_MASK), "r"(mask << FIRQ_OFFSET));
	
}

static inline uint32_t cv32e41p_litex_irq_getmask(void)
{
	uint32_t mask;

	__asm__ volatile ("csrr %0, %1" : "=r"(mask) : "i"(IRQ_MASK));
	return (mask >> FIRQ_OFFSET);
}

static inline uint32_t cv32e41p_litex_irq_pending(void)
{
	uint32_t pending;

	__asm__ volatile ("csrr %0, %1" : "=r"(pending) : "i"(IRQ_PENDING));
	return (pending >> FIRQ_OFFSET);
}

static inline void cv32e41p_litex_irq_setie(uint32_t ie)
{
	if (ie) {
		__asm__ volatile ("csrrs x0, mstatus, %0"
				:: "r"(MSTATUS_IEN));
	} else {
		__asm__ volatile ("csrrc x0, mstatus, %0"
				:: "r"(MSTATUS_IEN));
	}
}

 void cv32e41p_litex_irq_handler(const void *device)
{
	
	// printf("irq handler .... ");
	// litex_write32(3, 0x82001800);
	struct _isr_table_entry *ite;
	uint32_t pending, mask, irqs;

	pending = cv32e41p_litex_irq_pending();
	mask = cv32e41p_litex_irq_getmask();
	irqs = pending & mask;

#ifdef CONFIG_LITEX_TIMER
	if (irqs & (1 << TIMER0_IRQ)) {
		ite = &_sw_isr_table[TIMER0_IRQ];
		ite->isr(ite->arg);
	}
#endif

#ifdef CONFIG_UART_INTERRUPT_DRIVEN
	if (irqs & (1 << UART0_IRQ)) {
		ite = &_sw_isr_table[UART0_IRQ];
		ite->isr(ite->arg);
	}
#endif

#ifdef CONFIG_ETH_LITEETH
	if (irqs & (1 << ETH0_IRQ)) {
		ite = &_sw_isr_table[ETH0_IRQ];
		ite->isr(ite->arg);
	}
#endif

#ifdef CONFIG_I2S
	if (irqs & (1 << I2S_RX_IRQ)) {
		ite = &_sw_isr_table[I2S_RX_IRQ];
		ite->isr(ite->arg);
	}
	if (irqs & (1 << I2S_TX_IRQ)) {
		ite = &_sw_isr_table[I2S_TX_IRQ];
		ite->isr(ite->arg);
	}
#endif

	if (irqs & (1 << GPIO_IRQ)) {
		ite = &_sw_isr_table[GPIO_IRQ];
		ite->isr(ite->arg);
	}
}

void arch_irq_enable(unsigned int irq)
{
	cv32e41p_litex_irq_setmask(cv32e41p_litex_irq_getmask() | (1 << irq));
}

void arch_irq_disable(unsigned int irq)
{
	cv32e41p_litex_irq_setmask(cv32e41p_litex_irq_getmask() & ~(1 << irq));
}

int arch_irq_is_enabled(unsigned int irq)
{
	return cv32e41p_litex_irq_getmask() & (1 << irq);
}


static int cv32e41p_litex_irq_init(const struct device *dev)
{	
	csr_write(mie, 0x7FFF0880); // clear all interrupts
	// csr_write(mtvec, cv32e41p_litex_irq_handler); // clear all interrupts
	// cv32e41p_litex_irq_setmask(0); // set mask to zero (optional)??
	// csr_read_set(mie,(1 << RISCV_IRQ_MEXT)); // set irq 11 machine external interrupt enable


	IRQ_DIRECT_CONNECT(0, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 1, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 2, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 3, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 4, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 5, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 6, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 7, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 8, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 9, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 10, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 11, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 12, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 13, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 14, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 15, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 16, 0, cv32e41p_litex_irq_handler, 0);
		// irq_enable(16);
	IRQ_DIRECT_CONNECT( 17, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 18, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 19, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 20, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 21, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 22, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 23, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 24, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 25, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 26, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 27, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 28, 0, cv32e41p_litex_irq_handler, 0);

	IRQ_DIRECT_CONNECT( 29, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 30, 0, cv32e41p_litex_irq_handler, 0);
	
	IRQ_DIRECT_CONNECT( 31, 0, cv32e41p_litex_irq_handler, 0);

	cv32e41p_litex_irq_setie(1);
irq_enable(1);
	irq_enable(2);
// irq_enable(3);
// 	irq_enable(4);
// 	irq_enable(5);
// 	irq_enable(6);
// irq_enable(7);
// 	irq_enable(8);
// 	irq_enable(9);
// irq_enable(10);
// 	irq_enable(11);
// irq_enable(12);
// irq_enable(13);
// 	irq_enable(14);
// irq_enable(15);
// irq_enable(16);
// 	irq_enable(17);
// 	irq_enable(18);
// irq_enable(19);
// 	irq_enable(20);
// 	irq_enable(21);
// 	irq_enable(22);
// irq_enable(23);
// 	irq_enable(24);
// 	irq_enable(25);
// irq_enable(26);
// irq_enable(27);
// 	irq_enable(28);
// irq_enable(29);
// irq_enable(30);
// irq_enable(31);

	// IRQ_CONNECT(31, 0, cv32e41p_litex_irq_handler,
	// 		NULL, 0);
			
	return 0;
}

DEVICE_DT_INST_DEFINE(0, cv32e41p_litex_irq_init, NULL, NULL, NULL,
		      PRE_KERNEL_1, CONFIG_INTC_INIT_PRIORITY, NULL);
