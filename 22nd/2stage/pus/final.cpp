#include<iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int MAXN = 100'000;
const int MAXS = 100'000;
const int MAXM = 200'000;
const int INF = 1'000'000'000;

int n, m, s;
vector<PII> stable;
vector<pair<PII,vector<int>>> depend;

void getData(){
    cin>>n>>s>>m;
    for(int i = 0; i<s; i++){
        int a, b;
        cin>>a>>b;
        stable.PB(MP(a,b));
    }
    for(int i =0; i<m; i++){
        int l,r,k;
        cin>>l>>r>>k;
        vector<int> deeper;
        for(int j = 0; j<k; j++){
            int x;
            cin>>x;
            deeper.PB(x);
        }
        depend.PB(MP(MP(l,r),deeper));
    }
}

int R = 1;
int depth = 1;

int parent(int v){
    return v/2;
}

int left(int v){
    return 2*v;
}

int right(int v){
    return 2*v+1;
}

int leaf(int v){
    return R+v;
}

vector<int> cover(int l, int r){
    vector<int> ans;
    int vL = leaf(l);
    int vR = leaf(r);
    ans.PB(vL);
    if(vL != vR) ans.PB(vR);
    
    while(parent(vL) != parent(vR)){
        if(vL == left(parent(vL))){
            ans.PB(right(parent(vL)));
        }
        if(vR == right(parent(vR))){
            ans.PB(left(parent(vR)));
        }
        vL = parent(vL);
        vR = parent(vR);
    }
    return ans;
}

pair<bool, vector<int>> solve(){
    R = 1;
    depth = 1;
    vector<int> tree(4*n+1, INF);
    while(1<<depth < n){
        R += 1<<depth;
        depth++;
    }

    vector<bool> stab(n+1, false);
    for(int i = 0; i<s; i++){
        tree[leaf(stable[i].first)] = stable[i].second;
        stab[stable[i].first] = true;
    }

    vector<int> inEdge(4*n+1, 0);
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int l = depend[i].first.first;
        int r = depend[i].first.second;
        vector<int> x = depend[i].second;
        vector<int> vec;

        graph.PB(vector<int>());
        for(auto t: x){
            graph[t].PB(graph.size()-1);
        }
        
        //left to first of x
        if(l != x.front()){
            vector<int> temp = cover(l, x.front()-1);
            for(auto t: temp) vec.PB(t);
        }
        //last of x to right
        if(r != x.back()){
            vector<int> temp = cover(x.back()+1, r);
            for(auto t: temp) vec.PB(t);
        }

        //between x
        vector<int> temp;
        if(x.size() > 1){
            for(int i = 0; i<x.size()-1; i++){
                if(x[i] != x[i+1]-1)
                temp = cover(x[i] +1, x[i+1]-1);
                for(auto t: temp) vec.PB(t);
            }
        }

        for(auto v:vec){
            graph.back().PB(v);
            inEdge[v]++;
        }
    }

    vector<bool> vis(n+1, false);
    queue<int> S;
    S.push(1);
    bool ok = true;
    while(!S.empty()){
        int v = S.front();
        S.pop();
        if(v <= R){
            if(inEdge[left(v)] == 0){
                if(left(v) > R){
                    if(stab[left(v)-R]){
                        if(tree[v] < tree[left(v)]){
                            ok = false;
                            break;
                        }else{
                           tree[left(v)] = min(tree[v],tree[left(v)]); 
                        }
                    }
                }else{
                    tree[left(v)] = min(tree[v],tree[left(v)]);
                }
                S.push(left(v));
            }
            if(inEdge[right(v)] == 0){
                if(right(v) > R){
                    if(stab[right(v)-R]){
                        if(tree[v] < tree[right(v)]){
                            ok = false;
                            break;
                        }else{
                           tree[right(v)] = min(tree[v],tree[right(v)]); 
                        }
                    }
                }else{
                    tree[right(v)] = min(tree[v],tree[right(v)]);
                }
                S.push(right(v));
            }
        }else{
            v -= R;
            vis[v] = true;
            if(graph[v].size() > 0){
                for(int i = 0; i<graph[v].size(); i++){
                    int cur = graph[v][i];
                    for(int j = 0; j<graph[cur].size(); j++){
                        if(graph[cur][j] > R){
                            if(stab[graph[cur][j] - R]){
                                if(tree[graph[cur][j]] > tree[leaf(v)]-1){
                                    ok = false;
                                    break;
                                }
                            }
                        }
                        tree[graph[cur][j]] = min(tree[graph[cur][j]], tree[leaf(v)]-1);
                        inEdge[graph[cur][j]]--;
                        if(inEdge[graph[cur][j]] == 0){
                            S.push(graph[cur][j]);
                        }
                    }
                    if(!ok){
                        break;
                    }
                }
            }
        }
        if(!ok){
            break;
        }
    }
    
    for(int i = 1; i<=n; i++){
        if(!vis[i] || tree[leaf(i)] <= 0){
            ok = false;
            break;
        }
    }

    if(ok){
        vector<int> ans = {INF};
        for(int i = leaf(1); i<= leaf(n); i++){
            ans.PB(tree[i]);
        }
        return MP(true, ans);
    }else{
        return MP(false, vector<int>());
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    pair<bool, vector<int>> ansS = solve();

    if(ansS.first){
        cout<<"TAK\n";
        for(int i = 1; i<ansS.second.size(); i++){
            cout<<ansS.second[i]<<" ";
        }
        cout<<"\n";
    }else{
        cout<<"NIE\n";
    }


    return 0;
}