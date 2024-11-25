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

vector<bool> solve(){
    //create graph


    //traverse graph

    
}   

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    vector<bool> ansS = solve();
    for(int j = 0; j<k; j++){
        if(ansS[j] == false){
            cout<<"NIE\n";
        }else{
            cout<<"TAK\n";
        }
    }

    return 0;
}