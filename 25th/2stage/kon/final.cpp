#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m;
vector<PII> passengers;

const int MOD = 1'000'000'007;

void getData(){
    passengers.clear();

    cin>>m>>n;
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        passengers.PB(MP(a,b));
    }
}

bool comparePasLeft(const PII a, const PII b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first < b.first;
}

bool comparePasRed(const PII a, const PII b){
    if(a.first == b.first){
        return a.second > b.second;
    }
    return a.first < b.first;
}

PII solve(){
    //sort
    vector<PII> pas = passengers;
    sort(pas.begin(), pas.end(), comparePasRed);

    //find minimum ops
    vector<PII> marked;
    vector<vector<PII>> group;
    PII curMar = MP(-1,-1);
    for(int i =0 ; i<pas.size(); i++){
        if(pas[i].first >= curMar.second){ //create new group
            curMar = pas[i];
            marked.PB(curMar);
            group.PB(vector<PII>());
            group.back().PB(curMar);
        }else{
            if(pas[i].second < curMar.second){//reduce marked
                curMar = pas[i];
                marked.back() = curMar;
            }
            while(pas[i].second < group.back().back().second){ //reduce group
                group.back().pop_back();
                if(group.back().size() == 0) break;
            }
            group.back().PB(pas[i]);
        }
    }
    int minOps = marked.size();

    //process marked
    vector<int> dp(m+1, 0), dpRange(m+1, 0);
    for(int i = group.back().back().first; i<marked.back().second; i++){
        dp[i]++;
        dpRange[i] = dpRange[i-1] + 1;
    }
    for(int i = marked.size()-2; i>=0; i--){
        for(int j = 1; j<group[i].size(); j++){
            for(int o = group[i][j-1].first; o < group[i][j].first; o++){ //limited parts
                int sol = 0;
                if(group[i][j].second > marked[i+1].first){
                    sol = dpRange[min(group[i][j].second-1,marked[i+1].second-1)];
                }
                dp[o] = sol;
                dpRange[o] = dpRange[o-1]+sol;
            }
        }//the last part
        for(int o = group[i].back().first; o<marked[i].second; o++){
            int sol = dpRange[marked[i+1].second-1];
            dp[o] = sol;
            dpRange[o] = dpRange[o-1]+sol;
        }
    }

    //get ans
    int comb = dpRange[marked[0].second-1];

    return MP(minOps, comb);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    int z;
    cin>>z;
    for(int o = 0; o<z; o++){
        getData();

        PII ansS = solve();
        cout<<ansS.first<<" "<<ansS.second<<"\n";
    }

    return 0;
}