cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_prn C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# debug
# 2906

# release
# 2905

# set(CMAKE_CXX_FLAGS_RELEASE "-O1")
# 2898

# set(CMAKE_CXX_FLAGS_RELEASE "-O2")
# 2897

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# 2905

# set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK
# E:\pico\pico-sdk \pico_sdk_init.cmake 内のマクロ
pico_sdk_init()

add_compile_options(
	-Wall
	-Wno-format # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int        
	-Wno-unused-function # we have some for the docs that aren't called
	-Wno-maybe-uninitialized
	-L/usr/local/lib/
	-I/usr/local/include/
	)

add_subdirectory(freertos)
#add_subdirectory(libdmtx)
#add_subdirectory(zxing/core)

#target_compile_options (a PUBLIC -fexceptions)
#set(PICO_ENABLE_CXX_EXCEPTIONS 1)

add_executable(a
	main.cpp
	spi.cpp
	cutter.cpp
	printer.cpp
	sndbuf.cpp
	cg.cpp
	decode.cpp
	rcvbuf.cpp
	#uart.cpp
	taskbase.cpp
	ad.cpp

	rowBits.cpp
	barcode.cpp
	QR_Encode.cpp

	sample.cpp

	#zxing/DMWriter.cpp
	libdmtx/dmtx.c
	)

# Pull in our pico_stdlib which pulls in commonly used features
#target_link_libraries(a pico_stdlib pico_multicore)
target_link_libraries(a
	pico_stdlib
	freertos
	hardware_spi
	hardware_adc
	hardware_gpio
	hardware_pwm
	hardware_uart
	)

# create map/bin/hex file etc.
pico_add_extra_outputs(a)

pico_enable_stdio_usb(a 1)
#pico_enable_stdio_uart(a 1)
