

sudo cmake -DUSE_WIRINGPI_LIB=1 -DRPI=1 -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..
#cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..

sudo cmake --build .
#cmake --build .
