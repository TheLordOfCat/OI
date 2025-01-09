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
    n = rand()%4+3;
    for(int i = 0; i<n; i++){
        int s = rand()%(n-1)+1;
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

bool comparePLL(const PLL a, const PLL b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first < b.first;
}

bool compareLLVEC(const pair<ll,vector<ll>> a, const pair<ll,vector<ll>> b){
    if(a.second.size() == b.second.size()){
        for(int i = 0; i < a.second.size(); i++){
            if(a.second[i] != b.second[i]){
                return a.second[i]< b.second[i];
            }
        }
        return a.first < b.first;
    }
    return a.second.size() < b.second.size();
}

tuple<ll, vector<ll>, vector<PLL>> solve(){
    vector<pair<ll,vector<ll>>> kCopy;
    for(int i = 0; i<k.size(); i++){
        kCopy.PB(MP(i+1,k[i]));
    }

    for(int i = 0; i<kCopy.size(); i++){
        kCopy[i].second.PB(i+1);
        sort(kCopy[i].second.begin(), kCopy[i].second.end());
    }

    sort(kCopy.begin(), kCopy.end(), compareLLVEC);

    //get citizen locations
    tuple<ll,vector<ll>,vector<PLL>> ans = MT(0, vector<ll>(n+1, -1), vector<PLL>());
    for(int i = 0; i<n; i++){
        if(get<1>(ans)[kCopy[i].first] == -1){
            get<0>(ans)++;
            get<1>(ans)[kCopy[i].first] = get<0>(ans);
        }   
        if(i<n-1){
            if(kCopy[i].second.size() == kCopy[i+1].second.size()){
                bool ok = true;
                for(int  j =0; j<kCopy[i].second.size(); j++){
                    if(kCopy[i].second[j] != kCopy[i+1].second[j]){
                        ok = false;
                        break;
                    }
                }
                if(ok){
                    get<1>(ans)[kCopy[i+1].first] = get<1>(ans)[kCopy[i].first];
                }
            }
        }
    }

    //get graph
    vector<PLL> edges;
    for(ll i = 0; i<kCopy.size(); i++){
        for(int j = 0; j<kCopy[i].second.size(); j++){
            int v1 = get<1>(ans)[kCopy[i].second[j]], v2 = get<1>(ans)[kCopy[i].first];
            if(v1 != v2){
                edges.PB(MP(min(v1, v2), max(v1, v2)));
            }
        }
    }

    sort(edges.begin(), edges.end(), comparePLL);

    if(edges.size() > 0) get<2>(ans).PB(edges.front());
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
    for(int test = 1; test<=1'000'000'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        tuple<ll, vector<ll>, vector<PLL>> ansB = brute();
        tuple<ll, vector<ll>, vector<PLL>> ansS = solve();
        bool ok = true;
        if(get<0>(ansB) != get<0>(ansS)){
           ok = false; 
        }else{
            vector<bool> used(n+1, false);
            vector<int> tran(n+1, -1);
            for(int i = 1; i<=n; i++){
                if(!used[i]){
                    used[i] = true;
                    int typeB = get<1>(ansB)[i];
                    int typeS = get<1>(ansS)[i];
                    tran[typeB] = typeS;
                    for(int j = 1; j<=n; j++){
                        if(get<1>(ansB)[j] == typeB){
                            if(get<1>(ansS)[j] != typeS){
                                ok = false;
                                break;
                            }
                        }
                    }
                    if(!ok) break;
                }
            }
            if(!ok) break;
            if(get<2>(ansB).size() != get<2>(ansS).size()){
                ok = false;
            } else{
                vector<PLL> translated;
                for(int i =0; i<get<2>(ansB).size(); i++){
                    int v1 = tran[get<2>(ansB)[i].first], v2 =tran[get<2>(ansB)[i].second];
                    translated.PB(MP(min(v1,v2), max(v1,v2)));
                }
                sort(translated.begin(), translated.end());
                sort(get<2>(ansS).begin(), get<2>(ansS).end());
                for(int i = 0; i<get<2>(ansB).size(); i++){
                    if(translated[i].first != get<2>(ansS)[i].first || translated[i].second != get<2>(ansS)[i].second){
                        ok = false;
                        break;
                    }
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