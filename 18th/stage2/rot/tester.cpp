#include<iostream>
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
vector<pair<int,vector<int>>> graph;
vector<int> leaves;
vector<int> leavesIndex;

void getData(){
    cin>>n;

    int last = 1;
    stack<int> S;
    S.push(1);
    graph.assign(1, pair<int,vector<int>>());
    leavesIndex.assign(n+1, -1);
    while(!S.empty()){
        int v = S.top();
        S.pop();
        
        int o;
        cin>>o;
        graph[v].first = o;
        if(o == 0){
            S.push(last+1);
            graph[v].second.PB(last+1);
            S.push(last+2);
            graph[v].second.PB(last+2);
            last += 2;
        }else{
            leaves.PB(o);
            leavesIndex[o] = leaves.size()-1;
        }
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;

    vector<bool> used(n+1, false);
    int last = 1;
    stack<int> S;
    S.push(last);
    while(!S.empty()){
        int v = S.top();
        S.pop();

        if(S.size() == n){
            int l = n;
            while(!used[l]){
                l = rand()%n+1;
            }
            used[l] = true;
            leaves.PB(l);
            graph[v].first = l;
        }else{
            graph[v].first = 0;
            S.push(last+1);
            graph[v].second.PB(last+1);
            S.push(last+2);
            graph[v].second.PB(last+2);
            last += 2;
        }
    }
}

void printData(){
    cout<<n<<"\n";

    stack<int> S;
    S.push(1);
    while(!S.empty()){
        int v = S.top();
        S.pop();

        cout<<graph[v].first<<"\n";
        for(int i = 0; i<graph[v].second.size(); i++){
            int cur = graph[v].second[i];
            S.push(cur);
        }
    }
}

ll brute(){
    vector<PII> range(graph.size()+1, MP(0,0));
    
    stack<pair<int,bool>> S;
    S.push(MP(1,false));
    
    int lastLeaf = 1;

    while(!S.empty()){
        int v = S.top().first;
        int b =  S.top().second;
        S.pop();

        if(graph[v].first == 0){
            range[v] = MP(lastLeaf,lastLeaf);
            lastLeaf++;
            continue;
        }
        if(b){
            range[v] = MP(range[graph[v].second[0]].first, range[graph[v].second[1]].second);
            continue;
        }

        S.push(MP(v,true));
        for(int i = 0; i<graph[v].second.size(); i++){
            int cur = graph[v].second[i];
            S.push(MP(cur,false));
        }
    }

    ll ans = 0;

    stack<int> T;
    T.push(1);
    while(!T.empty()){
        int v = T.top();
        T.pop();

        PII left = range[graph[v].second[0]];
        PII right = range[graph[v].second[1]];

        ll totalInv = 0;
        for(int i = left.first; i<= left.second; i++){
            for(int j  = right.first; j<= right.second; j++){
                if(leaves[i] > leaves[j]){
                    totalInv++;
                }
            }
        }

        ll allCom = (left.second - left.first +1)* (right.second - right.first +1);
        ans += min(allCom - totalInv, totalInv);
    }

    return ans;
}

ll solve(){

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