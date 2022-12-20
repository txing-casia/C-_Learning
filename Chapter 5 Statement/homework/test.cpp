#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    vector<char> A = {1,2,3,'a','b','x','z'};
    vector<char> B = {1,2,2,3,'a','b','x','z'};
    if (A.size()>B.size())
        cout<<A.size()<<endl;
    else if (A.size()<=B.size())
        cout<<A.size()<<endl;


    return 0;
}

