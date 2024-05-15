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

void getRandom(){
    srand(time(0));
    graph.clear();
    graph.assign(n+1, vector<int>());

    n = rand()%10+1;
    m = 0;
    for(int i  = 1; i<=n; i++){
        int con = rand()%(n-i);
        vector<bool> vis(n+1, false);
        vis[0] = true;
        for(int j =0 ; j<con; j++){
            int a = 0;
            while(vis[a] && a<=i){
                a = rand()%n+1;
            }
            vis[a] = true;
            graph[i].PB(a);
            m++;
        }
    }
} 

void printData(){
    cout<<n<<" "<<m<<"\n";
    for(int i = 1; i<=n; i++){
        for(int j = 0; j<graph[i].size(); j++){
            cout<<i<<" "<<graph[i][j]<<"\n";
        }
    }
}

PII brute(){
    //making reverse graph
    vector<vector<int>> graphR(n+1, vector<int>());
    for(int i = 1; i<=n; i++){
        for(int j = 0; j<graph[i].size(); j++){
            graphR[graph[i][j]].PB(i);
        }
    }

    //iterating through each edge
    int ansLen = INF;
    int ansVec = -1;
    for(int i = 1; i<=n; i++){
        queue<int> Q;
        vector<int> dp(n+1, 0);
        for(int o = 1; o<=n;o++){
            if(graph[o].size() == 0){
                Q.push(o);
            }
        }

        while(!Q.empty()){
            int v = Q.front();
            if(dp[v] > ansLen){
                ansLen = dp[v];
                ansVec = i;
            }
            Q.pop();

            for(int o = 0; o<graphR[v].size(); o++){
                if(!(graphR[v][o] != i)){
                    Q.push(graphR[v][o]);
                    dp[graph[v][o]] = max(dp[graph[v][o]], dp[v]+1);
                }
            }
        }
    }

    return MP(ansVec, ansLen);    
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
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(vis[cur]){
                        S.push(MP(cur, false));
                    }   
                }
                S.push(MP(v, true));
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

}

int query(int v){
    
}

PII solve(){
    int ansLen = 0;
    int ansVec = 0;
    graph.clear();

    graphR.assign(n+1, vector<int>());
    for(int i = 1; i<=n; i++){
        for(int j = 0; j<graph[i].size(); j++){
            graphR[graph[i][j]].PB(i);
        }
    }

    //topological sort
    vector<int> order = topoSort();

    //left best
    // standard indexes
    vector<int> leftPath(n+1, 0);
    for(int i = 0; i<n; i++){
        int cur = order[i];
        if(ansLen < leftPath[cur]-1){
            ansLen = leftPath[cur]-1;
            ansVec = i;
        }
        for(int j = 0; j<graph[cur].size(); j++){
            leftPath[graph[cur][j]] = max(leftPath[graph[cur][j]], leftPath[cur]+1); 
        }
    }

    //right best
    // standard indexes
    vector<int> rightPath(n+1, 0);
    for(int i = n-1; i>=0; i--){
        int cur = order[i];
        if(ansLen < rightPath[cur]-1){
            ansLen = rightPath[cur]-1;
            ansVec = i;
        }
        for(int j = 0; j<graph[cur].size(); j++){
            rightPath[graph[cur][j]] = max(rightPath[graph[cur][j]], rightPath[cur]+1); 
        }
    }

    //bypass best
    while(1<<depth < n){
        R += 1<<depth;
        depth++;
    }

    for(int i = 0; i<n; i++){
        int v = order[i];
        for(int j =0; j<graph[v].size(); j++){
            addRange(i+1, toOrder[graph[v][j]]-1, leftPath[v] + rightPath[graph[v][j]] + 1);
        }
    }

    //ans
    for(int i = 0; i<n; i++){
        int temp = query(i);
        if(ansLen < temp){
            ansLen = temp;
            ansVec = toOrder[i];
        }
    }
    return MP(ansLen, ansVec);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1 ;test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        PII ansB = brute();
        PII ansS = solve();
        if(ansB.first != ansS.first && ansB.second != ansS.second){
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