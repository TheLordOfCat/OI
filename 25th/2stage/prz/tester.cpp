#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back

const int INF = 1'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;

int n;
vector<int> x;
vector<int> y;
vector<PII> edges;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        y.PB(temp);
    }
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    n = rand()%10+1;
    //testing "NIE"
    for(int i = 0; i<n; i++){
        int temp = rand()%11;
        x.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int temp = rand()%11;
        y.PB(temp);
    }

    //testing "TAK"
    // int sum = 0;
    // for(int i = 0; i<n; i++){
    //     int temp = rand()%11;
    //     x.PB(temp);
    //     sum += temp;
    // }
    // for(int i = 0; i<n-1; i++){
    //     if(sum != 0){
    //         int temp = rand()%sum;
    //         y.PB(temp);
    //     }else{
    //         y.PB(0);
    //     }
    // }
    // y.PB(sum);

    int ind = 2;
    for(int i = 1; i<=n; i++){
        int con = rand()%3+1;
        for(int j =0 ; j<con;j ++){
            edges.PB(MP(i,ind));
            ind++;
            if(ind > n){
                break;
            }
        }
        if(ind > n){
            break;
        }
    }

}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<x[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<n; i++){
        cout<<y[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<n; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

struct compare{
    bool operator()(const PII a, const PII b){
        return a.second < b.second;
    }
};

ll brute(){
    vector<int> dif(n+1, 0);
    ll sum = 0;
    for(int i = 0; i<n; i++){
        sum += x[i]-y[i];
        dif[i+1] = x[i]-y[i];
    }
    if(sum != 0){
        return -1;
    }

    //creating graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<n-1; i++){
        graph[edges[i].first].PB(edges[i].second);
        graph[edges[i].second].PB(edges[i].first);
    }

    //getting depth
    vector<int> depth(n+1, 0);
    depth[1] = 1;
    queue<PII> bfs;
    bfs.push(MP(1,1));
    while(!bfs.empty()){
        PII v = bfs.front();
        bfs.pop();

        for(int i = 0; i<graph[v.first].size(); i++){
            int cur = graph[v.first][i];
            if(depth[cur] == 0){
                depth[cur] = v.second+1;
                bfs.push(MP(cur, v.second+1));
            }
        }
    }

    //removign excess
    ll ans = 0;
    priority_queue<PII, vector<PII>, compare> Q; 
    
    for(int i = 1; i<=n; i++){
        if(dif[i] > 0){
            Q.push(MP(i,depth[i]));
        }
    }

    while(!Q.empty()){
        PII v = Q.top();
        Q.pop();

        if(dif[v.first] > 0){
            ans++;
            dif[v.first] -= graph[v.first].size();
            for(int i = 0; i<graph[v.first].size(); i++){
                int cur = graph[v.first][i];
                dif[cur]++;
                if(dif[cur] > 0){
                    Q.push(MP(cur,depth[cur]));
                }
            }
            if(dif[v.first] > 0){
                Q.push(MP(v.first, v.second));
            }
        }
    }

    return ans;
}

ll solve(){
    vector<int> dif(n+1, 0);
    ll sum = 0;
    for(int i = 0; i<n; i++){
        sum += x[i]-y[i];
        dif[i+1] = x[i]-y[i];
    }
    if(sum != 0){
        return -1;
    }

    //creating graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<n-1; i++){
        graph[edges[i].first].PB(edges[i].second);
        graph[edges[i].second].PB(edges[i].first);
    }

    //size of subTrees, root = 1
    vector<pair<int,ll>> subTree(n+1, MP(0,0));
    stack<pair<int, bool>> S;

    vector<bool> vis(n+1, false);
    vis[1] = true;

    S.push(MP(1,false));

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();

        if(b){
            int sumVer = 1;
            ll sumVal = dif[v];
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                sumVer += subTree[cur].first;
                sumVal += subTree[cur].second;
            }
            subTree[v] = MP(sumVer,sumVal);
            continue;
        }

        S.push(MP(v,true));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                vis[cur] = true;
                S.push(MP(cur,false));
            }
        }
    }

    //propagation
    vector<ll> prop(n+1, 0);

    for(int i = 1; i<=n; i++){
        if(subTree[i].second > 0){
            prop[i] += subTree[i].second;
        }else if(subTree[i].second < 0){
            prop[i] += subTree[i].second;
            prop[1] -= subTree[i].second;
        }
    }

    vector<ll> op(n+1, 0);

    stack<PII> P;
    vis.clear();
    vis.assign(n+1, false);

    P.push(MP(1, prop[1]));
    vis[1] = true;

    while(!P.empty()){
        PII v = P.top();
        P.pop();

        op[v.first] = v.second;
        for(int i = 0; i<graph[v.first].size(); i++){
            int cur = graph[v.first][i];
            if(!vis[cur]){
                vis[cur] = true;
                P.push(MP(cur,v.second + prop[cur]));
            }
        }
    } 

    //getting ans
    ll minOp = llINF;
    for(int i = 1; i<=n; i++){
        minOp = min(minOp, op[i]);
    }
    ll ans =  0;
    for(int i = 1; i<=n; i++){
        ans += (op[i]-minOp);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op =1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        ll ansB = brute();
        ll ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}