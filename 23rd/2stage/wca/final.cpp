#include<iostream>
#include<vector>

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

    if(lastZero <= 0){
        return MP(num, 0);
    }
    
    int ans = num>>(lastZero-1);
    return MP(ans, lastZero);
}

int nullify(int num){
    if(num == 1){
        return 1;
    }
    int pos = firstOnePos(num);
    int ans = pos;
    return ans;
}

ll solve(){
    ll ans = 0;

    //reduce to 2^k - 1
    vector<int> proces = a;
    for(int i =0 ; i <proces.size(); i++){
        PII temp = reduce(proces[i]);
        proces[i] = temp.first;
        ans += temp.second*2;
    }

    //finish
    int turn = 0;
    for(int i =0 ; i<proces.size(); i++){
        int temp = nullify(proces[i]);
        if(turn == 0){
            
        }else{

        }
        ans += temp;
        turn = (turn+1)%2;
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