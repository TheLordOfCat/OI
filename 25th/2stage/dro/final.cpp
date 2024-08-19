#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;
using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

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

vector<bool> visSCC;

void dfs(int v, vector<vector<int>>& graph, vector<int>& vec){
    visSCC[v] = true;
    for(int j = 0; j < graph[v].size(); j++){
        int cur = graph[v][j];
        if(!visSCC[cur]){
            dfs(cur, graph, vec);
        }
    }
    vec.PB(v);
}

void createSCC(vector<vector<int>>& graphSCC, vector<vector<int>>& components, vector<vector<int>>& graph, vector<vector<int>>& graphRev){
    //getting order
    visSCC.assign(n+1, false);
    vector<int> order;

    for(int i = 1; i<=n; i++){
        if(!visSCC[i]){
            dfs(i,graph,order);
        }   
    }

    reverse(order.begin(),order.end());

    visSCC.assign(n+1, false);
    vector<int> root(n+1, -1);
    for(int i = 0; i < order.size(); i++){
        if(!visSCC[order[i]]){
            vector<int> comp;
            dfs(order[i],graphRev,comp);
            components.PB(comp);
            for(int j = 0; j<comp.size(); j++){
                root[comp[j]] = components.size()-1;
            }
        }
    }
    graphSCC.assign(components.size(), vector<int>());

    for(int i = 1; i<=n; i++){
        for(int j = 0; j < graph[i].size(); j++){
            int cur = graph[i][j];
            if(root[i] != root[cur]){
                graphSCC[root[i]].PB(root[cur]);
            }
        }
    }
}


vector<int> solve(){
    //creating graph 
    vector<vector<int>> graph(n+1, vector<int>());    
    vector<vector<int>> graphR(n+1, vector<int>());    
    for(int i = 0; i<m; i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graphR[b].PB(a);
    }

    //creating SCC
    vector<vector<int>> graphSCC;
    vector<vector<int>> components;
    createSCC(graphSCC, components, graph, graphR);

    //dp on SCC
    vector<int> dp(components.size(), 0);
    vector<bool> vis(components.size(), false);
    vector<int> parent(components.size(), -1);

    for(int i = 0; i<components.size(); i++){
        if(!vis[i]){
            stack<pair<int,bool>> S;
            S.push(MP(i,false));
            vis[i] = true;

            while(!S.empty()){
                int v = S.top().first;
                bool b = S.top().second;
                S.pop();

                if(b){
                    int sum = components[v].size();
                    for(int j = 0; j<graphSCC[v].size(); j++){
                        int cur = graphSCC[v][j];
                        if(cur != parent[v]){
                            sum += dp[cur];
                        }
                    }
                    dp[v] = sum;
                    continue;
                }

                S.push(MP(v,true));
                for(int j = 0; j<graphSCC[v].size(); j++){
                    int cur = graphSCC[v][j];
                    if(!vis[cur]){
                        vis[cur] = true;
                        S.push(MP(cur,false));
                    }
                }
            }
        }
    }

    //geting the ans
    vector<int> ans(n, 0);

    for(int i = 0; i<components.size(); i++){
        for(int j = 0; j<components[i].size(); j++){
            ans[components[i][j]-1] = dp[i]-1;
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
    for(int j = 0; j<ansS.size(); j++){
        cout<<ansS[j]<<"\n";
    }    

    return 0;
}