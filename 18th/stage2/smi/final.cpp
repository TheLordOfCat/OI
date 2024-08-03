#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n, m;
vector<tuple<int,int,int,int>> edges;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b, s,t;
        cin>>a>>b>>s>>t;
        edges.PB(MT(a,b,s,t));
    }
}

vector<vector<int>> solve(){
    //create graph
    vector<vector<pair<PII,bool>>> graph(n+1, vector<pair<PII,bool>>());
    for(int i = 0; i<m; i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), s = get<2>(edges[i]), t = get<3>(edges[i]);  
        if(s != t){
            graph[a].PB(MP(MP(b, graph[b].size()),false));
            graph[b].PB(MP(MP(a, graph[a].size()-1),false));
        }
    }

    vector<int> degree(n+1, 0);
    for(int i = 1; i<=n; i++){
        degree[i] = graph[i].size(); 

        //checking for euler circut existance
        if(degree[i]%2 != 0){
            vector<vector<int>> temp(1, vector<int>());
            temp.front().PB(-1);
            return temp;
        }
    }

    vector<vector<int>> ans;

    //find euler circuts
    stack<int> S;
    vector<bool> vis(n+1, false);
    vector<int> last(n+1, 0);
    
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            vector<int> cycle;
            S.push(i);
            while(!S.empty()){
                int v = S.top();
                if(degree[v] == 0){
                    cycle.PB(v);
                    vis[v] = true;
                    S.pop();
                }else{
                    for(int j = last[v]; j<graph[v].size(); j++){
                        if(!graph[v][j].second){
                            degree[v]--;
                            degree[graph[v][j].first.first]--;
                            
                            S.push(graph[v][j].first.first);

                            graph[v][j].second = true;
                            graph[graph[v][j].first.first][graph[v][j].first.second].second = true;

                            last[v] = j+1;
                            break;
                        }
                    }
                }
            }

            //spliting the cycles too simple ones
            vector<vector<int>> cycleSplit;
            vector<int> temp;
            vector<bool> marked(n+1, false);
            for(int j = 0; j<cycle.size(); j++){
                temp.PB(cycle[j]);
                if(marked[temp.back()]){
                    cycleSplit.PB(vector<int>());

                    //separating the cycle
                    cycleSplit.back().PB(temp.back());
                    temp.pop_back();
                    while(temp.back() != cycle[j]){
                        cycleSplit.back().PB(temp.back());
                        marked[temp.back()] = false;
                        temp.pop_back();
                    }

                    cycleSplit.back().PB(temp.back());
                }
                marked[temp.back()] = true;
            }

            //updating the ans
            for(int j = 0; j<cycleSplit.size(); j++){
                ans.PB(cycleSplit[j]);                
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
    
    if(ansS.size() > 0 ){
        if(ansS.front().front()== -1){
            cout<<"NIE\n";
            return 0;
        }
    }

    cout<<ansS.size()<<"\n";
    for(int i = 0; i<ansS.size(); i++){
        cout<<ansS[i].size()-1<<" ";
        for(int j = 0; j <ansS[i].size(); j++){
            int cur = ansS[i][j];
            cout<<cur<<" ";
        }
        cout<<"\n";
    }

    return 0;
}