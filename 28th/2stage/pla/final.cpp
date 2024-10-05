#include<iostream>

using namespace std;

int main()
{
    int t = 1;
    int e = 1;
    for(int i = 1; i<=100; i++){
        if((t+e)%7 == 0 && (t+e) != 7){
            cout<<i<<"\n";
            break;
        }else{
            t *= 2;
            e *= 5;
        }
    }

    return 0;
}