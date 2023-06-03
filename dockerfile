FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
  g++ \
  git \
  gcc-multilib-mips-linux-gnu \
  gcc-mips-linux-gnu \
  g++-multilib-mips-linux-gnu \
  g++-mips-linux-gnu \
  qemu-user \ 
  cmake 

WORKDIR /root

RUN mkdir build

COPY MIPS_CMakeLists.txt CMakeLists.txt
COPY src src
COPY include include
COPY tests tests
COPY entrypoint.sh .
RUN chmod +x entrypoint.sh

RUN cmake -DCMAKE_CXX_COMPILER=mips-linux-gnu-g++ -B build .

WORKDIR /root/build

RUN make

CMD ["../entrypoint.sh"]

# docker build -t big-endian .
# docker run -it --rm big-endian
