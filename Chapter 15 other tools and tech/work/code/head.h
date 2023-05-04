#include <iostream>
const int N = 200;
template <typename T>
class My_Matrix
{
    // friend auto operator + (My_Matrix A, My_Matrix B)
    // {
    //     My_Matrix res;
    //     res.x = A.x + B.x;
    //     return res;
    // }
    T x;
    int leng = 1;
    int wid = 1;
};

template <>
struct My_Matrix<int>
{
    My_Matrix(int input = 1)
    {
        for(int i=0;i<leng;i++){
            for(int j=0;j<wid;j++){
                x[i][j] = input;
            }
        }
    }

    int leng = 1;
    int wid = 1;
    int x[N][N];

};


// template
// class My_Matrix<int>()
// {
// };



