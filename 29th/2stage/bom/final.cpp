#include<iostream>

using namespace std;

using ull = unsigned long long int;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ull x = 2, y = 1;
    ull mulitX = x*x, mulitY = y*y;
    ull tog = (x+y)*(x+y);
    for(int i = 2; i<=20; i+= 2){
        cout<<i<<" - ";
        if(tog%(mulitX+mulitY) == 0){
            cout<<"TAK\n";
        }else{
            cout<<"NIE\n";
        }
        mulitX *= x;
        mulitX *= x;
        mulitY *= y;
        mulitY *= y;
        tog *= (x+y);
        tog *= (x+y);
    }

    return 0;
}