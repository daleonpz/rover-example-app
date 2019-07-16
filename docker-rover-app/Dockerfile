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
RUN cd ~/  && \
    git clone git://git.drogon.net/wiringPi && \
    cd wiringPi/ &&  \
    git pull origin && \
    ./build

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
# Build rover-api
##############################
FROM rover-dep AS builder-roverapi
WORKDIR /roverapp/
RUN cd ~ &&\
    git clone https://github.com/app4mc-rover/rover-app.git &&\
    cd rover-app && \
    ./install_roverapp.sh &&\
    ldconfig 

#############################
# Build roverapp
#############################
FROM builder-roverapi AS builder-roverapp
WORKDIR /home/dev/
RUN git clone https://github.com/app4mc-rover/rover-app.git &&\
    cd rover-app &&\
    ./make_roverapp.sh 

RUN ls 

##############################
# Copy your app to lighter base image
##############################
FROM balenalib/raspberrypi3
#FROM raspbian/stretch
WORKDIR /app/

# Add driving_control
COPY --from=builder-roverapp /home/dev/rover-app/build/bin/roverapp /app/roverapp

# general libs
COPY --from=builder-roverapp /usr/local/lib/libwiringPi.so /usr/local/lib/libwiringPi.so
COPY --from=builder-roverapp /usr/local/lib/libwiringPiDev.so /usr/local/lib/libwiringPiDev.so
COPY --from=builder-roverapp /usr/local/lib/libhono_interaction.so /usr/local/lib/libhono_interaction.so
COPY --from=builder-roverapp /usr/local/lib/libpaho-mqtt3a.so.1 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libpaho-mqtt3as.so.1 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libpaho-mqtt3c.so.1 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libpaho-mqtt3cs.so.1 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libjsoncpp.so.1 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libopencv_highgui.so.3.4 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libopencv_videoio.so.3.4 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libopencv_imgcodecs.so.3.4 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libopencv_imgproc.so.3.4 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libopencv_core.so.3.4 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libbluetooth.so.3 /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libraspicam.so.0.1 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libgtk-3.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libgdk-3.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libpangocairo-1.0.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libpango-1.0.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libatk-1.0.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libcairo-gobject.so.2 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libcairo.so.2 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libgdk_pixbuf-2.0.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libgio-2.0.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libgobject-2.0.so.0 /usr/local/lib/
COPY --from=builder-roverapp /lib/arm-linux-gnueabihf/libglib-2.0.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libgthread-2.0.so.0 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libavcodec.so.57 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libavformat.so.57 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libavutil.so.55 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libswscale.so.4 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libavresample.so.3 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libjpeg.so.62 /usr/local/lib/
COPY --from=builder-roverapp /usr/lib/arm-linux-gnueabihf/libpng16.so.16 /usr/local/lib/

# roverapi libs
COPY --from=builder-roverapp /usr/local/lib/libconfig_reader.so /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libpthread_distribution.so /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libroverapi.so  /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libroverapptasks.so /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libtiming.so /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libhono_interaction.so /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libpthread_monitoring.so /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libroverappdrivers.so /usr/local/lib/
COPY --from=builder-roverapp /usr/local/lib/libstatus_library.so /usr/local/lib/

RUN ldconfig

# Start driving_control
ENTRYPOINT ["./roverapp"]
