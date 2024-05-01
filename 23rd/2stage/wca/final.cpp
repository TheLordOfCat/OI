#include<iostream>
#include<vector>
#include <queue>
#include <cmath>

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using namespace std;

using ll = long long int;

int n;
vector<int> a;

void getData(){
    cin>>n;
    for(int i =0 ; i<n; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
    }
}

struct pairCompare {
    bool operator()(PII a, PII b) {
        return a.first+a.second < b.first+b.second;
    }
};

ll floorLog2(ll n) {
    return floor(log2(n)) + 1;
}

ll solve(){
    ll ans = 0;

    for(int i = 0; i<n; i++){
       ans += floorLog2(a[i])*2; 
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    ll ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}