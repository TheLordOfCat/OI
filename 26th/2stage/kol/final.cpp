#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <tuple>
#include <cmath>

#include <cstdlib>
#include <ctime>

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

using namespace std;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

int n, r;
vector<int> t;
vector<tuple<int,int,int>> edges;
int q;
vector<tuple<int,int,int>> querys;

void getData(){
    cin>>n>>r;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        t.PB(temp);
    }
    for(int i = 0; i<n-1; i++){
        int a, b, c;
        cin>>a>>b>>c;
        edges.PB(MT(a,b,c));
    }
    cin>>q;
    for(int i =0; i<q; i++){
        int a, b, c;
        cin>>a>>b>>c;
        querys.PB(MT(a,b,c));
    }
}

bool compareQuerys(pair<int, tuple<int,int,int>> a, pair<int, tuple<int,int,int>> b){
    if(get<2>(a.second) == get<2>(b.second)){
        if(get<0>(a.second) == get<0>(b.second)){
            return get<1>(a.second) > get<1>(b.second);
        }   
        return get<0>(a.second) > get<0>(b.second); 
    }
    return get<2>(a.second) < get<2>(b.second);
}

vector<int> tin, tout;
vector<vector<int>> up;
vector<vector<ll>> mind;

vector<int> depth;
vector<ll> depthSum;

void dfsLCA(int V, vector<vector<PII>>& graph){
    tin.clear();
    tout.clear();
    up.clear();
    tin.assign(n+1, 0);
    tout.assign(n+1, 0);
    int l = ceil(log2(n));
    int timer = 0;
    vector<bool> vis(n+1, false);
    up.assign(n+1, vector<int>(l + 1, 0));

    stack<pair<int,bool>> S;
    S.push(MP(V,false));
    vis[V] = true;
    up[V][0] = V;

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();

        if(b){
            tout[v] = timer;
            timer++;
            continue;
        }

        tin[v] = timer;
        timer++;

        S.push(MP(v,true));

        for (int i = 1; i <= l; ++i) up[v][i] = up[up[v][i-1]][i-1];

        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            if(!vis[cur.first]){
                vis[cur.first] = true;
                S.push(MP(cur.first,false));
                up[cur.first][0] = v;
            }   
        }
        
    }
}

bool isAncestor(int a, int b){
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b){
    int l = ceil(log2(depth[a])); 
    if(isAncestor(a, b)){
        return a;
    }
    if(isAncestor(b,a)){
        return b;
    }
    for(int i = l; i >= 0; i--){
        if(!isAncestor(up[a][i], b)){
            a = up[a][i];
        }
    }
    return up[a][0];
}

vector<int> dfsOrder(int v, vector<vector<PII>> &graph, vector<bool>& pointIntrest){
    vector<int> order;
    vector<bool> vis(n+1, false);
    stack<int> S;
    S.push(v);
    vis[v] = true;
    order.PB(v);

    while(!S.empty()){
        int v =  S.top();
        S.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i].first;
            if(!vis[cur]){
                vis[cur] = true;
                S.push(cur);

                if(pointIntrest[cur]){
                    order.PB(cur);
                }
            }
        }
    }

    return order;
}

void dfsDepthLen(int V, vector<vector<PII>> &graph){
    depth.assign(n+1, INF);
    depthSum.assign(n+1, llINF);

    vector<bool> vis(n+1, false);
    stack<int> S;
    S.push(V);
    vis[V] = true;
    depth[V] = 0;
    depthSum[V] = 0;

    while(!S.empty()){
        int v =  S.top();
        S.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i].first;
            if(!vis[cur]){
                vis[cur] = true;
                S.push(cur);

                depth[cur] = depth[v]+1;
                depthSum[cur] = depthSum[v]+graph[v][i].second;
            }
        }
    }

    return;
}

void getMind(int V, vector<vector<PII>> &graph){
    vector<bool> vis(n+1, false);
    stack<int> S;
    S.push(V);

    while(!S.empty()){
        int v = S.top();
        int l = ceil(log2(n));
        S.pop();

        for (int i = 1; i <= l; ++i) mind[v][i] = min(mind[v][i-1], mind[up[v][i-1]][i-1]);

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i].first;
            if(!vis[cur]){
                vis[cur] = true;
                S.push(cur);
            }
        }
    }
}

vector<vector<PII>> preproces(vector<int> V, int c, vector<vector<PII>>& graph){
    //prepare LCA
    dfsDepthLen(V.front(), graph);
    dfsLCA(V.front(), graph);

    //compress the tree
    vector<bool> pointIntrest(n+1, false);
    for(int i = 0; i<V.size(); i++){
        pointIntrest[V[i]] = true;
    }

    for(int  i = 0; i<t.size(); i++){
        if(t[i] == c){
            pointIntrest[i+1] = true;
        }
    }

    vector<int> order = dfsOrder(V.front(), graph, pointIntrest);

    for(int i = 0; i<order.size()-1; i++){
        int l = lca(order[i], order[i+1]);
        pointIntrest[l] = true;
    }

    order = dfsOrder(V.front(), graph, pointIntrest);
    vector<vector<PII>> compresGraph(n+1, vector<PII>());

    for(int i = 0; i<order.size()-1; i++){
        int a = order[i], b = order[i+1];
        int l = lca(a, b);
        compresGraph[l].PB(MP(b, depthSum[b] - depthSum[l]));
        compresGraph[b].PB(MP(l, depthSum[b] - depthSum[l]));
    }

    //create mind
    mind.assign(n+1, vector<ll>(ceil(log2(n))+1, llINF));
    queue<int> Q;
    for(int  i = 0; i<t.size(); i++){
        if(t[i] == c){
            Q.push(i+1);
            mind[i+1][0] = 0;
        }
    }

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i<compresGraph[v].size(); i++){
            int cur = compresGraph[v][i].first;
            if(mind[cur][0] > mind[v][0] + compresGraph[v][i].second){
                mind[cur][0] = mind[v][0] + 2*compresGraph[v][i].second;
                Q.push(cur);
            }
        }
    }

    dfsDepthLen(V.front(), compresGraph);    
    getMind(V.front(), compresGraph);

    return compresGraph;
}

ll process(int a, int b, int c, vector<vector<PII>>& graph){
    ll ans = llINF;

    if(graph[a].size() == 0 || graph[b].size() == 0){
        return -1;
    }

    int A = a;
    int B = b;

    int l = ceil(log2(depth[A])); 
    for(int i = l; i >= 0; i--){
        if(!isAncestor(up[A][i], b)){
            ans = min(mind[A][i], ans);
            A = up[A][i];
        }
    }
    ans = min(mind[A][0], ans);

    l = ceil(log2(depth[B])); 
    for(int i = l; i >= 0; i--){
        if(!isAncestor(up[B][i], a)){
            ans = min(mind[B][i], ans);
            B = up[B][i];
        }
    }
    ans = min(mind[B][0], ans);

    l = lca(a,b);
    ll path = (depthSum[a] - depthSum[l]) + (depthSum[b] - depthSum[l]);
    return ans + path;
}

vector<ll> solve(){
    vector<ll> ans(q, -1);

    //create graph
    vector<vector<PII>> graph(n+1, vector<PII>());
    for(int i = 0; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    vector<pair<int, tuple<int,int,int>>> queryInd;
    for(int i = 0; i<querys.size(); i++){
        queryInd.PB(MP(i, querys[i]));
    }

    //sort
    sort(queryInd.begin(), queryInd.end(), compareQuerys);

    //proces querys
    vector<int> v;
    int last = 0;
    vector<vector<PII>> compresGraph;
    for(int i = 0; i<q; i++){
        int a = get<0>(queryInd[i].second), b = get<1>(queryInd[i].second), c = get<2>(queryInd[i].second);
        
        if(c != get<2>(queryInd[last].second)){
            compresGraph = preproces(v,  get<2>(queryInd[last].second), graph);
            for(int j = last; j<i; j++){
                ll temp = process(get<0>(queryInd[j].second),get<1>(queryInd[j].second),get<2>(queryInd[j].second), compresGraph);
                ans[queryInd[j].first] = temp;
            }
            v.clear();
            last = i;
        }
        v.PB(a);
        v.PB(b);
    }
    compresGraph = preproces(v, get<2>(queryInd[last].second), graph);
    for(int j = last; j<querys.size(); j++){
        ll temp = process(get<0>(queryInd[j].second),get<1>(queryInd[j].second),get<2>(queryInd[j].second), compresGraph);
        ans[queryInd[j].first] = temp;
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    vector<ll> ansS = solve();

    for(int j = 0; j<ansS.size(); j++){
        cout<<ansS[j]<<"\n";
    }

    return 0;
}