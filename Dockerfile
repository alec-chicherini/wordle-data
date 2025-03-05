FROM ubuntu:24.04 AS ubuntu2404_common_deps
ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && \
    apt install -y \
    git \
    python3 \
    build-essential \
    xz-utils \
    wget \
    clang-format

RUN wget -O - https://raw.githubusercontent.com/alec-chicherini/development-scripts/refs/heads/main/cmake/install_cmake.sh 2>/dev/null | bash

FROM ubuntu2404_common_deps AS wordle_data_build
RUN apt install -y protobuf-compiler
COPY . /wordle-data
RUN cd /wordle-data && mkdir build && cd build && \
    cmake .. -DCMAKE_C_COMPILER=gcc-13 -DCMAKE_CXX_COMPILER=g++-13 && \
    cmake --build .

ENTRYPOINT ["ctest","-VV","--test-dir","/wordle-data/build" ]