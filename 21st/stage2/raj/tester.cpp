#include<iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;

int n, m;
vector<PII> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a,b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    edges.clear();

    srand(time(0));
    n = rand()%20+2;
    m = 0;
    for(int i = 1; i<n; i++){
        // int con = rand()%(n-i);
        int con = rand()%2+1;
        if(con > n-i) continue;
        vector<bool> vis(n+1, false);
        for(int j = 0; j<con; j++){
            int temp = rand()%n+1;
            while(vis[temp] || temp <= i){
                temp = rand()%n+1;
            }
            vis[temp] = true;
            edges.PB(MP(i, temp));
            m++;
        }
    }    
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<m; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

PII brute(){
    PII ans = MP(-1,INF);

    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        graph[edges[i].first].PB(edges[i].second);
    }

    for(int i = 1; i<=n; i++){
        int bestLen = -1;
        for(int j = 1; j<=n; j++){
            if(j != i){
                stack<PII> S;
                S.push(MP(j, 0));

                while(!S.empty()){
                    int v = S.top().first;
                    int l = S.top().second;
                    S.pop();

                    if(l > bestLen){
                        bestLen = l;
                    }

                    for(int o = 0; o<graph[v].size(); o++){
                        int cur = graph[v][o];
                        if(cur != i){
                            S.push(MP(cur, l+1));
                        }
                    }
                }
            }
        }

        if(ans.second > bestLen){
            ans = MP(i,bestLen);
        }
    }

    return ans;
}

vector<int> order;
vector<int> toOrder;

void topoSort(vector<vector<int>>& graph){
    order.clear();
    toOrder.clear();

    toOrder.assign(n+1, -1);

    stack<pair<int,bool>> S;
    vector<bool> vis(n+1, false);

    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            S.push(MP(i,false));

            while(!S.empty()){
                int v= S.top().first;
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
                S.push(MP(v,true));
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

    for(int i = 0; i<order.size(); i++){
        toOrder[order[i]] = i;
    }
}

int R;
int depth;
int totalSize;
vector<int> tree;

inline int parent(int v){
    return v/2;
}

inline int left(int v){
    return 2*v;
}

inline int right(int v){
    return 2*v +1;
}

inline int leaf(int v){
    return R + v;
}

void updateRange(int a, int b, int val){
    int l = leaf(a);
    int r = leaf(b);
    if(l > r) return;

    tree[l] = max(tree[l], val);
    if(l != r){
        tree[r] = max(tree[r],val);
    }

    while(parent(l) != parent(r)){
        if(l == left(parent(l))){
            tree[right(parent(l))] = max(tree[right(parent(l))], val);
        }
        if(r == right(parent(r))){
            tree[left(parent(r))] = max(tree[left(parent(r))], val);
        }
        l = parent(l);
        r = parent(r);
    }
}

int query(int v){
    int ans = -1;
    int V = leaf(v);
    while(V >= 1){
        ans = max(ans, tree[V]);
        V = parent(V);
    }
    return ans;
}

vector<int> longestLeft;
vector<int> maxLongestLeft;

void travLeft(vector<vector<int>>& graph){
    longestLeft.clear();
    maxLongestLeft.clear();

    longestLeft.assign(n, 0);
    for(int i = 0; i<order.size(); i++){
        for(int j = 0; j<graph[order[i]].size(); j++){
            int cur = graph[order[i]][j];
            longestLeft[toOrder[cur]] = max(longestLeft[toOrder[cur]], longestLeft[i]+1);
        }
    }

    maxLongestLeft.assign(n, 0);
    int best = longestLeft[0];
    for(int i = 0; i<order.size(); i++){
        best = max(best, longestLeft[i]);
        maxLongestLeft[i] = best;
    }
}

vector<int> longestRight;
vector<int> maxLongestRight;

void travRight(vector<vector<int>>& graph){
    vector<vector<int>> graphRev(n+1, vector<int>());
    for(int i =1; i<=n; i++){
        for(int j =0; j<graph[i].size(); j++){
            int cur = graph[i][j];
            graphRev[cur].PB(i);
        }
    }

    longestRight.clear();
    maxLongestRight.clear();

    longestRight.assign(n, 0);
    for(int i = n-1; i>=0; i--){
        for(int j = 0; j<graphRev[order[i]].size(); j++){
            int cur = graphRev[order[i]][j];
            longestRight[toOrder[cur]] = max(longestRight[toOrder[cur]], longestRight[i]+1);
        }
    }

    maxLongestRight.assign(n, 0);
    int best = longestRight[n-1];
    for(int i = n-1; i >= 0; i--){
        best = max(best, longestRight[i]);
        maxLongestRight[i] = best;
    }
}

PII solve(){
    tree.clear();

    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        graph[edges[i].first].PB(edges[i].second);
    }

    //getting the order
    topoSort(graph);

    //getting the pre-post len
    travLeft(graph);
    travRight(graph);

    //initializing
    while(1<<depth < n){
        R += 1<<depth;
        depth++;
    }
    totalSize = R+ (1<<depth);
    tree.assign(totalSize+1, -1);
    
    //updating the tree
    for(int i =0; i<m; i++){
        int a = edges[i].first;
        int b = edges[i].second;
        updateRange(toOrder[a]+1, toOrder[b]-1, longestLeft[toOrder[a]] + longestRight[toOrder[b]] + 1);
    }

    //getting the answer
    PII ans = MP(-1,INF);

    for(int i = 1; i<=n; i++){
        int len = query(toOrder[i]);
        if(toOrder[i] > 0) len = max(len, maxLongestLeft[toOrder[i]-1]);
        if(toOrder[i] <n-1) len = max(len, maxLongestRight[toOrder[i]+1]);

        if(len < ans.second){
            ans = MP(i, len);
        }
    }

    return ans; 
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test<=10'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        PII ansB = brute();
        PII ansS = solve();
        if(ansB.second != ansS.second){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB.first<<" "<<ansB.second<<"\n";
            cout<<"SOLVE: "<<ansS.first<<" "<<ansS.second<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}