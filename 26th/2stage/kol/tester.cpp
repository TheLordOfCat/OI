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

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    r = rand()%10+2;
    for(int i = 0; i<n; i++){
        int temp = rand()%r+1;
        t.PB(temp);
    }
    int ind = 2;
    for(int i = 1; i<=n; i++){
        if(ind > n){
            break;
        }
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            if(ind > n){
                break;
            }
            int c = rand()%10+1;

            edges.PB(MT(i, ind, c));

            ind++;
        }
    }

    q = rand()%10+10;
    for(int i = 0; i<q; i++){
        int a = rand()%n+1, b = rand()%n+1, c = rand()%r+1;
        querys.PB(MT(a,b,c));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<r<<"\n";
    for(int i = 0; i<t.size(); i++){
        cout<<t[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    cout<<q<<"\n";
    for(int i = 0; i<querys.size(); i++){
        int a = get<0>(querys[i]), b = get<1>(querys[i]), c = get<2>(querys[i]);
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    cout<<"\n";

    return ;
}

void dfs(int v, vector<int>& mark, vector<vector<PII>>& graph){
    vector<int> dp(n+1, 0);
    vector<bool> vis(n+1, false);
    stack<int> S;
    S.push(v);

    while(!S.empty()){
        int v = S.top();
        S.pop();
        vis[v] = true;

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i].first;
            if(!vis[cur]){
                S.push(cur);
                vis[cur] = true;
                mark[cur] += graph[v][i].second + dp[v];
                dp[cur] = graph[v][i].second + dp[v];
            }
        }
    }
}

vector<int> brute(){
    vector<vector<PII>> graph(n+1, vector<PII>());

    for(int i = 0; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    vector<int> ans;

    for(int i = 0; i<querys.size(); i++){
        int p = get<0>(querys[i]), q = get<1>(querys[i]), s = get<2>(querys[i]);
        vector<int> dis(n+1, 0);

        dfs(p, dis, graph);
        dfs(q, dis, graph);

        PII best = MP(INF,INF);
        for(int j = 1; j<=n; j++){
            if(t[j-1] == s){
                if(best.second > dis[j]){
                    best = MP(j, dis[j]);
                }
            }
        }

        if(best.first == INF){
            ans.PB(-1);
        }else{
            ans.PB(best.second);
        }
    }

    return ans;
}

bool compareQuerys(tuple<int,int,int> a, tuple<int,int,int> b){
    if(get<2>(a) == get<2>(b)){
        if(get<0>(a) == get<0>(b)){
            return get<1>(a) > get<1>(b);
        }   
        return get<0>(a) > get<0>(b); 
    }
    return get<2>(a) > get<2>(b);
}

vector<int> tin, tout;
vector<vector<int>> up;
vector<vector<ll>> mind;

vector<int> depth;

void dfsLCA(int V, vector<vector<PII>>& graph){
    tin.clear();
    tout.clear();
    up.clear();
    tin.assign(n+1, 0);
    tout.assign(n+1, 0);
    int timer = 0;
    vector<bool> vis(n+1, false);
    up.assign(n, vector<int>(ceil(log2(n)) + 1, 0));

    stack<pair<int,bool>> S;
    S.push(MP(V,false));
    vis[V] = true;

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        int l = ceil(log2(depth[v]));

        S.pop();

        tin[v] = timer;
        timer++;

        if(b){
            tout[v] = timer;
            timer++;
            continue;
        }

        S.push(MP(v,true));

        for (int i = 1; i <= l; ++i) up[v][i] = up[up[v][i-1]][i-1];

        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            if(!vis[cur.first]){
                vis[cur.first] = true;
                S.push(MP(cur.first,false));
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

void dfsDepthLen(int v, vector<vector<PII>> &graph){
    depth.assign(n+1, 0);

    vector<bool> vis(n+1, false);
    stack<int> S;
    S.push(v);
    vis[v] = true;
    depth[v] = 0;

    while(!S.empty()){
        int v =  S.top();
        S.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i].first;
            if(!vis[cur]){
                vis[cur] = true;
                S.push(cur);

                depth[cur] = depth[v]+1;
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
        int l = ceil(log2(depth[v]));
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
    vector<vector<PII>> compresGraph(order.size(), vector<PII>());

    for(int i = 0; i<order.size()-1; i++){
        int a = order[i], b = order[i+1];
        int l = lca(a, b);
        compresGraph[l].PB(MP(b, depth[b] - depth[l]));
        compresGraph[b].PB(MP(l, depth[b] - depth[l]));
    }

    //create mind
    mind.assign(n+1, vector<ll>(ceil(log2(n))+1, llINF));
    vector<bool> vis(n+1, false);
    queue<int> Q;
    for(int  i = 0; i<t.size(); i++){
        if(t[i] == c){
            Q.push(i+1);
            vis[i+1] = true;
            mind[i+1][0] = 0;
        }
    }

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i<compresGraph[v].size(); i++){
            int cur = compresGraph[v][i].first;
            if(!vis[cur]){
                vis[cur] = true;
                mind[cur][0] = mind[v][0] + 1;
                Q.push(cur);
            }
        }
    }
    

    dfsDepthLen(V.front(), compresGraph);    
    getMind(V.front(), compresGraph);

    return compresGraph;
}

ll process(int a, int b, int c){
    ll ans = llINF;

    int A = a;
    int B = b;

    int l = ceil(log2(depth[A])); 
    for(int i = l; i >= 0; i--){
        if(!isAncestor(up[A][i], b)){
            ans = min(mind[A][i], ans);
            A = up[A][i];
        }
    }

    int l = ceil(log2(depth[B])); 
    for(int i = l; i >= 0; i--){
        if(!isAncestor(up[B][i], a)){
            ans = min(mind[B][i], ans);
            B = up[B][i];
        }
    }

    return ans;
}

vector<ll> solve(){
    vector<ll> ans;

    //create graph
    vector<vector<PII>> graph(n+1, vector<PII>());
    for(int i = 0; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    //sort
    sort(querys.begin(),querys.end(), compareQuerys);

    //proces querys
    vector<int> v;
    int last = 0;
    vector<vector<PII>> compresGraph;
    for(int i = 0; i<q; i++){
        int a = get<0>(querys[i]), b = get<1>(querys[i]), c = get<2>(querys[i]);
        
        if(i != q-1){
            if(c != get<2>(querys[last])){
                compresGraph = preproces(v, c, graph);
                for(int j = last; j<last + v.size(); j++){
                    ll temp = process(get<0>(querys[j]),get<1>(querys[j]),get<2>(querys[j]));
                    ans.PB(temp);
                }
                last = i+1;
            }else{
                v.PB(a);
                v.PB(b);
            }
        }
    }
    compresGraph = preproces(v, get<2>(querys[last]), graph);
    for(int j = last; j<last + v.size(); j++){
        ll temp = process(get<0>(querys[j]),get<1>(querys[j]),get<2>(querys[j]));
        ans.PB(temp);
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<ll> ansS = solve();
        for(int i = 0; i<ansS.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: \n";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: \n";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
    }

    return 0;
}