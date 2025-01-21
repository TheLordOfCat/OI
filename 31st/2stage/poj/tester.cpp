#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>
#include <map>

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

    n = rand()%5+5;
    k = rand()%20+1;

    for(int i =0 ; i<n; i++){
        int temp = rand()%(k+5)+1;
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

vector<vector<ll>> recBrute(vector<bool> used, vector<vector<ll>> cups){ 
    bool one = true;
    vector<vector<ll>> ans;
    for(int i = 0; i<n; i++){
        if(!used[i]){
            one = false;
            vector<bool> temp = used;
            temp[i] = true;
            vector<vector<ll>> c = cups;
            if(c.size() == 0){
                ll val = a[i];
                while(val > 0){
                    c.PB(vector<ll>());
                    c.back().PB(i+1);
                    c.back().PB(min(val,k));
                    val -= min(val,k);
                }
            }else if(c.back().size() == 2){
                ll val = a[i];
                if(c.back()[1] < k){
                    c.back().PB(i+1);
                    c.back().PB(min(k-c.back()[1], val));
                    val -= min(k-c.back()[1],val);
                }
                
                while(val > 0){
                    c.PB(vector<ll>());
                    c.back().PB(i+1);
                    c.back().PB(min(val,k));
                    val -= min(val,k);
                }
            }else{
                ll val = a[i];
                while(val > 0){
                    c.PB(vector<ll>());
                    c.back().PB(i+1);
                    c.back().PB(min(val,k));
                    val -= min(val,k);
                }
            }
            vector<vector<ll>> recTemp = recBrute(temp, c);
            if(ans.size() == 0 && recTemp.size() != 0){
                ans = recTemp;
                break;
            }
        }
    }

    if(one){
        if(cups.size() > n){
            return vector<vector<ll>>();
        }else{
            return cups;
        }
    }

    return ans;
}

vector<vector<ll>> brute(){
    vector<bool> used(n, false);
    vector<vector<ll>> ans = recBrute(used, vector<vector<ll>>());
    if(ans.size() != 0){
        while(ans.size() < n){
            ans.PB(vector<ll>());
        }
    }
    return ans;
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
    for(int test = 1; test<=100'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<vector<ll>> ansB = brute();
        vector<vector<ll>> ansS = solve();
        if(ansB.size() != ansS.size() || !verify(ansB) || !verify(ansS)){
            cout<<"ERORR\n";
            cout<<"BRUTE: \n";
            for(int i = 0; i<ansB.size(); i++){
                cout<<ansB[i].size()/2<<" ";
                for(int j = 0; j<ansB[i].size(); j++){
                    cout<<ansB[i][j]<<" ";
                }
                cout<<"\n";
            }
            cout<<"SOLVE: \n";
            for(int i = 0; i<ansS.size(); i++){
                cout<<ansS[i].size()/2<<" ";
                for(int j = 0; j<ansS[i].size(); j++){
                    cout<<ansS[i][j]<<" ";
                }
                cout<<"\n";
            }
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}