#!/bin/bash
if ! [ -d tools/ ]; then
	echo "Клонирование toolchain..."
	git clone https://github.com/raspberrypi/tools
fi
if ! [ -d PatternsCollection/ ]; 
then
	echo "Клонирование главного репозитория..."
	git clone https://github.com/akhtyamovpavel/PatternsCollection
fi
cd PatternsCollection

echo "Изменение CMakeLists.txt..."
rm CMakeLists.txt
cp ../CMakeLists.txt CMakeLists.txt

mkdir build
cd build

echo "Сборка проекта на raspberry pi"
cmake .. -DON_PI=ON -DSYSROOT=$(pwd)/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot/

echo "Компиляция проекта"
make
