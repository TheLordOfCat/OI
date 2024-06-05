#include<iostream>
#include <vector>
#include <queue>

#include <ctime>
#include <cstdlib>

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

void getRandom(){
    srand(time(0));
    graph.clear();

    n = rand()%15+1;
    m = rand()%(2*n)+1;
    k = rand()%n+1;

    graph.assign(n+1, vector<int>());
    for(int i =0; i<m; i++){
        int a = rand()%n+1;
        int b = rand()%n+1;
        while(a == b){
            b = rand()%n+1;
        }
        graph[a].PB(b);
        graph[b].PB(a);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<" "<<k<<"\n";

    vector<bool> vis(n+1, false);
    for(int i =1; i<= n; i++){
        if(!vis[i]){
            queue<int> Q;
            Q.push(i);

            while(!Q.empty()){
                int v= Q.front();
                Q.pop();
                if(vis[v]) continue;
                vis[v] = true;

                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        cout<<v<<" "<<cur<<"\n";
                        Q.push(cur);
                    }
                }
            }
        }
    }
}

vector<PII> brute(){
    int ans = 0; 

    vector<bool> vis(n+1, false);
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
        vector<int> out(n+1, 0);
        int in = 0;
        int trav = 0;
        if(!vis[i]){
            queue<int> Q;
            Q.push(i);
            while(!Q.empty()){
                int v = Q.front();
                Q.pop();
                if(vis[v]) continue;
                vis[v] = true;
                trav++;

                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(cur <=k){
                        if(!vis[cur]){
                            Q.push(cur);
                        }
                        in++;
                    }else{
                        out[cur]++;
                    }
                }
            }
            ans += (in/2-(trav-1));

            vector<bool> used(ind+1, false);
            int count = 0;
            for(int j = 1; j<=n; j++){
                if(out[j] > 0){
                    if(!used[seg[j]]){
                        count += out[j]-1;
                        used[seg[j]] = true;
                    }else{
                        count += out[j];
                    }
                }
            }
            ans += count;
        }
    }

    return vector<PII>(ans, MP(0,0));
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
    
    int op = 0;
    for(int test = 1; test<=100; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<PII> ansB = brute();
        vector<PII> ansS = solve();
        if(ansB.size() != ansS.size()){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB.size()<<"\n";
            cout<<"SOVLE:"<<ansS.size()<<"\n";
            for(int i = 0; i<ansS.size(); i++){
                cout<<ansS[i].first<<" "<<ansS[i].second<<"\n";
            }
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}