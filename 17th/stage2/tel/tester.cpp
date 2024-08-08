#include <iostream>
#include <vector>
#include <queue>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;

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

    n = 2;
    m = 0;

    vector<int> shortest(n+1, INF);
    vector<int> sectors;

    for(int i =0; i<4; i++){
        int con = rand()%2+1;
        n += con;
        sectors.PB(con);
    }

    int ind = 3;

    //connecting 1 sector to 1
    vector<int> sec1Num;
    for(int i = 0; i<sectors[0]; i++){
        edges.PB(MP(1,ind));
        sec1Num.PB(ind);
        ind++;
    }

    vector<int> sec2Num;
    //connecting 2 sector to first
    for(int i = 0; i<sectors[1]; i++){
        int r = rand()%sec1Num.size();
        edges.PB(MP(sec1Num[r],ind));
        sec2Num.PB(ind);
        ind++;
    }

    vector<int> sec4Num;
    //connecting 4 sector to 2
    for(int i = 0; i<sectors[3]; i++){
        edges.PB(MP(2,ind));
        sec4Num.PB(ind);
        ind++;
    }

    int con = rand()%10+1;
    for(int i = 0; i<con; i++){
        int r1 = rand()%sec2Num.size();
        int r2 = rand()%sec4Num.size();
        bool ok = true;
        for(int j = 0; j<edges.size(); j++){
            if((edges[i].first == r1 && edges[i].second == r2) || (edges[i].second == r1 && edges[i].first == r2)){
                ok = false;
                break;
            }
        }
        if(ok){
            edges.PB(MP(r1,r2));
        }
    }
}

void printData(){
    cout<<"DATA:\n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<m; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

ull brute(){
    ull ans = 0;
    vector<PII> edg;
    for(int i = 1; i<=n; i++){
        for(int j = i+1; j<=n; j++){
            edg.PB(MP(i,j));
        }
    }
    ull totalTel = 1<<edg.size();
    for(ull i = 0; i<totalTel; i++){
        ull con = 0;
        vector<vector<int>> graph(n+1, vector<int>());
        for(ull j = 0; j< edg.size(); j++){
            if(i & (1<<j)){
                int r1 = edg[j].first;
                int r2 = edg[j].second;
                if(r1 != r2){
                    graph[r1].PB(r2);
                    graph[r2].PB(r1);
                    con++;
                }
            }
        }

        for(int i = 0; i<m; i++){
            int a = edges[i].first;
            int b = edges[i].second;
            graph[a].PB(b);
            graph[b].PB(a);
            con++;
        }

        queue<PII> Q;
        Q.push(MP(1,0));
        bool ok = true;
        vector<bool> vis(n+1, false);

        while(!Q.empty()){
            int v = Q.front().first;
            int l = Q.front().second;
            Q.pop();

            if(v == 2){
                if(l < 5){
                    ok = false;
                    break;
                }else{
                    continue;
                }
            }

            for(int j = 0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if(!vis[cur]){
                    vis[cur] = true;
                    Q.push(MP(cur, l+1));
                }
            }
        }

        if(ok){
            ans = max(con,ans);
        }
    }
    return ans;
}

vector<int> BFS(int start, vector<vector<int>>& graph){
    vector<int> ans(n+1, INF);

    queue<PII> Q;
    Q.push(MP(start,0));
    bool ok = true;
    vector<bool> vis(n+1, false);

    while(!Q.empty()){
        int v = Q.front().first;
        int l = Q.front().second;
        Q.pop();

        ans[v] = l;

        for(int j = 0; j<graph[v].size(); j++){
            int cur = graph[v][j];
            if(!vis[cur]){
                vis[cur] = true;
                Q.push(MP(cur, l+1));
            }
        }
    }
    
    return ans;
}

ull solve(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0; i<edges.size(); i++){
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    ull s1 = 0, s2 = 0, s3 = 0, s4 =0;
    vector<int> t1 = BFS(1, graph);
    vector<int> t2 = BFS(2, graph);

    for(int i = 1; i<=n; i++){
        if(t1[i] == 1){
            s1++;
        }else if(t1[i] == 2){
            s2++;
        }
        if(t2[i] == 1){
            s4++;
        }else if(t2[i] == 2){
            s3++;
        }
    }

    ull excess = n-2-s1-s2-s3-s4;

    ull ans = n*(n-1)/2 - m - (n-1-s1) - s1*(1+s3+s4) - s2*(1+s4) - s3 - excess*(1+min(s1,s4));

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
        ull ansB = brute();
        ull ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}