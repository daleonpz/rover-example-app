
# rover-example-app
 


This is a small example application called driving_control, which utilizes the [rover-api](https://app4mc-rover.github.io/rover-app/) to perform some basic driving maneuver.
The steps described below are tested on Ubuntu 16.04. 


## Build with Docker

### Enable docker experimental feature.

Create a daemon.json file in /etc/docker/ and add 

```sh
{
 
  "experimental" : true

}
```


### Restart docker daemon

```sh
$ sudo systemctl restart docker
```

### Install qemu-user-static package

```sh
$ sudo apt-get install qemu-user-static
```

### Build the Docker image

```sh
$ cd <your rover-example-app dir>
$ cp /usr/bin/qemu-arm-static ./qemu-arm-static
$ docker build --platform linux/arm32v6 -f ./docker-rover-app/Dockerfile -t arm32v6/rover-app:0.0.1 . 
```

### Start the container

First time:
```sh
$ cd <your rover-example-app dir>/driving_control
$ docker run -v $(pwd):/root/workspace/driving_control -w /root/workspace/driving_control -it arm32v6/rover-app:0.0.1 /bin/bash
```
Thereafter:
```sh
$ docker start -i <your container id>
```

### Build driving_control

In the container:
```sh
$ cd /root/workspace/driving_control/src
$ g++ -lroverapi -o driving_control driving_control.cpp
```

# Dockerize your application

You can use the docker image that you built above as a base image to dockerize your application. The result won't be the smallest passible image but you will have the rover-api and all of its dependencies available. We created a minimal example of a corresponding dockerfile in the ```docker-example``` directory. You can build the image with:
```sh
$ cd <your rover-example-app dir>
$ docker build --platform linux/arm32v6 -f ./docker-rover-example/Dockerfile -t arm32v6/rover-example:0.0.1 . 
```
Alternatively consider just copying your binaries to a directory that is not mounted from the host system and create an image:
```sh
$ docker commit <your container id> 
```

Make sure to start the containers inferred from the resulting image on raspbian as follows:

```sh
$ docker run --privileged -v /var/run/systemd:/var/run/systemd -v /dev/video0:/dev/video0 -v /lib/modules:/lib/modules <your image id>
```

# Develop with an IDE inside the docker container

The docker container already contains a lightweight IDE called [geany](https://www.geany.org/). If you want to use it, allow all clients to access to the host's X-Server
```sh
$ xhost +
```

Start the container as follows:
```sh
$ cd <your rover-example-app dir>/driving_control
$ docker run -v $(pwd):/root/workspace/driving_control -w /root/workspace/driving_control -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix arm32v6/rover-app:0.0.1 geany
```
