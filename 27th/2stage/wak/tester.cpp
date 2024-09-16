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
        int prev = 0;
        int count = 0;
        int temp = twoBest[0];

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

        reverse(path.begin(), path.end());

        path.PB(ind);

        //path 2
        prev = 0;
        count = 0;
        temp = twoBest[1];

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
    }

    return MT(maxDp, townVis, path);
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