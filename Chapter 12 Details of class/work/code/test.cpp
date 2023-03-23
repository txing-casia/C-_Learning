#include <iostream>
#include <ctime>
#include <algorithm>
// #include <cstdlib>
#include <unistd.h>
using namespace std;

int main(){

    for(int i = 0; i < 10; i++){
        sleep(1);
        cout << i << endl;
    }
}