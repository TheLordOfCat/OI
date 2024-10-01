#include<iostream>

using namespace std;

int main()
{
    for(int i = 2; i<=100; i+=2){
        for(int j = 1; j<=100; j+=2){
            if((i*j*(i+j))%(i*i+j*j) == 0){
                cout<<i<<" "<<j<<"\n";
            }
        }
    }

    return 0;
}