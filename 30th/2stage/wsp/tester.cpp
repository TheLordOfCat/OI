#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back

int n, m, k;
vector<int> f;
vector<PII> edges;

void getData(){
    f.clear(); edges.clear();

    cin>>n>>m>>k;
    f.PB(-1);
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        f.PB(temp);
    }
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    f.clear(); edges.clear();

    srand(time(0));

    // n = rand()%50+1;
    n = 10;
    m = 0;
    // k = rand()%8+1;
    k = 8;

    f.PB(-1);
    for(int i = 0; i<n; i++){
        // int temp = rand()%1'000'000'000+1;
        int temp = rand()%200+1;
        f.PB(temp);
    }

    for(int i = 1; i<=n; i++){
        int con;
        if(k == 1){
            con = 1;
        }else{
            con = rand()%k+1;
        }
        for(int j = 1; j<=con && i+j<=n; j++){
            edges.PB(MP(i, i+j));
            m++;
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<" "<<k<<"\n";
    for(int i = 1; i<f.size(); i++){
        cout<<f[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

vector<ll> brute(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        if(a < b){
            graph[a].PB(b);
        }else{
            graph[b].PB(a);
        }
    }

    //process verticies
    vector<ll> ans(n+1, 0);

    for(int i = n; i>=1; i--){
        ll temp = 0;
        vector<bool> used(n+1, false);
        queue<int> Q;
        Q.push(i);
        temp += (ll)f[i];
        used[i] = true;
        while(!Q.empty()){
            int v = Q.front();
            Q.pop();

            for(int j = 0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if(!used[cur]){
                    used[cur] = true;
                    Q.push(cur);
                    temp += (ll)f[cur];
                }
            }
        }

        ans[i] = temp;
    }
    
    return ans;
}

vector<ll> solve(){
    int range = (1<<8) + 1;
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
    }

    //dp
    vector<vector<ll>> dp(n+1, vector<ll>(range, 0));
    for(int j = 0; j<range; j++){
        if(j & 1){
            dp[n][j] = f[n];
        }else{
            dp[n][j] = 0;
        }
    }

    for(int i = n-1; i>=1; i--){
        for(int j = 1; j<range; j++){
            if(j & 1){
                int prep = j>>1;
                for(int o = 0; o<graph[i].size(); o++){
                    int cur = graph[i][o];
                    int move = 1<<(cur-i-1);
                    prep |= move;
                }
                dp[i][j] = dp[i+1][prep] + f[i];                                
            }else{
                dp[i][j] = dp[i+1][j>>1];
            }
        }
    }

    //get ans
    vector<ll> ans = {-1};
    for(int i = 1; i<n; i++){
        int type = 0;
        for(int j = 0; j < graph[i].size(); j++){
            int cur = graph[i][j];
            int move = 1<<(cur-i-1);
            type |= move;
        }

        ans.PB(dp[i+1][type] + f[i]);
    }
    ans.PB(f[n]);

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1'000'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<ll> ansB = brute();
        vector<ll> ansS = solve();
        for(int i = 1; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 1; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 1; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}