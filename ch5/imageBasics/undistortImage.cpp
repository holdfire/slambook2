#include<string>
#include<math.h>
#include<opencv2/opencv.hpp>

using namespace std;

string image_file = "../distorted.png";      // 请确保路径正确

int main(int argc, char** argv){
    
    // 本程序实现去畸变部分的代码，尽管我们可以调用OpenCV的去畸变，但自己实现一遍有助于理解
    // 去畸变是在归一化平面上计算的，因此先把像素坐标转换到归一化平面上，去畸变，然后返回到像素坐标系上
    // 畸变参数
    double k1 = -0.28340811, k2 = 0.07395907, p1 = 0.00019359, p2 = 1.76187114e-05;
    // 相机内参
    double fx = 458.654, fy = 457.296, cx = 367.215, cy = 248.375;

    // 读取灰度图像
    cv::Mat image = cv::imread(image_file, 0); 
    int rows = image.rows, cols = image.cols;
    cv::Mat image_undistort = cv::Mat(rows, cols, CV_8UC1);    // 去畸变以后的图

    // 计算去畸变以后图像的内容
    for (int v = 0; v < rows; v++){
        for (int u = 0; u < cols; u++){
            // 按照公式，先把像素坐标还原成归一化平面坐标，然后去畸变，最后还原成像素坐标
            double x = (u - cx) / fx, y = (v - cy) / fy;
            double r = sqrt(x * x +  y * y);
            double x_distorted = x * (1 + k1 * r * r + k2 * r * r * r * r) + 2 * p1 * x * y + p2 * (r * r + 2 * x * x);
            double y_distorted = y * (1 + k1 * r * r + k2 * r * r * r * r) + p1 * (r * r + 2 * y * y) + 2 * p2 * x * y;
            double u_distorted = fx * x_distorted + cx;
            double v_distorted = fy * y_distorted + cy;

            // 赋值：最近邻插值
            if(u_distorted >= 0 && v_distorted >= 0 && u_distorted < cols && v_distorted < rows){
                image_undistort.at<uchar>(v, u) = image.at<uchar>((int) v_distorted, (int) u_distorted);
            }
            else
            {
                image_undistort.at<uchar>(v, u) = 0;
            }            
        }
    }
    cv::imwrite("undistort.jpg", image_undistort);
    return 0;
}

