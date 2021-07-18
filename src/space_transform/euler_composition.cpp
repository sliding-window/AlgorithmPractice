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
// 1. 万向锁时，分解欧拉角是否仍然有效
// 2. 万向锁反应了一个什么样的问题？
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

    // 1 没有万向锁
    Eigen::Matrix3d composition = rz * ry * rx;
    composition = OthMatrix(composition);
    Eigen::Vector3d euler_angles = composition.eulerAngles(2, 1, 0);
    std::cout << "正常情况:\n";
    std::cout << euler_angles.transpose() * 180 / M_PI << std::endl;

    // 2 将y改为90度，观察万向锁时的分解结果
    theta_y = M_PI * 90 / 180;
    ry =
        Eigen::AngleAxisd(theta_y, Eigen::Vector3d::UnitY()).toRotationMatrix();
    composition = rz * ry * rx;
    composition = OthMatrix(composition);
    std::cout << "万向锁对应的分解:\n";
    std::cout << composition << std::endl;
    euler_angles = composition.eulerAngles(2, 1, 0);
    std::cout << "eular angles :\n";
    std::cout << euler_angles.transpose() * 180 / M_PI << std::endl;

    // 3 x用合成角度
    theta_x = (40 - 60) * M_PI / 180;
    rx =
        Eigen::AngleAxisd(theta_x, Eigen::Vector3d::UnitX()).toRotationMatrix();
    Eigen::Matrix3d composition_yx = ry * rx;
    composition_yx = OthMatrix(composition_yx);

    std::cout << "\n考虑万向锁丢失了轴，仅用两个轴得到旋转矩阵，并进行分解\n";
    std::cout << composition_yx << std::endl;
    euler_angles = composition_yx.eulerAngles(2, 1, 0);
    std::cout << "eular angles :\n";
    std::cout << euler_angles.transpose() * 180 / M_PI << std::endl;

    // 4 使用
    double diff = (composition_yx - composition).norm();
    std::cout << "difference between zyx and yx: " << diff << std::endl;
}