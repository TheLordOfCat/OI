#include <iostream>
#include <vector>
#include <queue>
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

const int INF = 2'000'000'000;

int n, m, k;
vector<PII> edges;
vector<tuple<int,int,int>> requests;

void getData(){
    cin>>n>>m>>k;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
    for(int i = 0; i<k; i++){
        int s, t, d;
        cin>>s>>t>>d;
        requests.PB(MT(s,t,d));
    }
}

bool comp(const PII a, const PII b){
    return a.first< b.first;
}

vector<int> solve(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    /*
    traverse the graph
    vector<vector<PII>> shortest(n+1,vector<PII>(n+1, MP(INF,INF)));

    for(int i = 1; i<=n; i++){
        queue<PII> Q;
        Q.push(MP(i,0));

        while(!Q.empty()){
            int v = Q.front().first;
            int l = Q.front().second;
            Q.pop();

            for(int j = 0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if((l+1)%2 == 0){
                    if(shortest[i][cur].first >= l+1){
                        shortest[i][cur].first = l+1;
                        Q.push(MP(cur,l+1));
                    }
                }else{
                    if(shortest[i][cur].second >= l+1){
                        shortest[i][cur].second = l+1;
                        Q.push(MP(cur,l+1));
                    }
                }
            }
        }
    }

    //procces requests
    vector<int> ans;

    for(int i = 0; i<k; i++){
        int s = get<0>(requests[i]), t = get<1>(requests[i]), d = get<2>(requests[i]); 
        int ok = 0;
        if(d%2 == 0){
            if(shortest[s][t].first <= d){
                ok = 1;
            }
        }else{
            if(shortest[s][t].second <= d){
                ok = 1;
            }
        }
        ans.PB(ok);
    }
    */

    vector<PII> quests;
    for(int i = 0; i<k; i++) quests.PB(MP(get<0>(requests[i]),i));

    sort(quests.begin(), quests.end());

    vector<int> ans(k, -1);
    vector<PII> shortest(n+1, MP(INF,INF));

    for(int i = 0; i<k; i++){
        int s = get<0>(requests[quests[i].second]), t = get<1>(requests[quests[i].second]), d = get<2>(requests[quests[i].second]); 

        bool up = true;
        if(i > 1){
            if(quests[i-1].first == quests[i].first){
                up = false;
            }
        }
        
        if(up){
            shortest.clear();
            shortest.assign(n+1, MP(INF,INF));

            queue<PII> Q;
            Q.push(MP(s,0));

            while(!Q.empty()){
                int v = Q.front().first;
                int l = Q.front().second;
                Q.pop();

                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if((l+1)%2 == 0){
                        if(shortest[cur].first >= l+1){
                            shortest[cur].first = l+1;
                            Q.push(MP(cur,l+1));
                        }
                    }else{
                        if(shortest[cur].second >= l+1){
                            shortest[cur].second = l+1;
                            Q.push(MP(cur,l+1));
                        }
                    }
                }
            }
        }

        int ok = 0;
        if(d%2 == 0){
            if(shortest[t].first <= d){
                ok = 1;
            }
        }else{
            if(shortest[t].second <= d){
                ok = 1;
            }
        }
        ans[quests[i].second] = ok;
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    vector<int> ansS = solve();
    for(int j = 0; j<k; j++){
        if(ansS[j] == 0){
            cout<<"NIE\n";
        }else{
            cout<<"TAK\n";
        }
    }

    return 0;
}