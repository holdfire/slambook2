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
    cout<< "so3 hat = （seeeeee）\n"<<Sophus::SO3d::hat(so3)<<endl;
    // 相对的，vee为反对称矩阵到向量
    cout<< "so3 ha vee = （seeeeeee）"<< Sophus::SO3d::vee(Sophus::SO3d::hat(so3)).transpose()<<endl;

    // 增量扰动模型的更新
    Vector3d update_so3(1e-4, 0, 0);         // 假设更新量为这么多
    Sophus::SO3d SO3_updated = Sophus::SO3d::exp(update_so3) * SO3_R；
    cout<< "SO3 updated = \n"<< SO3_updated.matrix()<<endl;

    cout<<"****************************************"<<endl;
    // 对SE(3)操作大同小异
    Vector3d t(1, 0, 0);               // 沿x轴平移1
    Sophus::SE3d SE3_Rt(R, t);         // 用旋转矩阵R和平移向量t构造转矩阵SE(3)
    Sophus::SE3d SE3_qt(q, t);         // 从q，t构造SE(3)
    cout<< "SE(3) from R, T = \n"<<SE3_Rt.matrix()<<endl;
    cout<< "SE(3) from q, T = \n"<<SE3_qt.matrix()<<endl;
    // 李代数se(3)是一个六维向量，方便起见先typedef一下
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    Vector6d se3 = SE3_Rt.log();
    cout<< "se3 = "<< se3.transpose()<<endl;
    // 观察输出，会发现在Sophus中，se(3)的平移在前，旋转在后
    // 同样的，有hat和vee两个算符
    cout<< "se3 hat = \n"<< Sophus::SE3d::hat(se3)<<endl;
    cout<< "se3 hat vee = "<<Sophus::SE3d::vee(Sophus::SE3d::hat(se3)).transpose()<<endl;

    // 最后，演示一下更新
    Vector6d update_se3;    // 更新量
    update_se3.setZero();
    update_se3(0, 0) = 1e-4d;      // 啥意思啊？？？
    Sophus::SE3d SE3_updated = Sophus::SE3d::exp(update_se3) * SE3_Rt;
    cout<< " SE3 updated = "<<endl<<SE3.matrix()<<endl;

    return 0;
}
