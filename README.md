### 1. 简介slambook2
《视觉SLAM十四讲》高翔，书中所涉及代码  
第二版： https://github.com/gaoxiang12/slambook2  
第一版： https://github.com/gaoxiang12/slambook  
 
### 2. 本书需要安装的库    
#### ch3: eigen, pangolin
sudo apt-get install libeigen3-dev  


#### ch4: 模板类的sophus 
git clone https://github.com/strasdat/Sophus.git
cd Sophus 
mkdir build  
cd build  
cmake ..  
make  

#### ch5：点云库PCL：    
sudo add-apt-repository ppa:v-launchpad-jochen-sprickerhof-de/pcl  
sudo apt-get update  
sudo apt-get install libpcl-all  
