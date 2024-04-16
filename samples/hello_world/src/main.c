/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <soc.h>
int main(void)
{
	while(1){
	printf("Hello World! %s\n", CONFIG_BOARD);
	}
	litex_write32(1, 0x82001800);

	return 0;
}
