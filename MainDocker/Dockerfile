# From Base Image
FROM gcc:latest

# INSTALL NEEDED PACKAGES (DISABLE FOR SPEED BUILDING)
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y docker.io
RUN apt-get install -y sudo
RUN apt-get install -y iputils-ping curl bash

# REMOVE UNNEEDED PACKAGES
RUN apt-get remove openssh-server -y

# Set Working Directory
COPY . /usr/src/honeypi
WORKDIR /usr/src/honeypi

# This command compiles your app using GCC, adjust for your source code
RUN g++ -o honeypi home.cpp
RUN g++ -o test servertest.cpp

# This command runs your application, comment out this line to compile only
ENTRYPOINT ["./honeypi"]

# Versions and Labels
LABEL Name=honeypotpi Version=0.0.1
