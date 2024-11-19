#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <stack>

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
    for(int i = 0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
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

vector<int> getCenter(vector<vector<int>>& graph){
    vector<int> dp(n+1, 0);

    stack<pair<int,bool>> S;
    S.push(MP(1,false));
    vector<bool> vis(n+1, false);

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();
        if(b){
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                dp[v] += dp[cur];
            }
            dp[v]++;
        }
        if(vis[v]){
            continue;
        }

        vis[v] = true;
        S.push(MP(v,true));
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                S.push(MP(cur, false));
            }
        }
    }

    vector<int> centroids;

    queue<int> Q;
    vis.assign(n+1, false);
    vis[1] = true;
    Q.push(1);
    
    while(!Q.empty()){
        int v = Q.front();
        vis[v] = true;
        Q.pop();

        int maxim = n-dp[v];
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(vis[cur]){
                maxim = max(n-dp[cur]+1, maxim);
            }else{
                maxim = max(dp[cur], maxim);
                Q.push(cur);
            }
        }
        if(maxim <= n/2){
            centroids.PB(v);
        }
    }

    return centroids;
}

vector<int> getDistance(vector<vector<int>>& graph, vector<int>& center){
    vector<int> ans(n+1, 0);
    vector<bool> vis(n+1, false);

    queue<int> Q;
    for(int i = 0; i<center.size(); i++){
        vis[center[i]] = true;
        Q.push(center[i]);
    }

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i =0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                vis[cur] = true;
                ans[cur] = ans[v] +1;
                Q.push(cur);
            }
        }
    }

    return ans;
}

int left(int v){
    return v*2;
}

int right(int v){
    return v*2+1;
}

int parent(int v){
    return v/2;
}

int leaf(int v, int R){
    return v+R;
}

pair<vector<int>,int> buildTree(int len){
    int R = 0;
    int depth = 0;

    while((1<<depth) < len){
        R += (1<<depth);
        depth++;
    }

    vector<int> segTree(R+ (1<<depth)+1, 0);

    return MP(segTree, R);
}

ll sumRange(int l, int r, int R, vector<int>& segTree){
    int vL = leaf(l, R);
    int vR = leaf(r, R);

    ll ans = 0;
    ans += segTree[vL];
    if(vL != vR) ans += segTree[vR];

    while(parent(vL) != parent(vR)){
        if(left(parent(vL)) == vL){
            ans += segTree[right(parent(vL))];
        }
        if(right(parent(vR)) == vR){
            ans += segTree[left(parent(vR))];
        }
        vL = parent(vL);
        vR = parent(vR);
    }

    return ans;
}

void updateTree(int v, int R, int val, vector<int>& segTree){
    int V = leaf(v, R);

    while(V >= 1){
        segTree[V] += val;
        V = parent(V);        
    }
}

vector<ll> solve(){
    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    //get centorids
    vector<int> center = getCenter(graph);

    //get distance
    vector<int> distance = getDistance(graph, center);

    //get seg tree
    vector<bool> inA(n+1, false), inB(n+1, false);
    pair<vector<int>, int> segTreeA = buildTree(n), segTreeB = buildTree(n);
    for(int i = 0; i< A.size() ;i++){
        updateTree(distance[A[i]], segTreeA.second, 1, segTreeA.first);
        inA[A[i]] = true;
    }
    for(int i = 0; i< B.size() ;i++){
        updateTree(distance[B[i]], segTreeB.second, 1, segTreeB.first);
        inB[B[i]] = true;
    }

    //get the deafult
    vector<ll> ans;
    ll tempD = 0;
    for(int i = 0; i<A.size(); i++){
        ll temp = sumRange(distance[A[i]], n, segTreeB.second, segTreeB.first);
        if(inB[A[i]]) temp--;
        tempD += temp;
    }
    if(n == 2) tempD = 0;
    ans.PB(tempD);

    //process queries
    for(int o = 0; o<q; o++){
        tempD = 0; // getting the diffrence
        if(get<0>(query[o]) == 'A'){
            tempD = sumRange(distance[get<2>(query[o])], n, segTreeB.second, segTreeB.first);
            if(inB[get<2>(query[o])]) tempD--;

            int type = 1;
            inA[get<2>(query[o])] = true;
            if(get<1>(query[o]) == '-'){
                tempD *= -1;
                type *= -1;
                inA[get<2>(query[o])] = false;
            }

            updateTree(distance[get<2>(query[o])], segTreeA.second, type, segTreeA.first);
        }else{
            tempD = sumRange(1, distance[get<2>(query[o])], segTreeA.second, segTreeA.first);
            if(inA[get<2>(query[o])]) tempD--;

            int type = 1;
            inB[get<2>(query[o])] = true;
            if(get<1>(query[o]) == '-'){
                tempD *= -1;
                type *= -1;
                inB[get<2>(query[o])] = false;
            }

            updateTree(distance[get<2>(query[o])], segTreeB.second, type, segTreeB.first);
        }
        ans.PB(tempD + ans[o]);
    }   


    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
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