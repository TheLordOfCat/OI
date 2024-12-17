#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <tuple>
#include <cmath>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n, r;
vector<int> t;
vector<tuple<int,int,int>> edges;
int q;
vector<tuple<int,int,int>> query;

void getData(){
    t.clear(); edges.clear(); query.clear();

    cin>>n>>r;
    t.PB(-1);
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
        query.PB(MT(a,b,c));
    }
}

void getRandom(){
    t.clear(); edges.clear(); query.clear();
    srand(time(0));

    // n = rand()%5+2;
    n = 100000;
    r = rand()%10+1;
    t.PB(-1);
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

    // q = rand()%5+2;
    q = 100000;
    for(int i = 0; i<q; i++){
        int a = rand()%n+1, b = rand()%n+1, c = rand()%r+1;
        query.PB(MT(a,b,c));
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
    for(int i = 0; i<query.size(); i++){
        int a = get<0>(query[i]), b = get<1>(query[i]), c = get<2>(query[i]);
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    cout<<"\n";

    return ;
}

vector<ll> bruteDfs(int vS, vector<vector<PII>>& graph){
    queue<int> Q;
    Q.push(vS);
    vector<ll> ans(n+1, -1);
    ans[vS] = 0;

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i< graph[v].size(); i++){
            PII cur = graph[v][i];
            if(ans[cur.first] == -1){
                ans[cur.first] = ans[v]+cur.second;
                Q.push(cur.first);
            }
        }
    }

    return ans;
}

vector<ll> brute(){
    //create graph
    vector<vector<PII>> graph(n+1, vector<PII>());
    for(int i =0 ; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    //process queries
    vector<ll> ans;

    for(int i = 0; i<q; i++){
        int a = get<0>(query[i]),b = get<1>(query[i]),c = get<2>(query[i]);

        vector<ll> distA = bruteDfs(a, graph);
        vector<ll> distB = bruteDfs(b, graph);

        ll best = llINF;

        for(int j = 1; j<=n; j++){
            if(t[j] == c){
                best = min(best, distA[j] + distB[j]);
            }
        }
        if(best == llINF){
            ans.PB(-1);
        }else{
            ans.PB(best);
        }
    }
    return ans;
}

vector<int> numerate(vector<vector<pair<int,ll>>>& graph){
    stack<int> S;
    S.push(1);

    int totalOrder = 1;

    vector<int> order(n+1, -1);
    while(!S.empty()){
        int v = S.top();
        S.pop();
        if(order[v] != -1){
            continue;;
        }
        order[v] = totalOrder;
        totalOrder++;

        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            if(order[cur.first] == -1){
                S.push(cur.first);
            }
        }
    }

    return order;
}

vector<ll> getLenD(vector<vector<pair<int,ll>>>& graph){
    stack<int> S;
    S.push(1);
    vector<ll> ans(n+1, -1);
    ans[1] = 0;

    while(!S.empty()){
        int v = S.top();
        S.pop();

        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            if(ans[cur.first] == -1){
                ans[cur.first] = ans[v]+cur.second;
                S.push(cur.first);
            }
        }
    }

    return ans;
}

bool customPairComp(PII a, PII b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second < b.second;
}

vector<int> tin, tout;
vector<vector<int>> up;
int l;

vector<vector<int>> colorSplit;

bool isAncestor(int v, int u){
    return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int lca(int v, int u){
    if(isAncestor(v, u)){
        return v;
    }
    if(isAncestor(u,v)){
        return u;
    }
    for(int i = l; i>=0; i--){
        if(!isAncestor(up[u][i], v)){
            u = up[u][i];
        }
    }
    return up[u][0];
}

void dfs(vector<vector<pair<int,ll>>> &graph){
    stack<pair<int,bool>> S;
    int timer = 0;
    vector<bool> used(n+1, false);

    S.push(MP(1,false));
    used[1] = true;
    while(!S.empty()){
        pair<int,bool> v = S.top();
        S.pop();
        if(v.second){
            tout[v.first] = timer;
            timer++;
            continue;
        }

        tin[v.first] = timer;
        timer++;

        S.push(MP(v.first,true));
        int p = v.first;
        for(int i =0; i<graph[v.first].size(); i++){
            int cur = graph[v.first][i].first;
            if(!used[cur]){
                S.push(MP(cur,false));
                used[cur] = true;
            }else{
                p = cur;
            }
        }
        up[v.first][0] = p;
        for(int i = 1; i<=l; i++){
            up[v.first][i] = up[up[v.first][i-1]][i-1];
        }
    }
}

void preprocessLCA(vector<vector<pair<int,ll>>> &graph){
    tin.clear();
    tout.clear();
    tin.assign(n+1, 0);
    tout.assign(n+1, 0);
    l = ceil(log2(n));
    up.assign(n+1, vector<int>(l + 1));
    dfs(graph);
}

vector<vector<ll>> getMind(vector<vector<pair<int,ll>>>& graph, vector<ll>& dist){
    tin.clear();
    tout.clear();
    tin.assign(n+1, 0);
    tout.assign(n+1, 0);
    l = ceil(log2(n));
    vector<vector<ll>> mind(n+1, vector<ll>(l + 1));

    stack<int> S;
    int timer = 0;
    vector<bool> used(n+1, false);

    S.push(1);
    used[1] = true;
    while(!S.empty()){
        int v = S.top();
        S.pop();

        tin[v] = timer;
        timer++;

        int p = v;
        for(int i =0; i<graph[v].size(); i++){
            int cur = graph[v][i].first;
            if(!used[cur]){
                S.push(cur);
                used[cur] = true;
            }else{
                p = cur;
            }
        }

        mind[v][0] = dist[p];
        for(int i = 1; i<=l; i++){
            mind[v][i] = mind[up[v][i-1]][i-1];
        }
    }

    return mind;
}

ll lcaMind(int v, int u, vector<vector<ll>>& mind){
    ll ans = mind[v][0];
    if(isAncestor(v, u)){
        return 0;
    }
    if(isAncestor(u,v)){
        return 0;
    }
    for(int i = l; i>=0; i--){
        if(!isAncestor(up[u][i], v)){
            u = up[u][i];
            ans = min(ans, mind[u][i]);
        }
    }
    return ans;
}

vector<ll> getDist(int c, vector<vector<pair<int,ll>>>& graph){
    queue<int> Q;
    vector<ll> ans(n+1, -1);
    for(int i = 1; i<=n; i++){
        if(t[i] == c){
            Q.push(i);
            ans[i] = 0;
        }
    }

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i<graph[v].size(); i++){
            pair<int,ll> cur = graph[v][i];
            if(ans[cur.first] == -1){
                ans[cur.first] = ans[v]+cur.second;
                Q.push(cur.first);
            }else if(ans[cur.first] > ans[v]+cur.second){
                ans[cur.first] = ans[v]+cur.second;
                Q.push(cur.first);
            }
        }
    }

    return ans;
}

void process(int ind, PII con, vector<ll>& ans, vector<int>& order, vector<ll>& lenD, vector<PII>& qS){
    //fill points of interest
    vector<bool> used(n+1, false);
    vector<int> poi; 
    for(int i = ind-con.second; i<ind; i++){
        int a = get<0>(query[qS[i].first]), b = get<1>(query[qS[i].first]), c = get<2>(query[qS[i].first]); 
        if(!used[a]){
            poi.PB(a);
            used[a] = true;
        }
        if(!used[b]){
            poi.PB(b);
            used[b] = true;
        }
    }
    for(int i = 0; i<colorSplit[con.first].size(); i++){
        int a = colorSplit[con.first][i];
        if(!used[a]){
            poi.PB(a);
            used[a] = true;
        }
    }   

    //get the compressed graph
    if(!used[1]) poi.PB(1);

    vector<PII> pointsOfIntrest;
    for(int i = 0; i<poi.size(); i++){
        pointsOfIntrest.PB(MP(poi[i], order[poi[i]]));
    }

    sort(pointsOfIntrest.begin(), pointsOfIntrest.end(), customPairComp);
    vector<int> next;
    for(int i =0; i<pointsOfIntrest.size()-1; i++){
        int l = lca(pointsOfIntrest[i].first, pointsOfIntrest[i+1].first);
        if(!used[l]){
            next.PB(l);
            used[l] = true;
        }
    }

    for(int i = 0; i<next.size(); i++){
        pointsOfIntrest.PB(MP(next[i], order[next[i]]));
    }
    sort(pointsOfIntrest.begin(), pointsOfIntrest.end(), customPairComp);

    vector<vector<pair<int,ll>>> compGraph(n+1, vector<pair<int,ll>>());

    for(int i =0; i<pointsOfIntrest.size()-1; i++){
        int a = pointsOfIntrest[i].first, b = pointsOfIntrest[i+1].first;
        int l = lca(a, b);
        compGraph[l].PB(MP(b, lenD[b]-lenD[l]));
        compGraph[b].PB(MP(l, lenD[b]-lenD[l]));
    }

    //get dp
    vector<ll> dist = getDist(con.first, compGraph);
    vector<vector<ll>> mind = getMind(compGraph, dist);
    preprocessLCA(compGraph);
    
    for(int i = ind-con.second; i<ind; i++){
        int a = get<0>(query[qS[i].first]), b = get<1>(query[qS[i].first]), c = get<2>(query[qS[i].first]); 
        ll len = lcaMind(a,b, mind);
        if(len == -1){
            ans[qS[i].first] = -1;
            continue;
        }
        int l = lca(a,b);
        ll temp = len + lenD[a] + lenD[b] - 2*lenD[l];
        ans[qS[i].first] = temp;
    }
}

vector<ll> solve(){
    //split by color
    colorSplit.assign(r+1, vector<int>());
    for(int i =1; i<=n; i++){
        colorSplit[t[i]].PB(i);
    }

    //create graph
    vector<vector<pair<int,ll>>> graph(n+1, vector<pair<int,ll>>());
    for(int i =0 ; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    //numerate
    vector<int> order = numerate(graph);
    vector<ll> lenD = getLenD(graph);

    vector<ll> ans(q, -1);

    vector<PII> qS;
    for(int i =0; i<query.size(); i++){
        int c = get<2>(query[i]);
        qS.PB(MP(i,c));
    }
    sort(qS.begin(), qS.end(), customPairComp);

    //process query
    preprocessLCA(graph);
    PII con = MP(qS.front().second, 1);
    for(int i = 1; i<qS.size(); i++){
        if(qS[i].second == con.first){
            con.second++;
        }else{
            process(i, con,ans, order, lenD, qS);
            con = MP(qS[i].second, 1);
        }
    }
    process(qS.size(), con,ans, order, lenD, qS);    

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test<=1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        // vector<ll> ansB = brute();
        vector<ll> ansS = solve();
        for(int i = 0; i<ansS.size(); i++){
            // if(ansB[i] != ansS[i]){
            //     cout<<"ERROR\n";
            //     cout<<"BRUTE: \n";
            //     for(int j = 0; j<ansB.size(); j++){
            //         cout<<ansB[j]<<" ";
            //     }
            //     cout<<"\n";
            //     cout<<"SOLVE: \n";
            //     for(int j = 0; j<ansS.size(); j++){
            //         cout<<ansS[j]<<" ";
            //     }
            //     cout<<"\n";
            //     printData();
            //     return 0;
            // }
        }
    }

    return 0;
}