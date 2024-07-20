# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/honeypi
WORKDIR /usr/src/honeypi

# This command compiles your app using GCC, adjust for your source code
RUN g++ -o honeypi home.cpp
RUN g++ -o test servertest.cpp

# REMOVE UNNEEDED PACKAGES
RUN  apt-get remove openssh-server -y

# INSTALL NEEDED PACKAGES (DISABLE FOR SPEED BUILDING)
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y docker.io
RUN apt-get install sudo -y


# This command runs your application, comment out this line to compile only
CMD ["./honeypi"]


LABEL Name=honeypotpi Version=0.0.1
