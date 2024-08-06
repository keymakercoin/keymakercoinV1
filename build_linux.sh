
chmod +x ./share/genbuild.sh

chmod +x ./contrib/install_db4.sh
./contrib/install_db4.sh `pwd`

chmod +x ./autogen.sh
./autogen.sh
export BDB_PREFIX='/db4'

chmod +x ./configure
./configure BDB_LIBS="-L${BDB_PREFIX}/lib -ldb_cxx-4.8" BDB_CFLAGS="-I${BDB_PREFIX}/include"

make -j "$(($(nproc)+1))"

