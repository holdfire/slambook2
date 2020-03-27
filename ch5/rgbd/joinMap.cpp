
#include<iostream>
#include<fstream>

#include<opencv2/opencv.hpp>
#include<boost/format.hpp>       // for formating strings
#include<sophus/se3.hpp>
#include<pangolin/pangolin.h>

using namespace std;
typedef vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d>> TrajectoryType;
typedef Eigen::Matrix<double, 6, 1> Vector6d;

// 在pangolin中画图，已写好，无需调整





