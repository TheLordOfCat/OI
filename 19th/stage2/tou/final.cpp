#include<iostream>
#include <vector>
#include <queue>


#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using namespace std;

const int MAXN = 1'000'000;
const int MAXM = 2'000'000;
const int MAXK = 1'000'000;

int n, m, k;
vector<vector<int>> graph;

void getData(){
    cin>>n>>m>>k;
    graph.assign(n+1, vector<int>());

    for(int i =0; i<m; i++){
        int a,b;
        cin>>a>>b;
        graph[a].PB(b);
        graph[b].PB(a);
    }
}

vector<PII> solve(){
    vector<PII> ans;

    vector<bool> vis(n+1, false);
    vector<bool> con(n+1, false);

    vector<int> seg(n+1, 0);
    int ind = 0;
    for(int i = k+1; i<=n; i++){
        if(!vis[i]){
            queue<int> Q;
            ind++;
            Q.push(i);
            vis[i] = true;
            while(!Q.empty()){
                int v = Q.front();
                Q.pop();

                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur] && cur > k){
                        vis[cur] = true;
                        seg[cur] = ind;
                        Q.push(cur);
                    }
                }
            }
        }
    }

    for(int i = 1; i<=k; i++){
        if(!vis[i]){
            vector<bool> oneOut(n+1, false);
            queue<int> Q;
            Q.push(i);
            con[i] = true;
            while(!Q.empty()){
                int v = Q.front();
                vis[v] = true;
                Q.pop();

                for(int j = 0; j< graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(cur <= k){
                        if(!con[cur]){
                            Q.push(cur);
                            con[cur] = true;
                        }else if(!vis[cur]){
                            ans.PB(MP(v,cur));
                        }
                    }else{
                        if(!oneOut[seg[cur]]){
                            oneOut[seg[cur]] = true;
                        }else{
                            ans.PB(MP(v,cur));
                        }
                    }
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<PII> ansS = solve();
    cout<<ansS.size()<<"\n";
    for(int i = 0; i<ansS.size(); i++){
        cout<<min(ansS[i].first, ansS[i].second)<<" "<<max(ansS[i].first,ansS[i].second)<<"\n";
    }


    return 0;
}