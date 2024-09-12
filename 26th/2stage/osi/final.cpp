#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define PIVC pair<int,vector<char>> 

int n, m;
vector<PII> edges;

void getData(){
    edges.clear();

    cin>>n>>m;
    for(int i =0 ; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void dfsSCC(int v, vector<vector<PII>>& graph, vector<bool>& vis, vector<int>& ans){
    vis[v] = true;

    for(int i = 0; i<graph[v].size(); i++){
        int cur = graph[v][i].first;
        if(!vis[cur]){
            dfsSCC(cur,graph,vis,ans);
        }
    }

    ans.PB(v);
}

int getSCC(vector<vector<PII>>& graph){
    vector<vector<int>> SCC;

    vector<vector<PII>> graphRev(n+1, vector<PII>());
    for(int i = 1; i<graph.size(); i++){
        for(int j = 0; j<graph[i].size(); j++){
            PII cur = graph[i][j];
            graphRev[cur.first].PB(MP(i,cur.second));
        }
    }

    vector<bool> vis(n+1, false);
    vector<int> order;
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            dfsSCC(i,graph,vis,order);
        }
    }

    vis.assign(n+1, false);
    reverse(order.begin(), order.end());
    for(int i = 0; i<order.size(); i++){
        int v = order[i];
        if(!vis[v]){
            vector<int> com;
            dfsSCC(v,graphRev,vis,com);
            SCC.PB(com);
        }
    }

    return SCC.size();
}

void dfs(int v, vector<vector<PII>>& graph, vector<bool>& visVec, vector<bool>& visEdge, vector<vector<PII>>& ans, vector<int>& depth){
    visVec[v] = true;

    for(int i = 0; i<graph[v].size(); i++){
        PII cur = graph[v][i];
        if(!visVec[cur.first]){
            visEdge[cur.second] = true;
            ans[v].PB(cur);
            depth[cur.first] = depth[v] + 1;
            dfs(cur.first, graph,visVec, visEdge, ans, depth);
        }
    }

}

PIVC solve(){
    vector<vector<PII>> graph(n+1, vector<PII>());
    vector<vector<PII>> graphDir(n+1, vector<PII>());

    //create base graph
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(MP(b,i));
        graph[b].PB(MP(a,i));
    }

    vector<bool> visVec(n+1, false);
    vector<bool> visEdge(m+1, false);
    vector<int> depth(n+1, 0);

    //create directed graph

    //down edges
    for(int i = 1; i<=n; i++){
        if(!visVec[i]){
            dfs(i,graph,visVec, visEdge, graphDir, depth);
        }
    }

    //returning edges
    for(int i = 0; i<m; i++){
        if(!visEdge[i]){
            int a = edges[i].first, b = edges[i].second;
            if(depth[a] > depth[b]){
                graphDir[a].PB(MP(b,i));
            }else{
                graphDir[b].PB(MP(a,i));
            }
        }
    }

    //get SCC
    int temp = getSCC(graphDir);
    vector<char> c(m, '-');
    for(int i = 1; i<graphDir.size(); i++){
        for(int j = 0; j<graphDir[i].size(); j++){
            PII cur = graphDir[i][j];
            int a = edges[cur.second].first, b = edges[cur.second].second;
            if(a == i && cur.first == b){
                c[cur.second] = '>';
            }else{
                c[cur.second] = '<';
            }
        }
    }

    PIVC ans = MP(temp, c);

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    PIVC ansS = solve();
    cout<<ansS.first<<"\n";
    for(int j = 0; j<ansS.second.size(); j++){
        cout<<ansS.second[j];
    }
    cout<<"\n";
    
    return 0;
}