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
    for(ll i = 0; i<n; i++){
        ll temp;
        cin>>temp;
        a.PB(temp);
    }
}

void getRandom(){
    a.clear();

    srand(time(0));

    // n = rand()%10+1;
    // k = rand()%20+1;

    n = 1000000;
    k = 10000000001;

    for(ll i =0 ; i<n; i++){
        // int temp = rand()%(k+10)+1;
        ll temp = ((ll)10000000000)-i;
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
    
    vector<PLL> s, b;
    for(ll i = 0; i<a.size(); i++){
        if(a[i] <= k){
            s.PB(MP(a[i],i+1));
        }else{
            b.PB(MP(a[i], i+1));
        }
    }

    while(!b.empty()){
        ans.PB(vector<ll>());
        if(!s.empty()){
            PLL v1 = s.back(), v2 = b.back();
            s.pop_back(); b.pop_back();

            ans.back().PB(v1.second);
            ans.back().PB(v1.first);
            if(k-v1.first != 0){
                ans.back().PB(v2.second);
                ans.back().PB(k-v1.first);
            }

            v2.first -= k-v1.first;
            if(v2.first <= k){
                s.PB(v2);
            }else{
                b.PB(v2);
            }
        }else{
            PLL v = b.back();
            b.pop_back();

            ans.back().PB(v.second);
            ans.back().PB(k);
            v.first -= k;
            if(v.first <= k){
                s.PB(v);
            }else{
                b.PB(v);
            }
        }
    }

    for(int i = 0; i<s.size(); i++){
        ans.PB(vector<ll>());
        ans.back().PB(s[i].second);
        ans.back().PB(s[i].first);
    }

    //check
    if(ans.size() > n){
        return vector<vector<ll>>();
    }
    while(ans.size() < n){
        ans.PB(vector<ll>());
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
        }else if(cups[i].size() == 4){
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

    int op = 0;
    for(int test = 1; test<=1; test++){
        if(op == 0){
            getData();
        }else{
            getRandom();
        }
        vector<vector<ll>> ansS = solve();

        // if(!verify(ansS)){
        //     cout<<"ERROR\n";
        //     return 0;
        // }

        if(ansS.size() == 0){
            cout<<"NIE\n";
        }else{
            cout<<"TAK\n";
            for(int i = 0; i<ansS.size(); i++){
                cout<<ansS[i].size()/2<<" ";
                for(int j = 0; j<ansS[i].size(); j++){
                    cout<<ansS[i][j]<<" ";
                }
                cout<<"\n";
            }
        }
    }

    return 0;
}