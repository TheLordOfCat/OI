#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n;
vector<vector<int>> graph;
vector<int> val;

void getData(){
    cin>>n;
    graph.assign(2, vector<int>());
    val.assign(2, 0);
    
    stack<int> S;
    S.push(1);
    while(!S.empty()){
        int v = S.top();
        S.pop();

        int temp;
        cin>>temp;
        val[v] = temp;
        if(temp == 0){
            graph.PB(vector<int>());
            S.push(graph.size()-1);
            graph[v].PB(graph.size()-1);
            
            graph.PB(vector<int>());
            S.push(graph.size()-1);
            graph[v].PB(graph.size()-1);

            val.PB(-1);
            val.PB(-1);
        }
    }
}

void getRandom(){
    graph.clear();
    val.clear();

    srand(time(0));

    n = 0;
    stack<int> S;
    S.push(1);
    graph.assign(2, vector<int>());
    val.assign(2, -1);

    while(!S.empty()){
        int v = S.top();
        S.pop();

        int type = rand()%5+1;
        if(type == 1){
            val[v] = 1;
            graph.PB(vector<int>());
            val.PB(-1);
            S.push(graph.size()-1);
            graph[v].PB(graph.size()-1);

            graph.PB(vector<int>());
            val.PB(-1);
            S.push(graph.size()-1);
            graph[v].PB(graph.size()-1);
        }else{
            n++;
            val[v] = n;
        }
    }
}

void printData(){
    cout<<"DATA: ";
    stack<int> S;
    S.push(1);
    
    while(!S.empty()){
        int v = S.top();
        S.pop();

        cout<<val[v]<<"\n";
        for(int i =0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            S.push(cur);
        }
    }
}

pair<ll,vector<int>> mergeVert(int ind){
    if(val[ind] == 0){
        pair<ll,vector<int>> A = mergeVert(graph[ind][0]);
        pair<ll,vector<int>> B = mergeVert(graph[ind][1]);

        ll inv = 0;
        for(int i = 0; i<A.second.size(); i++){
            int a = A.second[i];
            for(int j = 0; j<B.second.size(); j++){
                int b = B.second[j];
                if(a>b){
                    inv++;
                }
            }
        }

        vector<int> con;
        for(int i = 0; i<A.second.size(); i++){
            con.PB(A.second[i]);
        }
        for(int i = 0; i<B.second.size(); i++){
            con.PB(B.second[i]);
        }

        ll ans = A.first + inv + B.first;
        return MP(ans, con);
    }else{
        vector<int> temp = {val[ind]};
        return MP(0, temp);
    }
}

ll brute(){
    pair<ll,vector<int>> merged = mergeVert(1);
    
    return merged.first;
}

ll solve(){
    return 1;
}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"Test nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        ll ansB = brute();
        ll ansS = solve();
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