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

void getRandom(){
    edges.clear();
    requests.clear();

    srand(time(0));

    n = rand()%10+2;
    m = rand()%(n+5)+1;
    for(int i = 0; i<m; i++){
        int a = -1, b = -1;
        while(a != b){
            a = rand()%n+1;
            b = rand()%n+1;
        }
        edges.PB(MP(a,b));
    }
    int k = rand()%10+1;
    for(int i = 0; i<k; i++){
        int s = rand()%n+1;
        int t = rand()%n+1;
        int d = rand()%10+1;
        requests.PB(MT(s,t,d));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<" "<<k<<"\n";
    for(int i =0; i<n; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
    for(int i = 0; i<k; i++){
        cout<<get<0>(requests[i])<<" "<<get<1>(requests[i])<<" "<<get<2>(requests[i])<<"\n";
    }
}

vector<int> brute(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }
    
    vector<int> ans;
    for(int o = 0; o<k; o++){
        int found = 0;

        int s = get<0>(requests[o]), t = get<1>(requests[o]), d = get<2>(requests[o]);
        queue<PII> Q;
        Q.push(MP(s,0));
        while(!Q.empty()){
            int v = Q.front().first;
            int l = Q.front().second;
            Q.pop();

            if(l == d){
                if(v == t){
                    found = 1;
                    break;
                }

                continue;
            }

            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                Q.push(MP(cur,l+1));
            }
        }

        ans.PB(found);
    }

    return ans;
}

vector<int> solve(){
    vector<int>();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1 ;test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<k; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<k; j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<k; j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}