#include <iostream>
#include <vector>
#include <stack>

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

    n = rand()%10+2;
    int ind = 2;
    for(int i = 0; i<n-1; i++){
        int con = rand()%3+1;
        for(int j =0 ; j<con;j ++){
            if(ind > n) break;
            edges.PB(MP(i+1, ind));
            ind++;
        }
        if(ind > n) break;
    }
    
    m = rand()%10+1;
    vector<bool> strike(n+1, false);
    for(int i = 0; i<m; i++){
        int s = rand()%n+1;
        if(strike[s]){
            query.PB((-1)*s);
        }else{
            query.PB(s);
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

vector<int> brute(){
    vector<int> ans;

    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    vector<bool> strike(n+1, false);
    for(int i = 0; i<query.size(); i++){
        //update strike
        int s = query[i];
        if(s < 0){
            strike[(-1)*s] = false;
        }else{
            strike[s] = true;
        }

        //get scc
        int scc = 0;
        vector<bool> vis(n+1, false);
        for(int j = 1; j<=n; j++){
            if(!vis[j] && !strike[j]){
                scc++;

                stack<int> S;
                S.push(j);
                vis[j] = true;

                while(!S.empty()){
                    int v = S.top();
                    S.pop();

                    for(int o = 0; o<graph[v].size(); o++){
                        int cur = graph[v][o];
                        if(!vis[cur] && !strike[cur]){
                            vis[cur] = true;
                            S.push(cur);
                        }
                    }
                }
            }
        }

        ans.PB(scc);
    }

    return ans;
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
            if(ans[cur] != v){
                ans[cur] = v;
                S.push(cur);
            }
        }
    }

    return ans;
}

vector<int> traverseGraph(vector<int>& parent, vector<vector<int>>& graph){
    vector<int> ans;

    stack<pair<int,bool>> S;
    S.push(MP(1, false));

    vector<bool> vis(n+1, false);
    vis[1] = true;

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;

        if(b){
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                if(cur != parent[v]){
                    ans.PB((-1)*cur);
                }
            }
        }
    
        ans.PB(v);
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

void buildTree(int s){
    tree.clear();

    int depth = 0;
    R = 0;
    while((1<<depth) < s){
        R += (1<<depth);
        depth++;
    }

    tree.assign(R + (1<<depth) + 1, 0);
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
            ans += right(parent(l));
        }
        if(right(parent(r)) == r){
            ans += left(parent(r));
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
    vector<int> trav = traverseGraph(parent, graph);

    //get ranges
    vector<PII> range(n+1, MP(0,0));
    for(int i = 0; i<trav.size(); i++){
        if(trav[i]>0){
            range[trav[i]].first = i;
        }else{
            range[trav[i]].second = i-1;
        }
    }

    //create seg tree 
    buildTree(trav.size());

    //process queries
    vector<int> ans;

    for(int i = 0; i<query.size(); i++){
        int temp = queryRange(range[query[i]].first, range[query[i]].second);
        ans.PB(temp);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j =0 ; j<ansB.size(); j++) cout<<ansB[j]<<" ";
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<" ";
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}