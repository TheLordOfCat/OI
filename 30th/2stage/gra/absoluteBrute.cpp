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

bool queryBrute(int a, int b, vector<vector<int>> &graph){
    //find path 
    vector<int> previous(n+1, -1);
    previous[a] = 0;
    queue<int> Q;
    Q.push(a);
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        
        for(int i =0 ; i< graph[v].size(); i++){
            int cur = graph[v][i];
            if(previous[cur] == -1){
                previous[cur] = v;
                Q.push(cur);
            }
        }
    }

    //find ans    
    int len = 0;
    int p = previous[b];
    while(p != a){
        len++;
        p = previous[p];
    }

    len/=2;
    vector<bool> usedB(n+1, false);
    p = previous[b];
    for(int i = 0; i<len; i++){
        p = previous[p];
    }
    
    int covert = 1;
    Q.push(b);
    usedB[b] = true;
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();

        for(int i =0 ; i< graph[v].size(); i++){
            int cur= graph[v][i];
            if(!usedB[cur] && cur != p){
                usedB[cur] = true;
                covert++;
                Q.push(cur);
            }
        }
    }

    if(covert >= n/2){
        return false;
    }
    return true;
}

vector<ll> brute(){
    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    //process base base
    vector<ll> ans;
    ll baseComb = 0;
    for(int i =0 ; i<A.size(); i++){
        for(int j = 0;j < B.size();j ++){
            if(A[i] != B[j]){
                bool pos = queryBrute(A[i], B[j], graph);
                if(pos) baseComb++;
            }
        }
    }
    ans.PB(baseComb);

    vector<bool> usedA(n+1, false), usedB(n+1, false);
    for(int i =0; i<A.size(); i++) usedA[A[i]] = true;
    for(int i =0; i<B.size(); i++) usedB[B[i]] = true;
    
    //process quries
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
                    if(usedB[j] && i != j){
                        bool pos = queryBrute(i, j, graph);
                        if(pos) comb++;
                    }
                }
            }
        }

        ans.PB(comb);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        // cout<<"TEST nr."<<test<<" = \n";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<ll> ansB = brute();

        for(int j = 0; j<ansB.size(); j++){
            cout<<ansB[j]<<"\n";
        }
        // cout<<"\n";
    }

    return 0;
}