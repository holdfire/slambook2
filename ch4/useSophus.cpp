#include<iostream>
#include<cmath>
#include<Eigen/Core>
#include<Eigen/Geometry>
#include"sophus/se3.hpp"

using namespace std;
using namespace Eigen;

int main(int argc, char** argv){

    // 沿Z轴旋转90度的旋转矩阵（李群）：由旋转向量（李代数）通过罗德里格斯公式求得
    Matrix3d R = AngleAxisd(M_PI/2, Vector3d(0, 0, 1)).toRotationMatrix();
    // 和该旋转矩阵等价的四元数
    Quaterniond q(R);

    Sophus::SO3d SO3_R(R);        // 由旋转矩阵构造李群（特殊正交群）；
    Sophus::SO3d SO3_q(q);        // 也可通过四元数构造李群；
    // 二者是等价的
    cout<< "SO(3) from matrix: \n"<<SO3_R.Matrix()<<endl;
    cout<< "SO(3) from quaternion: \n"<<SO3_q.Matrix()<<endl;
    cout<<"They are equal."

    // 使用对数映射获得它的李代数
    Vector3d so3 = SO3_R.log();
    cout << "so3 = "<<so3.transpose()<<endl;
    // hat 为向量到反对称矩阵
    cout<< "so3 hat = \n"<<Sophus::SO3d::hat(so3)<<endl;
    // 相对的，vee为反对称矩阵到向量
    cout<< "so3 ha vee = "<< Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose()<<endl;

    // 增量扰动模型的更新
    

}
