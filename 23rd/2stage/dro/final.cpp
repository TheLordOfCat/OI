#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

const int MAXN = 500'000;
const int MAXM = 1'000'000;

int n,m;
vector<vector<int>> graph;
vector<vector<int>> graphR;

void getData(){
    cin>>n>>m;
    for(int i =0 ; i<=n; i++){
        graph.PB(vector<int>());
        graphR.PB(vector<int>());
    }
    for(int i =0; i<m; i++){
        int a, b;
        cin>>a>>b;
        graph[a].PB(b);
        graphR[b].PB(a);
    }
}

void getRandom(){
    srand(time(0));
    int N =rand()%5+1;

    graph.clear();
    graphR.clear();

    for(int i = 0; i<=N; i++){
        graph.push_back(vector<int>());
        graphR.push_back(vector<int>());
    }

    for(int i  = 1; i<=N ; i++){
        graph[i].PB((i+1)%N);
        graphR[(i+1)%N].PB(i);
    }

    m = N;

    int n = N;
    for(int i = 1; i<= N; i++){
        int con = rand()%2+1;
        for(int j = 0; j<con; j++){
            if(j == 0){
                n++;
                graph[i].PB(n);
                graphR[n].PB(i);
                m++;
            }else{
                n++;
                graph[n-1].PB(n);
                graphR[n].PB(n-1);
                m++;
            }
        }    
        graph[n].PB(i);
        graphR[i].PB(n);
        m++;
    }
}

void printData(){
    cout<<n<<" "<<m<<"\n";
    for(int i = 1; i<=n; i++){
        for(int j = 0; j<graph[i].size(); j++){
            cout<<i<<" "<<graph[i][j]<<"\n";
        }
    }
}

vector<int> brute(){
    vector<int> ans;
    for(int i = 1; i<=n; i++){
        queue<int> Q;
        Q.push(i);
        vector<bool> vis(n+1, false);
        vis[i] = true;
        while(!Q.empty()){
            int v = Q.front();
            Q.pop();
            for(int j = 0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if(!vis[cur]){
                    vis[cur] = true;
                    Q.push(cur);
                }
            }
        }
        Q.push(i);
        vector<bool> visR(n+1, false);
        visR[i] = true;
        while(!Q.empty()){
            int v = Q.front();
            Q.pop();
            for(int j = 0; j<graphR[v].size(); j++){
                int cur = graphR[v][j];
                if(!visR[cur]){
                    visR[cur] = true;
                    Q.push(cur);
                }
            }
        }

        bool ok = true;
        for(int j = 1; j<=n; j++){
            if(!(vis[i] || visR[i])){
                ok = false;
            }
        }
        if(ok){
            ans.push_back(i);
        }

    }
    return ans;
}

vector<int> topoSort(vector<int>& verticies, vector<vector<int>>& g){
    vector<bool> vis(n+1, false);
    vector<int> ans;

    for(int i = 0; i<verticies.size(); i++){
        if(!vis[verticies[i]]){
            stack<pair<int, bool>>  S;
            S.push(MP(verticies[i],false));   
            while(!S.empty()){
                int v = S.top().first;
                int b = S.top().second;
                S.pop();
                if(b){
                    ans.push_back(v);
                }
                if(vis[v]){
                    continue;
                }
                vis[v] = true;
                for(int j = 0; j<g[v].size(); j++){
                    int cur = g[v][j];
                    if(!vis[cur]){
                        vis[cur] = true;
                        S.push(MP(cur, false));
                    }
                }
                S.push(MP(v,true));
            }
        }
    }

    reverse(ans.begin(), ans.end());

    return ans;
} 

vector<int> SCC(vector<int> &roots){
    vector<int> vTemp;
    for(int i = 1; i<=n; i++) vTemp.push_back(i);
    vector<int> order = topoSort(vTemp, graph);

    vector<bool> used(n+1, false);
    vector<int> rootNodes;
    for(int i = 1; i<=n; i++){
        if(!used[i]){
            stack<int> S;
            vector<int> component;
            S.push(i);
            used[i] = true;
            while(!S.empty()){
                int v = S.top();
                S.pop();
                component.push_back(v);
                for(int j = 0; j<graphR[v].size(); j++){
                    int cur = graphR[v][j];
                    if(!used[cur]){
                        used[cur] = true;
                        S.push(cur);
                    }
                }
            }

            int root = component.front();
            for(int u: component) roots[u] = root;
            rootNodes.push_back(root);
        }
    }
    return rootNodes;
}

vector<int> solve(){
    //SCC
    vector<int> roots(n+1, -1);
    vector<int> verticies = SCC(roots);
    vector<bool> specV(n+1, false);
    for(int i = 0; i<verticies.size(); i++){
        specV[verticies[i]] = true;
    }

    vector<vector<int>> sccGraph(n+1, vector<int>());
    vector<vector<int>> sccGraphR(n+1, vector<int>());
    for(int i = 0; i<verticies.size(); i++){
        for(int j = 0; j<graph[verticies[i]].size(); j++){
            int cur = graph[verticies[i]][j];
            if(specV[cur]){
                sccGraph[verticies[i]].push_back(cur);
                sccGraphR[cur].push_back(verticies[i]);
            }
        }
    }

    //topoSort
    vector<int> order = topoSort(verticies, sccGraph);
    vector<int> toOrder(n+1,-1);
    for(int i = 0; i<order.size(); i++){
        toOrder[order[i]] = i;
    }

    vector<bool> R(n+1, false);
    vector<bool> vis(n+1, false);
    int maxInd = -1;
    for(int i = 0; i<order.size(); i++){
        if(i >= toOrder[maxInd]){
            R[order[i]] = true;
        }
        for(int j = 0; j<sccGraph[order[i]].size(); j++){
            int cur = sccGraph[order[i]][j];
            maxInd = max(maxInd, toOrder[cur]);
        }
    }

    reverse(order.begin(), order.end());

    maxInd = -1;
    for(int i = 0; i<order.size(); i++){
        if(i >= toOrder[maxInd]){
            R[order[i]] = true;
        }
        for(int j = 0; j<sccGraphR[order[i]].size(); j++){
            int cur = sccGraphR[order[i]][j];
            maxInd = max(maxInd, toOrder[cur]);
        }
    }

    vector<int> ans;
    for(int i = 1; i<=n; i++){
        if(R[roots[i]]){
            ans.push_back(i);
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        if(ansB.size() != ansS.size()){
            cout<<"ERROR\n";
            printData();
            cout<<"BRUTE: \n";
            cout<<ansB.size()<<"\n";
            for(int i = 0; i<ansB.size(); i++){
                cout<<ansB[i]<<" ";
            }
            cout<<"SOLVE: \n";
            cout<<ansS.size()<<"\n";
            for(int i = 0; i<ansS.size(); i++){
                cout<<ansS[i]<<" ";
            }
            return 0;
        }
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                printData();
                cout<<"BRUTE: \n";
                cout<<ansB.size()<<"\n";
                for(int i = 0; i<ansB.size(); i++){
                    cout<<ansB[i]<<" ";
                }
                cout<<"SOLVE: \n";
                cout<<ansS.size()<<"\n";
                for(int i = 0; i<ansS.size(); i++){
                    cout<<ansS[i]<<" ";
                }
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}