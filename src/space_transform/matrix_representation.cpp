#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <iostream>

Eigen::Matrix3d OthMatrix(const Eigen::Matrix3d& input) {
    Eigen::Quaterniond q(input);
    q.normalize();
    return q.toRotationMatrix();
}

// 解决如下问题
// 1. Affine3d, Isomtry3d,  Matrix4d表示同一个欧式变换时，求逆是否不同
// 从输出可以看出来结果一致
int main(int argv, char** argc) {
    double theta_z = M_PI * 60 / 180;
    double theta_y = M_PI * 30 / 180;
    double theta_x = M_PI * 40 / 180;
    Eigen::Matrix3d rz =
        Eigen::AngleAxisd(theta_z, Eigen::Vector3d::UnitZ()).toRotationMatrix();
    Eigen::Matrix3d ry =
        Eigen::AngleAxisd(theta_y, Eigen::Vector3d::UnitY()).toRotationMatrix();
    Eigen::Matrix3d rx =
        Eigen::AngleAxisd(theta_x, Eigen::Vector3d::UnitX()).toRotationMatrix();

    Eigen::Quaterniond rotation(rz * ry * rx);
    std::cout << rotation.matrix() << std::endl;
    Eigen::Translation3d t(1, 2, 3);
    Eigen::Affine3d matrix_affine = t * rotation;
    std::cout <<"matrix_affine : \n" << matrix_affine.matrix() << std::endl;

    Eigen::Isometry3d isometry3d(t * rotation);
    std::cout << "isometry3 : \n" << isometry3d.matrix() << std::endl;

    Eigen::Matrix4d m4d = matrix_affine.matrix();
    std::cout << "matrix4d : \n" << m4d.matrix() << std::endl;

    std::cout <<"matrix_affine inverse: \n" <<  matrix_affine.inverse().matrix() << std::endl;
    std::cout << "matrix4d inverse : \n" << m4d.inverse() << std::endl;
    std::cout << "isometry3 inverse : \n" << isometry3d.inverse().matrix() << std::endl;

}