# @file Dockerfile-v1.4-base
# @author liangrui (liangrui5526@126.com) 
# @date 2023/9/9
# 
# @par 修改日志:
# <table>
# <tr><th>Date       <th>Version  <th>Author       <th>Description
# <tr><td>2023/9/9   <td>v1.0     <td>liangrui     <td>创建文件
# </table>

FROM nvcr.io/nvidia/cuda:12.4.1-cudnn-devel-ubuntu22.04 AS deps_base
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
RUN apt-get update && apt-get install -y --no-install-recommends \
    tzdata unzip pkg-config nasm yasm libx264-dev libx265-dev git gdb wget curl

# 设置构建目录
ARG BUILD_DIR=/opt/packages
WORKDIR ${BUILD_DIR}

# 设置构建核心数
ARG BUILD_CORES=8

# 安装boost
RUN wget https://archives.boost.io/release/1.87.0/source/boost_1_87_0_rc1.tar.gz -O ${BUILD_DIR}/boost_1_87_0.tar.gz
RUN tar -zxvf ${BUILD_DIR}/boost_1_87_0.tar.gz -C ${BUILD_DIR}/
RUN cd ${BUILD_DIR}/boost_1_87_0 && \
    ./bootstrap.sh && ./b2 threading=multi variant=release address-model=64 --disable-optimization \
    --with-atomic \
    --with-chrono \
    --with-date_time \
    --with-filesystem \
    --with-system \
    --with-random \
    --with-regex \
    --with-test \
    --with-thread \
    --with-serialization \
    --with-program_options \
    --with-log \
    --with-iostreams \
    -s NO_BZIP2=1 -s NO_LZMA=1 -s NO_ZSTD=1 \
    install -j ${BUILD_CORES}

# 安装cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v4.0.0-rc2/cmake-4.0.0-rc2-linux-x86_64.sh -O ${BUILD_DIR}/cmake-4.0.0-rc2-linux-x86_64.sh
RUN cd ${BUILD_DIR} && sh cmake-4.0.0-rc2-linux-x86_64.sh --skip-license --prefix=/usr/local

# 安装nv-codec-headers
RUN git clone -b n12.2.72.0 https://git.videolan.org/git/ffmpeg/nv-codec-headers.git ${BUILD_DIR}/nv-codec-headers \
    && cd ${BUILD_DIR}/nv-codec-headers && make install

# 安装ffmpeg
RUN wget https://ffmpeg.org/releases/ffmpeg-7.1.tar.xz -O ${BUILD_DIR}/ffmpeg-7.1.tar.xz
RUN tar -xvf ${BUILD_DIR}/ffmpeg-7.1.tar.xz -C ${BUILD_DIR}/
RUN cd ${BUILD_DIR}/ffmpeg-7.1 \
    && ./configure --toolchain=hardened --enable-shared --enable-libx264 --enable-libx265 \
    --enable-pic --enable-cuda --enable-cuvid --enable-nvenc  --enable-gpl \
    && make install -j${BUILD_CORES}

# 安装opencv
ARG OPENCV_VERSION=4.11.0
RUN git clone -b ${OPENCV_VERSION} https://github.com/opencv/opencv.git ${BUILD_DIR}/opencv-${OPENCV_VERSION}
RUN git clone -b ${OPENCV_VERSION} https://github.com/opencv/opencv_contrib.git ${BUILD_DIR}/opencv_contrib-${OPENCV_VERSION}
RUN cd opencv-${OPENCV_VERSION} && mkdir build && cd build \
    && cmake -DCMAKE_BUILD_TYPE=RELEASE \
    -DWITH_FFMPEG=ON \
    -DWITH_CUDA=ON \
    -DBUILD_CUDA_STUBS=ON \
    -DWITH_TBB=ON \
    -DBUILD_DOCS=OFF \
    -DBUILD_PERF_TESTS=OFF \
    -DBUILD_TESTS=OFF \
    -DWITH_1394=OFF \
    -DWITH_GTK=ON \
    -DWITH_QT=ON \
    -DWITH_OPENGL=ON \
    -DWITH_IPP=OFF \
    -DWITH_MATLAB=OFF \
    -DWITH_TIFF=OFF \
    -DWITH_WEBP=OFF \
    -DCUDA_GENERATION=Pascal \
    -DENABLE_PRECOMPILED_HEADERS=ON \
    -DCUDA_nppicom_LIBRARY= \
    -DOPENCV_EXTRA_MODULES_PATH=${BUILD_DIR}/opencv_contrib-${OPENCV_VERSION}/modules \
    .. \
    && make install -j${BUILD_CORES}

# 设置环境变量
ENV LD_LIBRARY_PATH $LD_LIBRARY_PATH:/usr/local/lib:/usr/local/cuda/lib64
ENV PATH $PATH:/usr/local/bin:/usr/local/sbin:/usr/local/tools:/usr/local/cuda/bin
