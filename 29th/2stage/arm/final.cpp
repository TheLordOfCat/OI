#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

ull n, a, b;

void getData(){
    cin>>n>>a>>b;
}

ull solve(){
    ull ans = ullINF;
    for(ull m = 1; (1<<m) <= 4*n; m++){
        ull s = pow((n+1), 1.0 / m);
        for(ull k = 0; k<=m; k++){
            ull sum = pow(s,k) * pow(s+1,m-k);
            if(sum >= n+1){
                ull cost = m*a+(s*m-k)*b;
                if(cost < ans){
                    ans = cost;
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    ull ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}