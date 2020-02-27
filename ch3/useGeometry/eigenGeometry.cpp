#include<iostream>
#include<cmath>

using namespace std;

#include<Eigen/Core>
#include<Eigen/Geometry>

using namespace Eigen;

//本程序演示了Eigen几何模块的使用方法

int main(int argc, char** argv){
    // Eigen/Geometry模块提供了各种旋转和平移的表示
    // 3D旋转矩阵直接使用Matrix3d 或 Matrix3f
    Matrix3d rotation_matrix = Matrix3d::Identity();         // 此处的::符号是作为访问类的静态成员函数
    
    // 旋转向量使用AngelAxis，它底层不直接是Matrix，但运算可以当做矩阵（因为重载了运算符）
    AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1));      //沿Z轴旋转45度，两个参数分别是旋转的角度和轴
    cout.precision(3);
    cout<<"rotation matrix = \n"<<rotation_vector.matrix()<<endl;     //用成员函数matrix()转换成矩阵

    // 也可以通过赋值的方式，将旋转向量rotation_vector转换为旋转矩阵rotation_matrix
    rotation_matrix = rotation_vector.toRotationMatrix();

    // 方式1：用旋转向量进行坐标转换：通过旋转向量rotation_vector对运算符*的重载，来实现目标向量v的旋转；
    Vector3d v(1, 0, 0);
    Vector3d v_rotated = rotation_vector * v;
    cout<<"(1,0,0) after rotation (by angle axis) = "<<v_rotated.transpose()<<endl;

    // 方式2：用旋转矩阵进行坐标转换
    v_rotated = rotation_matrix * v;
    cout << "(1,0,0) after rotation (by matrix) = " << v_rotated.transpose() << endl;

    // 方式3：用欧拉角实现。可以先将旋转矩阵转换成欧拉角
    Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0);    // ZYX顺序，即yaw-pitch-roll顺序
    cout<<"yaw-pithc-roll = "<<euler_angles.transpose()<<endl;

    // 方式4：欧式变换矩阵使用Eigen::Isometry
    Isometry3d T = Isometry3d::Identity();
    T.rotate(rotation_vector);
    T.pretranslate(Vector3d(1, 3, 4));                  // 把平移向量设为（1，3，4）
    cout<< "Transform matrix = \n"<<T.matrix()<<endl;
    // 用变换矩阵进行坐标变换
    Vector3d v_transformed = T * v;                    // 相当于R*v+t
    cout << "v tranformed = " << v_transformed.transpose() << endl;

    // 对于仿射和射影变换，使用Eigen::Affine3d和Eigen::Projective2d即可，略

    // 方式5：四元数，可以直接把AngelAxis赋值给四元数，反之亦然
    Quaterniond q = Quaterniond(rotation_vector);
    cout<<"quaternion from rotation vector is: "<<q.coeffs().transpose()<<endl;   //注意coeffs的顺序是(x,y,z,w)前三者为虚部，w为实部
    // 也可以把旋转矩阵赋给它
    q = Quaterniond(rotation_matrix);
    cout<< "quaternion from rotation matrix = " << q.coeffs().transpose() << endl;
    // 使用四元数旋转一个向量，使用乘法的运算重载符即可
    v_rotated = q * v;      // 注意数学上是qvq{-1}
    cout<<"(1,0,0) after rotation = "<<v_rotated.transpose()<<endl;
    // 用常规向量乘法表示，则应该如下计算
    cout << "should be equal to " << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << endl;

    return 0;
}

