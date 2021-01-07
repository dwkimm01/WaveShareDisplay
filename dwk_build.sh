#!/bin/sh

#cmake .. -DCMAKE_PREFIX_PATH=/mnt/LMSfiles/mnt/opt/json_1_8_1 -DBROTLI_HOME=/mnt/LMSfiles/mnt/opt/brotli_1_0_9/ -DCMAKE_INSTALL_PREFIX=/mnt/LMSfiles/mnt/opt
#/drogon -DENABLE_DROGON:bool=true


echo "Configuring"
sudo cmake .. \
 -DCMAKE_PREFIX_PATH=/mnt/LMSfiles/mnt/opt/json_1_8_1 \
 -DBROTLI_HOME=/mnt/LMSfiles/mnt/opt/brotli_1_0_9/ \
 -DCMAKE_INSTALL_PREFIX=/mnt/LMSfiles/mnt/opt \
 -DBOOST_ROOT=/mnt/LMSfiles/mnt/opt/boost_1_72_0

echo "Building"
sudo cmake --build .


