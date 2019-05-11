#Building everything
FROM arm32v6/rover-app:0.0.1

# Add driving_control
COPY ./driving_control/src/driving_control.cpp /root/workspace/driving_control/src/driving_control.cpp

WORKDIR /root/workspace/driving_control/src/
RUN sudo g++ -lroverapi -o driving_control driving_control.cpp

# Start driving_control
CMD ["./driving_control"]
