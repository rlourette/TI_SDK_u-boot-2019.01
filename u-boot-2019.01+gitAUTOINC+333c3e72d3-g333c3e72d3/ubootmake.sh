CROSS_COMPILE=/home/rich/ti-processor-sdk-linux-am335x-evm-06.03.00.106/linux-devkit/sysroots/x86_64-arago-linux/usr/bin/arm-linux-gnueabihf-
V=0
make V=${V} ARCH=arm CROSS_COMPILE=${CROSS_COMPILE} u-boot
echo DONE

