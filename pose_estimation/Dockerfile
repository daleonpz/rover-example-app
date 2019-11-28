##############################
## Installing dependencies 
##############################
FROM tdicola/pi_python_opencv_contrib:3.4.1 AS rover-dep

# Set up a tools dev directory
RUN mkdir /home/dev
WORKDIR /home/dev

#Install git
RUN apt-get update \
    && apt-get install -y git

# Install wiringPi
RUN sudo apt-get install wiringpi

# Install jsoncpp
RUN apt-get -y install libjsoncpp-dev && \
    ln -s /usr/include/jsoncpp/json/ /usr/include/json

#Install openssl
RUN apt-get install libssl-dev

# Install paho.mqtt.c
RUN cd ~/ && \
    git clone https://github.com/eclipse/paho.mqtt.c.git && \
    cd paho.mqtt.c/ && \
    make && \
    sudo make install

# Install i2c
RUN apt-get install -y libi2c-dev i2c-tools lm-sensors

# Install psutil
RUN pip install psutil
 
# Install raspicam
RUN cd ~/ && \
    git clone https://github.com/6by9/raspicam-0.1.3.git && \
    cd raspicam-0.1.3 && \
    mkdir -p build && \
    cd build && \
    cmake .. &&\
    make &&\
    sudo make install
 
# Install bluetooth
RUN sudo apt-get install -y bluez \
    libbluetooth-dev 

# Install geany
RUN sudo apt-get install geany

##############################
## Install rover-api
##############################
FROM rover-dep AS builder-roverapi
WORKDIR /roverapi/
RUN cd ~ &&\
    git clone https://github.com/daleonpz/rover-app.git &&\
    cd rover-app && \
    ./install_roverapp.sh &&\
    ldconfig   

##############################
#Building your APP
##############################
FROM builder-roverapi AS builder-myapp
WORKDIR /home/dev/
COPY ./pose_estimation/src/pose_estimation.cpp /home/dev/pose_estimation.cpp
RUN sudo g++ -lroverapi $(pkg-config --libs --cflags opencv) -o pose_estimation pose_estimation.cpp

##############################
# Copy your app to lighter base image
##############################
FROM balenalib/raspberrypi3
#FROM raspbian/stretch
WORKDIR /app/

# Add pose_estimation
COPY --from=builder-myapp /home/dev/pose_estimation /app/pose_estimation

# general libs
COPY --from=builder-myapp /usr/lib/libwiringPi.so /usr/lib/libwiringPi.so
COPY --from=builder-myapp /usr/lib/libwiringPiDev.so /usr/lib/libwiringPiDev.so
COPY --from=builder-myapp /usr/local/lib/libhono_interaction.so /usr/local/lib/libhono_interaction.so
COPY --from=builder-myapp /usr/local/lib/libpaho-mqtt3a.so.1 /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libpaho-mqtt3as.so.1 /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libpaho-mqtt3c.so.1 /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libpaho-mqtt3cs.so.1 /usr/local/lib/
COPY --from=builder-myapp /usr/lib/arm-linux-gnueabihf/libjsoncpp.so.1 /usr/local/lib/

# OpenCV
COPY --from=builder-myapp /usr/local/lib/libopencv_*.so.3.4 /usr/local/lib/

COPY --from=builder-myapp /usr/lib/arm-linux-gnueabihf/libfreetype.so.6  /usr/local/lib/

# roverapi libs
COPY --from=builder-myapp /usr/local/lib/libconfig_reader.so /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libpthread_distribution.so /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libroverapi.so  /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libroverapptasks.so /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libtiming.so /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libhono_interaction.so /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libpthread_monitoring.so /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libroverappdrivers.so /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libstatus_library.so /usr/local/lib/

RUN ldconfig

# Start driving_control
ENTRYPOINT ["./pose_estimation"]
