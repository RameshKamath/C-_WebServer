FROM ubuntu:18.04

RUN apt-get -qq update && apt-get -qq upgrade

RUN apt-get -qq install cmake build-essential
RUN apt-get -qq install libboost-all-dev
RUN apt-get -qq install libtcmalloc-minimal4 && \
    ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so

WORKDIR /usr/program

COPY server .

WORKDIR /usr/program/build

RUN cmake .. && make 

CMD ["./cppServer"]
