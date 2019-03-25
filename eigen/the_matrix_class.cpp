#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

void matrix_class()
{
    // 动态矩阵 在编译时不会计算出矩阵的大小
    MatrixXd m(2, 2); // 构造函数 2*2大小的动态矩阵
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << "Here is the matrix m:\n"
              << m << std::endl;
    VectorXd v(2);
    v(0) = 4;
    v(1) = v(0) - 1;
    std::cout << "Here is the vector v:\n"
              << v << std::endl;

    Matrix3f m3;
    // 逗号初始化
    m3 << 1, 2, 3,
        4, 5, 6,
        7, 8, 9;
    std::cout << m3;

    // 调整大小
    MatrixXd m4(2, 5);
    m4.resize(4, 3);
    std::cout << "矩阵m的大小" << m4.rows() << "x" << m4.cols() << std::endl;
    std::cout << "它有" << m4.size() << "系数" << std::endl;

    // 自动分配大小
    MatrixXf a(2, 2);
    std::cout << a.rows() << "x" << a.cols() << std::endl;
    MatrixXf b(3, 3);
    a = b;
    std::cout << a.rows() << "x" << a.cols() << std::endl;

    // 尽可能使用固定大小的类型 避免动态存储器分配和循环,固定大小的矩阵只是一个普通的数组
    // Matrix4f mymatrix 等效于 float mymatrix[16]
    Matrix<float, Dynamic, Dynamic, 0, 3, 4> m5;
    std::cout << m5;
}

/**
 * @brief 矩阵和向量的算术运算
 * 
 * @return int 
 */
void matrix_vector_algrithem()
{
    Matrix2d a;
    a << 1, 2,
        3, 4;

    MatrixXd b(2, 2);
    b << 2, 3,
        1, 4;
    std::cout << "a + b = \n"
              << a + b << std::endl;

    std::cout << "a - b = \n"
              << a - b << std::endl;

    std::cout << "做一个 += b," << std::endl;
    a += b;

    std::cout << "现在a = \n"
              << a << std::endl;

    Vector3d v(1, 2, 3);
    Vector3d w(1, 0, 0);
    std::cout << "-v + w - v = \n"
              << -v + w - v << std::endl;
}

int main()
{
    matrix_class();

    matrix_vector_algrithem();
}