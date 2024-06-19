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
    for(int i = 0; i<m; i++){
        int a, b, s, t;
        cin>>a>>b>>s>>t;
        graph[a].PB(MP(b,MP(s,t)));
        graph[b].PB(MP(a,MP(s,t)));
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    m = rand()%(2*n)+1;
    if(n == 1){
        m = 0;
    }

    //check for not existaning
    for(int i = 0; i<m; i++){
        int a = rand()%n+1;
        int b = a;
        while(b == a){
            b = rand()%n+1;
        }
        int s = rand()%2;
        int t = rand()%2;
        if(a > b){
            swap(a,b);
        }
        graph[a].PB(MP(b,MP(s,t)));
        graph[b].PB(MP(a,MP(s,t)));
    }

    //check for loops
    int l = rand()%4+1;
    n = 1;
    for(int i = 0; i<l; i++){
        int start = n;
        int v = n;
        int len = rand()%3+1;
        for(int j = 0; j<len; j++){
            int con = rand()%2;
            if(con || n == 1){
                n++;
                graph[v].PB(MP(n,MP(0,1)));
                graph[n].PB(MP(v,MP(0,1)));
                v = n;
            }else{
                int temp = v;
                while(temp == v){
                    temp = rand()%n+1;
                }
                graph[v].PB(MP(temp,MP(1,0)));
                graph[temp].PB(MP(v,MP(1,0)));
                v = temp;
            }
        }
        graph[v].PB(MP(start,MP(1,0)));
        graph[start].PB(MP(v,MP(1,0)));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    
    vector<bool> vis(n+1, false);
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            stack<int> S;
            S.push(i);
            while(!S.empty()){
                int v = S.top();
                S.pop();
                vis[v] = true;
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j].first;
                    if(!vis[cur]){
                        cout<<v<<" "<<cur<<" "<<graph[v][j].second.first<<" "<<graph[v][j].second.second<<"\n";
                    }
                }
            }
        }
    }
}

bool verify(vector<vector<int>> v){
    bool ans = true;

    vector<vector<pair<int,PII>>> graphCopy = graph;

    for(int i = 0; i<v.size(); i++){
        v[i].PB(v[i].front());
        for(int j = 0; j<v[i].size()-1; j++){
            
            for(int o = 0; o<graphCopy[v[i][j]].size(); o++){
                int cur = graphCopy[v[i][j]][o].first;
                if(cur == v[i][j+1]){
                    graphCopy[v[i][j]][o].second.first = (graphCopy[v[i][j]][o].second.first + 1)%2;
                }
            }
        }
        v[i].pop_back();
    }

    vector<bool> vis(n+1, false);
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            stack<int> S;
            S.push(i);
            while(!S.empty()){
                int v = S.top();
                S.pop();
                vis[v] = true;
                for(int j = 0; j<graphCopy[v].size(); j++){
                    int cur = graphCopy[v][j].first;
                    if(!vis[cur]){
                        if(graphCopy[v][j].second.first != graphCopy[v][j].second.second){
                            ans = false;
                            break;
                        }
                    }
                }
            }
        }
        if(!ans){
            break;
        }
    }

    return ans;
}

vector<vector<int>> solve(){
    return vector<vector<int>>();
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
        vector<vector<int>> ansS = solve();
        if(!verify(ansS)){
            cout<<"ERROR\n";
            if(ansS.size() == 0){
                cout<<"NIE\n";
            }else{
                cout<<"TAK";
                for(int i = 0; i<ansS.size(); i++){
                    cout<<ansS[i].size()<<" ";
                    for(int j = 0; j<ansS[i].size(); j++){
                        cout<<ansS[i][j]<<" ";
                    }
                    cout<<ansS[i].front()<<"\n";
                }
            }
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}