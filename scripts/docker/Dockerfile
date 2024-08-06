FROM ubuntu:18.04 as base
MAINTAINER kp <support@keymaker.cc>

#Default branch name develop
ARG BRANCH_NAME=develop
#docker build -t keymaker .
#Default
#ARG REPO_SLUG=keymaker/keymaker
#ENV REPO_SLUG=${REPO_SLUG}
#ENV REPO_URL=https://github.com/${REPO_SLUG}

RUN apt-get update -qq
RUN apt-get upgrade -y -qq
RUN apt-get -qqy install git sudo
RUN apt-get install wget

#RUN git clone ${REPO_URL} --branch $BRANCH_NAME --single-branch --depth 1 

#COPY keymaker.tar.gz /keymaker.tar.gz
#RUN tar -xvf /keymaker.tar.gz



RUN wget https://raw.githubusercontent.com/keymakercoin/keymakercoin/main/scripts/dependencies-ubuntu.sh 
#RUN ./dependencies-ubuntu.sh  
RUN	apt-get install build-essential -qy
RUN apt-get install -y -qq autoconf  libssl-dev
RUN apt-get install -y -qq miniupnpc libminiupnpc-dev gettext libevent-dev protobuf-compiler libprotobuf-dev
RUN apt-get install -y -qq qtbase5-dev qttools5-dev-tools
RUN apt-get install -y -qq libdb++-dev
RUN apt-get install -y -qq libfakeroot fakeroot
RUN apt-get install libzmq3-dev -y
RUN apt-get install libminiupnpc-dev libzmq3-dev -y
RUN apt-get install build-essential bsdmainutils libtool autotools-dev libboost-all-dev libssl-dev libevent-dev libprotobuf-dev protobuf-compiler pkg-config python3 -y
RUN apt-get install git cmake automake unzip net-tools -y
RUN  apt-get install libqrencode-dev -y


EXPOSE 12421
#EXPOSE 12422
#EXPOSE 22421
#EXPOSE 22422

RUN wget https://github.com/keymakercoin/keymakercoin/releases/download/v1.0.2.16/keymakerd
RUN mv keymakerd /usr/local/bin
RUN chmod +x /usr/local/bin/keymakerd
RUN mkdir /opt/keymaker
RUN cd /opt/keymaker
VOLUME ["/opt/keymaker"]

#RUN chmod +x keymakerd
#RUN cp keymakerd /usr/local/bin

ENTRYPOINT ["keymakerd"]
#CMD	["-printtoconsole"]

CMD ["-datadir=/opt/keymaker/", "--conf=/opt/keymaker/keymaker.conf", "--printtoconsole", "-addnode=170.187.198.126", "-addnode=180.150.56.209"]