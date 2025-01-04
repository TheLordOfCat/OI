#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <stack>
#include <set>

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

    vector<bool> bA(n+1, false), bB(n+1, false);
    for(int i = 0; i<A.size(); i++){
        bA[A[i]] = true;
    }
    for(int i = 0; i<B.size(); i++){
        bB[B[i]] = true;
    }
    for(int i = 0; i<q; i++){
        int type = rand()%2+1;
        if((type == 1 && curA != 0 && curB != 0) || curA == n || curB == n){
            int s = rand()%2+1;
            if((s == 1 && curA != 0) || curB == 0){
                int v = rand()%n+1;
                while(!bA[v]){
                    v = rand()%n+1;
                }
                query.PB(MT('A','-',v));
                curA--;
                bA[v] = false;
            }else{
                int v = rand()%n+1;
                while(!bB[v]){
                    v = rand()%n+1;
                }
                query.PB(MT('B','-',v));
                curB--;
                bB[v] = false;
            }
        }else{
            int s = rand()%2+1;
            if((s == 1 && curA != n) || curB == n){
                int v = rand()%n+1;
                while(bA[v]){
                    v = rand()%n+1;
                }
                query.PB(MT('A','+',v));
                curA++;
                bA[v] = true;
            }else{
                int v = rand()%n+1;
                while(bB[v]){
                    v = rand()%n+1;
                }
                query.PB(MT('B','+',v));
                curB++;
                bB[v] = true;
            }
        }
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

vector<int> getCentroidBrute(vector<vector<int>> &graph){
    vector<int> ans;
    for(int i = 1; i<=n; i++){
        bool ok = true;
        for(int j = 0; j<graph[i].size(); j++){
            int cur = graph[i][j];

            int count = 1;
            queue<int> Q;
            Q.push(cur);
            vector<bool>used(n+1, false);
            used[cur] = true;
            used[i] = true;

            while(!Q.empty()){
                int v = Q.front();
                Q.pop();

                for(int o = 0; o<graph[v].size(); o++){
                    int c = graph[v][o];
                    if(!used[c]){
                        used[c] = true;
                        count++;
                        Q.push(c);
                    }
                }
            }
            if(count > n/2) ok = false;

            if(!ok) break;
        }
        if(ok){
            ans.PB(i);
        }
    }

    return ans;
}

vector<int> getDist(vector<int> centorid, vector<vector<int>> &graph){
    queue<int>Q;
    vector<int> ans(n+1, -1);
    ans[centorid.front()] = 0;
    ans[centorid.back()] = 0;
    Q.push(centorid.front());
    if(centorid.size() > 1) Q.push(centorid.back());
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i =0 ; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(ans[cur] == -1){
                ans[cur] = ans[v] +1;
                Q.push(cur);
            }
        }
    }
    return ans;
}

bool processQuery(int a, int b, vector<int>& dist, vector<int>& centroid){
    if(centroid.size() == 1){
        if(dist[a] <= dist[b]){
            return true;
        }
        return false;   
    }else{
        if(dist[a] < dist[b]){
            return true;
        }
        return false;   
    }
}

vector<ll> brute(){
    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    //find centroid
    vector<int> centroid = getCentroidBrute(graph);

    //get dist to centoid
    vector<int> dist = getDist(centroid, graph);

    //process base request
    vector<ll> ans;
    ll firstComb =  0;
    for(int i = 0; i<A.size(); i++){
        for(int j = 0; j<B.size(); j++){
            bool pos = processQuery(A[i], B[j], dist, centroid);
            if(pos) firstComb++;
        }
    }
    ans.PB(firstComb);

    //process queries
    vector<bool> usedA(n+1, false), usedB(n+1, false);
    for(int i = 0; i<A.size(); i++) usedA[A[i]] = true;
    for(int i = 0; i<B.size(); i++) usedB[B[i]] = true;

    for(int o = 0; o<q; o++){
        char s = get<0>(query[o]), t = get<1>(query[o]);
        int val = get<2>(query[o]);
        //update set
        if(s == 'A'){
            if(t == '+'){
                usedA[val] = true;
            }else{
                usedA[val] = false;
            }
        }else{
            if(t == '+'){
                usedB[val] = true;
            }else{
                usedB[val] = false;
            }
        }

        ll comb = 0;
        for(int i = 1; i<=n; i++){
            if(usedA[i]){
                for(int j = 1; j<=n; j++){
                    if(usedB[j]){
                        bool pos = processQuery(i, j, dist, centroid);
                        if(pos) comb++;
                    }
                }
            }
        }

        ans.PB(comb);
    }

    return ans;
}

vector<int> getCentoid(vector<vector<int>> &graph){
    vector<int> parent(n+1, 0);
    vector<int> graphDown(n+1, 0), graphUp(n+1, 0);
    //get graphDown
    stack<pair<int,bool>> S;
    S.push(MP(1, false));

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();
        if(b){
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                if(cur != parent[v]){
                    graphDown[v] += graphDown[cur];
                }
            }
            graphDown[v]++;
            continue;
        }

        S.push(MP(v,true));
        for(int i = 0 ; i<graph[v].size(); i++){
            int cur=  graph[v][i];
            if(cur != parent[v]){
                S.push(MP(cur,false));
                parent[cur] = v;
            }
        }
    }

    //getGraphUp
    queue<int> Q;
    Q.push(1);
    graphUp[1] = 1;
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        ll sum = graphUp[v];
        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != parent[v]){
                sum += graphDown[cur];
            }
        }

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(cur != parent[v]){
                graphUp[cur] = sum - graphDown[cur]+1;
                Q.push(cur);
            }
        }
    }

    //get centroids
    vector<int> ans;
    for(int i = 1; i<=n; i++){
        bool ok = true;
        for(int j = 0; j<graph[i].size();j ++){
            int cur = graph[i][j];
            if(cur == parent[i]){
                if(graphUp[i]-1 > n/2){
                    ok = false;
                    break;
                }
            }else{
                if(graphDown[cur] > n/2){
                    ok = false;
                    break;
                }
            }
            if(!ok) break;
        }
        if(ok){
            ans.PB(i);
        }
    }
    return ans;
}

vector<ll> solve(){
    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i< edges.size(); i++){
        int a=  edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    //get centorid
    vector<int> centroid = getCentoid(graph);

    //get dist
    vector<int> dist = getDist(centroid, graph);

    //process base
    vector<ll> ans;
    ll countWins = 0;
    set<ll> sA, sB;
    for(int i = 0; i<A.size(); i++){
        sA.insert(dist[A[i]]);
    }
    for(int i = 0; i<B.size(); i++){
        sB.insert(dist[B[i]]);
    }
    for(int i = 0; i<A.size(); i++){
        auto itr = sB.lower_bound(dist[A[i]]);
            ll temp = distance(itr, sB.end());
            countWins += temp;  
    }

    ans.PB(countWins);
    
    //process queries
    for(int o =  0; o<q; o++){
        char s = get<0>(query[o]), t = get<1>(query[o]);
        int val = get<2>(query[o]);

        if(s == 'A'){
            if(t == '+'){
                sA.insert(dist[val]);
                auto itr = sB.lower_bound(dist[val]);
                ll temp = distance(itr, sB.end());
                countWins += temp;  
            }else{
                sA.erase(dist[val]);
                auto itr = sB.lower_bound(dist[val]);
                ll temp = distance(itr, sB.end());
                countWins -= temp;
            }
        }else{
            if(t == '+'){
                sB.insert(dist[val]);
                auto itr = sA.lower_bound(dist[val]);
                ll temp = distance(sA.begin(), itr);
                countWins += temp;     
            }else{
                sB.erase(dist[val]);
                auto itr = sA.lower_bound(dist[val]);
                ll temp = distance(sA.begin(), itr);
                countWins -= temp;     
            }
        }
        ans.PB(countWins);
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