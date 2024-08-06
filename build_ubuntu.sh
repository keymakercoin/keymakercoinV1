#!/bin/sh

# =============================================================================#
# this script can use for Ubuntu 18.04 LTS and Ubuntu 20.04 LTS
# recommended use linux fresh installer
# copy this file into root folder
# make to the executable file with command :
# chmod +x smcn-build-ubuntu.sh 
# ./smcn-build-ubuntu.sh
# =============================================================================#

# added swapfile ( you can change swapfile allocate in : fallocate -l 3G /swapfile

#swapoff -a
#fallocate -l 3G /swapfile  
#chown root:root /swapfile  
#chmod 0600 /swapfile  
#sudo bash -c "echo 'vm.swappiness = 10' >> /etc/sysctl.conf"  
#mkswap /swapfile  
#swapon /swapfile    
#echo '/swapfile none swap sw 0 0' >> /etc/fstab
#free -m 
#df -h

# Prepare to build, Update your Ubuntu server
cd ~ && sudo apt-get update && sudo apt-get upgrade -y &&

# Install the required dependencies
sudo apt-get install build-essential gcc bsdmainutils libtool autotools-dev libboost-all-dev libssl-dev libevent-dev libprotobuf-dev protobuf-compiler pkg-config python3 -y &&

sudo apt-get install git cmake automake unzip net-tools -y &&

# port UPnP
sudo apt-get install libminiupnpc-dev libzmq3-dev -y &&

# (provides ZMQ API 4.x)
sudo apt-get install libzmq3-dev -y &&

# Qt 5 with GUI
sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler -y &&

# libqrencode 
sudo apt-get install libqrencode-dev -y &&

# Install the repository ppa:bitcoin/bitcoin
sudo apt-get install software-properties-common -y &&
sudo add-apt-repository ppa:bitcoin/bitcoin -y &&
sudo apt-get update -y &&
sudo apt-get install libdb4.8-dev libdb4.8++-dev -y &&

# Download keymakercoin on github 

cd ~ 

 
git clone -b 1.0.2.22 --single-branch https://github.com/keymakercoin/keymakercoin.git
 
 

cd keymakercoin && chmod +x autogen.sh && cd share && chmod +x genbuild.sh && cd ..

# Install libdb6.2 (Berkeley DB)

BITCOIN_ROOT=$(pwd)

# Pick some path to install BDB to, here we create a directory within the keymakercoin directory
BDB_PREFIX="${BITCOIN_ROOT}/build"
mkdir -p $BDB_PREFIX

# Fetch the source and verify that it is not tampered with
wget 'http://download.oracle.com/berkeley-db/db-6.2.32.tar.gz'
echo 'a9c5e2b004a5777aa03510cfe5cd766a4a3b777713406b02809c17c8e0e7a8fb  db-6.2.32.tar.gz' | sha256sum -c
# -> db-6.2.32.tar.gz: OK
tar -xzvf db-6.2.32.tar.gz

# Build the library and install to our prefix
cd db-6.2.32/build_unix/
#  Note: Do a static build so that it can be embedded into the executable, instead of having to find a .so at runtime
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX
make install

# build and install keymakercoin 

cd $BITCOIN_ROOT

./autogen.sh

./configure LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/" CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768"

make

#make install
 

 