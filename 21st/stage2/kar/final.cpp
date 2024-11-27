#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;

int n;
vector<PII> cards;
int m;
// vector<PII> change;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        cards.PB(MP(a,b));
    }    
    cin>>m;
}

vector<int> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<int> ansS = solve();
    // for(int i = 0; i<m; i++){
    //     if(ansS[i] == 1){
    //         cout<<"TAK\n";
    //     }else{
    //         cout<<"NIE\n";
    //     }
    // }

    return 0;
}