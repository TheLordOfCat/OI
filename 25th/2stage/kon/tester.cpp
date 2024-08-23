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

    m = rand()%15+10;
    n = rand()%5+4;

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
    if(a.first == b.first){
        return a.second > b.second;
    }
    return a.first < b.first;
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

    int op = 0;
    int z = 1;
    // cin>>z;
    for(int o = 0; o<z; o++){
        for(int test = 1; test<=100'000; test++){
            cout<<"TEST nr."<<test<<" = ";
            if(op == 1){
                getData();
            }else{
                getRandom();
            }
            // printData();
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