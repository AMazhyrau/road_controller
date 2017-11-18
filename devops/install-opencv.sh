#!/usr/bin/bash

############################
# INSTALL OPENCV ON UBUNTU #
############################

coloredEcho() {
  local code="\033["
    case "$1" in
     black  | bk) color="${code}0;30m";;
     red    |  r) color="${code}1;31m";;
     green  |  g) color="${code}1;32m";;
     yellow |  y) color="${code}1;33m";;
     blue   |  b) color="${code}1;34m";;
     purple |  p) color="${code}1;35m";;
     cyan   |  c) color="${code}1;36m";;
     gray   | gr) color="${code}0;37m";;
     *) local text="$1"
    esac
    [ -z "$text" ] && local text="$color$2${code}0m\n"
    printf "$text"
}

coloredEcho cyan "BUILD AND INSTALL OPENCV"

# 1. UPDATE UBUNTU
coloredEcho purple "UPDATE SYTEM"

sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y dist-upgrade
sudo apt-get -y autoremove

# 2. INSTALL THE DEPENDENCIES
coloredEcho purple "INSTALL THE DEPENDENCIES"

coloredEcho yellow "Build tools:"
sudo apt-get install -y build-essential cmake

coloredEcho yellow "GUI:"
# If you want to use GTK instead of Qt, replace 'qt5-default'
# with 'libgtkglext1-dev' and remove '-DWITH_QT=ON' option in CMake:
sudo apt-get install -y qt5-default libvtk6-dev

coloredEcho yellow "Media I/O:"
sudo apt-get install -y zlib1g-dev libjpeg-dev libwebp-dev libpng-dev \
  libtiff5-dev libjasper-dev libopenexr-dev libgdal-dev

coloredEcho yellow "Video I/O:"
sudo apt-get install -y libdc1394-22-dev libavcodec-dev libavformat-dev \
  libswscale-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev yasm \
  libopencore-amrnb-dev libopencore-amrwb-dev libv4l-dev libxine2-dev \
  ffmpeg libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev

coloredEcho yellow "Parallelism and linear algebra libraries:"
sudo apt-get install -y libtbb-dev libeigen3-dev

coloredEcho yellow "Python:"
sudo apt-get install -y python-dev python-tk python-numpy python3-dev \
  python3-tk python3-numpy

coloredEcho yellow "Java:"
sudo apt-get install -y ant default-jdk

coloredEcho yellow "Documentation:"
sudo apt-get install -y doxygen

# 3. INSTALL THE LIBRARY (YOU CAN CHANGE '3.3.1' FOR THE LAST STABLE VERSION)
coloredEcho cyan "DOWNLOAD OPENCV"

mkdir -p ../tools
cd ../tools

sudo apt-get install -y unzip wget

wget -O opencv-3.3.1.zip \
  https://github.com/opencv/opencv/archive/3.3.1.zip

unzip opencv-3.3.1.zip
rm opencv-3.3.1.zip
mv opencv-3.3.1 opencv

wget -O opencv_contrib-3.3.1.zip \
  https://github.com/opencv/opencv_contrib/archive/3.3.1.zip

unzip opencv_contrib-3.3.1.zip
rm opencv_contrib-3.3.1.zip
mv opencv_contrib-3.3.1 opencv_contrib

coloredEcho cyan "BUILD OPENCV"
cd opencv
mkdir -p build
cd build

cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local/opencv-3.3.1 \
      -D WITH_QT=ON \
      -D WITH_CUDA=ON \
      -D CUDA_FAST_MATH=ON \
      -D WITH_GSTREAMER=ON \
      -D WITH_OPENCL=ON \
      -D WITH_OPENGL=ON \
      -D FORCE_VTK=ON \
      -D WITH_V4L=ON \
      -D WITH_LIBV4L=ON \
      -D WITH_FFMPEG=ON \
      -D WITH_TBB=ON \
      -D WITH_GDAL=ON \
      -D WITH_XINE=ON \
      -D INSTALL_C_EXAMPLES=ON \
      -D INSTALL_PYTHON_EXAMPLES=ON \
      -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
      -D BUILD_EXAMPLES=ON \
      -D ENABLE_PRECOMPILED_HEADERS=OFF ..

make -j4
sudo make install
sudo ldconfig
