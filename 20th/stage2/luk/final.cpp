#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ll = long long int;
using ull = unsigned long long int;

int n;
vector<PII> edges;

void getData(){
    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

bool check(int k, vector<vector<int>>& graph){
    vector<int> dp(n+1, 0);
    vector<int> parent(n+1, -1);

    parent[1] = 0;
    stack<pair<int,bool>> S;
    S.push(MP(1,false));
    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();

        if(b){
            int sum = 0;
            for(int j = 0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if(cur != parent[v]){
                    sum += dp[cur] + 1;
                }
            }
            dp[v] = max(0,sum-k);

            continue;
        }

        S.push(MP(v,true));
        for(int j = 0; j<graph[v].size(); j++){
            int cur = graph[v][j];
            if(parent[cur] == -1){
                parent[cur] = v;
                S.push(MP(cur, false));
            }
        }
    }

    if(dp[1] == 0){
        return true;
    }

    return false;
}

int solve(){
    vector<vector<int>> graph(n+1, vector<int>());

    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    int ans = n;
    int l = 0;
    int r = n;
    while(l<=r){
        int mid = (l+r)/2;
        if(check(mid, graph)){
            ans = mid;
            r = mid-1;
        }else{
            l = mid+1;
        }
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    int ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}