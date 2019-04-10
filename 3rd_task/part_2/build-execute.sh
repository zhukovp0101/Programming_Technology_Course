#!/bin/bash

if ! [ -d PatternsCollection/ ]; 
then
	echo "Клонирование главного репозитория..."
	git clone https://github.com/akhtyamovpavel/PatternsCollection
fi
cd PatternsCollection

echo "Добавление config.ini..."
rm Decorator/cpp-source/configs/config.ini.example
cp ../config.ini Decorator/cpp-source/configs/config.ini

echo "Исправление EmailNotifier.cpp..."
rm Decorator/cpp-source/notifiers/EmailNotifier.cpp
cp ../EmailNotifier.cpp Decorator/cpp-source/notifiers/EmailNotifier.cpp

echo "Изменение CMakeLists.txt для сборки одного Decorator..."
rm CMakeLists.txt
cp ../CMakeLists.txt CMakeLists.txt

echo "Сборка проекта..."
mkdir build
cd build
cmake ..

echo "Компиляция проекта..."
make
echo "Исправление SendMail..."
rm Decorator/cpp-source/vmime_project-prefix/src/vmime_project/CMakeLists.txt
cp ../../CMakeLists.txt-vmime Decorator/cpp-source/vmime_project-prefix/src/vmime_project/CMakeLists.txt

echo "Запуск..."
cd ../bin
./Decorator
