#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

using ll = long long int;
using ull = unsigned long long int;

const int INF = 1'000'000'000;

int n, s, m;
vector<PII> well;
vector<tuple<PII,int,vector<int>>> dep;

void getData(){
    cin>>n>>s>>m;
    for(int i = 0; i<s; i++){
        int p, d;
        cin>>p>>d;
        well.PB(MP(p,d));
    }
    for(int i = 0; i<m;  i++){
        PII ran;
        int len;
        vector<int> vec;
        cin>>ran.first>>ran.second>>len;
        for(int j = 0; j<len; j++){
            int temp;
            cin>>temp;
            vec.PB(temp);
        } 
        dep.PB(MT(ran,len,vec));
    }
}

vector<int> tree;
vector<int> input;
int R = 1;
int depth = 1;
int specVec = 2;

vector<vector<PII>> graph;

inline int left(int v){
    return v*2;
}

inline int right(int v){
    return v*2+1;
}

inline int leaf(int v){
    return R+v;
} 

inline int parent(int v){
    return v/2;
}

void connect(int l, int r, int ind){
    if(r < l) return;
    int L = leaf(l);
    int R = leaf(r);

    graph[ind].PB(MP(L,0));
    input[L]++;
    if(L != R){
        graph[ind].PB(MP(R,0));
        input[R]++;
    } 

    while(parent(L) != parent(R)){
        if(L == left(parent(L))){
            graph[ind].PB(MP(right(parent(L)),0));
            input[right(parent(L))]++;
        }
        if(R == right(parent(R))){
            graph[ind].PB(MP(left(parent(R)),0));
            input[left(parent(R))]++;
        }
        L = parent(L);
        R = parent(R);
    }
}

vector<int> solve(){
    tree.clear();
    graph.clear();
    input.clear();

    //build tree
    while(1<<depth < n){
        R += 1<<depth;
        depth++;
    }

    tree.assign(R + 1 + (1<<depth), INF);
    graph.assign(R + 1 + (1<<depth), vector<PII>());
    input.assign(R + 1 + (1<<depth), 0);
    for(int i = 1; i<=R; i++){
        graph[i].PB(MP(left(i),0));
        input[left(i)]++;
        graph[i].PB(MP(right(i),0));
        input[right(i)]++;
    }

    for(int i = 0; i<m; i++){
        PII ran = get<0>(dep[i]);
        int len = get<1>(dep[i]);
        vector<int> vec = get<2>(dep[i]);
        int ind = 0;
        tree.PB(INF);
        graph.PB(vector<PII>());
        input.PB(0);

        connect(ran.first, vec[0]-1, tree.size()-1);
        for(int i = 0; i< len-1; i++){
            graph[leaf(vec[i])].PB(MP(tree.size()-1, 1));
            input[tree.size()-1]++;
            connect(vec[i]+1, vec[i+1]-1, tree.size()-1);
        }
        graph[leaf(vec.back())].PB(MP(tree.size()-1, 1));
        input[tree.size()-1]++;
        connect(vec.back()+1, ran.second, tree.size()-1);
    }

    vector<bool> isWell(n+1, false);
    for(int i = 0; i<s; i++){
        tree[leaf(well[i].first)] = well[i].second;
        isWell[well[i].first] = true;
    }

    vector<bool> vis(tree.size(), false);
    queue<int> Q;
    if(input[1] == 0)Q.push(1);
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            input[cur.first]--;
            if(input[cur.first] == 0){
                Q.push(cur.first);
                vis[cur.first] = true;
            }
            if(cur.second == 1){
                if(cur.first > R && cur.first <= leaf(n)){
                    if(isWell[cur.first-R]){
                        if(tree[v]-1 < tree[cur.first]){
                            return vector<int>();
                        }
                    }else{
                        tree[cur.first] = min(tree[cur.first], tree[v]-1);
                    }
                }else{
                    tree[cur.first] = min(tree[cur.first], tree[v]-1);
                }
            }else{
                if(cur.first > R && cur.first <= leaf(n)){
                    if(isWell[cur.first-R]){
                        if(tree[v] < tree[cur.first]){
                            return vector<int>();
                        }
                    }else{
                        tree[cur.first] = min(tree[cur.first], tree[v]);
                    }
                }else{
                    tree[cur.first] = min(tree[cur.first], tree[v]);
                }
            }
        }
    }
    for(int i = 1; i<=n; i++){
        if(!vis[leaf(i)]){
            return vector<int>();
        }
    }

    vector<int> ans;
    for(int i = 0; i<=n; i++){
        ans.PB(tree[leaf(i)]);
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<int> ansS = solve();
    if(ansS.size() == 0){
        cout<<"NIE\n";
    }else{
        cout<<"TAK\n";
        for(int i = 1; i<ansS.size(); i++){
            cout<<ansS[i]<<" ";
        }
    }

    return 0;
}