#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

int n, k;
string start, finish;
vector<string> removed;

void getData(){
    start.clear(); finish.clear(); removed.clear();

    cin>>n>>k;
    cin>>start>>finish;
    for(int i = 0; i<k; i++){
        string temp;
        cin>>temp;
        removed.PB(temp);
    }
}

bool solve(){
    //change to number
    vector<ll> vR;
    for(int i =0 ; i<removed.size(); i++){
        ll temp = 0;
        for(int j = removed[i].size()-1; j>=0; j--){
            if(removed[i][j] == '1'){
                temp += (1<<(removed[i].size()-j-1));
            }
        }
        vR.PB(temp);
    }

    //get into set
    unordered_set<ll> S(vR.begin(), vR.end());

    //bfs
    ll vS = 0, vF = 0;
    for(int i = start.size()-1; i>=0; i--){
        if(start[i] == '1'){
            vS += (1<<(start.size()-i-1));
        }
    }
    for(int i = finish.size()-1; i>=0; i--){
        if(finish[i] == '1'){
            vF += (1<<(finish.size()-i-1));
        }
    }


    bool ans = false;
    unordered_set<ll> U;
    queue<int> Q;

    Q.push(vS);
    U.insert(vS);
    int used = 1;
    int limit = n*k + 1;

    while(!Q.empty() && used < limit){
        ll v = Q.front();
        Q.pop();

        if(v == vF){
            ans = true;
        }

        for(int i = 0; i<n; i++){
            ll temp = v;
            temp ^= (1<<i);
            if(U.find(temp) == U.end()){
                Q.push(temp);
                U.insert(temp);
                used++;
            }
        }
        if(used >= limit){
            ans = true;
        }
    }

    return ans;    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    bool ansS = solve();
    if(ansS){
        cout<<"TAK\n";
    }else{
        cout<<"NIE\n";
    }

    return 0;
}