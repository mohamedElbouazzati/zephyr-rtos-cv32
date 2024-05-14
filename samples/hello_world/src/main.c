/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <soc.h>

void printBinary(int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0)
            printf(" ");
    }
    printf("\n");
}

int main(void)
{
	uint32_t ev_pending = 0x82003010;
	uint32_t ev_enable = 0x82003014;
	printf("Hello World! %s\n", CONFIG_BOARD);
	// __asm__ volatile ("csrw %0, %1" :: "i"(0x344), "r"(0));
	// litex_write32(1, 0x82001800);

		uint32_t mtvec;

	__asm__ volatile ("csrr %0, %1" : "=r"(mtvec) : "i"(0x305));
	printBinary(mtvec);
	// __asm__ volatile ("csrw %0, %1" :: "i"(0x344), "r"((mask & ~(1<<0)<<16)));

	// litex_write32(ev_pending,litex_read32(ev_pending));
	// litex_write32(ev_enable,0x1& 0x2 );
// 	while ( 1 )
// 	{
// 			uint32_t pending;
// 	// __asm__ volatile ("csrr %0, %1" : "=r"(mask) : "i"(0x344));
// 	__asm__ volatile ("csrr %0, %1" : "=r"(mask) : "i"(0xbc0));
// // __asm__ volatile ("csrr %0, %1" : "=r"(pending) : "i"(0x304));
// __asm__ volatile ("csrr %0, %1" : "=r"(pending) : "i"(0xfc0));
// printf("mask or mip:");
// 		printBinary(mask);
// printf("pending or mie:");
// printBinary(pending);

// printf("pending & mask");
// printBinary(pending&mask);

// 	}
	





	// while (1)
	// {
	// uint32_t pending=0;

	// __asm__ volatile ("csrr %0, %1" : "=r"(pending) : "i"(0x304));
	// 	printf("%d\n",pending);
	// 	/* code */
	// 	uint32_t mask=0;

	// __asm__ volatile ("csrr %0, %1" : "=r"(mask) : "i"(0x344));

	// 	printf("%d",mask);

	// }
	
	

	return 0;
}
