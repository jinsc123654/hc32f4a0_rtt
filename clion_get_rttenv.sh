#!/bin/bash

# 卸载自带kconfiglib  想安装回来请调用 pip3 install kconfiglib
pip uninstall -y kconfiglib

# 设置 RTT_ROOT 环境变量
if [ -d "${PWD}/rt-thread" ]; then
    export RTT_ROOT="${PWD}/rt-thread"
else
    export RTT_ROOT="${PWD}/../../../"
fi

export ENV_ROOT="${HOME}/.env"
export BSP_ROOT="${PWD}"
#设置RTT的编译器环境变量
export RTT_EXEC_PATH=~/SDK/gcc_arm/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux/gcc-arm-none-eabi-9-2020-q2-update/bin


rtt_dir='../../rt-thread'
lib_dir='../../libraries'

# 创建符号链接到 rt-thread
if [ ! -L "rt-thread" ]; then
    if [ -d "$rtt_dir" ]; then
        ln -s "$rtt_dir" ./rt-thread
    fi
fi

# 创建符号链接到 libraries
if [ ! -L "libraries" ]; then
    if [ -d "$lib_dir" ]; then
        ln -s "$lib_dir" ./libraries
    fi
fi

