FROM nilbro/rover-api AS builder-myapp
WORKDIR /home/dev/
COPY ./driving_control_iotplayground/src/driving_control.cpp /home/dev/driving_control.cpp
RUN sudo g++ -lroverapi -o driving_control driving_control.cpp

#Building everything
#FROM balenalib/raspberrypi3-alpine
FROM balenalib/raspberrypi3
#FROM raspbian/stretch
WORKDIR /app/
# Add driving_control
COPY --from=builder-myapp /home/dev/driving_control /app/driving_control

# general libs
COPY --from=builder-myapp /usr/lib/libwiringPi.so /usr/lib/libwiringPi.so
COPY --from=builder-myapp /usr/lib/libwiringPiDev.so /usr/lib/libwiringPiDev.so
COPY --from=builder-myapp /usr/local/lib/libhono_interaction.so /usr/local/lib/libhono_interaction.so
COPY --from=builder-myapp /usr/local/lib/libpaho-mqtt3a.so.1 /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libpaho-mqtt3as.so.1 /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libpaho-mqtt3c.so.1 /usr/local/lib/
COPY --from=builder-myapp /usr/local/lib/libpaho-mqtt3cs.so.1 /usr/local/lib/
COPY --from=builder-myapp /usr/lib/arm-linux-gnueabihf/libjsoncpp.so.1 /usr/local/lib/


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
ENTRYPOINT ["./driving_control"]
