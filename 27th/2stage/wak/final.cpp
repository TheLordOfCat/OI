#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <algorithm>

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

void dfsSolve(int V, vector<vector<pair<ll,int>>> &dp, vector<vector<int>>& graph){
    vector<int> parent(n+1, 0);
    stack<pair<int,bool>> S;
    S.push(MP(V,false));


    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();

        if(b){
            //type 1
            ll maxDp = 0;
            int ind = 0;
            ll sum = 0;

            for(int i = 0; i<graph[v].size(); i++){
                sum = 0;
                int cur = graph[v][i];
                if(cur == parent[v]) continue;
                for(int j = 0; j<graph[cur].size(); j++){
                    int c = graph[cur][j];
                    if(c != parent[cur]){
                        sum += atr[c-1];
                    }
                }
                for(int j = 0; j<graph[cur].size(); j++){
                    int c = graph[cur][j];
                    if(c == v) continue;
                    if(dp[c][0].first + sum - atr[c-1] > maxDp){
                        maxDp = dp[c][0].first + sum - atr[c-1];
                        ind = cur;
                    }
                }
            }

            dp[v][0].first = maxDp + atr[v-1];
            dp[v][0].second = ind;

            //type 2
            vector<int> twoBest = {0,0};
            for(int j= 0 ; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if(cur == parent[v]) continue;
                if(dp[cur][0] > dp[twoBest[0]][0]){
                    twoBest[0] = cur;
                }else if(dp[cur][0] > dp[twoBest[1]][0]){
                    twoBest[1] = cur;
                }
            }

            sum = 0;
            for(int j =0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if(cur != twoBest[0] && cur != twoBest[1]){
                    sum += atr[cur-1];
                }
            }

            dp[v][1].first = dp[twoBest[0]][0].first + dp[twoBest[1]][0].first + sum; 
            if(dp[twoBest[0]][0].first > dp[twoBest[1]][0].first){
                dp[v][1].second = twoBest[0];
            }else{
                dp[v][1].second = twoBest[1];
            }

            continue;
        }

        S.push(MP(v,true));
        for(int j = 0; j<graph[v].size(); j++){
            int cur = graph[v][j];
            if(cur != parent[v]){
                S.push(MP(cur,false));
                parent[cur] = v;
            }
        }
    }

}

vector<int> getPath(int ind, vector<vector<pair<ll,int>>>& dp, vector<vector<int>>& graph, int& townVis, int type){
    vector<int> path;

    int prev = 0;
    int count = 1;
    int temp = ind;

    while(temp != 0){
        path.PB(temp);
        if(count == 0){
            for(int i = 0; i<graph[temp].size(); i++){
                int cur = graph[temp][i];
                if(cur != prev && cur != dp[temp][type].second){
                    path.PB(cur);
                    path.PB(temp);
                    townVis++;
                }
            }
        }else{
            townVis++;
        }
        count++;
        count %= 2;

        prev = temp;
        temp = dp[temp][type].second;

        type = (type+1)%2;
    }
    return path;
}

tuple<ll,int,vector<int>> solve(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    vector<vector<pair<ll,int>>> dp(n+1, vector<pair<ll,int>>(2, MP(0,0)));

    dfsSolve(1, dp, graph);

    ll maxDp = 0;
    int townVis = 0;
    vector<int> path;

    int type = -1;
    int ind = 0;

    //best verticie
    for(int i = 1; i <= n; i++){
        if(dp[i][0].first > maxDp){
            type = 0;
            ind = i;
            maxDp = dp[i][0].first;
        }
        if(dp[i][1].first > maxDp){
            type = 1;
            ind = i;
            maxDp = dp[i][1].first;
        }
    }

    //getPath
    if(type == 0){ // 1 path
        path = getPath(ind, dp, graph, townVis, type);

    }else if(type == 1){ // two paths

        //best two paths
        vector<int> twoBest = {0,0};
        for(int j= 0 ; j<graph[ind].size(); j++){
            int cur = graph[ind][j];
            if(dp[cur][1] > dp[twoBest[0]][1]){
                twoBest[0] = cur;
            }else if(dp[cur][1] > dp[twoBest[1]][1]){
                twoBest[1] = cur;
            }
        }

        //path 1
        path = getPath(twoBest[0], dp, graph, townVis, type);

        reverse(path.begin(), path.end());

        path.PB(ind);
        for(int i = 0; i<graph[ind].size(); i++){
            int cur = graph[ind][i];
            if(cur != twoBest[0] && cur != twoBest[1]){
                path.PB(cur);
                path.PB(ind);
                townVis++;
            }
        }

        //path 2
        vector<int> path2 = getPath(twoBest[1], dp, graph, townVis, type);

        for(int i =0 ; i<path2.size(); i++){
            path.PB(path2[i]);
        }
    }

    return MT(maxDp, townVis, path);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    tuple<ll,int, vector<int>> ansS = solve();

    int a = get<0>(ansS), b = get<1>(ansS); vector<int> c = get<2>(ansS);
    cout<<a<<"\n"<<b<<"\n";
    for(int i = 0; i< c.size(); i++){
        cout<<c[i]<<" ";
    }
    cout<<"\n";


    return 0;
}