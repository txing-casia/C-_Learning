#include <iostream>
#include <vector>
using namespace std;

void change(double a[3])
{
    a[0] = 1.0;
    a[1] = 2.0;
    a[2] = 3.0;
}

int main(void)
{
    vector<char> A = {1,2,3,'a','b','x','z'};
    vector<char> B = {1,2,2,3,'a','b','x','z'};
    double out[3]{0.0,0.0,0.0};
    change(out);
    for(int i=0;i<3;i++)
    {
        cout << out[i] << endl;
    }


    return 0;
}

