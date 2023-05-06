#include <iostream>
#include "head.h"
#include <cassert>
using namespace std;



int main()
{
    try
    {
        My_Matrix<int> mat1;
        cout << "1. 无参构造:" << endl;
        cout << "m x n size: " << size(mat1.data) << ", value: " << mat1.data.at(0) << endl;

        My_Matrix<int> mat2(2,2);
        cout << "2. 输入矩阵尺寸构造:" << endl;
        cout << "m x n size: " << size(mat2.data) << ", value: " << mat2.data.at(0) << endl;

        mat2[1][0] = 42;
        cout << "3. 通过[][]访问内部元素" << endl;
        cout << "mat2[1][0]: " << mat2[1][0] << endl;

        cout << "4. 使用at访问矩阵按行展开后对应的元素:" << endl;
        cout << "mat2.at(2): " << mat2.at(2) << endl;

        cout << "5. at访问越界时抛出异常: (取消注释可查看)" << endl;
        // cout << "mat2.at(5): " << mat2.at(5) << endl;

        mat2.at(1);
        cout << "6. 可用at实现赋值 mat2.at(1) = 1:" << endl;
        cout << mat2.at(1) << endl;



    }
    catch(...)
    {
        cout << endl << "----Catch error!!!----" << endl;
    }

}






