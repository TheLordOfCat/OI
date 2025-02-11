#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
#include <set>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PLL pair<ll,ll>
#define PB push_back
#define MT make_tuple

int n, k;
vector<tuple<int,int,int>> kon;

void getData(){
    kon.clear();
    cin>>n>>k;
    for(int i =0 ; i<k; i++){
        int a,l, d;
        cin>>a>>l>>d;
        kon.PB(MT(a,l,d));
    }
}

void getRandom(){
    kon.clear();
    n = rand()%10+1;
    k = rand()%10+1;

    for(int i =0 ; i<k; i++){
        int a = rand()%n+2; 
        int d = rand()%n+1;
        int l = rand()%10+1;
        while(a + (l-1)*d > n){
            l--;
        }
        if(l == 1) d = 1;

        kon.PB(MT(a,l,d));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<k<<"\n";
    for(int i = 0; i<kon.size(); i++){
        int a = get<0>(kon[i]), l = get<1>(kon[i]), d = get<2>(kon[i]);
        cout<<a<<" "<<l<<" "<<d<<"\n";
    }
}

vector<int> brute(){
    vector<int> ans(n+1, 0);
    for(int i = 0; i<k; i++){
        int a = get<0>(kon[i]), l = get<1>(kon[i]), d = get<2>(kon[i]);
        for(int j = a; j<=a+(l-1)*d; j += d){
            ans[j]++;
        }
    }
    return ans;
}

vector<int> solve(){
    vector<int> ans(n+1, 0);

    vector<multimap<int, int>> change(n+1, multimap<int, int>());
    for(int i = 0; i<k; i++){
        int a = get<0>(kon[i]), l = get<1>(kon[i]), d = get<2>(kon[i]);
        auto itr = change[a].find(d);
        if(itr != change[a].end()){
            itr->second++;
        }else{
            change[a].insert(MP(d,1));
        }
        itr = change[a + (l-1)*d].find(d);
        if(itr != change[a].end()){
            itr->second--;
        }else{
            change[a].insert(MP(d,-11));
        }
    }

    vector<vector<PII>> pos;

    for(int i = 1; i<=n; i++){
        for(int j  =0; j<pos[i].size(); j++){
            ans[i] += pos[i][j].second;
            auto add = change[i].find(pos[i][j].first);
            if(add != change[i].end()){
                if(add ->second + pos[i][j].second > 0){
                    pos[i+pos[i][j].first].PB(MP(pos[i][j].first, add ->second + pos[i][j].second));                
                }
                change[i].erase(add);
            }else{
                pos[i+pos[i][j].first].PB(pos[i][j]);
            }
        }   
        for(auto itr = change[i].begin(); itr != change[i].end(); itr++){
            pos[i+itr->first].PB(MP(itr->first, itr->second));
        }
        pos[i].clear();
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}