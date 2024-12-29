#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back
#define MT make_tuple
#define PIC pair<int,char>

int n;
vector<tuple<int,int,char>> edges;

void getData(){
    edges.clear();

    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        char c;
        cin>>a>>b>>c;
        edges.PB(MT(a,b,c));
    }
}

vector<string> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<string> ansS = solve();
    cout<<ansS.size()<<"\n";
    for(int i =0 ; i<ansS.size(); i++){
        cout<<ansS[i]<<"\n";
    }

    return 0;
}