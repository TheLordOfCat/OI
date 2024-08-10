#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, k;
vector<vector<int>> passen;

void getData(){
    cin>>n>>k;
    for(int i =1; i<n; i++){
        vector<int> vec;
        for(int j =1; j <=n-i; j++){
            int temp;
            cin>>temp;
            vec.PB(temp);
        }
        passen.PB(vec);
    }
}

void getRandom(){
    passen.clear();

    srand(time(0));

    n = rand()%20+1;
    for(int i =1; i<n; i++){
        vector<int> vec;
        for(int j =1; j <=n-i; j++){
            int temp = rand()%10+1;
            vec.PB(temp);
        }
        passen.PB(vec);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<k<<"\n";
    for(int i = 0; i<passen.size(); i++){
        for(int j = 0; j<passen[i].size(); j++){
            cout<<passen[i][j]<<" ";
        }
        cout<<"\n";
    }
}

pair<int,vector<int>> brute(){
    int ansSum = 0;
    vector<int> ans;

    ll totalStations = 1<<n;
    for(ll i = 0; i<totalStations; i++){
        vector<int> stations;
        for(int j = 0; j<n; j++){
            if(i & (1<<j)){
                stations.PB(j+1);
            }
        }

        if(stations.size() != k){
            continue;
        }

        int tempSum = 0;
        vector<vector<bool>> vis(n+1, vector<bool>(n+1, false));

        for(int j = k-1; j>=0; j--){
            int cur = stations[j];

            for(int l = cur-1; l>=0; l--){
                for(int o = cur-1-l; o < passen[l].size(); o++){
                    if(!vis[l][o]){
                        vis[l][o] = true;
                        tempSum += passen[l][o];
                    }
                }
            }
        }

        if(tempSum > ansSum){
            ansSum = tempSum;
            ans = stations;
        }
    }

    return MP(ansSum, ans);
}

pair<int,vector<int>> solve(){
    //creating sum table
    vector<vector<int>> pas(n, vector<int>(n, 0));
    for(int i = 0; i<n; i++){
        for(int j =0; j<n-i-1; j++){
            pas[i+1][n-i-1-j] = passen[i][j];
        }
    }
    vector<vector<int>> S(n, vector<int>(n, 0));

    for(int i = 1; i<n; i++){
        for(int j = 1; j<n; j++){
            S[i][j] = pas[i][j] + S[i-1][j] + S[i][j-1] - S[i-1][j-1];
        }
    }

    //dynamic programming the answer
    vector<vector<int>> dp(n+1, vector<int>(k+1, 0));
    vector<vector<int>> pre(n+1, vector<int>(k+1, 0));

    for(int i = 1; i<n; i++){
        for(int j = 1; j<=k; j++){

            for(int o = i-1; o>=0; o--){
                int sum = S[i][n-i]-S[o][n-i];
                if(dp[i][j] < dp[o][j-1] + sum){
                    pre[i][j] = o;
                    dp[i][j] = dp[o][j-1] + sum;
                }
            }

        }
    }

    int best = k;
    for(int i = k+1; i<n; i++){
        if(dp[i][k] > dp[best][k]){
            best = i;
        }
    }

    vector<int> ans;
    int ind = best;
    int t = k;
    while(ind != 0 && t != 0){
        ans.PB(ind);
        ind = pre[ind][t];
        t--;
    }
    reverse(ans.begin(),ans.end());

    return MP(dp[best][k], ans);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test<=10'000 ;test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        pair<int,vector<int>> ansB = brute();
        pair<int,vector<int>> ansS = solve();

        if(ansB.first != ansS.first){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB.first<<"\n";
            for(int j = 0; j<ansB.second.size(); j++){
                cout<<ansB.second[j]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: "<<ansS.first<<"\n";
            for(int j = 0; j<ansS.second.size(); j++){
                cout<<ansS.second[j]<<" ";
            }
            cout<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}