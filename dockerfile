FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
  gcc-multilib-mips-linux-gnu \
  gcc-mips-linux-gnu \
  g++-multilib-mips-linux-gnu \
  g++-mips-linux-gnu \
  qemu-user \ 
  cmake 

WORKDIR /root

RUN mkdir build

COPY CMakeLists.txt .
COPY src src
COPY include include

RUN cmake -DCMAKE_CXX_COMPILER=mips-linux-gnu-g++ -B build .

WORKDIR /root/build

RUN make

CMD ["qemu-mips", "-L", "/usr/mips-linux-gnu/", "./run_test"]

# docker build -t big-endian .
# docker run -it --rm big-endian
