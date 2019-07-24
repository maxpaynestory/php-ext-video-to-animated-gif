# PHP Video to Animated GIF converter
An php extension to convert video into animated GIF

## Requiments
* PHP-CPP v2.0.0 [Download Zip](https://github.com/CopernicaMarketingSoftware/PHP-CPP/archive/v2.0.0.zip)
* OpenCV v3.4.3 [Download Zip](https://github.com/opencv/opencv/archive/3.4.3.zip)
* OpenCV Contrib v3.4.3 [Download Zip](https://github.com/opencv/opencv_contrib/archive/3.4.3.zip)
* PHP 7.0
* GCC 7

## Setup inside Ubuntu 16.04

### PHP-CPP v2.0.0 with PHP 7.0, GCC 7
```bash
sudo apt-get install unzip

wget https://github.com/CopernicaMarketingSoftware/PHP-CPP/archive/v2.0.0.zip

sudo apt-get install -y software-properties-common

sudo add-apt-repository ppa:ubuntu-toolchain-r/test

sudo apt update

sudo apt install g++-7 -y

sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7

sudo update-alternatives --config gcc

unzip v2.0.0.zip

cd PHP-CPP-2.0.0/

sudo apt-get install build-essential make cmake pkg-config -y

sudo apt-get install php7.0-cli php7.0-dev -y

make

sudo make install

```

### OpenCV
```bash
sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libavresample-dev -y

cd ~

wget https://github.com/opencv/opencv/archive/3.4.3.zip

unzip 3.4.3.zip

rm 3.4.3.zip

wget https://github.com/opencv/opencv_contrib/archive/3.4.3.zip

unzip 3.4.3.zip

rm 3.4.3.zip

cd opencv-3.4.3/

mkdir build

cd build/

cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D INSTALL_C_EXAMPLES=OFF -D INSTALL_PYTHON_EXAMPLES=OFF -D WITH_FFMPEG=ON -D OPENCV_GENERATE_PKGCONFIG=ON -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib-3.4.3/modules -D BUILD_EXAMPLES=OFF ..

make -j$(nproc)

sudo make install

sudo cp lib/* /usr/lib/
```

## Build extension
clone this repository on the machine and run

```bash
make -f Makefile CONF=DEBUG clean all

sudo make install
```

## Verify Build
Now you are ready to use php extension inside your php scripts.

For testing, make sure you have a sample_video.mp4 file and then try the below command

```bash
php -r 'echo v2gConvertVideoToGif("sample_video.mp4","/tmp/outputgif.gif");'
```