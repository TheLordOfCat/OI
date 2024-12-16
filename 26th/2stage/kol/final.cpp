#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <tuple>

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

using namespace std;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

int n, r;
vector<int> t;
vector<tuple<int,int,int>> edges;
int q;
vector<tuple<int,int,int>> query;

void getData(){
    t.clear(); edges.clear(); query.clear();

    cin>>n>>r;
    t.PB(-1);
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        t.PB(temp);
    }
    for(int i = 0; i<n-1; i++){
        int a, b, c;
        cin>>a>>b>>c;
        edges.PB(MT(a,b,c));
    }
    cin>>q;
    for(int i =0; i<q; i++){
        int a, b, c;
        cin>>a>>b>>c;
        query.PB(MT(a,b,c));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<r<<"\n";
    for(int i = 0; i<t.size(); i++){
        cout<<t[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    cout<<q<<"\n";
    for(int i = 0; i<query.size(); i++){
        int a = get<0>(query[i]), b = get<1>(query[i]), c = get<2>(query[i]);
        cout<<a<<" "<<b<<" "<<c<<"\n";
    }
    cout<<"\n";

    return ;
}

vector<int> numerate(vector<vector<PII>>& graph){
    stack<int> S;
    S.push(1);

    int totalOrder = 2;

    vector<int> order(n+1, -1);
    order[1] = 1;
    while(!S.empty()){
        int v = S.top();
        S.pop();

        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            if(order[cur.first] == -1){
                order[cur.first] = totalOrder;
                totalOrder++;
                S.push(cur.first);
            }
        }
    }

    return order;
}

bool customPairComp(PII a, PII b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first < b.first;
}

void process(PII con, vector<bool>& used, vector<int>& poi, vector<ll>& ans, vector<int>& order){

}

vector<ll> solve(){
    //create graph
    vector<vector<PII>> graph(n+1, vector<PII>());
    for(int i =0 ; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graph[b].PB(MP(a,c));
    }

    //numerate
    vector<int> order = numerate(graph);

    vector<ll> ans(q, -1);

    vector<PII> qS;
    for(int i =0; i<query.size(); i++){
        int c = get<2>(query[i]);
        qS.PB(MP(i,c));
    }
    sort(qS.begin(), qS.end(), customPairComp);

    //process query
    PII con = MP(qS.front().second, 1);
    vector<bool> used(n+1, false);
    vector<int> pointsOfInterst; 
    for(int i = 1; i<qS.size(); i++){
        if(qS[i].second == con.first){
            con.second++;
        }else{
            process(con,used,pointsOfInterst,ans, order);
        }
    }
    process(con,used,pointsOfInterst,ans, order);    

    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    vector<ll> ansS = solve();

    for(int j = 0; j<ansS.size(); j++){
        cout<<ansS[j]<<"\n";
    }

    return 0;
}