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

void getRandom(){
    passengers.clear();
    srand(time(0));

    m = rand()%15+1;
    n = rand()%5+1;

    for(int i = 0; i<n; i++){
        int a = -1, b = -1;
        while(a == b || a == -1|| b == -1){
            a = rand()%m+1;
            b = rand()%m+1;
        }
        if(a>b) swap(a,b);
        passengers.PB(MP(a,b));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<m<<" "<<n<<"\n";
    for(int i =0; i<passengers.size(); i++){
        cout<<passengers[i].first<<" "<<passengers[i].second<<"\n";
    }
}

bool comparePasLeft(const PII a, const PII b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first < b.first;
}

bool comparePasRed(const PII a, const PII b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second > b.second;
}

PII brute(){
    ll minOp, comb = 0;
    vector<PII> pas = passengers;
    sort(pas.begin(), pas.end(), comparePasLeft);

    for(int o = 1; o <= m; o++){

        vector<bool> vis(m, false);
        for(int i= 0; i<o; i++){
            vis[m-i-1] = true;
        }
        
        //iterate through combinations
        do{
            //verifying
            int count = 0;
            for(int i = 0; i<pas.size(); i++){
                for(int j = pas[i].first; j<pas[i].second; j++){
                    if(vis[j-1]){
                        count++;
                        break;
                    }
                }
            }

            if(count == n){
                comb++;
            }

        }while(next_permutation(vis.begin(), vis.end()));

        if(comb > 0){
            minOp = o;
            break;
        }
    }   

    pair<int,int> ans = MP(minOp, comb);

    return ans;
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
            if(pas[i].second <= rightBoundary.back().second){
                rightBoundary.pop_back();
            }
        }
        if(rightBoundary.size() != 0 ){
            if(pas[i].second > rightBoundary.back().second){
                redPas.PB(pas[i]);
                rightBoundary.pop_back();
            }
        }
        rightBoundary.PB(pas[i]);
    }

    if(rightBoundary.size() != 0 ){
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
    vector<int> dp(m+2, 0);
    vector<int> sufDp(m+1, 0);
    for(int i = boundary.back().first; i<= boundary.back().second; i++){
        dp[i] = 1;
    }
    for(int i = boundary.back().second-1; i>= boundary.back().first; i--){
        sufDp[i] = dp[i]+sufDp[i+1];
    }

    for(int i = groups.size()-2; i>=0; i--){
        vector<int> g = groups[i];
        vector<int> parts;
        parts.PB(boundary[i].first);
        for(int j =0 ; j<g.size(); j++){
            parts.PB(pas[g[j]].first);
        }
        parts.PB(boundary[i].second);

        int ind = 0;
        for(int j = parts.front(); j<parts.back(); j++){
            if(j >= parts[ind+1]){
                ind++;
            }
            if(ind < parts.size()-1){
                dp[j] = sufDp[boundary[i+1].first] - sufDp[pas[g[ind]].second];
            }else{
                dp[j] = sufDp[boundary[i+1].first] - sufDp[boundary[i+1].second];
            }
        }
        for(int j = boundary[i].second-1; j>= boundary[i].first; j--){
            sufDp[i] = dp[i]+sufDp[i+1];
        }  
    }
    
    //getting the ans
    pair<int,ll> ans = MP(groups.size(),0);
    for(int i = boundary.front().first; i<boundary.front().second; i++){
        ans.second += dp[i];
        ans.second = ans.second%MOD;
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    int z = 1;
    // cin>>z;
    for(int o = 0; o<z; o++){
        for(int test = 1; test<=1; test++){
            cout<<"TEST nr."<<test<<" = ";
            if(op == 1){
                getData();
            }else{
                getRandom();
            }
            PII ansB = brute();
            PII ansS = solve();
            if(ansB.first != ansS.first || ansB.second != ansS.second){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                cout<<ansB.first<<" "<<ansB.second<<"\n";
                cout<<"SOLVE: ";
                cout<<ansS.first<<" "<<ansS.second<<"\n";
                printData();
                return 0;
            }
            cout<<"CORRECT\n";
        }
    }

    return 0;
}