FROM rockylinux/rockylinux:latest
ENV container docker
# gcc
RUN dnf install gcc -y
# make
RUN dnf install epel-release -y
RUN dnf install make -y
RUN dnf install findutils -y
# unittest
RUN dnf install libtool -y
RUN dnf install unittest* -y
# RUN dnf install valgrind -y
# git
RUN dnf install git -y
#
RUN dnf install cjson* -y


RUN export LD_LIBRARY_PATH=/usr/local/lib/
