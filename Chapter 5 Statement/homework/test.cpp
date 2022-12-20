#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    vector<char> A = {1,2,3,'a','b','x','z'};
    vector<char> B = {1,2,2,3,'a','b','x','z'};
    // if (A.size()>B.size())
    //     cout<<A.size()<<endl;
    // else if (A.size()<=B.size())
    //     cout<<A.size()<<endl;
    string C="132465798";
    cout<<C[1 : C.length()];

    return 0;
}

