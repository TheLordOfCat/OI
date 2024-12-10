#include <iostream>
#include <vector>
#include <algorithm>

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

    // m = rand()%15+10;
    // n = rand()%10+10;

    m = 15;
    n = 5;

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

bool compareRanges(const vector<int> a, const vector<int> b){
    if(a[0] == b[0]){
        if(a[1] == b[1]){
            return a[2]<b[2];
        }
        return a[1]<b[1];
    }
    return a[0]<b[0];
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
    //sort
    vector<PII> pas = passengers;
    sort(pas.begin(), pas.end(), comparePasRed);

    //find minimum ops
    vector<PII> reduced;
    reduced.PB(pas[0]);
    PII curMar = MP(-1,-1);
    for(int i =1; i<pas.size(); i++){
        while(pas[i].second < reduced.back().second){ //reduce group
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
    marked.PB(reduced.size());
    reduced.PB(MP(INF,INF));

    sort(range.begin(), range.end(), compareRanges);
    vector<vector<vector<int>>> groups;
    groups.PB(vector<vector<int>>());
    vector<PII> g(reduced.size()-1, MP(0,0));
    int mark = 0;
    for(int i = 0; i< range.size()-1; i++){
        if(range[i][2] == marked[mark] && range[i][1] == -1){
            groups.PB(vector<vector<int>>());
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

    //process groups
    vector<vector<int>> dp(groups.size(), vector<int>());
    dp.back().PB(0);
    for(int i = 0; i< groups.back().size(); i++){
        dp.back().PB(groups.back()[i][2]);
    }
    for(int i = groups.size()-2; i>=0; i--){
        dp[i].PB(0);
        for(int j = 0; j<groups[i].size(); j++){
            if(reduced[groups[i][j][1]].second < reduced[groups[i+1].front()[0]].first){
                dp[i].PB(dp[i+1].back()*groups[i][j][2] + dp[i].back());
            }else{
                dp[i].PB(dp[i+1][g[groups[i][j][1]].second]*groups[i][j][2] + dp[i].back());
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

    int op = 0;
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