#include <iostream>
#include <vector>
#include <span>
#include <initializer_list>
template <typename T>
class My_Matrix
{
    friend My_Matrix operator + (const My_Matrix& A, const My_Matrix& B)
    {
        // ref: 加法实现参考助教老师代码
        if ((A.i != B.i) || (A.j != B.j))
        {
            std::cout << "std::length_error(My_Matrix::operator +, length does not match)" << std::endl;
            throw std::length_error("My_Matrix::operator +, length does not match");
        }
        My_Matrix ret(A.i, A.j);
        const uint16_t len = A.i * A.j;
        for (auto i = 0; i < len; ++i)
            ret.data[i] = A.data[i] + B.data[i];
        return ret;
    }

    friend My_Matrix operator - (const My_Matrix& A, const My_Matrix& B)
    {
        // ref: 减法实现参考助教老师代码
        if ((A.i != B.i) || (A.j != B.j))
        {
            std::cout << "std::length_error(My_Matrix::operator -, length does not match)" << std::endl;
            throw std::length_error("My_Matrix::operator -, length does not match");
        }
        My_Matrix ret(A.i, A.j);
        //cant use data.len due to push_back
        const uint16_t len = A.i * A.j;
        for (auto i = 0; i < len; ++i)
            ret.data[i] = A.data[i] - B.data[i];
        return ret;
    }



public: // private:
    T x;
    std::vector<T> data;
    int i;
    int j;
    int length = i * j;
    // 无参数初始化
    My_Matrix():x(0), i(1), j(1), length(1), data(1, x){}
    // 输入矩阵尺寸初始化
    My_Matrix(int m, int n): x(0), i(m), j(n),length(m * n) ,data(m * n, x){}
    // initializer_list初始化
    My_Matrix(std::initializer_list<T> list) : data(list), i(1), j(list.size()), length(list.size())
    {
        // ref: initializer_list初始化功能参考助教老师的代码示例
        if (list.size() == 0)
        *this = My_Matrix();
    }

    typename std::vector<T>::iterator operator [](const std::size_t idx)
    {
        // ref: [][]访问功能参考助教老师的代码示例
        if(idx > (i - 1)){
            std::cout << "My_Matrix::operator[], access invalid row!" << std::endl;
            throw std::range_error("My_Matrix::operator[], access invalid row!");
        }
        return data.begin() + (idx * j);
    }

    auto& at(const std::size_t idx)
    {
        if(idx > length - 1){
            std::cout << "My_Matrix::operator[], access invalid row!" << std::endl;
            throw std::range_error("My_Matrix::operator[], access invalid row!");
        }
        return data[idx];  // data[idx] ;
    }

    void push_back(const int input)
    {
        data.push_back(input);
        length++;
    }

    void reshape(const int A, const int B)
    {
        if (A * B <= length)
        {
            for(int i = A * B; i < length; i++)
            {
                data.erase(data.begin() + A * B);
            }
        }else
        {
            for(int i = length; i < A * B; i++)
            {
                data.push_back(x);
            }
        }
        i = A;
        j = B;
        length = i * j;
    }

    My_Matrix operator * (const My_Matrix& A)
    {
        // ref: 减法实现参考助教老师代码
        if ((this->i != A.j) || (this->j != A.i))
        {
            std::cout << "std::length_error(My_Matrix::operator *, length does not match)" << std::endl;
            throw std::length_error("My_Matrix::operator *, length does not match");
        }
        int ii = this->i;
        int jj = A.j;
        My_Matrix ret(ii, jj);
        //cant use data.len due to push_back
        const uint16_t len = A.i * A.j;
        for (auto i = 0; i < ii; ++i)
        {
            for (auto j = 0; j < jj; ++j)
            {
                for (auto k = 0; k < A.i; ++k)
                {
                    //debug use
                    //std::cout << this->getVal(i, k) << ' ' << m.getVal(k, j) << std::endl;
                    ret[i][j] += (this->data[i * k]) * (A.data[k * j]);
                }
            }
        }
        return ret;
    }

};


