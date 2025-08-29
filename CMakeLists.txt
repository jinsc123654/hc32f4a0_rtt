CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR cortex-m4)
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

SET(CMAKE_C_COMPILER "/home/jinsc/SDK/gcc_arm/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux/gcc-arm-none-eabi-9-2020-q2-update/bin/arm-none-eabi-gcc")
SET(CMAKE_ASM_COMPILER "/home/jinsc/SDK/gcc_arm/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux/gcc-arm-none-eabi-9-2020-q2-update/bin/arm-none-eabi-gcc")
SET(CMAKE_C_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g")
SET(CMAKE_ASM_FLAGS " -c -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -x assembler-with-cpp -Wa,-mimplicit-it=thumb  -gdwarf-2")
SET(CMAKE_C_COMPILER_WORKS TRUE)

SET(CMAKE_CXX_COMPILER "/home/jinsc/SDK/gcc_arm/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux/gcc-arm-none-eabi-9-2020-q2-update/bin/arm-none-eabi-g++")
SET(CMAKE_CXX_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Dgcc -O0 -gdwarf-2 -g")
SET(CMAKE_CXX_COMPILER_WORKS TRUE)

SET(CMAKE_OBJCOPY "/home/jinsc/SDK/gcc_arm/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux/gcc-arm-none-eabi-9-2020-q2-update/bin/arm-none-eabi-objcopy")
SET(CMAKE_SIZE "/home/jinsc/SDK/gcc_arm/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux/gcc-arm-none-eabi-9-2020-q2-update/bin/arm-none-eabi-size")

SET(CMAKE_EXE_LINKER_FLAGS " -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -ffunction-sections -fdata-sections -Wl,--gc-sections,-Map=rtthread.map,-cref,-u,Reset_Handler -T ${CMAKE_SOURCE_DIR}/board/linker_scripts/link.ld")

SET(CMAKE_CXX_STANDARD 14)
PROJECT(rtthread C CXX ASM)
INCLUDE_DIRECTORIES(
	applications
	packages/CherryUSB-v1.3.1/common
	packages/CherryUSB-v1.3.1/core
	packages/CherryUSB-v1.3.1/class/cdc
	packages/CherryUSB-v1.3.1/class/msc
	packages/CherryUSB-v1.3.1/class/hid
	packages/CherryUSB-v1.3.1/class/audio
	packages/CherryUSB-v1.3.1/class/video
	packages/CherryUSB-v1.3.1/class/wireless
	packages/CherryUSB-v1.3.1/class/dfu
	packages/CherryUSB-v1.3.1/class/midi
	packages/CherryUSB-v1.3.1/class/vendor/net
	packages/CherryUSB-v1.3.1/class/vendor/serial
	packages/CherryUSB-v1.3.1/osal
	rt-thread/components/libc/compilers/common/include
	rt-thread/components/libc/compilers/newlib
	rt-thread/components/drivers/include
	rt-thread/components/drivers/spi
	rt-thread/components/drivers/spi/sfud/inc
	board
	board/ports
	board/config
	board/config/usb_config
	libraries/hc32_drivers
	libraries/hc32_drivers/drv_flash
	rt-thread/components/fal/inc
	board/ports/fal
	rt-thread/components/dfs/dfs_v1/include
	rt-thread/components/dfs/dfs_v1/filesystems/elmfat
	rt-thread/components/dfs/dfs_v1/filesystems/devfs
	rt-thread/components/finsh
	.
	rt-thread/include
	rt-thread/libcpu/arm/common
	rt-thread/libcpu/arm/cortex-m4
	libraries/hc32f4a0_ddl/drivers/cmsis/Device/HDSC/hc32f4xx/Include
	libraries/hc32f4a0_ddl/drivers/cmsis/Include
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/inc
	packages/littlefs-latest
	rt-thread/components/libc/posix/io/poll
	rt-thread/components/libc/posix/io/eventfd
	rt-thread/components/libc/posix/io/epoll
	rt-thread/components/libc/posix/ipc
)

ADD_DEFINITIONS(
	-DHC32F4A0
	-DLFS_CONFIG=lfs_config.h
	-DRT_USING_LIBC
	-DRT_USING_NEWLIBC
	-DUSE_DDL_DRIVER
	-D_POSIX_C_SOURCE=1
	-D__DEBUG
	-D__RTTHREAD__
)

SET(PROJECT_SOURCES
	applications/xtal32_fcm.c
	applications/main.c
	applications/usb_app.c
	packages/CherryUSB-v1.3.1/class/cdc/usbd_cdc.c
	packages/CherryUSB-v1.3.1/platform/rtthread/usb_check.c
	packages/CherryUSB-v1.3.1/core/usbd_core.c
	packages/CherryUSB-v1.3.1/osal/usb_osal_rtthread.c
	packages/CherryUSB-v1.3.1/port/dwc2/usb_dc_dwc2.c
	packages/CherryUSB-v1.3.1/platform/rtthread/usb_msh.c
	packages/CherryUSB-v1.3.1/class/msc/usbd_msc.c
	packages/CherryUSB-v1.3.1/port/dwc2/usb_glue_hc.c
	rt-thread/components/libc/compilers/common/cctype.c
	rt-thread/components/libc/compilers/common/cstdlib.c
	rt-thread/components/libc/compilers/common/cstring.c
	rt-thread/components/libc/compilers/common/ctime.c
	rt-thread/components/libc/compilers/common/cunistd.c
	rt-thread/components/libc/compilers/common/cwchar.c
	rt-thread/components/libc/compilers/newlib/syscalls.c
	rt-thread/components/drivers/core/device.c
	rt-thread/components/drivers/ipc/completion.c
	rt-thread/components/drivers/ipc/condvar.c
	rt-thread/components/drivers/ipc/dataqueue.c
	rt-thread/components/drivers/ipc/pipe.c
	rt-thread/components/drivers/ipc/ringblk_buf.c
	rt-thread/components/drivers/ipc/ringbuffer.c
	rt-thread/components/drivers/ipc/waitqueue.c
	rt-thread/components/drivers/ipc/workqueue.c
	rt-thread/components/drivers/mtd/mtd_nor.c
	rt-thread/components/drivers/pin/pin.c
	rt-thread/components/drivers/rtc/rtc.c
	rt-thread/components/drivers/sdio/block_dev.c
	rt-thread/components/drivers/sdio/gpt.c
	rt-thread/components/drivers/sdio/mmc.c
	rt-thread/components/drivers/sdio/mmcsd_core.c
	rt-thread/components/drivers/sdio/sd.c
	rt-thread/components/drivers/sdio/sdio.c
	rt-thread/components/drivers/serial/serial.c
	rt-thread/components/drivers/spi/sfud/src/sfud.c
	rt-thread/components/drivers/spi/sfud/src/sfud_sfdp.c
	rt-thread/components/drivers/spi/spi_core.c
	rt-thread/components/drivers/spi/spi_dev.c
	rt-thread/components/drivers/spi/spi_flash_sfud.c
	board/board.c
	board/board_config.c
	board/ports/drv_spi_flash.c
	libraries/hc32f4a0_ddl/drivers/cmsis/Device/HDSC/hc32f4xx/Source/GCC/startup_hc32f4a0.S
	libraries/hc32_drivers/drv_common.c
	libraries/hc32_drivers/drv_flash/drv_flash_f4.c
	libraries/hc32_drivers/drv_gpio.c
	libraries/hc32_drivers/drv_irq.c
	libraries/hc32_drivers/drv_rtc.c
	libraries/hc32_drivers/drv_sdio.c
	libraries/hc32_drivers/drv_spi.c
	libraries/hc32_drivers/drv_usart.c
	libraries/hc32_drivers/drv_usbd.c
	rt-thread/components/fal/src/fal.c
	rt-thread/components/fal/src/fal_rtt.c
	rt-thread/components/fal/src/fal_partition.c
	rt-thread/components/fal/src/fal_flash.c
	board/ports/fal/fal_flash_sfud_port.c
	rt-thread/components/dfs/dfs_v1/filesystems/devfs/devfs.c
	rt-thread/components/dfs/dfs_v1/filesystems/elmfat/dfs_elm.c
	rt-thread/components/dfs/dfs_v1/filesystems/elmfat/ff.c
	rt-thread/components/dfs/dfs_v1/filesystems/elmfat/ffunicode.c
	rt-thread/components/dfs/dfs_v1/src/dfs.c
	rt-thread/components/dfs/dfs_v1/src/dfs_file.c
	rt-thread/components/dfs/dfs_v1/src/dfs_fs.c
	rt-thread/components/dfs/dfs_v1/src/dfs_posix.c
	rt-thread/components/finsh/msh_file.c
	rt-thread/components/finsh/msh_parse.c
	rt-thread/components/finsh/shell.c
	rt-thread/components/finsh/msh.c
	rt-thread/components/finsh/cmd.c
	rt-thread/src/clock.c
	rt-thread/src/components.c
	rt-thread/src/idle.c
	rt-thread/src/ipc.c
	rt-thread/src/irq.c
	rt-thread/src/klibc/kstdio.c
	rt-thread/src/klibc/kstring.c
	rt-thread/src/kservice.c
	rt-thread/src/mem.c
	rt-thread/src/mempool.c
	rt-thread/src/object.c
	rt-thread/src/scheduler_comm.c
	rt-thread/src/scheduler_up.c
	rt-thread/src/thread.c
	rt-thread/src/timer.c
	rt-thread/libcpu/arm/common/atomic_arm.c
	rt-thread/libcpu/arm/common/div0.c
	rt-thread/libcpu/arm/common/showmem.c
	rt-thread/libcpu/arm/cortex-m4/context_gcc.S
	rt-thread/libcpu/arm/cortex-m4/cpuport.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_aos.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32f4a0_ll_interrupts_share.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_rtc.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_dma.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_utility.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_fcm.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_pwc.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_icg.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_clk.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_tmr0.c
	libraries/hc32f4a0_ddl/drivers/cmsis/Device/HDSC/hc32f4xx/Source/system_hc32f4a0.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_rmu.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_spi.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_gpio.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_usb.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_usart.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_fcg.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_efm.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_interrupts.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_sram.c
	libraries/hc32f4a0_ddl/drivers/hc32_ll_driver/src/hc32_ll_sdioc.c
	packages/littlefs-latest/lfs_crc.c
	packages/littlefs-latest/lfs.c
	packages/littlefs-latest/dfs_lfs.c
	packages/littlefs-latest/lfs_util.c
)

LINK_DIRECTORIES(
)

LINK_LIBRARIES(
	c
	m
)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}.elf ${PROJECT_SOURCES})
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD 
COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf)