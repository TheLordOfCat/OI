#include<iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

const int MAXN = 500'000;
const int MAXM = 1'000'000;
const int INF = 2'000'000'000;

int n, m;
vector<vector<int>> graph;
vector<vector<int>> graphR;
vector<int> toOrder;


void getData(){
    cin>>n>>m;
    graph.assign(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        graph[a].PB(b);
    }
}

vector<int> topoSort(){
    toOrder.clear();

    vector<int> order;
    vector<bool> vis(n+1, false);

    for(int i = 1; i<=n ;i++){
        if(!vis[i]){
            stack<pair<int,bool>> S;
            S.push(MP(i,false));
            while(!S.empty()){
                int v = S.top().first;
                bool b = S.top().second;
                S.pop();
                if(b){
                    order.PB(v);
                    continue;
                }
                if(vis[v]){
                    continue;
                }
                vis[v] = true;
                S.push(MP(v, true));
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        S.push(MP(cur, false));
                    }   
                }
            }
        }
    }

    reverse(order.begin(), order.end());
    toOrder.clear();
    toOrder.assign(n+1, 0);

    for(int i = 0; i<n; i++){
        toOrder[order[i]] = i;
    }
    return order;
}

vector<int> tree;
int R;
int depth;

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

void addRange(int l, int r, int val){
    int vL = leaf(l);
    int vR = leaf(r);
    tree[vL] = max(tree[vL], val);
    if(vL != vR) max(tree[vR], val);
    while(parent(vL) != parent(vR)){
        if(vL = left(parent(vL))){
            tree[right(parent(vL))] = max(tree[right(parent(vL))] , val);
        }
        if(vR = right(parent(vR))){
            tree[left(parent(vL))] = max(tree[left(parent(vR))] , val);
        }
        vL = parent(vL);
        vR = parent(vR);
    }
}

int query(int v){
    int V = leaf(v);
    int ans = 0;
    while(V > 0){
        ans = max(tree[V], ans);
        V = parent(V);
    }    
    return ans;
}

PII solve(){
    graphR.assign(n+1, vector<int>());
    for(int i = 1; i<=n; i++){
        for(int j = 0; j<graph[i].size(); j++){
            graphR[graph[i][j]].PB(i);
        }
    }

    //topological sort
    vector<int> order = topoSort();

    //left best
    vector<int> leftPath(n+1, 0);
    for(int i = 0; i<n; i++){
        int cur = order[i];
        for(int j = 0; j<graphR[cur].size(); j++){
            leftPath[cur] = max(leftPath[graphR[cur][j]]+1, leftPath[cur]); 
        }
    }

    vector<int> longestLeft(n+1, 0);
    longestLeft[0] = leftPath[order[0]];
    for(int i = 1; i<n; i++){
        longestLeft[i] = max(longestLeft[i-1], leftPath[order[i]]);
    }


    //right best
    vector<int> rightPath(n+1, 0);
    for(int i = n-1; i>=0; i--){
        int cur = order[i];
        for(int j = 0; j<graph[cur].size(); j++){
            rightPath[cur] = max(rightPath[graph[cur][j]]+1, rightPath[cur]); 
        }
    }
    vector<int> longestRight(n+1, 0);
    longestRight[0] = rightPath[order[0]];
    for(int i = n-2; i>=0; i--){
        longestRight[i] = max(longestRight[i+1], rightPath[order[i]]);
    }

    //bypass best
    tree.assign(4*n+1, 0);
    while(1<<depth < n){
        R += 1<<depth;
        depth++;
    }

    for(int i = 0; i<n; i++){
        int v = order[i];
        for(int j =0; j<graph[v].size(); j++){
            int val =  leftPath[v] + rightPath[graph[v][j]] + 1;
            addRange(i+1, toOrder[graph[v][j]]-1, val);
        }
    }

    //ans
    int ansLen = INF;
    int ansVec = 11;
    for(int i = 0; i<n; i++){
        int temp = -1;
        if(i > 0) temp = max(temp, longestLeft[i-1]);
        if(i<n-1) temp = max(temp, longestRight[i+1]);
        temp = max(temp, query(i));
        if(temp < ansLen){
            ansLen = temp;
            ansVec = toOrder[i];
        }
    }
    return MP(ansVec, ansLen);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    PII ansS = solve();
    cout<<ansS.first<<" "<<ansS.second<<"\n";

    return 0;
}