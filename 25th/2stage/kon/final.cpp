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

bool comparePasRed(const PII a, const PII b){
    if(a.first == b.first){
        return a.second > b.second;
    }
    return a.first < b.first;
}

bool compareRanges(const vector<int> a, const vector<int> b){
    if(a[0] == b[0]){
        if(a[1] == b[1]){
            return a[2]<b[2];
        }
        return a[1]<b[1];
    }
    return a[0]<b[0];
}

PII solve(){
    //sort
    vector<PII> pas = passengers;
    sort(pas.begin(), pas.end(), comparePasRed);

    //find minimum ops
    vector<PII> reduced;
    reduced.PB(pas[0]);
    PII curMar = MP(-1,-1);
    for(int i =1; i<pas.size(); i++){
        while(pas[i].second <= reduced.back().second){ //reduce group
            reduced.pop_back();
            if(reduced.size() == 0) break;
        }
        reduced.PB(pas[i]);
    }

    //getting new groups
    vector<int> marked;
    vector<vector<int>> range;
    for(int i = 0; i<reduced.size(); i++){
        if(reduced[i].first >= curMar.second){ //create new group
            curMar = reduced[i];
            marked.PB(i);
        }
        range.PB({reduced[i].first, 1,i});
        range.PB({reduced[i].second, -1,i});
    }
    int minOps = marked.size();

    sort(range.begin(), range.end(), compareRanges);
    vector<vector<vector<int>>> groups;
    groups.PB(vector<vector<int>>());
    vector<PII> g(reduced.size(), MP(0,0));
    int mark = 0;
    for(int i = 0; i< range.size()-1; i++){
        if(mark <marked.size()){
            if(range[i][2] == marked[mark] && range[i][1] == -1){
                if(mark != marked.size()-1){
                    groups.PB(vector<vector<int>>());
                }
                mark++;
            }else if(range[i][0] >= reduced[marked[mark]].first){
                groups.back().PB({range[i][2], range[i+1][2], range[i+1][0]-range[i][0]});
                if(range[i+1][1] == 1){
                    g[range[i+1][2]].first = groups.back().size();
                }else{
                    g[range[i+1][2]].second = groups.back().size();
                }
            }
        }
    }

    //process groups
    vector<vector<int>> dp(groups.size(), vector<int>());
    for(int i =0 ; i<=groups.back().size(); i++){
        dp.back().PB(0);
    }
    for(int i = groups.back().size()-1; i>=0; i--){
        if(groups.back()[i][1] )
    }
    

    for(int i = groups.size()-2; i>=0; i--){
        dp[i].PB(0);
        for(int j = 0; j<groups[i].size(); j++){
            if(i == 0 && j <groups[i].size()-1){
                if(reduced[groups[i][j][1]].second < reduced[groups[i+1].front()[0]].first){
                    dp[i].PB(0 + dp[i].back());
                }else{
                    int next = dp[i+1][g[groups[i][j][1]].second];
                    dp[i].PB(next*groups[i][j][2] + dp[i].back());
                }
            }else{
                if(reduced[groups[i][j][1]].second <= reduced[groups[i+1].front()[0]].first){
                    int next = dp[i+1].back();
                    dp[i].PB(next*groups[i][j][2] + dp[i].back());
                }else{
                    int next = dp[i+1][g[groups[i][j][1]].second];
                    dp[i].PB(next*groups[i][j][2] + dp[i].back());
                }
            }
        }
    }

    int comb = dp.front().back();
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