#include<iostream>
#include <vector>
#include <stack>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int MAXN = 300'000;

int n;
vector<vector<int>> graph;

void getData(){
    cin>>n;
    graph.assign(n+1, vector<int>());
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        graph[a].PB(b);
        graph[b].PB(a);
    }
}

void getRandom(){
    n = rand()%10+1;
    graph.clear();
    graph.assign(n+1,vector<int>());
    int ind = 2;
    for(int i = 1; i<n; i++){
        if(ind >n){
            break;
        }
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            graph[i].PB(ind);
            ind++;
        }
    }
}

void printData(){
    cout<<n<<"\n";
    stack<int> S;
    vector<bool> vis(n+1, false);
    for(int i =1 ;i<=n; i++){
        if(!vis[i]){
            S.push(i);
            vis[i] = true;
            while(!S.empty()){
                int v=  S.top();
                for(int j =0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    cout<<i<<" "<<cur<<"\n";
                    vis[cur] = true;
                }
            }
        }
    }
}

int brute(){

}

int solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1;test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        int ansB = brute();
        int ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }
    return 0;
}