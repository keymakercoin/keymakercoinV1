
cd ~ 
 
git clone -b 1.0.2.22 --single-branch https://github.com/keymakercoin/keymakercoin.git
 
 
cd keymakercoin  && chmod +x autogen.sh && cd share && chmod +x genbuild.sh && cd ..
sudo apt-get update -y
sudo apt-get upgrade -y
sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3 -y
sudo apt-get install unzip -y

wget http://download.oracle.com/berkeley-db/db-4.8.30.zip
unzip db-4.8.30.zip
cd db-4.8.30
cd build_unix/
../dist/configure --prefix=/usr/local --enable-cxx

#sudo apt-get install libminiupnpc-dev -y
#sudo apt-get install libzmq3-dev -y
sudo apt install g++-mingw-w64-x86-64 -y
#sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler -y

sudo update-alternatives --config x86_64-w64-mingw32-g++ # Set the default mingw32 g++ compiler option to posix.

# Install libdb6.2 (Berkeley DB)

BITCOIN_ROOT=$(pwd)

# Pick some path to install BDB to, here we create a directory within the Keymaker Coin directory
BDB_PREFIX="${BITCOIN_ROOT}/build"
mkdir -p $BDB_PREFIX

# Fetch the source and verify that it is not tampered with
wget 'http://download.oracle.com/berkeley-db/db-6.2.32.tar.gz'
#echo 'a9c5e2b004a5777aa03510cfe5cd766a4a3b777713406b02809c17c8e0e7a8fb  db-6.2.32.tar.gz' | sha256sum -c
# -> db-6.2.32.tar.gz: OK
tar -xzvf db-6.2.32.tar.gz

# Build the library and install to our prefix
cd db-6.2.32/build_unix/
#  Note: Do a static build so that it can be embedded into the executable, instead of having to find a .so at runtime
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX
make install


 # build and install Keymaker Coin

cd $BITCOIN_ROOT

PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g') # strip out problematic Windows %PATH% imported var
sudo bash -c "echo 0 > /proc/sys/fs/binfmt_misc/status"

cd $BITCOIN_ROOT

chmod +x *.*
cd depends
chmod +x *.*
make
make HOST=x86_64-w64-mingw32

cd ..

./autogen.sh

CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/" CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768"

make