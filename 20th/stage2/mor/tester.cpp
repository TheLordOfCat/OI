#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

const int INF = 2'000'000'000;

int n, m, k;
vector<PII> edges;
vector<tuple<int,int,int>> query;

void getData(){
    edges.clear(); query.clear();

    cin>>n>>m>>k;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
    for(int i = 0; i<k; i++){
        int s, t, d;
        cin>>s>>t>>d;
        query.PB(MT(s,t,d));
    }
}

void getRandom(){
    edges.clear(); query.clear();

    srand(time(0));

    n = rand()%100+2;
    m = 0;
    k = 10;

    for(int i = 1; i<=n; i++){
        int con = rand()%4+1;
        for(int j = 1; j <= con; j++){
            if(i + j > n){
                break;
            }
            edges.PB(MP(i,i+j));
            m++;
        }
    }

    for(int i = 0; i<k; i++){
        int s = rand()%n+1;
        int t = rand()%n+1;
        int d = rand()%10+1;
        query.PB(MT(s,t,d));
    }
}

void printData(){
    cout<<"DATA:\n";
    cout<<n<<" "<<m<<" "<<k<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
    for(int i = 0; i<k; i++){
        cout<<get<0>(query[i])<<" "<<get<1>(query[i])<<" "<<get<2>(query[i])<<"\n";
    }
}

bool comp(const PII a, const PII b){
    return a.first< b.first;
}

vector<bool> brute(){
    //get graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    //process queries
    vector<bool> ans;

    for(int o = 0; o<query.size(); o++){
        int s,t,d;
        s = get<0>(query[o]); t = get<1>(query[o]); d = get<2>(query[o]);

        bool found = false;
        queue<PII> Q;
        Q.push(MP(s,0));
        while(!Q.empty()){
            int v = Q.front().first;
            int l = Q.front().second;
            Q.pop();
            if(v == t && d%2 == l%2 ){
                found = true;
            }
            if(d == l){
                continue;
            }
            for(int i = 0; i<graph[v].size(); i++){
                int cur = graph[v][i];
                Q.push(MP(cur, l+1));
            }
        }

        ans.PB(found);
    }

    return ans;
}

vector<vector<int>> traverse(int s, vector<vector<int>>& graph){
    vector<vector<int>> mark(n+1, vector<int>(2, INF));

    queue<PII> Q;
    Q.push(MP(s,0));
    mark[s][0] = true;

    while(!Q.empty()){
        int v = Q.front().first;
        int dist = Q.front().second;
        Q.pop();

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(mark[cur][(dist+1)%2] == INF){
                mark[cur][(dist+1)%2] = dist+1;
                Q.push(MP(cur, dist+1));
            }   
        }
    }

    return mark;
}

bool customCompare(pair<tuple<int,int,int>, int> a, pair<tuple<int,int,int>, int> b){
    if(get<0>(a.first) != get<0>(b.first)){
        return get<0>(a.first) < get<0>(b.first);
    }else if(get<1>(a.first) != get<1>(b.first)){
        return get<1>(a.first) < get<1>(b.first);
    }else if(get<2>(a.first) != get<2>(b.first)){
        return get<2>(a.first) < get<2>(b.first);
    }else{
        return a.second < b.second;
    }
}

vector<bool> solve(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    vector<pair<tuple<int,int,int>, int>> queryS;
    for(int i =0 ; i<query.size(); i++){
        queryS.PB(MP(query[i], i));
    }

    sort(queryS.begin(), queryS.end(), customCompare);

    //process queries
    vector<bool> ans(k, false);
    vector<vector<int>> mark;
    for(int o = 0; o < k; o++){
        int s,t,d;
        s = get<0>(queryS[o].first); t = get<1>(queryS[o].first); d = get<2>(queryS[o].first);

        //traverse graph
        if(o > 0){
            if(get<0>(queryS[o].first) != get<0>(queryS[o-1].first)){
                mark = traverse(s, graph);
            }
        }else{
            mark = traverse(s, graph);
        }

        if(mark[t][d%2] <= d){
            ans[queryS[o].second] = true;
        }
    }

    return ans;
}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test<=1000'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<bool> ansB = brute();
        vector<bool> ansS = solve();
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
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}