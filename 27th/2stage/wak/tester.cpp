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

void dfsBrute(int V, vector<PII>& dp, vector<vector<int>>& graph){
    vector<bool> vis(n+1, false);
    vis[V] = true;

    stack<tuple<int,bool, bool>> S;
    S.push(MT(V,false, true));
    vector<int> parent(n+1, -1);

    while(!S.empty()){
        int v = get<0>(S.top());
        bool b = get<1>(S.top()), t = get<2>(S.top());
        S.pop();

        if(b){
            int ind = -1;
            int maxDp = 0;
            int sum = 0;

            if(t){
                for(int i = 0; i<graph[v].size(); i++){
                    int cur = graph[v][i];
                    if(cur != parent[v]){
                        if( maxDp < dp[cur].first || ind == -1){
                            maxDp = dp[cur].first;
                            ind = cur;
                        }
                    }
                }
                maxDp += atr[v-1];
            }else{
                for(int i = 0; i<graph[v].size(); i++){
                    int cur = graph[v][i];
                    if(cur != parent[v]){
                        sum += atr[cur-1];
                    }
                }
                for(int i = 0; i<graph[v].size(); i++){
                    int cur = graph[v][i];
                    if(cur != parent[v]){
                        if( maxDp < sum - atr[cur-1] + dp[cur].first || ind == -1){
                            maxDp = sum - atr[cur-1] + dp[cur].first;
                            ind = cur;
                        }
                    }
                }
            }

            dp[v] = MP(maxDp, ind);

            continue;
        }

        S.push(MT(v,true, t));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != parent[v]){
                parent[cur] = v;
                S.push(MT(cur,false, !t));
            }
        }
    }
}

void getPathBrute(int V, vector<bool>& vis, vector<PII>& dp,  vector<vector<int>>& graph, vector<int>& path, int& ansVis){
    stack<pair<int,bool>> S;
    S.push(MP(V,true));
    vector<int> parent(n+1, -1);
    path.PB(V);

    while(!S.empty()){
        int v = S.top().first;
        bool t = S.top().second;
        S.pop();

        vis[v] = true;
        if(!t){
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                if(cur != dp[v].second && cur != parent[v]){
                    path.PB(cur);
                    path.PB(v);
                    ansVis++;
                }
                vis[cur] = true;
            }
            ansVis++;
        }
        if(dp[v].second != -1){
            path.PB(dp[v].second);
            parent[dp[v].second] = v;
            S.push(MP(dp[v].second, !t)); 
        }
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
        dfsBrute(i, dp, graph);

        //create path
        if(ansAtr < dp[i].first){
            ansAtr = dp[i].first;
            vector<bool> vis(n+1, false);
            getPathBrute(i, vis, dp, graph, ansTown, ansVis);
        }
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