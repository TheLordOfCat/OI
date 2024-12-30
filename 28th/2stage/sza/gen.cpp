#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back
#define MT make_tuple
#define PIC pair<int,char>

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout<<200<<"\n";
    for(int i = 2; i<=500; i++){
        cout<<1<<" "<<i<<" A\n";
    }
    for(int i = 501; i<=1001; i++){
        cout<<1<<" "<<i<<" B\n";
    }

    return 0;
}