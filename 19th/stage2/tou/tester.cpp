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

void getRandom(){
    graph.clear();

    n = rand()%10+1;
    m = rand()%(2*n)+1;
    k = rand()%10+1;

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
            vis[i] = true;

            while(!Q.empty()){
                int v= Q.front();
                Q.pop();
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        cout<<v<<" "<<cur<<"\n";
                        vis[cur] = true;
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
    for(int i = 1; i<=k; i++){
        int out = 0;
        int in = 0;
        if(!vis[i]){
            vis[i] = true;
            queue<int> Q;
            Q.push(i);
            while(!Q.empty()){
                int v = Q.front();
                Q.pop();
                vis[v] = true;

                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(cur <=k){
                        if(!vis[cur]){
                            Q.push(cur);
                        }else{
                            in++;
                        }
                    }else{
                        out++;
                    }
                }
            }
        }
        ans += (out-1);
        ans += in;
    }

    return vector<PII>(ans, MP(0,0));
}

vector<PII> solve(){

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
    }

    return 0;
}