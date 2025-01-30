#include <iostream>
#include <vector>
#include <stack>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back
#define PLL pair<ll,ll>

int n;
vector<PII> edges;
int m;
vector<int> query;

void getData(){
    edges.clear();
    query.clear();

    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
    
    cin>>m;
    for(int i = 0; i<m; i++){
        int a;
        cin>>a;
        query.PB(a);
    }
}

void getRandom(){
    edges.clear();
    query.clear();

    srand(time(0));

    n = rand()%10+2;
    int ind = 2;
    for(int i = 0; i<n-1; i++){
        int con = rand()%3+1;
        for(int j =0 ; j<con;j ++){
            if(ind > n) break;
            edges.PB(MP(i+1, ind));
            ind++;
        }
        if(ind > n) break;
    }
    
    m = rand()%10+1;
    vector<bool> strike(n+1, false);
    for(int i = 0; i<m; i++){
        int s = rand()%n+1;
        if(strike[s]){
            query.PB((-1)*s);
        }else{
            query.PB(s);
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i =0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
    cout<<m<<"\n";
    for(int i = 0; i<query.size(); i++){
        cout<<query[i]<<"\n";
    }
}

vector<int> brute(){
    vector<int> ans;

    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    vector<bool> strike(n+1, false);
    for(int i = 0; i<query.size(); i++){
        //update strike
        int s = query[i];
        if(s < 0){
            strike[(-1)*s] = false;
        }else{
            strike[s] = true;
        }

        //get scc
        int scc = 0;
        vector<bool> vis(n+1, false);
        for(int j = 1; j<=n; j++){
            if(!vis[j] && !strike[j]){
                scc++;

                stack<int> S;
                S.push(j);
                vis[j] = true;

                while(!S.empty()){
                    int v = S.top();
                    S.pop();

                    for(int o = 0; o<graph[v].size(); o++){
                        int cur = graph[v][o];
                        if(!vis[cur] && !strike[cur]){
                            vis[cur] = true;
                            S.push(cur);
                        }
                    }
                }
            }
        }

        ans.PB(scc);
    }

    return ans;
}

vector<int> solve(){

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
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j =0 ; j<ansB.size(); j++) cout<<ansB[j]<<" ";
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<" ";
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}