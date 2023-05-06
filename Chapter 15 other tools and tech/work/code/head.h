#include <iostream>
#include <vector>
#include <span>
template <typename T>
class My_Matrix
{
    // friend auto operator + (My_Matrix A, My_Matrix B)
    // {
    //     My_Matrix res;
    //     res.x = A.x + B.x;
    //     return res;
    // }

public: // private:
    T x;
    std::vector<T> data;
    int i;
    int j;
    // 无参数初始化
    My_Matrix():x(0), i(1), j(1), data(1, x){}
    // 输入矩阵尺寸初始化
    My_Matrix(int m, int n): x(0), i(m), j(n) ,data(m * n, x){}

    // std::span<T> operator[](int row)
    // {
    //     const auto beginIt = data.begin() + row * j;
    //     return std::span(beginIt, j);
    // }


    typename std::vector<T>::iterator operator [](std::size_t idx)
    {
        /*
        ref: [][]访问功能参考助教老师的代码示例
        */
        if(idx > (i - 1)){
            throw std::range_error("My_Matrix::operator[], access invalid row!");
        }
        return data.begin() + (idx * j);
    }

    T at(std::size_t idx)
    {
        if(idx > j * i - 1){
            throw std::range_error("My_Matrix::operator[], access invalid row!");
        }
        return data[idx];  // data[idx] ;
    }


    My_Matrix& My_Matrix::operator=(const My_Matrix &c)
    {//具备自我赋值安全性和备异常安全性
        A *temp=p;
        p=new A(*c.p);
        delete temp;
        return *this;
    }

};

// template <>
// struct My_Matrix<int>
// {

//     std::span<int> operator [](int row)
//     {
//         const auto beginIt = data.begin() + row * j;
//         return std::span(beginIt, j)
//     }

// };


// template
// class My_Matrix<int>()
// {
// };



