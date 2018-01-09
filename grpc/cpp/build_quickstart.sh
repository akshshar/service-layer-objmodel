#!/bin/bash

# install grpc and protobuf
# grpc version = 0.13.1
# protobuf version = 3.5.0

set -x

PROTOBUF_INSTALLED_VERSION=`pkg-config --exists protobuf && pkg-config --modversion protobuf`
GRPC_INSTALLED_VERSION=`pkg-config --exists grpc && pkg-config --modversion grpc`

# protobuf 3.5.0 
PROTOBUF_VERSION="3.5.0"
PROTOBUF_HASH=2761122b810fe8861004ae785cc3ab39f384d342
# grpc 0.13.1
GRPC_VERSION="0.13.1"
GRPC_HASH=80893242c1ee929d19e6bec5dc19a1515cd8dd81


SCRIPT_DIR="$(cd "$(dirname "${0}")"; echo "$(pwd)")"

if [[ $GRPC_INSTALLED_VERSION != $GRPC_VERSION  || \
          $PROTOBUF_INSTALLED_VERSION != $PROTOBUF_VERSION ]]; then 
    sudo apt-get update && sudo apt-get install -y \
         autoconf automake libtool curl make g++ unzip git

    rm -rf ~/tempdir
    mkdir -p ~/tempdir/

    if [[ $PROTOBUF_INSTALLED_VERSION != $PROTOBUF_VERSION ]]; then
        #install protobuf
        git clone https://github.com/google/protobuf.git ~/tempdir/protobuf && \

        cd ~/tempdir/protobuf && \
        git checkout $PROTOBUF_HASH && \
        ./autogen.sh && \
        ./configure && \
        make && \
        sudo make install &&\
        sudo ldconfig 

    fi

    if [[ $GRPC_INSTALLED_VERSION != $GRPC_VERSION ]]; then
        #install grpc
        git clone https://github.com/grpc/grpc.git ~/tempdir/grpc && \
        cd ~/tempdir/grpc && \
        git checkout $GRPC_HASH && \
        git submodule update --init && \
        make && \
        sudo make install 
    fi
 
fi


# Install glog

if [[ `pkg-config --exists glog` ]]; then
    git clone https://github.com/google/glog.git ~/tempdir/glog
    cd ~/tempdir/glog
    ./autogen.sh && ./configure && make && sudo make install && sudo ldconfig
fi

# Clean up
cd ~/ && rm -rf ~/tempdir

# Clean up first
cd $SCRIPT_DIR
./clean.sh

# Create the c++ bindings from proto files
./gen-bindings.sh

# Drop into the src directory to build and install the service layer bindings as a static library libiosxrsl.a
cd ./src
# Create the genobj directory
mkdir -p genobj
make
sudo make install

# Drop into the tutorial directory to build quickstart that links to libiosxrsl.a
cd ./tutorial
make

cd ./rshuttle
make

