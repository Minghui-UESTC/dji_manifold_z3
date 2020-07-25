# 妙算1读取Z3相机图像

## 硬件连接

妙算1的CAM_IN连接Z3相机，CAM_OUT连接M100飞行器上的飞控即可。

## 开发环境

需要先安装CUDA和OpenCV。妙算1计算单元其实是英伟达的TK1，英伟达基于OpenCV2.4为TK1适配了CPU和GPU硬件加速版本OpenCV4tegra。不过在安装OpenCV4tegra之前需要安装CUDA。

适用于TK1的CUDA：cuda-repo-l4t-r21.2-6-5-prod_6.5-34_armhf.deb。

下载地址：http://developer.download.nvidia.com/compute/cuda/6_5/rel/installers/cuda-repo-l4t-r21.2-6-5-prod_6.5-34_armhf.deb。

下载安装并添加环境变量：

```
sudo dpkg -i cuda-repo*.deb
sudo apt-get update
sudo apt-get install cuda-toolkit-6-5
echo"# Add CUDA bin & library paths:" >> ~/.bashrc
echo"export PATH=/usr/local/cuda-6.5/bin:$PATH">> ~/.bashrc
echo"exportLD_LIBRARY_PATH=/usr/local/cuda-6.5/lib:$LD_LIBRARY_PATH">>~/.bashrc
source~/.bashrc
```

最后安装OpenCV4tegra，libopencv4tegra-repo_l4t-r21_2.4.10.1_armhf.deb。

下载地址：http://developer.download.nvidia.com/embedded/OpenCV/L4T_21.2/libopencv4tegra-repo_l4t-r21_2.4.10.1_armhf.deb

```
sudo dpkg -i libopencv4tegra-repo_l4t-r21_2.4.10.1_armhf.deb
sudo apt-get update
sudo apt-get install libopencv4tegra libopencv4tegra-dev libopencv4tegra-python
```

## 编程

CUDA和OpenCV都安装完毕后就可以写程序读取图像了。在妙算自带的Ubuntu14.04系统中，大疆提供了Z3相机的驱动——dcam库文件。这个库文件提供了相机初始化、直接显示图像、读取NV12格式的图像buffer、转发图像到遥控器等接口。为了在妙算上读取Z3图像数据，进行二次开发，我们需要使用大疆提供的驱动接口，读取图像buffer并转换成OpenCV中的图像数据。接口函数在dcam库文件中实现了，因此我们在写自己程序的时候需要用extern关键字申明一下函数，然后在CMakeLists.txt文件中链接dcam库文件就可以了。
