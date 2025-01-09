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

    vector<vector<bool>> graph(n+1,vector<bool>(n+1, false));

    tuple<ll,vector<ll>, vector<PLL>> ans = MT(0, vector<ll>(n+1, -1), vector<PLL>());
    for(int i = 0; i< kCopy.size(); i++){
        if(get<1>(ans)[i+1] == -1){
            get<0>(ans)++;
            get<1>(ans)[i+1] = get<0>(ans);
        }
        for(int j = i+1; j<kCopy.size(); j++){
            
            vector<int> con(n+1, 0);
            for(int o = 0; o<kCopy[i].size(); o++){
                con[kCopy[i][o]]++;  
            }
            for(int o = 0; o<kCopy[j].size(); o++){
                con[kCopy[j][o]]++;  
            }

            bool ok = true;
            for(int o = 1; o<con.size(); o++){
                if(con[o] == 1){
                    ok = false;
                }
            }
            
            if(!ok){
                if(!graph[get<1>(ans)[i+1]][get<1>(ans)[j+1]]){
                    graph[get<1>(ans)[i+1]][get<1>(ans)[j+1]] = true;
                    graph[get<1>(ans)[j+1]][get<1>(ans)[i+1]] = true;
                    get<2>(ans).PB(MP(get<1>(ans)[i+1], get<1>(ans)[j+1]));
                }
            }else{
                get<1>(ans)[j+1] = get<1>(ans)[i+1]; 
            }
        }    
    }

    return ans;
}

tuple<ll, vector<ll>, vector<PLL>> solve(){
    vector<vector<ll>> kCopy = k;

    for(int i = 0; i<kCopy.size(); i++){
        kCopy[i].PB(i+1);
    }

    sort(kCopy.begin(), kCopy.end());

    //get citizen locations
    tuple<ll,vector<ll>,vector<PLL>> ans = MT(0, vector<ll>(n+1, -1), vector<PLL>());
    for(int i = 0; i<n; i++){
        if(get<1>(ans)[i+1] == -1){
            get<0>(ans)++;
            get<1>(ans)[i+1] = get<0>(ans);
        }   
        if(i<n-1){
            if(kCopy[i].size() == kCopy[i+1].size()){
                int ptrI = 0, ptrJ = 0;
                bool ok = true;
                while(ptrI != kCopy[i].size() || ptrJ != kCopy[i+1].size()){
                    if(kCopy[i][ptrI] == i+1) ptrI++;
                    if(kCopy[i+1][ptrJ] == i+2) ptrJ++;
                    if(kCopy[i][ptrI] != kCopy[i+1][ptrJ]){
                        ok = false;
                        break;
                    }
                    if(!ok) break;
                }
                if(ok){
                    get<1>(ans)[i+1] = get<1>(ans)[i];
                }
            }
        }
    }

    //get graph
    vector<PLL> edges;
    for(ll i = 0; i<kCopy.size(); i++){
        for(int j = 0; j<kCopy[i].size(); j++){
            if(get<1>(ans)[kCopy[i][j]] != get<1>(ans)[i+1]){
                edges.PB(MP(min(kCopy[i][j], i+1), max(kCopy[i][j], i+1)));
            }
        }
    }

    sort(edges.begin(), edges.end());

    get<2>(ans).PB(edges.front());
    for(int i =1 ; i<edges.size(); i++){
        if(edges[i].first != edges[i-1].first || edges[i].second != edges[i-1].second){
            get<2>(ans).PB(edges[i]);
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
        tuple<ll, vector<ll>, vector<PLL>> ansS = solve();
        bool ok = true;
        if(get<0>(ansB) != get<0>(ansS)) ok = false;
        for(int i = 1; i<get<1>(ansB).size(); i++){
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