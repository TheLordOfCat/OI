#include<iostream>
#include <vector>
#include <stack>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m;
vector<vector<pair<int,PII>>> graph;

void getData(){
    cin>>n>>m;
    graph.assign(n+1, vector<pair<int, PII>>());
    for(int i = 0; i<m; i++){
        int a, b, s, t;
        cin>>a>>b>>s>>t;
        graph[a].PB(MP(b,MP(s,t)));
        graph[b].PB(MP(a,MP(s,t)));
    }
}

vector<vector<int>> solve(){
    vector<vector<int>> ans;
    //create a new graph
    vector<bool> used(n+1, false);
    vector<vector<pair<PII,bool>>> graph0(n+1, vector<pair<PII,bool>>());
    for(int i = 1; i<=n; i++){
        if(!used[i]){
            stack<int> S;
            S.push(i);
            while(!S.empty()){
                int v = S.top();
                S.pop();
                used[v] = true;
                
                for(int j= 0; j<graph[v].size(); j++){
                    int cur = graph[v][j].first;
                    if(!used[cur]){
                        if(graph[v][j].second.first != graph[v][j].second.second){
                            graph0[v].PB(MP(MP(cur,graph0[cur].size()), false));
                            graph0[cur].PB(MP(MP(v,graph0[v].size()-1),false));
                        }
                        S.push(cur);
                    }
                }
            }
        }
    }
    
    //check if valid 
    for(int i = 1; i<=n; i++){
        if(graph0[i].size()%2 != 0){
            return vector<vector<int>>();
        }
    }

    //find loops
    vector<bool> vis(n+1, false);
    vector<int> pre(n+1, -1);

    for(int i = 1; i<=n; i++){
        stack<int> S;
        S.push(i);
        while(!S.empty()){
            int v = S.top();
            S.pop();
            vis[v] = true;

            for(int j = 0; j<graph0[v].size(); j++){
                int cur = graph0[v][j].first.first;
                int rev = graph0[v][j].first.second;
                int b = graph0[v][j].second;
                if(!b){
                    graph0[v][j].second = true;
                    graph0[cur][rev].second = true;

                    if(vis[cur]){
                        //found loop
                        int V = v;
                        int end = cur;
                        
                        vector<int> temp;
                        while(V != end){
                            if(V == i){
                                temp.PB(V);
                                vis[V] = false;
                                reverse(temp.begin(), temp.end());
                                V = cur;
                                end = i;
                            }else{
                                temp.PB(V);
                                vis[V] = false;
                                V = pre[V];
                            }
                        }
                        if(vis[cur]){
                            temp.PB(cur);
                            vis[cur] = false;
                        }

                        reverse(temp.begin(), temp.end());
                        ans.PB(temp);
                    }else{
                        S.push(cur);
                        vis[cur] = true;
                        pre[cur] = v;
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

    vector<vector<int>> ansS = solve();
    if(ansS.size() == 0){
        cout<<"NIE\n";
    }else{
        cout<<ansS.size()<<"\n";
        for(int i = 0; i<ansS.size(); i++){
            cout<<ansS[i].size()<<" ";
            for(int j = 0; j<ansS[i].size(); j++){
                cout<<ansS[i][j]<<" ";
            }
            cout<<ansS[i].front()<<"\n";
        }
    }

    return 0;
}