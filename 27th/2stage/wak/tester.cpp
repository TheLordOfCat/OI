#include <iostream>
#include <vector>
#include <stack>
#include <tuple>

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

int n;
vector<int> atr;
vector<PII> edges;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        atr.PB(temp);
    }
    for(int i =0 ; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    for(int i = 0; i<n; i++){
        int temp = rand()%10+10;
        atr.PB(temp);
    }
    int ind = 2;
    for(int i = 1; i<=n; i++){
        if(ind > n){
            break;
        }
        int con = rand()%3+1;
        for(int  j = 0; j<con; j++){
            if(ind > n){
                break;
            }
            edges.PB(MP(i,ind));
            ind++;
        }
    }
}

void printData(){
    cout<<n<<"\n";
    for(int i = 0; i<atr.size(); i++){
        cout<<atr[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

void dfsBrute(int v, vector<bool>& vis, vector<PII>& dp, vector<vector<int>>& graph){
    vis[v] = true;

    for(int i = 0; i<graph[v].size(); i++){
        int cur = graph[v][i];
        ll sum = 0;
        if(!vis[cur]){
            sum += dp[cur].first;
            dfsBrute(cur, vis, dp, graph);
        }
        dp[cur].first += sum + atr[v];
    }

    PII best = MP(0,-1);
    for(int i = 0; i<graph[v].size(); i++){
        int cur = graph[v][i];
        if(best.first < dp[cur].first - atr[cur]){
            best.first += dp[cur].first - atr[cur];
            best.second = cur;
        }
    }

    dp[v].first += best.first;
    dp[v].second = best.second;
}

void getPathBrute(int V, vector<bool>& vis, vector<PII>& dp,  vector<vector<int>>& graph, vector<int>& path){
    stack<int> S;
    S.push(V);

    while(!S.empty()){
        int v = S.top();
        S.pop();

        vis[v] = true;

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != dp[v].second){
                path.PB(cur);
                path.PB(v);
            }
            vis[cur] = true;
        }
        path.PB(dp[v].first);
        S.push(dp[v].first);
    }

}

tuple<ll,int,vector<int>> brute(){
    ll ansAtr = -1; int ansVis = 0; vector<int> ansTown;

    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a  = edges[i].first, b =  edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }


    for(int i = 1; i<=n; i++){
        //get ansAtr
        vector<PII> dp(n+1, MP(0,-1));
        vector<bool> vis(n+1, false);
        dfsBrute(i, vis, dp, graph);

        //create path
        vis.assign(n+1, false);
        getPathBrute(i, vis, dp, graph, ansTown);
    }

    return MT(ansAtr, ansVis, ansTown); 
}

tuple<ll,int,vector<int>> solve(){
    
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
        tuple<ll,int, vector<int>> ansB = brute(); 
        tuple<ll,int, vector<int>> ansS = solve();
        bool ok = true;

        if(get<0>(ansB) != get<0>(ansS)){
            ok = false;
        }else if(get<1>(ansB) != get<1>(ansS)){
            ok = false;
        }else{
            // use based on way of coding
            //
            // vector<int> c = get<2>(ansB);
            // vector<int> d = get<2>(ansS);
            // for(int i = 0; i<c.size(); i++){
            //     if(c[i] !=d[i]){
            //         ok = false;
            //         break;
            //     }
            // }
        }


        if(!ok){
            cout<<"ERROR\n";
            cout<<"BURTE: \n";
            ll a = get<0>(ansB); int b = get<1>(ansB); vector<int> c = get<2>(ansB);
            cout<<a<<"\n"<<b<<"\n";
            for(int i = 0; i< c.size(); i++){
                cout<<c[i]<<" ";
            }
            cout<<"\n";

            cout<<"SOLVE: \n";
            a = get<0>(ansS), b = get<1>(ansS), c = get<2>(ansS);
            cout<<a<<"\n"<<b<<"\n";
            for(int i = 0; i< c.size(); i++){
                cout<<c[i]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        } else{
            cout<<"CORRECT\n";
        }
    }

    return 0;
}