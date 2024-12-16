#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <tuple>
#include <cmath>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n, r;
vector<int> t;
vector<tuple<int,int,int>> edges;
int q;
vector<tuple<int,int,int>> query;

void getData(){
    t.clear(); edges.clear(); query.clear();

    cin>>n>>r;
    t.PB(-1);
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
        query.PB(MT(a,b,c));
    }
}

void getRandom(){
    t.clear(); edges.clear(); query.clear();
    srand(time(0));

    n = rand()%5+2;
    r = rand()%10+1;
    t.PB(-1);
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

    q = rand()%5+2;
    for(int i = 0; i<q; i++){
        int a = rand()%n+1, b = rand()%n+1, c = rand()%r+1;
        query.PB(MT(a,b,c));
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
    for(int i = 0; i<query.size(); i++){
        int a = get<0>(query[i]), b = get<1>(query[i]), c = get<2>(query[i]);
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    cout<<"\n";

    return ;
}

vector<ll> bruteDfs(int vS, vector<vector<PII>>& graph){
    queue<int> Q;
    Q.push(vS);
    vector<ll> ans(n+1, -1);
    ans[vS] = 0;

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i< graph[v].size(); i++){
            PII cur = graph[v][i];
            if(ans[cur.first] == -1){
                ans[cur.first] = ans[v]+cur.second;
                Q.push(cur.first);
            }
        }
    }

    return ans;
}

vector<ll> brute(){
    //create graph
    vector<vector<PII>> graph(n+1, vector<PII>());
    for(int i =0 ; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    //process queries
    vector<ll> ans;

    for(int i = 0; i<q; i++){
        int a = get<0>(query[i]),b = get<1>(query[i]),c = get<2>(query[i]);

        vector<ll> distA = bruteDfs(a, graph);
        vector<ll> distB = bruteDfs(b, graph);

        ll best = llINF;

        for(int j = 1; j<=n; j++){
            if(t[j] == c){
                best = min(best, distA[j] + distB[j]);
            }
        }
        if(best == llINF){
            ans.PB(-1);
        }else{
            ans.PB(best);
        }
    }
    return ans;
}

vector<ll> solve(){
    
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
        vector<ll> ansB = brute();
        vector<ll> ansS = solve();
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