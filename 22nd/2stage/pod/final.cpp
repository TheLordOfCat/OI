#include <iostream>
#include <vector>

using namespace std;

using ull = unsigned long long int;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

const int INF = 2'000'000'000;
const int MAXN = 1'000'000;
const int MAXK = 1'000'000;

int n, k;
vector<int> r;

void getData(){
    cin>>n>>k;
    for(int i = 0; i<n; i++){
        int a;
        cin>>a;
        r.PB(a);
    }
}

pair<ull,int> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    pair<ull, int> ansS = solve();
    cout<<ansS.first<<" "<<ansS.second<<"\n";

    return 0;
}