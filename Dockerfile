FROM		ubuntu:18.04
MAINTAINER	cv <cv.swan20@gmail.com>
WORKDIR		/keymaker
RUN     echo "-- Keymaker Coin - v1.0.2.16"
RUN		apt-get update
RUN		apt-get install -y build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3
RUN		apt-get install -y libboost-all-dev
RUN		apt-get install -y software-properties-common
RUN		add-apt-repository ppa:bitcoin/bitcoin
RUN		apt-get update
RUN		apt-get install -y libdb4.8-dev libdb4.8++-dev
ADD		. .
RUN     ./autogen.sh
RUN     ./configure
RUN     make -j 9
ENTRYPOINT	["./src/keymakerd"]