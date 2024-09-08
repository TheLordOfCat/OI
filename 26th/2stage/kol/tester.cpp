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

void dfsLCA(int V, vector<vector<PII>>& graph){
    tin.clear();
    tout.clear();
    up.clear();
    tin.assign(n+1, 0);
    tout.assign(n+1, 0);

    int l = ceil(log2(n));
    int timer = 0;
    vector<bool> vis(n+1, false);
    up.assign(n, vector<int>(l + 1, 0));

    stack<pair<int,bool>> S;
    S.push(MP(V,false));
    vis[V] = true;

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();

        tin[v] = timer;
        timer++;

        if(b){
            tout[v] = timer;
            timer++;
            continue;
        }

        S.push(MP(v,true));

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
    int l = ceil(log2(n));
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

void preproces(vector<int> v, int c, vector<vector<PII>>& graph){
    //prepare LCA
    dfsLCA(v.front(), graph);

    //compress the tree
    vector<bool> pointIntrest(n+1, false);
    for(int i = 0; i<v.size(); i++){
        pointIntrest[v[i]] = true;
    }

    vector<int> order;
    vector<bool> vis(n+1, false);
    stack<int> S;
    S.push(v.front());
    vis[v.front()] = true;
    order.PB(v.front());

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

    for(int i = 0; i<order.size()-1; i++){
        
    }

    //create mind


}

ll process(int a, int b, int c){

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
    for(int i = 0; i<q; i++){
        int a = get<0>(querys[i]), b = get<1>(querys[i]), c = get<2>(querys[i]);
        
        if(i != q-1){
            if(c != get<2>(querys[last])){
                preproces(v, c, graph);
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
    preproces(v, get<2>(querys[last]), graph);
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