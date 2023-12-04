FROM ubuntu:latest

ARG BOOST_VERSION=1.81.0
ARG CMAKE_VERSION=3.25.1
ARG NUM_JOBS=8

ENV DEBIAN_FRONTEND noninteractive

# Install package dependencies
# Update package lists

RUN apt-get -o Acquire::Check-Valid-Until=false -o Acquire::Check-Date=false update && apt-get install unzip
RUN apt-get install -y --no-install-recommends ca-certificates locales
RUN apt-get clean
RUN rm -rf /var/lib/apt/lists/*


# System locale
# Important for UTF-8
ENV LC_ALL en_US.UTF-8
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

# Upgrade installed packages
RUN apt-get update && apt-get upgrade -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install essential build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    software-properties-common && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install additional tools and libraries
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf \
    automake \
    libtool \
    pkg-config \
    libssl-dev \
    wget \
    git \
    curl \
    language-pack-en \
    vim \
    gdb \
    valgrind && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*



# Install CMake
RUN cd /tmp && \
    wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.tar.gz && \
    tar xzf cmake-${CMAKE_VERSION}.tar.gz && \
    cd cmake-${CMAKE_VERSION} && \
    ./bootstrap && \
    make -j${NUM_JOBS} && \
    make install && \
    rm -rf /tmp/*

# Install Boost
# https://www.boost.org/doc/libs/1_80_0/more/getting_started/unix-variants.html
RUN cd /tmp && \
    BOOST_VERSION_MOD=$(echo $BOOST_VERSION | tr . _) && \
    wget https://boostorg.jfrog.io/artifactory/main/release/${BOOST_VERSION}/source/boost_${BOOST_VERSION_MOD}.tar.bz2 && \
    tar --bzip2 -xf boost_${BOOST_VERSION_MOD}.tar.bz2 && \
    cd boost_${BOOST_VERSION_MOD} && \
    ./bootstrap.sh --prefix=/usr/local && \
    ./b2 install && \
    rm -rf /tmp/*

# Install SFML
RUN set -e \
       && mkdir /usr/local/sfml_install \
       && wget https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip --no-check-certificate \
       && unzip -q SFML-2.5.1-sources.zip \ #unzip doesnt work, needs fixing
       && pushd SFML-2.5.1 \
       && mkdir build && cd build \
       && cmake .. && make \
       && make DESTDIR=/usr/local/sfml_install install \
       && popd

# Clone the repository
RUN git clone https://github.com/TomerKigel/AgentTown /usr/local/AgentTown

# Build and run
RUN cd /usr/local/AgentTown \
    && mkdir build \
    && cd build \
    && cmake .. \
    && cmake --build . --config Debug

# Final stage create image with previous build and compilation step
FROM ubuntu:latest
COPY --from=0 /usr/local/AgentTown /usr/local/AgentTown

EXPOSE 7777