#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n;
vector<int> a;

void getData(){
    cin>>n;
    for(int i =0 ; i<n; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
    }
}

int firstOnePos(int num){
    int ans = 0;

    int moves = 0;
    while(num > 0){
        if(num&1){
            ans = moves;
        }
        moves++;
        num = num>>1;
    }

    return ans;
}

PII reduce(int num){
    int pos = firstOnePos(num);
    int lastZero = pos;
    while(lastZero >= 0 && num&(1<<lastZero)){
        lastZero--;
    }

    if(lastZero < 0){
        return MP(1, pos);
    }
    
    int ans = num>>lastZero;
    return MP(ans, lastZero);
}

ll solve(){
    ll ans = 0;

    //reduce to 2^k - 2
    vector<int> proces = a;
    for(int i =0 ; i <proces.size(); i++){
        PII temp = reduce(proces[i]);
        proces[i] = temp.first;
        ans += temp.second*2;
    }

    //finish
    priority_queue<int> Q;
    for(int i =0 ; i<proces.size(); i++){
        Q.push(proces[i]);
    }
    while(!Q.empty()){
        int v = Q.top();
        Q.pop();
        if(v == 1){
            ans += 2;
        }else{

        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    ll ansS = solve();
    cout<<ansS<<"\n"; 

    return 0;
}