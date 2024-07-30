#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

const int INF = 2'000'000'000;

int n, m, k;
vector<PII> edges;
vector<tuple<int,int,int>> requests;

void getData(){
    cin>>n>>m>>k;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
    for(int i = 0; i<k; i++){
        int s, t, d;
        cin>>s>>t>>d;
        requests.PB(MT(s,t,d));
    }
}

vector<int> solve(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    vector<vector<int>> querys(n+1, vector<int>());
    for(int i = 0; i<k; i++){
        querys[get<0>(requests[i])].PB(i);
    }


    vector<int> ans(k, -1);

    for(int i = 1; i<=n; i++){
        if(querys[i].size() == 0) continue;

        vector<PII> shortest(n+1, MP(INF,INF));

        queue<PII> Q;
        Q.push(MP(i,0));

        while(!Q.empty()){
            int v = Q.front().first;
            int l = Q.front().second;
            Q.pop();

            for(int j = 0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if((l+1)%2 == 0){
                    if(shortest[cur].first >= l+1){
                        shortest[cur].first = l+1;
                        Q.push(MP(cur,l+1));
                    }
                }else{
                    if(shortest[cur].second >= l+1){
                        shortest[cur].second = l+1;
                        Q.push(MP(cur,l+1));
                    }
                }
            }
        }

        for(int j = 0; j<querys[i].size(); j++){
            int s = get<0>(requests[querys[i][j]]), t = get<1>(requests[querys[i][j]]), d = get<2>(requests[querys[i][j]]); 

            int ok = 0;
            if(d%2 == 0){
                if(shortest[t].first <= d){
                    ok = 1;
                }
            }else{
                if(shortest[t].second <= d){
                    ok = 1;
                }
            }
            ans[querys[i][j]] = ok;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    vector<int> ansS = solve();
    for(int j = 0; j<k; j++){
        if(ansS[j] == 0){
            cout<<"NIE\n";
        }else{
            cout<<"TAK\n";
        }
    }

    return 0;
}