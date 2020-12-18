cmake_minimum_required(VERSION 3.3)
#project(wseink_cpp CXX)
project(wseink_cpp)

set(CMAKE_CXX_STANDARD 14)

#add_definitions(-DUSE_WIRINGPI_LIB=1)
add_definitions(-DUSE_DEV_COUT=1)
add_definitions(-DRPI=1)
add_definitions(-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON)

#find_library(wiringPi_LIB wiringPi)

# set_source_files_properties(*.c PROPERTIES LANGUAGE CXX )

set(EINK_SRCS
    ../c/lib/e-Paper/EPD_2in9.c
    ../c/lib/e-Paper/EPD_2in9.h

    ../c/lib/Config/Debug.h
    ../c/lib/Config/DEV_Config.c
    ../c/lib/Config/DEV_Config.h
#    ../c/lib/Config/dev_hardware_SPI.c
    ../c/lib/Config/dev_hardware_SPI.h
    ../c/lib/Config/RPI_sysfs_gpio.c
    ../c/lib/Config/RPI_sysfs_gpio.h
##    ../c/lib/Config/sysfs_gpio.c
##    ../c/lib/Config/sysfs_gpio.h
    ../c/lib/Config/sysfs_software_spi.c
    ../c/lib/Config/sysfs_software_spi.h

    ../c/lib/Fonts/font8.c
    ../c/lib/Fonts/font12.c
    ../c/lib/Fonts/font12CN.c
    ../c/lib/Fonts/font16.c
    ../c/lib/Fonts/font20.c
    ../c/lib/Fonts/font24.c
    ../c/lib/Fonts/font24CN.c
    ../c/lib/Fonts/fonts.h

    ../c/lib/GUI/GUI_BMPfile.c
    ../c/lib/GUI/GUI_BMPfile.h
    ../c/lib/GUI/GUI_Paint.c
    ../c/lib/GUI/GUI_Paint.h
)


SET_SOURCE_FILES_PROPERTIES(${CFILES} PROPERTIES LANGUAGE CXX )

add_executable(wseink_cpp
    ${EINK_SRCS}   

    bitmap_display_2in9.cpp
    bitmap_display_2in9.h
    bitmap_image.cpp
    bitmap_image.h
    i_bitmap_display.h
    main.cpp
    )

target_include_directories(wseink_cpp PUBLIC 
    ../c/lib/Config
    ../c/lib/GUI/
    )
target_link_libraries(wseink_cpp PUBLIC ${wiringPi_LIB})


