#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define PB push_back
#define PLL pair<ll,ll>
#define MT make_tuple

int n;
vector<vector<ll>> k;

void getData(){
    k.clear();

    cin>>n;
    for(int i = 0; i<n; i++){
        int s;
        cin>>s;
        vector<ll> vec;
        for(int j =0; j<s; j++){
            ll temp;
            cin>>temp;
            vec.PB(temp);
        }
        k.PB(vec);
    }
}

void getRandom(){
    k.clear();

    srand(time(0));
    n = rand()%10+3;
    for(int i = 0; i<n; i++){
        int s = rand()%n+1;
        vector<bool> used(n+1, false);
        vector<ll> vec;
        for(int j =0; j<s; j++){
            ll temp = rand()%n+1;
            while(used[temp] || temp == i+1){
                temp = rand()%n+1;
            }
            vec.PB(temp);
            used[temp] = true;
        }
        k.PB(vec);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<k[i].size()<<" ";
        for(int j =0 ;j <k[i].size(); j++){
            cout<<k[i][j]<<" ";
        }
        cout<<"\n";
    }
}

tuple<ll, vector<ll>, vector<PLL>> brute(){
    
}

tuple<ll, vector<ll>, vector<PLL>> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        tuple<ll, vector<ll>, vector<PLL>> ansB = brute();
        tuple<ll, vector<ll>, vector<PLL>> ansS = solve();
        bool ok = true;
        if(get<0>(ansB) != get<0>(ansS)) ok = false;
        for(int i = 0; i<get<1>(ansB).size(); i++){
            if(get<1>(ansB)[i] != get<1>(ansS)[i]){
                ok = false;
                break;
            }
        }
        if(get<2>(ansB).size() != get<2>(ansS).size()){
            ok = false;
        }else{
            for(int i = 0; i<get<2>(ansB).size(); i++){
                if(get<2>(ansB)[i] != get<2>(ansS)[i]){
                    ok = false;
                    break;
                }
            }
        }

        if(!ok){
            cout<<"ERROR\n";
            cout<<"BRUTE:\n";
            cout<<get<0>(ansB)<<"\n";
            for(int j  =0;j <get<1>(ansB).size(); j++){
                cout<<get<1>(ansB)[j]<<" ";
            }
            cout<<"\n";
            for(int j = 0; j<get<2>(ansB).size(); j++){
                cout<<get<2>(ansB)[j].first<<" "<<get<2>(ansB)[j].second<<"\n";
            }
            cout<<"SOLVE:\n";
            cout<<get<0>(ansS)<<"\n";
            for(int j  =0;j <get<1>(ansS).size(); j++){
                cout<<get<1>(ansS)[j]<<" ";
            }
            cout<<"\n";
            for(int j = 0; j<get<2>(ansS).size(); j++){
                cout<<get<2>(ansS)[j].first<<" "<<get<2>(ansS)[j].second<<"\n";
            }
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}