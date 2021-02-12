cmake_minimum_required(VERSION 3.3)
#project(wseink_cpp CXX)
project(wseink_cpp)

set(CMAKE_CXX_STANDARD 17)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(LINUX)
    add_definitions(-DUSE_WIRINGPI_LIB=1)
    add_definitions(-DRPI=1)
    add_definitions(-DCMAKE_VERBOSE_MAKEFILE:BOOL=ON)
    find_library(wiringPi_LIB wiringPi)
else()
    add_definitions(-DUSE_DEV_COUT=1)
    set(wiringPi_LIB)
endif()

if(ENABLE_DROGON)
# -DCMAKE_PREFIX_PATH=/Users/dwkimm01/opt/drogon/lib/cmake
find_package(Drogon CONFIG REQUIRED)
add_definitions(-DENABLE_DROGON)

set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.72.0 COMPONENTS date_time filesystem system)
#if(Boost_FOUND)
#  include_directories(${Boost_INCLUDE_DIRS})
#  add_executable(foo foo.cc)
#  target_link_libraries(foo ${Boost_LIBRARIES})
#endif()

endif()

# set_source_files_properties(*.c PROPERTIES LANGUAGE CXX )

set(EINK_SRCS
        c/lib/e-Paper/EPD_2in9.c
        c/lib/e-Paper/EPD_2in9.h

        c/lib/Config/Debug.h
        c/lib/Config/DEV_Config.c
        c/lib/Config/DEV_Config.h
#       c/lib/Config/dev_hardware_SPI.c
#        c/lib/Config/dev_hardware_SPI.h
        c/lib/Config/RPI_sysfs_gpio.c
        c/lib/Config/RPI_sysfs_gpio.h
##      c/lib/Config/sysfs_gpio.c
##      c/lib/Config/sysfs_gpio.h
#        c/lib/Config/sysfs_software_spi.c
#        c/lib/Config/sysfs_software_spi.h

       c/lib/Fonts/font8.c
       c/lib/Fonts/font12.c
#       c/lib/Fonts/font12CN.c
       c/lib/Fonts/font16.c
       c/lib/Fonts/font20.c
       c/lib/Fonts/font24.c
#       c/lib/Fonts/font24CN.c
       c/lib/Fonts/fonts.h

#       c/lib/GUI/GUI_BMPfile.c
#       c/lib/GUI/GUI_BMPfile.h
#       c/lib/GUI/GUI_Paint.c
#       c/lib/GUI/GUI_Paint.h
)


SET_SOURCE_FILES_PROPERTIES(${CFILES} PROPERTIES LANGUAGE CXX )

add_executable(wseink_cpp
    ${EINK_SRCS}

        cpp/active_timer.h
        cpp/bitmap_display_2in9.cpp
        cpp/bitmap_display_2in9.h

        cpp/bitmap_display_2in9_null.cpp
        cpp/bitmap_display_2in9_null.h

        cpp/bitmap_image.cpp
        cpp/bitmap_image.h
        cpp/drawing.cpp
        cpp/drawing.h

        cpp/impl/screens/gimp_monkey_image.cpp
        cpp/impl/screens/gimp_monkey_image.h
        cpp/impl/screens/screen_bender.cpp
        cpp/impl/screens/screen_bender.h
        cpp/impl/screens/screen_circle.cpp
        cpp/impl/screens/screen_circle.h
        cpp/impl/screens/screen_currently_playing.cpp
        cpp/impl/screens/screen_currently_playing.h
        cpp/impl/screens/screen_diamond.cpp
        cpp/impl/screens/screen_diamond.h
        cpp/impl/screens/screen_square.cpp
        cpp/impl/screens/screen_square.h
        cpp/impl/screens/screen_widgets.cpp
        cpp/impl/screens/screen_widgets.h
        cpp/impl/screens/screen_x.cpp
        cpp/impl/screens/screen_x.h

        cpp/impl/bitmaps.cpp
        cpp/impl/bitmaps.h
        cpp/impl/screen_manager.cpp
        cpp/impl/screen_manager.h
        cpp/impl/widget_bitmap.cpp
        cpp/impl/widget_bitmap.h
        cpp/impl/widget_current_time.cpp
        cpp/impl/widget_current_time.h
        cpp/impl/widget_string.cpp
        cpp/impl/widget_string.h

        cpp/interfaces/i_bitmap_display.h
        cpp/interfaces/i_screen.h
        cpp/interfaces/i_screen_manager.h
        cpp/interfaces/i_widget.h

        cpp/main.cpp
        cpp/matrix.h

        cpp/web_service/lms_client.cpp
        cpp/web_service/lms_client.h
        cpp/web_service/waveshare_web_service.cpp
        cpp/web_service/waveshare_web_service.h
        cpp/web_service/web_service.cpp
        cpp/web_service/web_service.h
    )

target_include_directories(wseink_cpp PUBLIC
        c/lib/Config
        c/lib/GUI
        cpp
    )
target_link_libraries(wseink_cpp PUBLIC ${wiringPi_LIB})

if(Boost_FOUND)
   target_link_libraries(wseink_cpp PUBLIC Boost::boost)
endif()

if(ENABLE_DROGON)
    target_link_libraries(wseink_cpp PUBLIC Drogon::Drogon)
endif()