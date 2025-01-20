#include <iostream>
#include <vector>
#include <set>
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

vector<vector<ll>> recBrute(vector<bool> used, vector<vector<ll>> cups){ 
    bool one = true;
    vector<vector<ll>> ans;
    for(int i = 0; i<n; i++){
        if(used[i]){
            one = false;
            vector<bool> temp = used;
            temp[i] = true;
            vector<vector<ll>> c = cups;
            if(c.back().size() == 2){
                ll val = a[i];
                if(c.back()[1] < k){
                    c.back().PB(a[i]);
                    c.back().PB(k-c.back()[1]);
                    val -= k-c.back()[1];
                }
                
                while(val > 0){
                    c.PB(vector<ll>());
                    c.back().PB(a[i]);
                    c.back().PB(min(val,k));
                    val -= min(val,k);
                }
            }else{
                ll val = a[i];
                while(val > 0){
                    c.PB(vector<ll>());
                    c.back().PB(a[i]);
                    c.back().PB(min(val,k));
                    val -= min(val,k);
                }
            }
            vector<vector<ll>> recTemp = recBrute(used, c);
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
    return recBrute(used, vector<vector<ll>>());
}

vector<vector<ll>> solve(){

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
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}