# From Base Image
FROM debian:bookworm-slim

# Install Needed Packages
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y docker.io
RUN apt-get install -y sudo
RUN apt-get install -y iputils-ping curl bash
RUN apt-get install -y g++

# Expose Server Needed Ports
EXPOSE 63599
EXPOSE 11535
EXPOSE 9090

# Expose Port Blocking Needed Ports (9000-9010)
EXPOSE 9000
EXPOSE 9001
EXPOSE 9002
EXPOSE 9003
EXPOSE 9004
EXPOSE 9005
EXPOSE 9006
EXPOSE 9007
EXPOSE 9008
EXPOSE 9009
EXPOSE 9010

# Set Working Directory
COPY . /usr/src/honeypi
WORKDIR /usr/src/honeypi

# This command compiles your app using GCC, adjust for your source code
RUN g++ -o honeypi home.cpp
RUN g++ -o test servertest.cpp

# Remove Unneeded Packages
RUN apt-get remove g++ -y
RUN apt-get remove openssh-server -y
RUN apt-get autoremove -y

# This command runs your application, comment out this line to compile only
ENTRYPOINT ["./honeypi"]

# Versions and Labels
LABEL Name=honeypotpi Version=0.0.1
