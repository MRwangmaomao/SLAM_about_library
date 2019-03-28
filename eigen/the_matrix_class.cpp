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

void multiplication_and_division()
{
    Matrix2d a;

    a << 1, 2,
        3, 4;
    Vector3d v(1, 2, 3);
    std::cout << "a * 2.5 = \n"
              << a * 2.5 << std::endl;
    std::cout << "0.1 * v = \n"
              << 0.1 * v << std::endl;
    std::cout << "Doing v *= 2;" << std::endl;
}

/**
 * @brief 矩阵的转置和共轭
 * 
 */
void transposition_and_conjugation()
{
    MatrixXcf a = MatrixXcf::Random(2, 2);
    std::cout << "Here is the matrix a \n"
              << a << std::endl;
    std::cout << "Here is the matrix a^T \n"
              << a.transpose() << std::endl; // 转置矩阵

    std::cout << "Here is the conjugate of a\n"
              << a.conjugate() << std::endl; // 共轭矩阵

    std::cout << "Here is the matrix a^*\n"
              << a.adjoint() << std::endl; //伴随矩阵
}

/**
 * @brief 点乘 叉乘
 * 
 */
void dot_product_and_cross_product()
{
    Vector3d v(1, 2, 3);
    Vector3d w(0, 1, 2);

    std::cout << "Dot product: " << v.dot(w) << std::endl;
    std::cout << "Cross product:\n"
              << v.cross(w) << std::endl;
}

/**
 * @brief array操作
 * 
 */
void array_class()
{
    std::cout << "array_class" << std::endl;

    ArrayXXf m(2, 2);

    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(1, 0) = 3.0;
    m(1, 1) = m(0, 0) + m(1, 0);

    std::cout << m << std::endl;

    m << 1.0, 2.0,
        3.0, 4.0;

    std::cout << m << std::endl;
}

/**
 * @brief 块操作
 * 
 */
void using_block_operation()
{
    std::cout << "using_block_operation" << std::endl;
    Eigen::MatrixXf m(4, 4);
    m << 1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16;
    std::cout << "Block in the middle" << std::endl;
    std::cout << m.block<2, 2>(1, 1) << std::endl;

    for (int i = 1; i <= 3; i++)
    {
        std::cout << "block size is " << i << std::endl;
        std::cout << m.block(0, 0, i, i) << std::endl
                  << std::endl;
    }

    Array22f m1;
    m1 << 1, 2,
        3, 4;
    Array44f a = Array44f::Constant(0.6);
    std::cout << "Here is the array a:" << std::endl
              << a << std::endl
              << std::endl;
    a.block<2, 2>(1, 1) = m1;
    std::cout << "Here is now a with m1 copled into its central 2x2 block:" << std::endl
              << a
              << std::endl;
    a.block(0, 0, 2, 3) = a.block(2, 1, 2, 3);
    std::cout << "Here is now a with bottom-right 2x3 block copied into top-left 2x3 block:" << std::endl
              << a << std::endl
              << std::endl;
}

void columns_and_rows()
{
    MatrixXf m(3, 3);
    m << 1, 2, 3,
    4, 5, 6,
        7, 8, 9;
}

int main()
{
    matrix_class();

    matrix_vector_algrithem();

    multiplication_and_division();

    transposition_and_conjugation();

    dot_product_and_cross_product();

    array_class();

    using_block_operation();
}