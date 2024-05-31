#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m, k;
vector<vector<int>> graph;
vector<pair<PII,int>> query;

void getData(){
    cin>>n>>m>>k;
    graph.assign(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        graph[a].PB(b);
        graph[b].PB(a);
    }
    for(int i = 0; i<k; i++){
        int s, t, d;
        cin>>s>>t>>d;
        query.PB(MP(MP(s,t),d));
    }
}

void getRandom(){
    srand(time(0));
    n = rand()%10+1;
    m = rand()%20+1;
    k = rand()%5+1;
    for(int i =0; i<m; i++){
        int a = rand()%n+1;
        int b = rand()%n+1;
        graph[a].PB(b);
        graph[b].PB(a);
    }
    for(int i = 0; i<k; i++){
        int s = rand()%n+1;
        int t = rand()%n+1;
        int d = rand()%(2*n)+1;
        query.PB(MP(MP(s,t),d));
    }
}

void printData(){
    cout<<n<<" "<<m<<" "<<k<<"\n";
    for(int i= 1; i<=n; i++){
        for(int j =0; j<graph[i].size(); j++){
            cout<<i<<" "<<graph[i][j]<<"\n";
        }
    }
    for(int i = 0; i<k; i++){
        cout<<query[i].first.first<<" "<<query[i].first.second<<" "<<query[i].second<<"\n";
    }
}

vector<bool> brute(){

}

vector<bool> solve(){

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
        vector<bool> ansB = brute();
        vector<bool> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j =0;j <ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j =0;j <ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }
    return 0;
}