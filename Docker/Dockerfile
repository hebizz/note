FROM arm64v8/ubuntu:18.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends build-essential \
    cmake \
    gcc \
    g++ \
    libprotobuf-dev \
    protobuf-compiler \
    liblapack-dev \
    libjpeg-dev \
    zlib1g-dev \
    python3-dev \
    python3-pip \
    python3-scipy \
    python3-opencv \
    libhdf5-dev \
    gfortran \
    libgfortran5-dbg \
    python3-h5py


COPY libprotobuf.so.15  /usr/lib

COPY ./pack  /home/pack

WORKDIR /home/pack

RUN pip3 install --no-cache-dir -U setuptools
RUN pip3 install --no-cache-dir scipy-1.2.0-cp36-cp36m-linux_aarch64.whl \
    onnx-1.4.1-cp36-cp36m-linux_aarch64.whl \
    tensorflow-1.10.1-cp36-cp36m-linux_aarch64.whl \
    rknn_toolkit-1.2.0-cp36-cp36m-linux_aarch64.whl \
    && rm -rf /home/pack