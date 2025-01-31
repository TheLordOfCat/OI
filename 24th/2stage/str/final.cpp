#include <iostream>
#include <vector>
#include <stack>
#include <chrono>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back
#define PLL pair<ll,ll>

int n;
vector<PII> edges;
int m;
vector<int> query;

void getData(){
    edges.clear();
    query.clear();

    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
    
    cin>>m;
    for(int i = 0; i<m; i++){
        int a;
        cin>>a;
        query.PB(a);
    }
}

void getRandom(){
    edges.clear();
    query.clear();

    srand(time(0));

    // n = rand()%1000+2000;
    n = 500'000;
    int ind = 2;
    for(int i = 0; i<n-1; i++){
        int con = rand()%n+1;
        for(int j =0 ; j<con;j ++){
            if(ind > n) break;
            edges.PB(MP(i+1, ind));
            ind++;
        }
        if(ind > n) break;
    }
    
    // m = rand()%10+1000;
    m = n/2;
    vector<bool> strike(n+1, false);
    for(int i = 0; i<m; i++){
        int s = rand()%n+1;
        if(strike[s]){
            query.PB((-1)*s);
            strike[s] = false;
        }else{
            query.PB(s);
            strike[s] = true;
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i =0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
    cout<<m<<"\n";
    for(int i = 0; i<query.size(); i++){
        cout<<query[i]<<"\n";
    }
}

vector<int> getParent(vector<vector<int>> graph){
    vector<int> ans(n+1, -1);
    
    stack<int> S;
    S.push(1);

    while(!S.empty()){
        int v = S.top();
        S.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(ans[v] != cur){
                ans[cur] = v;
                S.push(cur);
            }
        }
    }

    return ans;
}

vector<int> traverseGraph(vector<int>& parent, vector<vector<int>>& graph, vector<PII>& range){
    vector<int> ans;

    stack<pair<int,bool>> S;
    S.push(MP(1, false));

    vector<bool> vis(n+1, false);
    vis[1] = true;

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();

        if(b){
            range[v].second = ans.size()-1;
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                if(cur != parent[v]){
                    ans.PB((-1)*cur);
                }
            }
            continue;
        }
    
        ans.PB(v);
        range[v].first = ans.size();
        S.push(MP(v, true));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                vis[cur] = true;
                S.push(MP(cur, false));
            }
        }
    }

    ans.PB(-1);

    return ans;
}

vector<int> tree;
int R;

int left(int v){
    return v*2;
}

int right(int v){
    return v*2+1;
}

int parent(int v){
    return v/2;
}

int leaf(int v){
    return v+R+1;
}

void buildTree(vector<int>& trav){
    tree.clear();

    int depth = 0;
    R = 0;
    while((1<<depth) < trav.size()){
        R += (1<<depth);
        depth++;
    }

    tree.assign(R + (1<<depth) + 1, 0);
    for(int i = 0; i<trav.size(); i++){
        if(trav[i] > 0){
            tree[leaf(i)] += 1;
        }else{
            tree[leaf(i)] -= 1;
        }
    }
    for(int i = R; i>=1; i--){
        tree[i] = tree[left(i)] + tree[right(i)];
    }
}

int updateSingle(int v, int val){
    int V = leaf(v);

    while(V >= 1){
        tree[V] += val;
        V = parent(V);
    }
}

int queryRange(int a, int b){
    int l = leaf(a), r = leaf(b);
    int ans = 0;

    ans += tree[l];
    if(l != r){
        ans += tree[r];
    }

    while(parent(l) != parent(r)){
        if(left(parent(l)) == l){
            ans += tree[right(parent(l))];
        }
        if(right(parent(r)) == r){
            ans += tree[left(parent(r))];
        }
        l = parent(l);
        r = parent(r);
    }
    return ans;
}

vector<int> solve(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    //get parents
    vector<int> parent = getParent(graph);

    //traverse graph
    vector<PII> range(n+1, MP(0,0));
    vector<int> trav = traverseGraph(parent, graph, range);

    //index
    vector<PII> index(n+1, MP(0,0));
    for(int i =0; i<trav.size(); i++){
        int val = trav[i];
        if(val > 0){
            index[val].first = i;
        }else{
            index[val*(-1)].second = i;
        }
    }

    //create seg tree 
    buildTree(trav);

    //process queries
    vector<int> ans;

    int curSplit = 1;

    for(int i = 0; i<query.size(); i++){
        int val = query[i];
        if(val < 0) val *= -1;
        int temp = 0;

        if(query[i] > 0){
            updateSingle(index[val].first, -1);
            updateSingle(index[val].second, 1);
        }else{
            updateSingle(index[val].first, 1);
            updateSingle(index[val].second, -1);
        }
        if(range[val].first <= range[val].second){
            temp = queryRange(range[val].first, range[val].second);
        }
        if(parent[val] != -1){
            if(tree[leaf(index[parent[val]].first)] == 1){
                temp++;
            }
        }

        if(query[i] > 0){
            curSplit += temp-1;
        }else{
            curSplit -= temp-1;
        }
        ans.PB(curSplit);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test<=1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        // auto start = std::chrono::high_resolution_clock::now();
        vector<int> ansS = solve();
        for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<"\n";
        // auto stop = std::chrono::high_resolution_clock::now();
        // auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        // cout << "Time taken: " << duration.count() << " microseconds\n";
    }

    return 0;
}