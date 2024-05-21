#include <zephyr/linker/linker-tool.h>

OUTPUT_FORMAT("elf64-littleriscv", "elf64-littleriscv",
	      "elf64-littleriscv")
OUTPUT_ARCH(riscv)
ENTRY(_start)





SECTIONS
{

    /* CORE-V: interrupt vectors */
  .vectors (ORIGIN(RAM)):
  {
    PROVIDE(__vector_start = .);
    KEEP(*(.vectors));
  } >RAM

}

#include <zephyr/arch/riscv/common/linker.ld>