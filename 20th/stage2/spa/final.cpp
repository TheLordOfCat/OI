#include<iostream>
#include <vector>
#include <queue>

using namespace std;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

using ll = long long int;

ll n, k;
ll start = 0, finish = 0;
vector<ll> removed;



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    bool ansS = solve();
    if(ansS){
        cout<<"TAK\n";
    }else{
        cout<<"NIE\n";
    }

    return 0;
}