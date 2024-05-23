#include<iostream>
#include <vector>
#include <queue>

using namespace std;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

using ll = long long int;

ll n, k;
ll start = 0, finish = 0;
vector<ll> removed;

void getData(){
    cin>>n>>k;
    for(int i = 1; i<=n; i++){
        char temp;
        cin>>temp;
        start += (1<<(n-i)) * (temp-'0');
    }
    for(int i = 1; i<=n; i++){
        char temp;
        cin>>temp;
        finish += (1<<(n-i)) * (temp-'0');
    }
    for(int i = 0; i<k; i++){
        ll num = 0;
        for(int j = 1; j<=n; j++){
            char temp;
            cin>>temp;
            num += (1<<(n-j)) * (temp-'0');
        }
        removed.PB(num);
    }
}

bool solve(){
    vector<ll> firstVec = {start, finish};
    bool ans = true;
    for(int t = 0; t<2; t++){
        ll count = 0;
        ll s = ((ll)1)<<n;
        vector<bool> vis(s, false);
        for(int i = 0; i<k; i++){
            vis[removed[i]] = true;
        }
        queue<ll> Q;
        Q.push(firstVec[t]);
        while(!Q.empty()){
            ll v =  Q.front();
            Q.pop();
            count++;
            for(int j = 0; j<n; j++){
                ll cur = v;
                cur ^= (1<<j);
                if(!vis[cur]){
                    vis[cur] = true;
                    Q.push(cur);
                    if(cur == firstVec[(t+1)%2]){
                        return true;
                    }
                }
            }
        }   
        if(count < n*k){
            ans = false;
            break;
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    bool ansS = solve();
    if(ansS){
        cout<<"TAK\n";
    }else{
        cout<<"NIE\n";
    }

    return 0;
}