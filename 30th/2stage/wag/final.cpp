#include <iostream>
#include <vector>
#include <stack>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

ll n; int d, a, b;

void getData(){
    cin>>n>>d>>a>>b;
}

ull f(ull w, ull v){
    ull temp = ((ull)a)*w + ((ull)b)*v;
    return temp%1001;
}

ull solve(){
    //generate ranges
    stack<pair<ll,ll>> S;

    S.push(MP(n,n));
    while(true){
        pair<ll,ll> r = S.top();
        if(r.first == 1){
            break;
        }
        S.push(MP(max(r.first/2-d/2-2, (ll)1), min(r.second/2+d/2+2, n)));
    }

    //get base
    ll baseRight = S.top().second;
    vector<ull> dp(baseRight+1, 0);
    for(ull i = 2; i<=baseRight; i++){
        ull m = ullINF;
        ll bestJ = llINF;

        ull bottom = 1;
        if(i/2-d/2-2 > bottom && i/2 > d/2+2) bottom = i/2-d/2-2;

        for(ll  j = min(i/2+d/2+2,i-1); j >= bottom; j--){
            ll dif;
            if(i-j > j) {
                dif = i-j-j;
            }else{
                dif = j-(i-j);
            }

            if(dif <= d){
                ull temp1 = min(f(j,i-j),f(i-j,j));
                if(temp1 + dp[j] + dp[i-j]  < m){
                    m = temp1+ dp[j] + dp[i-j];
                    bestJ = j;
                }
            }
        }
        dp[i] = m;
    }

    //process ranges
    S.pop();
    ll firstElement = 0;
    while(!S.empty()){
        pair<ll,ll> r = S.top();
        S.pop();
        
        vector<ull> nextDp(r.second+1-r.first+1, 0);
        for(ll i = r.first; i<=r.second; i++){
            ull m = ullINF;
            ll bestJ = llINF;
            for(ll  j = min(i/2+d/2+2, i-1); j>= max((ll)1, i/2-d/2-2); j--){
                ll dif;
                if(i-j > j) {
                    dif = i-j-j;
                }else{
                    dif = j-(i-j);
                }

                if(dif <= d){
                    ull temp1 = min(f(j,i-j),f(i-j,j));
                    if(temp1 + dp[j-firstElement] + dp[i-j-firstElement]  < m){
                        m = temp1 + dp[j-firstElement] + dp[i-j-firstElement];
                        bestJ = j;
                    }
                }
            }
            nextDp[i-r.first+1] = m;
        }

        dp = nextDp;
        firstElement = r.first-1;
    }

    return dp.back();
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