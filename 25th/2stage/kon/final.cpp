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
    vector<PII> pas = passengers;
    sort(pas.begin(), pas.end(), comparePasRed);
    vector<vector<int>> groups;
    vector<PII> boundary;
    
    //reduction
    vector<PII> rightBoundary;
    vector<PII> redPas;
    for(int i = 0; i<pas.size(); i++){
        if(rightBoundary.size() != 0 ){
            while(pas[i].second <= rightBoundary.back().second){
                rightBoundary.pop_back();
                if(rightBoundary.size() == 0){
                    break;
                }
            }
        }
        rightBoundary.PB(pas[i]);
    }

    while(rightBoundary.size() != 0 ){
        redPas.PB(rightBoundary.back());
        rightBoundary.pop_back();
    }

    pas = redPas;

    //iterating from left to right
    sort(pas.begin(), pas.end(), comparePasLeft);
    int left = pas.front().first;
    int right = pas.front().second;
    vector<int> g;
    for(int i = 0; i < pas.size(); i++){
        PII cur = pas[i];
        if(cur.first < right){
            left = cur.first;
            g.push_back(i);
        }else{
            groups.PB(g);
            boundary.PB(MP(left,right));
            g.clear();

            g.push_back(i);
            left = cur.first;
            right = cur.second;
        }
    }

    groups.PB(g);
    boundary.PB(MP(left,right));
    g.clear();

    //dp by groups
    vector<ll> dp(m+2, 0);
    vector<ll> sufDp(m+1, 0);
    for(int i = boundary.back().first; i< boundary.back().second; i++){
        dp[i] = 1;
    }
    sufDp[boundary.back().second-1] = dp[boundary.back().second-1];
    for(int i = boundary.back().second-2; i >= pas[groups.back().front()].first; i--){
        sufDp[i] = (dp[i]+sufDp[i+1])%MOD;
    }

    for(int i = groups.size()-2; i>=0; i--){
        vector<int> gr = groups[i];
        vector<int> parts;
        for(int j =0 ; j<gr.size(); j++){
            parts.PB(pas[gr[j]].first);
        }
        parts.PB(boundary[i].second);

        int ind = 0;
        for(int j = parts.front(); j<parts.back(); j++){
            while(j >= parts[ind+1]){
                ind++;
            }
            if(ind < gr.size()-1){
                dp[j] = (sufDp[boundary[i+1].first] - sufDp[pas[gr[ind+1]].second])%MOD;
            }else{
                dp[j] = (sufDp[boundary[i+1].first])%MOD;
            }
        }
        sufDp[boundary[i].second-1] = dp[boundary[i].second-1];
        for(int j = boundary[i].second-2; j>= pas[gr.front()].first; j--){
            sufDp[j] = (dp[j] + sufDp[j+1])%MOD;
        }  
    }
    
    //getting the ans
    pair<int,ll> ans = MP(groups.size(), sufDp[pas.front().first]%MOD);

    return ans;
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