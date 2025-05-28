FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ENV QT_VERSION=6.9.0
ENV QT_ARCH=linux_gcc_64
ENV CMAKE_PREFIX_PATH=/opt/Qt/6.9.0/gcc_64/lib/cmake
ENV QT_PLUGIN_PATH=/opt/Qt/6.9.0/gcc_64/plugins

# Install system dependencies
RUN apt update && apt install -y \
    python3 python3-pip curl unzip wget \
    libglib2.0-0 libglib2.0-dev \
    libdbus-1-3 libdbus-1-dev \
    libxkbcommon-dev libxkbcommon-x11-dev \
    build-essential g++ cmake git wget \
    libgl1-mesa-dev libxcb-xinerama0 libxkbcommon-x11-0

# Install aqt
RUN pip3 install aqtinstall==3.1.*

# Install Qt with modules
RUN aqt install-qt linux desktop ${QT_VERSION} ${QT_ARCH} \
      -m qtlocation qtpositioning  \
      -O /opt/Qt

ENV QT_DIR=/opt/Qt/${QT_VERSION}/gcc_64
ENV PATH="$QT_DIR/bin:$PATH"

WORKDIR /app
