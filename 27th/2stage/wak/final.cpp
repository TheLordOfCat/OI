#include <iostream>
#include <vector>
#include <stack>
#include <tuple>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n;
vector<int> w;
vector<PII> edges;

void getData(){
    w.clear(); edges.clear();

    cin>>n;
    w.PB(-INF);
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        w.PB(temp);
    }
    for(int i =0 ; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

tuple<ll,int,vector<int>> solve(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    tuple<ll,int, vector<int>> ansS = solve();

    int a = get<0>(ansS), b = get<1>(ansS); vector<int> c = get<2>(ansS);
    cout<<a<<"\n"<<b<<"\n";
    for(int i = 0; i< c.size(); i++){
        cout<<c[i]<<" ";
    }
    cout<<"\n";


    return 0;
}