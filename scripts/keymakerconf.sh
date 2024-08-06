#!/bin/bash -ev

mkdir -p ~/.keymaker
echo "rpcuser=username" >>~/.keymaker/keymaker.conf
echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >>~/.keymaker/keymaker.conf

