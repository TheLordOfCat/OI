#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <tuple>

#include <cstdlib>
#include <ctime>

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

using namespace std;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

int n, r;
vector<int> t;
vector<tuple<int,int,int>> edges;
int q;
vector<tuple<int,int,int>> querys;

void getData(){
    cin>>n>>r;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        t.PB(temp);
    }
    for(int i = 0; i<n-1; i++){
        int a, b, c;
        cin>>a>>b>>c;
        edges.PB(MT(a,b,c));
    }
    cin>>q;
    for(int i =0; i<q; i++){
        int a, b, c;
        cin>>a>>b>>c;
        querys.PB(MT(a,b,c));
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    r = rand()%10+2;
    for(int i = 0; i<n; i++){
        int temp = rand()%r+1;
        t.PB(temp);
    }
    int ind = 2;
    for(int i = 1; i<=n; i++){
        if(ind > n){
            break;
        }
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            if(ind > n){
                break;
            }
            int c = rand()%10+1;

            edges.PB(MT(i, ind, c));

            ind++;
        }
    }

    q = rand()%10+10;
    for(int i = 0; i<q; i++){
        int a = rand()%n+1, b = rand()%n+1, c = rand()%r+1;
        querys.PB(MT(a,b,c));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<r<<"\n";
    for(int i = 0; i<t.size(); i++){
        cout<<t[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    cout<<q<<"\n";
    for(int i = 0; i<querys.size(); i++){
        int a = get<0>(querys[i]), b = get<1>(querys[i]), c = get<2>(querys[i]);
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    cout<<"\n";

    return ;
}

void dfs(int v, vector<int>& mark, vector<vector<PII>>& graph){
    vector<int> dp(n+1, 0);
    vector<bool> vis(n+1, false);
    stack<int> S;
    S.push(v);

    while(!S.empty()){
        int v = S.top();
        S.pop();
        vis[v] = true;

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i].first;
            if(!vis[cur]){
                S.push(cur);
                vis[cur] = true;
                mark[cur] += graph[v][i].second + dp[v];
                dp[cur] = graph[v][i].second + dp[v];
            }
        }
    }
}

vector<int> brute(){
    vector<vector<PII>> graph(n+1, vector<PII>());

    for(int i = 0; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    vector<int> ans;

    for(int i = 0; i<querys.size(); i++){
        int p = get<0>(querys[i]), q = get<1>(querys[i]), s = get<2>(querys[i]);
        vector<int> dis(n+1, 0);

        dfs(p, dis, graph);
        dfs(q, dis, graph);

        PII best = MP(INF,INF);
        for(int j = 1; j<=n; j++){
            if(t[j-1] == s){
                if(best.second > dis[j]){
                    best = MP(j, dis[j]);
                }
            }
        }

        if(best.first == INF){
            ans.PB(-1);
        }else{
            ans.PB(best.second);
        }
    }

    return ans;
}

vector<int> solve(){

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansS.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: \n";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: \n";
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