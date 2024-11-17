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

void getRandom(){
    edges.clear(); A.clear(); B.clear(); query.clear();

    srand(time(0));

    n = rand()%10+1; 
    Sa = rand()%n + 1;
    Sb = rand()%n + 1;
    // q = rand()%10+1;
    q = 0;

    int ind = 2;
    for(int i = 1; i<=n; i++){
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            edges.PB(MP(i,ind));
            ind++;
            if(ind > n){
                break;
            }
        }
        if(ind > n){
            break;
        }
    }

    vector<bool> visA(n+1, false);
    visA[0] = true;
    for(int i = 0; i<Sa; i++){
        int v =0;
        while(visA[v]){
            v = rand()%n+1;
        }
        visA[v] = true;
        A.PB(v);
    }
    vector<bool> visB(n+1, false);
    visB[0] = true;
    for(int i = 0; i<Sb; i++){
        int v =0;
        while(visB[v]){
            v = rand()%n+1;
        }
        visB[v] = true;
        B.PB(v);
    }

    int curA = A.size(), curB =  B.size();

    for(int i =0 ; i<q; i++){
        char Z, t;
        int w = 0;

        int typeSet = rand()%2+1;
        int typeOps = rand()%2+1;
        if(typeSet == 0){
            Z = 'A';
        }else{
            Z = 'B';
        }

        if(typeOps == 0){
            if(Z == 'A'){
                if(curA == n){
                    typeOps = 1;
                    while(!visA[w]){
                        w = rand()%n+1;
                    }
                    visA[w] = false;
                }else{
                    while(visA[w]){
                        w = rand()%n+1;
                    }
                    visA[w] = true;
                }
            }else{
                if(curB == n){
                    typeOps = 1;
                    while(!visB[w]){
                        w = rand()%n+1;
                    }
                    visB[w] = false;
                }else{
                    while(visB[w]){
                        w = rand()%n+1;
                    }
                    visB[w] = true;
                }
            }
        }else{
            if(Z == 'A'){
                if(curA == 0){
                    typeOps = 0;
                    while(visA[w]){
                        w = rand()%n+1;
                    }
                    visA[w] = true;
                }else{
                    while(!visA[w]){
                        w = rand()%n+1;
                    }
                    visA[w] = false;
                }
            }else{
                if(curB == n){
                    typeOps = 0;
                    while(visB[w]){
                        w = rand()%n+1;
                    }
                    visB[w] = true;
                }else{
                    while(!visB[w]){
                        w = rand()%n+1;
                    }
                    visB[w] = false;
                }
            }
        }

        if(typeOps == 0){
            t = '+';
        }else{
            t = '-';
        }

        query.PB(MT(Z,t,w));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    cout<<Sa<<" "<<Sb<<" "<<q<<"\n";
    for(int i = 0; i<Sa; i++){
        cout<<A[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<Sb; i++){
        cout<<B[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<query.size(); i++){
        cout<<get<0>(query[i])<<" "<<get<1>(query[i])<<" "<<get<2>(query[i])<<"\n";
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
            if(con[cur] == 1){
                Q.push(cur);
            }
        }
    }
    
    return ans;
}

vector<int> getParents(vector<vector<int>>& graph){
    queue<int> Q;
    Q.push(1);
    vector<int> parent(n+1, -1);
    parent[1] = -2;
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(parent[cur] == -1){
                Q.push(cur);
                parent[cur] = v;
            }
        }
    }

    return parent;
}

ll winStrategy(int a, int b, vector<vector<int>>& graph, vector<int> &parent, vector<int>& part){
    //get mid point
    queue<PII> Q;
    vector<int> previous(n+1, -1);
    Q.push(MP(a,0));

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

    vector<int> center;
    if(dist%2 == 0){
        int v = b;
        int moves = dist;
        while(v != a && moves > (dist)/2 + 1){
            v = previous[v];
            dist--;
        }
        center.PB(v);
        center.PB(previous[v]);
    }else{
        int v = b;
        int moves = dist;
        while(v != a && moves > (dist+1)/2){
            v = previous[v];
            dist--;
        }
        center.PB(v);
    }

    //get the ans
    queue<int> P;
    P.push(a);
    int c = -1;
    while(!P.empty()){
        int v = P.front();
        P.pop();
        for(int i = 0; i<center.size(); i++){
            if(v == center[i]){
                c = center[i];
                break;
            }
        }

        if(parent[v] != -1){
            P.push(parent[v]);
        }
    }

    ll ans = 0;

    if(c == -1){
        if(n%2 == 0){
            if(part[center.back()] < n/2){
                ans = 1;
            } 
        }else{
            if(part[center.back()] <= n/2){
                ans = 1;
            } 
        } 
    }else{
        if(part[c] > n/2){
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
    vector<int> parent = getParents(graph);

    vector<ll> ans;

    vector<int> Acopy = A, Bcopy = B; 
    //process default
    ll tempD = 0;
    for(int i = 0; i<Acopy.size(); i++){
        for(int j = 0; j<Bcopy.size(); j++){
            ll temp = winStrategy(A[i], B[j], graph, parent, part);
            tempD += temp;
        }
    }
    ans.PB(tempD);

    //process queyrys
    for(int o = 0; o<q; o++){
        tempD = 0; // getting the diffrence
        if(get<0>(query[o]) == 'A'){
            for(int i = 0; i<Bcopy.size(); i++){
                ll temp = winStrategy(get<2>(query[o]), B[i], graph, parent, part);
                tempD += temp;
            }
            if(get<1>(query[o]) == '-'){
                tempD *= -1;
            }
        }else{
            for(int i = 0; i<Acopy.size(); i++){
                ll temp = winStrategy(A[i], get<2>(query[o]), graph, parent, part);
                tempD += temp;
            }
            if(get<1>(query[o]) == '-'){
                tempD *= -1;
            }
        }
        ans.PB(tempD + ans[o]);
    }   

    return ans;
}

vector<ll> solve(){

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
        vector<ll> ansB = brute();
        vector<ll> ansS = solve();
        for(int i = 0; i<q+1; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
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