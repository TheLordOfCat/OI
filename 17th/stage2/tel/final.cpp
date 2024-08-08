#include <iostream>
#include <vector>
#include <queue>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;

int n, m;
vector<PII> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

vector<int> BFS(int start, vector<vector<int>>& graph){
    vector<int> ans(n+1, INF);

    queue<PII> Q;
    Q.push(MP(start,0));
    bool ok = true;
    vector<bool> vis(n+1, false);

    while(!Q.empty()){
        int v = Q.front().first;
        int l = Q.front().second;
        Q.pop();

        ans[v] = l;

        for(int j = 0; j<graph[v].size(); j++){
            int cur = graph[v][j];
            if(!vis[cur]){
                vis[cur] = true;
                Q.push(MP(cur, l+1));
            }
        }
    }
    
    return ans;
}

ull solve(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0; i<edges.size(); i++){
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    ull s1 = 0, s2 = 0, s3 = 0, s4 =0;
    vector<int> t1 = BFS(1, graph);
    vector<int> t2 = BFS(2, graph);

    for(int i = 3; i<=n; i++){
        if(t1[i] == 1){
            s1++;
        }else if(t1[i] == 2){
            s2++;
        }
        if(t2[i] == 1){
            s4++;
        }else if(t2[i] == 2){
            s3++;
        }
    }

    ull excess = n-2-s1-s2-s3-s4;

    ull ans = n*(n-1)/2 - m - (n-1-s1) - s1*(1+s3+s4) - s2*(1+s4) - s3 - excess*(1+min(s1,s4));

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