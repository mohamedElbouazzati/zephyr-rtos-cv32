#
# Copyright (c) 2018 - 2019 Antmicro <www.antmicro.com>
#
# SPDX-License-Identifier: Apache-2.0
#

zephyr_sources(
    ${ZEPHYR_BASE}/soc/common/riscv-privileged/soc_irq.S
    ${ZEPHYR_BASE}/soc/common/riscv-privileged/vector.S
)

zephyr_include_directories(.)

set(SOC_LINKER_SCRIPT ${ZEPHYR_BASE}/include/zephyr/arch/riscv/common/linker.ld CACHE INTERNAL "")


# zephyr_sources(
#   crt0.S
#   handlers.S
#   vectors.S
#   riscv_hal_stubs.c
  
 
# )
# zephyr_include_directories(.)

# set(SOC_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/link.ld CACHE INTERNAL "")
