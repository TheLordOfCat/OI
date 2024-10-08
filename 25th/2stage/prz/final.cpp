//solution differs slightly from the one in tester.cpp

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back

const int INF = 1'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

int n;
vector<int> x;
vector<int> y;
vector<PII> edges;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        y.PB(temp);
    }
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

bool notEqual = false;

ull solve(){
    vector<ll> dif(n+1, 0);
    ll sum = 0;
    for(int i = 0; i<n; i++){
        sum += x[i]-y[i];
        dif[i+1] = x[i]-y[i];
    }
    if(sum != 0){
        notEqual = true;
        return 0;
    }

    //creating graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<n-1; i++){
        graph[edges[i].first].PB(edges[i].second);
        graph[edges[i].second].PB(edges[i].first);
    }

    //size of subTrees, root = 1
    vector<pair<ll,ll>> subTree(n+1, MP(0,0));
    stack<pair<ll, bool>> S;

    vector<bool> vis(n+1, false);
    vis[1] = true;

    S.push(MP(1,false));

    while(!S.empty()){
        ll v = S.top().first;
        bool b = S.top().second;
        S.pop();

        if(b){
            ll sumVer = 1;
            ll sumVal = dif[v];
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                sumVer += subTree[cur].first;
                sumVal += subTree[cur].second;
            }
            subTree[v] = MP(sumVer,sumVal);
            continue;
        }

        S.push(MP(v,true));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                vis[cur] = true;
                S.push(MP(cur,false));
            }
        }
    }

    //propagation
    vector<ll> prop(n+1, 0);

    for(int i = 1; i<=n; i++){
        if(subTree[i].second > 0){
            prop[i] += subTree[i].second;
        }else if(subTree[i].second < 0){
            prop[i] += subTree[i].second;
            prop[1] -= subTree[i].second;
        }
    }

    vector<ull> op(n+1, 0);

    stack<pair<ll,ull>> P;
    vis.clear();
    vis.assign(n+1, false);

    P.push(MP(1, prop[1]));
    vis[1] = true;

    while(!P.empty()){
        pair<ll,ull> v = P.top();
        P.pop();

        op[v.first] = v.second;
        for(int i = 0; i<graph[v.first].size(); i++){
            int cur = graph[v.first][i];
            if(!vis[cur]){
                vis[cur] = true;
                P.push(MP(cur,v.second + prop[cur]));
            }
        }
    } 

    //getting ans
    ull minOp = ullINF;
    for(int i = 1; i<=n; i++){
        minOp = min(minOp, op[i]);
    }

    ull ans = 0;
    for(int i = 1; i<=n; i++){
        ans += (op[i]-minOp);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    ull ansS = solve();
    if(notEqual){
        cout<<"NIE\n";
    }else{
        cout<<"TAK\n";
        cout<<ansS<<"\n";
    }

    return 0;
}