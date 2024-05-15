#include<iostream>
#include <vector>
#include <queue>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

const int MAXN = 500'000;
const int MAXM = 1'000'000;
const int INF = 2'000'000'000;

int n, m;
vector<vector<int>> graph;

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

PII solve(){
    
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