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
    cout<<n<<" "<<m<<"\n";
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

bool comparePasRight(const PII a, const PII b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second < b.second;
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
    pair<int,ll> ans = MP(0,0);
    vector<PII> pas = passengers;
    sort(pas.begin(), pas.end(), comparePasLeft);
    vector<vector<int>> groups;
    vector<PII> boundary;

    //iterating from left to right
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

    //updating ans
    ans = MP(groups.size(), 1);
    for(int i = 0; i<groups.size(); i++){
        ans.second *= (boundary[i].second- boundary[i].first);
        ans.second = ans.second%MOD;
    }

    groups.clear();
    boundary.clear();

    //iterating form right to left
    left = pas.back().first;
    right = pas.back().second;
    g.clear();
    for(int i = pas.size()-1; i >= 0; i++){
        PII cur = pas[i];
        if(cur.second < left){
            right = cur.second;
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

    //updating answer
    for(int i = 0; i<boundary.size(); i++){
        ans.second *= (boundary[i].second- boundary[i].first);
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