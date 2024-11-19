#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

int n;
vector<PII> edges;
int Sa, Sb, q;
vector<int> A, B;
vector<tuple<char, char,int>> query;

void getData(){
    edges.clear(); A.clear(); B.clear(); query.clear();

    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
    cin>>Sa>>Sb>>q;
    for(int i =0; i<Sa; i++){
        int temp;
        cin>>temp;
        A.PB(temp);
    }
    for(int i =0; i<Sb; i++){
        int temp;
        cin>>temp;
        B.PB(temp);
    }
    for(int i = 0; i<q; i++){
        char Z, t;
        int w;
        cin>>Z>>t>>w;
        query.PB(MT(Z,t,w));
    }
}

vector<int> getPart(vector<vector<int>>& graph){
    vector<int> con(n+1, 0);
    for(int i = 1; i<= n; i++){
        con[i] = graph[i].size();
    }

    vector<int> ans(n+1, 1);
    queue<int> Q;
    for(int i = 2; i<=n; i++){
        if(graph[i].size() == 1){
            Q.push(i);
        }
    }
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i =0 ; i<graph[v].size(); i++){
            int cur = graph[v][i];
            con[cur]--;
            if(con[cur] != 0){
                ans[cur] += ans[v];
            } 
            if(con[cur] == 1 && cur != 1){
                Q.push(cur);
            }
        }
    }

    for(int i =0 ; i< graph[1].size(); i++){
        int cur = graph[1][i];
        ans[1] += ans[cur];
    }
    
    return ans;
}

vector<int> getParents(vector<vector<int>>& graph){
    queue<int> Q;
    Q.push(1);
    vector<int> parents(n+1, -1);
    parents[1] = -2;
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(parents[cur] == -1){
                Q.push(cur);
                parents[cur] = v;
            }
        }
    }

    return parents;
}

ll winStrategy(int a, int b, vector<vector<int>>& graph, vector<int> &parents, vector<int>& part){
    //get mid point
    queue<PII> Q;
    vector<int> previous(n+1, -1);
    Q.push(MP(a,1));

    int dist = 0;

    while(!Q.empty()){
        int v = Q.front().first;
        int len = Q.front().second;
        Q.pop();

        if(v == b){
            dist = len;
            break;
        }

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(previous[cur] == -1){
                Q.push(MP(cur,len+1));
                previous[cur] = v;
            }
        }
    }

    previous[1] = -1;

    vector<int> center;
    if(dist%2 == 0){
        int v = b;
        int moves = dist;
        while(v != a && moves > (dist)/2 + 1){
            v = previous[v];
            moves--;
        }
        center.PB(v);
        center.PB(previous[v]);
    }else{
        int v = b;
        int moves = dist;
        while(v != a && moves > (dist+1)/2){
            v = previous[v];
            moves--;
        }
        center.PB(v);
    }

    //get the ans
    queue<int> P;
    P.push(a);
    int cA = -1;
    while(!P.empty()){
        int v = P.front();
        P.pop();
        for(int i = 0; i<center.size(); i++){
            if(v == center[i]){
                cA = center[i];
                break;
            }
        }
        if(cA != -1){
            break;
        }

        if(parents[v] != -1 && parents[v] != -2){
            P.push(parents[v]);
        }
    }

    ll ans = 0;

    if(cA == -1){
        while(!P.empty()){
            P.pop();
        }
        P.push(b);
        int cB = -1;
        while(!P.empty()){
            int v = P.front();
            P.pop();

            if(parents[v] != -1 && parents[v] != -2){
                P.push(parents[v]);
                for(int i = 0; i<center.size(); i++){
                    if(parents[v] == center[i]){
                        cB = v;
                        break;
                    }
                }
                if(cB != -1){
                    break;
                }
            }
        }

        if(center.size() == 2){
            if(part[center.front()] < n/2){
                ans = 1;
            } 
        }else{
            if(part[cB] <= n/2){
                ans = 1;
            } 
        } 
    }else{
        if(part[cA] > n/2){
            ans = 1;
        }        
    }

    return ans;
}

vector<ll> brute(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    //get parts of graph
    vector<int> part = getPart(graph);

    //get parents
    vector<int> parents = getParents(graph);

    vector<ll> ans;

    vector<int> Acopy = A, Bcopy = B; 
    //process default
    ll tempD = 0;
    for(int i = 0; i<Acopy.size(); i++){
        for(int j = 0; j<Bcopy.size(); j++){
            if(Acopy[i] != Bcopy[i]){
                ll temp = winStrategy(A[i], B[j], graph, parents, part);
                tempD += temp;
            }
        }
    }
    ans.PB(tempD);

    //process queyrys
    for(int o = 0; o<q; o++){
        tempD = 0; // getting the diffrence
        if(get<0>(query[o]) == 'A'){
            for(int i = 0; i<Bcopy.size(); i++){
                if(Bcopy[i] != get<2>(query[o])){
                    ll temp = winStrategy(get<2>(query[o]), B[i], graph, parents, part);
                    tempD += temp;   
                }
            }
            if(get<1>(query[o]) == '-'){
                tempD *= -1;
            }
        }else{
            for(int i = 0; i<Acopy.size(); i++){
                if(Acopy[i] != get<2>(query[o])){
                    ll temp = winStrategy(A[i], get<2>(query[o]), graph, parents, part);
                    tempD += temp;
                }
            }
            if(get<1>(query[o]) == '-'){
                tempD *= -1;
            }
        }
        ans.PB(tempD + ans[o]);
    }   

    return ans;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    vector<ll> ansB = brute();
    for(int j = 0; j<ansB.size(); j++){
        cout<<ansB[j]<<" ";
    }
    cout<<"\n";


    return 0;
}