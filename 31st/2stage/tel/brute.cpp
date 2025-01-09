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
#define MP make_pair

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
    vector<vector<ll>> kCopy = k;

    tuple<ll,vector<ll>, vector<PLL>> ans = MT(0, vector<ll>(n+1, -1), vector<PLL>());
    for(int i = 0; i< kCopy.size(); i++){
        if(get<1>(ans)[i+1] == -1){
            get<0>(ans)++;
            get<1>(ans)[i+1] = get<0>(ans);
        }
        for(int j = i+1; j<n; j++){
            
            vector<int> con(n+1, 0);
            for(int o = 0; o<kCopy[i].size(); o++){
                con[kCopy[i][o]]++;  
            }
            for(int o = 0; o<kCopy[j].size(); o++){
                con[kCopy[j][o]]++;  
            }

            bool ok = true;
            for(int o = 1; o<con.size(); o++){
                if(con[o] == 1 && o != i+1 && o != j+1){
                    ok = false;
                    break;
                }
            }

            if(con[i+1] != 1 || con[j+1] != 1) ok = false;
            
            if(ok){
                get<1>(ans)[j+1] = get<1>(ans)[i+1]; 
            }
        }    
    }

    //create graph
    vector<vector<bool>> graph(n+1,vector<bool>(n+1, false));

    for(int i = 0; i<kCopy.size(); i++){
        for(int j = 0; j<kCopy[i].size(); j++){
            int v1 = get<1>(ans)[kCopy[i][j]], v2 = get<1>(ans)[i+1];
            if(v1 != v2){
                if(!graph[v1][v2]){
                    graph[v1][v2] = true;
                    graph[v2][v1] = true;
                    get<2>(ans).PB(MP(min(v1,v2), max(v1,v2)));
                }
            }
        }
    }

    return ans;
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
        cout<<get<0>(ansB)<<"\n";
        for(int j  =1;j <get<1>(ansB).size(); j++){
            cout<<get<1>(ansB)[j]<<" ";
        }
        cout<<"\n";
        for(int j = 0; j<get<2>(ansB).size(); j++){
            cout<<get<2>(ansB)[j].first<<" "<<get<2>(ansB)[j].second<<"\n";
        }

    }

    return 0;
}