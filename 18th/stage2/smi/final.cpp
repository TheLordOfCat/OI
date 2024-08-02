#include <iostream>
#include <vector>
#include <stack>
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

int n, m;
vector<tuple<int,int,int,int>> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b, s,t;
        cin>>a>>b>>s>>t;
        edges.PB(MT(a,b,s,t));
    }
}

vector<vector<int>> solve(){
    vector<vector<pair<PII,bool>>> graph(n+1, vector<pair<PII,bool>>());
    for(int i = 0; i<m; i++){
        int a = get<0>(edges[i]), b = get<0>(edges[i]), s = get<0>(edges[i]), t = get<0>(edges[i]);  
        if(s != t){
            graph[a].PB(MP(MP(b, graph[b].size()),false));
            graph[b].PB(MP(MP(a, graph[a].size()-1),false));
        }
    }

    vector<int> degree(n+1, 0);
    for(int i = 1; i<=n; i++){
        degree[i] = graph[i].size(); 
    }

    vector<vector<int>> ans;

    stack<int> S;
    vector<bool> vis(n+1, false);
    
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            vector<int> cycle;
            S.push(i);
            while(!S.empty()){
                int v = S.top();
                if(degree[v] == 0){
                    cycle.PB(v);
                    vis[v] = true;
                    S.pop();
                }else{
                    for(int j = 0; j<graph[v].size(); j++){
                        if(!graph[v][j].second){
                            S.push(graph[v][j].first.first);
                            graph[v][j].second = true;
                            graph[graph[v][j].first.first][graph[v][j].first.second].second = true;
                            break;
                        }
                    }
                }
            }
            ans.PB(cycle);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<vector<int>> ansS = solve();

    cout<<ansS.size()<<"\n";
    for(int i = 0; i<ansS.size(); i++){
        for(int j = 0; j <ansS[i].size(); j++){
            int cur = ansS[i][j];
            cout<<cur<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";

    return 0;
}