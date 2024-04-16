## steps to reproduce:

- Build for FPGA board
```
$ west build -p auto -b litex_cv32e41p samples/hello_world -DDTC_OVERLAY_FILE=overlay_fpga.dts

$ litex_term /dev/ttyUSB1 --kernel=build/zephyr/zephyr.bin

```

- output: stucks at
```
--============= Liftoff! ===============--

```

- Build and run on simulation (verilator):

```
$ west build -p auto -b litex_cv32e41p samples/hello_world -DDTC_OVERLAY_FILE=overlay_fpga.dts

$ litex_sim --cpu-type=cv32e41p --with-sdram --timer-uptime \ 
	--sdram-init=$(HOME)/zephyrproject/zephyr/build/zephyr/zephyr.bin 
```
- output:

```
--=============== SoC ==================--
CPU:		CV32E41P @ 1MHz
BUS:		wishbone 32-bit @ 4GiB
CSR:		32-bit data
ROM:		128.0KiB
SRAM:		97.6KiB
L2:		8.0KiB
SDRAM:		64.0MiB 32-bit @ 1MT/s (CL-2 CWL-2)
MAIN-RAM:	64.0MiB

--========== Initialization ============--
Initializing SDRAM @0x40000000...
Switching SDRAM to software control.
Switching SDRAM to hardware control.

--============== Boot ==================--
Booting from serial...
Press Q or ESC to abort boot completely.
sL5DdSMmkekro
Timeout
Executing booted program at 0x40000000

--============= Liftoff! ===============--
*** Booting Zephyr OS build v3.6.0-937-gcb6f44c3b966 ***
hello_world! litex_cv32e41p
...
```