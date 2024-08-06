#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using ll = long long int;
using ull = unsigned long long int;

using namespace std;

#define PB push_back
#define PII pair<int,int>
#define MP make_pair

const int i_INF = 2'000'000;
const ll ll_INF = 9'000'000'000'000'000;

int n, m;
vector<int> x;
vector<int> k;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<m; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }
}

vector<int> solve(){
    vector<int> ans;

    for(int o = 0; o<m; o++){
        int lim = k[o];

        vector<int> w;
        for(int i = 0; i<n; i++){
            w.PB(x[i]-lim);
        }

        vector<int> a;
        a.PB(0);
        for(int i = 0; i<n; i++){
            a.PB(a[i]+w[i]);
        }

        ll cur = ll_INF;
        vector<int> pref;
        for(int i = 0; i<=n; i++){
            if(a[i] < cur){
                pref.PB(i);
                cur = a[i];
            }
        }

        cur = -ll_INF;
        vector<int> suf;
        for(int i = n; i >= 0; i--){
            if(a[i] > cur){
                suf.PB(i);
                cur = a[i];
            }
        }

        int best = 0;
        int sufInd = 0;
        for(int i = pref.size()-1; i>=0; i--){
            while(a[pref[i]] > a[suf[sufInd]]){
                sufInd++;
            }
            best = max(best, (suf[sufInd] - pref[i]));
        }
        ans.PB(best);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();        

    vector<int> ansS = solve();
    for(int j = 0; j<ansS.size(); j++){
        cout<<ansS[j]<<" ";
    }

    return 0;
}