#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;
using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

int n, m;
vector<PII> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    edges.clear();
    
    srand(time(0));

    n = rand()%10+1;
    m = 0;

    int ind = 2;
    for(int i = 1; i<=n; i++){
        int con = rand()%3;
        for(int j = 0; j<con; j++){
            if(ind > n){
                break;
            }
            edges.PB(MP(i,ind));
            m++;
            ind++;
        }
        if(ind > n){
            break;
        }
    }

    int com = rand()%2+1;
    for(int  i =0 ; i<com; i++){
        int v = rand()%n+1;
        int con = rand()%2+1;
        edges.PB(MP(v,n+1));
        m++;
        n++;
        for(int j = 0; j<con; j++){
            edges.PB(MP(n,n+1));
            m++;
            n++;
        }
        edges.PB(MP(n,v));
        m++;
    } 
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<m; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

vector<int> brute(){
    //creating graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int  i =0; i<m; i++){
        graph[edges[i].first].PB(edges[i].second);
    }

    vector<int> ans;

    //iterating throught each vertex
    for(int i = 1; i <= n; i++){
        int con = 0;

        vector<bool> vis(n+1, false);
        queue<int> Q;
        Q.push(i);
        vis[i] = true;

        while(!Q.empty()){
            int v = Q.front();
            Q.pop();

            for(int j = 0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if(!vis[cur]){
                    vis[cur] = true;
                    Q.push(cur);
                    con++;
                }
            }
        }

        ans.PB(con);
    }

    return ans;
}

vector<bool> visSCC;

void dfs(int v, vector<vector<int>>& graph, vector<int>& vec){
    visSCC[v] = true;
    for(int j = 0; j <= graph[v].size(); j++){
        int cur = graph[v][j];
        if(!visSCC[cur]){
            dfs(cur, graph, vec);
        }
    }
    vec.PB(v);
}

void createSCC(vector<vector<int>>& graphSCC, vector<vector<int>>& components, vector<vector<int>>& graph, vector<vector<int>>& graphRev){
    //getting order
    visSCC.assign(n+1, false);
    vector<int> order;

    for(int i = 1; i<=n; i++){
        if(!visSCC[i]){
            dfs(i,graph,order);
        }   
    }

    reverse(order.begin(),order.end());

    visSCC.assign(n+1, false);
    vector<int> root(n+1, -1);
    for(int i = 0; i < order.size(); i++){
        if(!visSCC[i]){
            vector<int> comp;
            dfs(i,graphRev,comp);
            components.PB(comp);
            int r = comp.back();
            for(int j = 0; j<comp.size()-1; j++){
                root[comp[j]] = r;
            }
        }
    }

    for(int i = 1; i<=n; i++){
        for(int j = 0; j < graph[i].size(); j++){
            int cur = graph[i][j];
            if(root[i] != root[cur]){
                graphSCC[root[i]].PB(root[cur]);
            }
        }
    }
}

vector<int> solve(){
    //creating graph 
    vector<vector<int>> graph(n+1, vector<int>());    
    vector<vector<int>> graphR(n+1, vector<int>());    
    for(int i = 0; i<m; i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graphR[b].PB(a);
    }

    //creating SCC
    vector<vector<int>> graphSCC;
    vector<vector<int>> components;
    createSCC(graphSCC, components, graph, graphR);

    //dp on SCC
    vector<int> dp(components.size(), 0);
    vector<bool> vis(components.size(), false);
    vector<int> parent(components.size(), -1);

    for(int i = 0; i<components.size(); i++){
        if(!vis[i]){
            stack<pair<int,bool>> S;
            S.push(MP(i,false));
            vis[i] = true;

            while(!S.empty()){
                int v = S.top().first;
                bool b = S.top().second;
                S.pop();

                if(b){
                    int sum = 0;
                    for(int j = 0; j<graphSCC[v].size(); j++){
                        int cur = graphSCC[v][j];
                        if(cur != parent[v]){
                            sum += dp[cur] + 1;
                        }
                    }
                    dp[v] = sum;
                    continue;
                }

                S.push(MP(v,true));
                for(int j = 0; j<graphSCC[v].size(); j++){
                    int cur = graphSCC[v][j];
                    if(!vis[cur]){
                        vis[cur] = true;
                        S.push(MP(v,false));
                    }
                }
            }
        }
    }

    //geting the ans
    vector<int> ans(n, 0);

    for(int i = 0; i<components.size(); i++){
        for(int j = 0; j<components[i].size(); j++){
            dp[components[i][j]] = dp[i];
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<= 1; test++){
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
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }    
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }    
                cout<<"\n";
                printData();
                return 0;
            }
        }
    }

    return 0;
}