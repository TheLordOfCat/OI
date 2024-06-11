#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

ull k;

void getData(){
    cin>>k;
}

vector<ull> fibonaci(ull l){
    vector<ull> ans;
    ans.PB(0);
    ans.PB(1);

    ull cur = 0+1;
    while(cur <= l){
        cur = ans[ans.size()-1] + ans[ans.size()-2];
        ans.PB(cur);
    }

    return ans;
}

int solve(){
    vector<ull> fib = fibonaci(k);

    ull ans = 0;
    ull cur = k;
    while(cur != 0){
        auto itr = lower_bound(fib.begin(),fib.end(), cur);
        ull m = itr - fib.begin()-1;

        if(cur - fib[m] < fib[m+1] - cur){
            ans++;
            cur -= fib[m];
        }else{
            ans++;
            cur = fib[m+1] - cur;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int p;
    cin>>p;
    for(int i = 0; i<p; i++){
        getData();

        ull ansS = solve();
        cout<<ansS<<"\n";
    }
    return 0;
}