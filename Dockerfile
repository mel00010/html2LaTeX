FROM debian:experimental
EXPOSE 22
RUN  echo 'deb http://deb.debian.org/debian sid main' > /etc/apt/sources.list.d/sid.list && \
apt-get update && \
apt-get install -t experimental -y --no-install-recommends \
    clang libc++1 libc++-dev clang-tidy lld \
    llvm python cmake doxygen ninja-build \
    libboost-all-dev git libc++abi-dev \
    ca-certificates gcc lcov libstdc++-10-dev
RUN mv /usr/bin/ld /usr/bin/ld.gold
RUN mv /usr/bin/lld /usr/bin/ld.lld
RUN update-alternatives --install /usr/bin/ld ld /usr/bin/ld.lld 100
RUN update-alternatives --install /usr/bin/ld ld /usr/bin/ld.gold 1
RUN update-alternatives --install /usr/bin/ld ld /usr/bin/ld.gold 1
RUN update-alternatives --set cc /usr/bin/clang
RUN update-alternatives --set c++ /usr/bin/clang++


