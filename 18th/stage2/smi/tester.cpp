#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <tuple>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n, m;
vector<tuple<int,int,int,int>> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b, s,t;
        cin>>a>>b>>s>>t;
        edges.PB(MT(a,b,s,t));
    }
}

void getRandom(){
    edges.clear();

    srand(time(0));

    n = rand()%2+3;
    m = 0;

    for(int i = 1; i<=n; i++){
        edges.PB(MT(i,(i+1)%n,1,0));
        m++;
    }

    for(int i = 1; i<=n; i++){
        int con = rand()%2+2;
        edges.PB(MT(i,n+1, 0, 1));
        for(int j = 0; j<con-1; j++){
            n++;
            edges.PB(MT(n,n+1, 0,1));
        }
        n++;
        edges.PB(MT(n,i,0,1));
        m += con+1;
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<get<0>(edges[i])<<" "<<get<1>(edges[i])<<" "<<get<2>(edges[i])<<" "<<get<3>(edges[i])<<"\n";
    }
}

bool verify(vector<vector<int>> cycles){
    //make graph
    vector<vector<pair<int,bool>>> graph(n+1, vector<pair<int,bool>>());
    for(int i = 0; i<m; i++){
        int a = get<0>(edges[i]), b = get<0>(edges[i]), s = get<0>(edges[i]), t = get<0>(edges[i]);  
        if(s != t){
            graph[a].PB(MP(b,false));
            graph[b].PB(MP(a,false));
        }
    }

    //traverse cycles
    for(int i = 0; i<cycles.size(); i++){
        cycles.PB(cycles.front());
        for(int j = 0; j<cycles[i].size()-1; j++){
            int a = cycles[i][j];
            int b = cycles[i][j+1];
            for(int o = 0; o<graph[a].size(); o++){
                int cur = graph[a][o].first;
                if(cur == b){
                    graph[a][o].second = true;
                    break;
                }
            }
            for(int o = 0; o<graph[b].size(); o++){
                int cur = graph[b][o].first;
                if(cur == a){
                    graph[b][o].second = true;
                    break;
                }
            }

        }
    }

    //verify
    for(int i = 1; i<=n; i++){
        for(int j = 0; j<graph[i].size(); j++){
            if(!graph[i][j].second){
                return false;
            }
        }
    }
    return true;
}

vector<vector<int>> solve(){
    vector<vector<pair<PII,bool>>> graph(n+1, vector<pair<PII,bool>>());
    for(int i = 0; i<m; i++){
        int a = get<0>(edges[i]), b = get<0>(edges[i]), s = get<0>(edges[i]), t = get<0>(edges[i]);  
        if(s != t){
            graph[a].PB(MP(MP(b, graph[b].size()),false));
            graph[b].PB(MP(MP(a, graph[a].size()-1),false));
        }
    }

    vector<int> degree(n+1, 0);
    for(int i = 1; i<=n; i++){
        degree[i] = graph[i].size(); 
    }

    vector<vector<int>> ans;

    stack<int> S;
    vector<bool> vis(n+1, false);
    
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            vector<int> cycle;
            S.push(i);
            while(!S.empty()){
                int v = S.top();
                if(degree[v] == 0){
                    cycle.PB(v);
                    vis[v] = true;
                    S.pop();
                }else{
                    for(int j = 0; j<graph[v].size(); j++){
                        if(!graph[v][j].second){
                            S.push(graph[v][j].first.first);
                            graph[v][j].second = true;
                            graph[graph[v][j].first.first][graph[v][j].first.second].second = true;
                            break;
                        }
                    }
                }
            }
            ans.PB(cycle);
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
        vector<vector<int>> ansS = solve();
        if(!verify(ansS)){
            cout<<"ERORR\n";
            cout<<"SOLVE: \n";
            cout<<ansS.size()<<"\n";
            for(int i = 0; i<ansS.size(); i++){
                for(int j = 0; j <ansS[i].size(); j++){
                    int cur = ansS[i][j];
                    cout<<cur<<" ";
                }
                cout<<"\n";
            }
            cout<<"\n";
        }
        cout<<"CORRECT\n";
    }

    return 0;
}