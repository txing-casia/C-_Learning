#include <iostream>
#include "head.h"
#include <cassert>
using namespace std;

void print_a_matrix(My_Matrix<int> mat)
{
    for(int m = 0; m < mat.i; m++)
    {
        for(int n = 0; n < mat.j; n++)
        {
            cout << mat.at(n + m*mat.j) << " ";
            if (n == mat.j-1)
            {
                cout << endl;
            }
        }
    }
}

int main()
{
    try
    {
        My_Matrix<int> mat1;
        cout << "1. 无参构造:" << endl;
        cout << "m x n size: " << size(mat1.data) << ", value: " << mat1.data.at(0) << endl;
        cout << endl;

        My_Matrix<int> mat2(2,2);
        cout << "2. 输入矩阵尺寸构造:" << endl;
        cout << "m x n size: " << size(mat2.data) << ", value: " << mat2.data.at(0) << endl;
        print_a_matrix(mat2);
        cout << endl;

        mat2[1][0] = 42;
        cout << "3. 通过[][]访问内部元素" << endl;
        cout << "mat2[1][0]: " << mat2[1][0] << endl;
        print_a_matrix(mat2);
        cout << endl;

        cout << "4. 使用at访问矩阵按行展开后对应的元素:" << endl;
        cout << "mat2.at(2): " << mat2.at(2) << endl;
        cout << "assert(mat2.at(2) == 42);" << endl;
        assert(mat2.at(2) == 42);
        cout << endl;

        cout << "5. at访问越界时抛出异常: (取消注释可查看)" << endl;
        // cout << "mat2.at(5): " << mat2.at(5) << endl;
        cout << endl;

        mat2.at(1) = 1;
        cout << "6. 可用at实现赋值 mat2.at(1) = 1:" << endl;
        cout << "mat2.at(1): "<< mat2.at(1) << endl;
        cout << endl;

        mat2.push_back(13);
        cout << "7. 使用push_back()向Matrix添加元素，可以用at访问" << endl;
        cout << "mat2.push_back(13); mat2.at(4): " << mat2.at(4) << endl;
        cout << "assert(mat2.at(4) == 13);" << endl;
        assert(mat2.at(4) == 13);
        print_a_matrix(mat2);
        mat2.push_back(14);
        cout << "mat2.push_back(14); mat2.at(5): " << mat2.at(5) << endl;
        cout << "assert(mat2.at(5) == 14);" << endl;
        assert(mat2.at(5) == 14);
        print_a_matrix(mat2);
        cout << endl;


        cout << "8. 使用reshape()修改矩阵尺寸，多余的元素会被删除，缺少的元素会使用默认值填充:" << endl;
        mat2.reshape(3, 3);
        cout << "mat2.reshape(3, 3);" << endl;
        cout << "mat2.length: " << mat2.length << ", mat2.i: " << mat2.i << ", mat2.j: " << mat2.j <<  endl;
        print_a_matrix(mat2);
        mat2.reshape(1, 3);
        cout << "mat2.reshape(1, 3);" << endl;
        cout << "mat2.length: " << mat2.length << ", mat2.i: " << mat2.i << ", mat2.j: " << mat2.j << endl;
        print_a_matrix(mat2);
        cout << endl;

        My_Matrix<int> mat3{1, 2, 3, 4};
        My_Matrix<int> mat4{5, 6, 7, 8};
        cout << "9. 使用initializer_list构造Matrix，此时Matrix为一个行向量" << endl;
        mat3.reshape(2, 3);
        cout << "mat3.reshape(2, 3);" << endl;
        cout << "mat3.length: " << mat3.length << ", mat2.i: " << mat3.i << ", mat2.j: " << mat3.j <<  endl;
        print_a_matrix(mat3);
        mat4.reshape(2, 3);
        cout << "mat4.reshape(2, 3);" << endl;
        cout << "mat4.length: " << mat4.length << ", mat2.i: " << mat4.i << ", mat2.j: " << mat4.j <<  endl;
        print_a_matrix(mat4);
        cout << endl;

        cout << "10. 矩阵加法，如果矩阵尺寸不同需抛出异常:" << endl;
        cout << "mat3 + mat4;" << endl;
        print_a_matrix(mat3 + mat4);
        cout << endl;

        cout << "11. 矩阵减法，如果矩阵尺寸不同需抛出异常:" << endl;
        cout << "mat3 - mat4;" << endl;
        print_a_matrix(mat3 - mat4);
        cout << endl;

        cout << "12. 矩阵乘法，此处为两个2*3的矩阵相乘，不满足矩阵乘法定义，需要抛出异常:" << endl;
        cout << "mat3 * mat4; // 抛出异常（取消下一行的注释可查看异常）" << endl;
        // print_a_matrix(mat3 * mat4);
        cout << endl;

        cout << "13. 将 mat4 reshape 正确之后，执行mat3 * mat4：" << endl;
        mat4.reshape(3,2);
        print_a_matrix(mat3 * mat4);
        cout << endl;

        My_Matrix mat5 = move(mat4);
        cout << "14. 支持移动构造 My_Matrix mat5 = move(mat4);" << endl;
        // print_a_matrix(mat5);
        cout << endl;


    }
    catch(...)
    {
        cout << endl << "----Catch error!!!----" << endl;
    }

}






