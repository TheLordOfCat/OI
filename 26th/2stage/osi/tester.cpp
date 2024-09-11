#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define PIVC pair<int,vector<char>> 

int n, m;
vector<PII> edges;

void getData(){
    edges.clear();

    cin>>n>>m;
    for(int i =0 ; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    edges.clear();

    n = rand()%10+1;
    m = rand()%3+n;

    for(int i =0 ; i<m; i++){
        int a = -1, b = -1;
        while(a == b){
            a = rand()%n+1;
            b = rand()%n+1;
        }
        edges.PB(MP(a,b));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

void dfs(int v, vector<vector<PII>>& graph, vector<bool>& vis, vector<int>& ans){
    vis[v] = true;

    for(int i = 0; i<graph[v].size(); i++){
        int cur = graph[v][i].first;
        if(vis[cur]){
            dfs(cur,graph,vis,ans);
        }
    }

    ans.PB(v);
}

int getSCC(vector<vector<PII>>& graph){
    vector<vector<int>> SCC;

    vector<vector<PII>> graphRev(n+1, vector<PII>());
    for(int i = 1; i<graph.size(); i++){
        for(int j = 0; j<graph[i].size(); j++){
            PII cur = graph[i][j];
            graphRev[cur.first].PB(MP(i,cur.second));
        }
    }

    vector<bool> vis(n+1, false);
    vector<int> order;
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            dfs(i,graph,vis,order);
        }
    }

    vis.assign(n+1, false);
    reverse(order.begin(), order.end());
    for(int i = 0; i<order.size(); i++){
        int v = order[i];
        if(!vis[v]){
            vector<int> com;
            dfs(v,graphRev,vis,com);
            SCC.PB(com);
        }
    }

    return SCC.size();
}

PIVC brute(){
    PIVC ans = MP(INF,vector<char>());

    int totalCom = 1<<m;
    for(int i = 0; i<totalCom; i++){
        vector<vector<PII>> graph(n+1, vector<PII>());
        for(int j = 0; j<m; j++){
            int a = edges[j].first, b = edges[j].second;
            if(1<<j & i){
                graph[a].PB(MP(b,j));
            }else{
                graph[b].PB(MP(a,j));
            }
        }

        int temp = getSCC(graph);
        if(ans.first > temp){
            ans.first = temp;
            vector<char> c;
            for(int j = 0; j<m; j++){
                if(1<<j & i){
                    c.PB('>');
                }else{
                    c.PB('<');
                }
            }
            ans.second = c;
        }

    }

    return ans;
}

PIVC solve(){
    vector<vector<PII>> graph(n+1, vector<PII>());
    vector<vector<PII>> graphDir(n+1, vector<PII>());

    //create base graph
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(MP(b,i));
        graph[b].PB(MP(a,i));
    }

    vector<bool> vis(n+1, false);
    stack<PII> S;
    S.push(MP(1,-1));

    //create directed graph
    while(!S.empty()){
        int v = S.top().first;
        int ind = S.top().second;
        S.pop();

        for(int j = 0; j<graph[v].size(); j++){
            PII cur = graph[v][j];
            if(cur.second != ind){
                if(!vis[cur.first]){
                    vis[cur.first] = true;
                    S.push(cur);
                    graphDir[v].PB(cur);
                }else{
                    graphDir[cur.first].PB(MP(v,cur.second));
                }
            }
        }
    }

    //get SCC
    int temp = getSCC(graphDir);
    vector<char> c(m, '-');
    for(int i = 1; i<graphDir.size(); i++){
        for(int j = 0; j<graphDir[i].size(); j++){
            PII cur = graphDir[i][j];
            int a = edges[cur.second].first, b = edges[cur.second].second;
            if(a == i && cur.first == b){
                c.PB('>');
            }else{
                c.PB('<');
            }
        }
    }

    PIVC ans = MP(INF, vector<char>());

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
        PIVC ansB = brute();
        PIVC ansS = solve();
        if(ansB.first != ansS.first){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<ansB.first<<"\n";
            for(int j = 0; j<ansB.second.size(); j++){
                cout<<ansB.second[j];
            }
            cout<<"\n";
            cout<<"SOLVE: \n";
            cout<<ansS.first<<"\n";
            for(int j = 0; j<ansS.second.size(); j++){
                cout<<ansS.second[j];
            }
            cout<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}