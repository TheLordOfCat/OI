#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define PLL pair<ll,ll>

int n;
ll k;
vector<ll> a;

void getData(){
    a.clear();

    cin>>n>>k;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
    }
}

void getRandom(){
    a.clear();

    srand(time(0));

    n = rand()%10+1;
    k = rand()%20+1;

    for(int i =0 ; i<n; i++){
        int temp = rand()%(k+10)+1;
        a.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<k<<"\n";
    for(int i = 0; i<n; i++){
        cout<<a[i]<<"\n";
    }
}



vector<vector<ll>> solve(){
    vector<vector<ll>> ans;
    vector<ll> aCopy = a;

    //reduce to modulo
    for(int i =0 ; i<aCopy.size(); i++){
        while(aCopy[i] >= k){
            aCopy[i] -= k;
            ans.PB(vector<ll>());
            ans.back().PB(i+1);
            ans.back().PB(k);
        }
    }

    //fill
    multiset<ll> S;
    multimap<ll,ll> M;
    for(int i = 0; i<aCopy.size(); i++){
        S.insert(aCopy[i]);
        M.insert(MP(aCopy[i],i+1));
    }

    while(!S.empty()){
        auto itr = S.end();
        itr--;
        ll val = k - *itr;
        auto sec = S.lower_bound(val);
        if(sec != S.end()){
            ans.PB(vector<ll>());
            auto temp1 = M.find(*itr);
            auto temp2 = M.find(*sec);
            ans.back().PB(temp1->second);
            ans.back().PB(*itr);
            ans.back().PB(temp2->second);
            ans.back().PB(*sec);
            M.erase(temp1);
            M.erase(temp2);
            S.erase(itr);
            S.erase(sec);
        }else{
            ans.PB(vector<ll>());
            auto temp = M.find(*itr);
            ans.back().PB(temp->second);
            ans.back().PB(*itr);
            M.erase(temp);
            S.erase(itr);
        }
    }

    //check
    if(ans.size() > n){
        return vector<vector<ll>>();
    }
    return ans;
}

bool verify(vector<vector<ll>> cups){
    if(cups.size() == 0) return true;

    vector<ll> levels(n+1, 0);
    for(int i = 0; i<cups.size(); i++){
        if(cups[i].size() == 2){
            if(cups[i][1] > k) return false;
            levels[cups[i][0]] += cups[i][1];
        }else{
            if(cups[i][1] + cups[i][3] > k) return false;
            levels[cups[i][0]] += cups[i][1];
            levels[cups[i][2]] += cups[i][3];
        }
    }

    for(int i = 1; i<levels.size(); i++){
        if(levels[i] != a[i-1]){
            return false;
        }
    }    

    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();

    int op = 1;
    for(int test = 1; test<=1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<vector<ll>> ansS = solve();

        for(int i = 0; i<ansS.size(); i++){
            cout<<ansS[i].size()/2<<" ";
            for(int j = 0; j<ansS[i].size(); j++){
                cout<<ansS[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

    return 0;
}