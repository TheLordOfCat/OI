#include<iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <bitset>

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

void getRandom(){
    start.clear(); finish.clear(); removed.clear();

    srand(time(0));

    // n = rand()%10+1;
    n = 60;
    // k = rand()%((1<<n)-4)+1;
    k = (((ll)1)<<n)/2;

    ll vStart = rand()%(1<<n), vFinish = rand()%(1<<n);
    if(vStart == vFinish){
        if(vStart == n){
            vFinish--;
        }else{
            vFinish++;
        }
    }

    vector<ll> vRemoved;
    vector<bool> vis((1<<n) + 1, false);
    vis[0] = true;
    vis[vStart] = true; vis[vFinish] = true;
    for(int i = 0; i<k; i++){
        ll temp = 0;
        while(vis[temp]){
            temp = rand()%(1<<n)+1;
        }
        vis[temp] = true;
        vRemoved.PB(temp);
    }

    bitset<60> bS(vStart);
    start = bS.to_string();
    bitset<60> bF(vFinish);
    finish = bF.to_string();
    for(int i = 0; i<vRemoved.size(); i++){
        bitset<60> temp(vRemoved[i]);
        removed.PB(temp.to_string());
    }
}

void printData(){
    cout<<n<<" "<<k<<"\n";
    cout<<start<<" "<<finish<<"\n";
    for(int i =0; i<removed.size(); i++){
        cout<<removed[i]<<"\n";
    }
}

bool brute(){
    //get graph
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

    vector<bool> vR((1<<n)+1, false);
    for(int i = 0; i<removed.size(); i++){
        ll temp = 0;
        for(int j = removed[i].size()-1; j>=0; j--){
            if(removed[i][j] == '1'){
                temp += (1<<(removed[i].size()-j-1));
            }
        }
        vR[temp] = true;
    }

    vector<vector<ll>> graph((1<<n)+1, vector<ll>());
    for(int i = 0; i<(1<<n); i++){
        if(vR[i]){
            continue;
        }

        for(int j = 0; j <n; j++){
            int con = i ^ (1<<j);

            if(!vR[con]){
                graph[i].PB(con);
            }
        }
    }

    //process graph
    bool ans = false;
    vector<bool> vis((1<<n)+1, false);
    queue<ll> Q;
    Q.push(vS);

    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        if(v == vF){
            ans = true;
            break;
        }

        for(int i = 0; i<graph[v].size(); i++){
            int cur = graph[v][i];
            if(!vis[cur]){
                Q.push(cur);
                vis[cur] = true;
            }
        }
    }

    return ans;
}

bool solve(){
    //change to number
    vector<ll> vR;
    for(int i =0 ; i<removed.size(); i++){
        ll temp = 0;
        for(int j = removed[i].size()-1; j>=0; j--){
            if(removed[i][j] == '1'){
                temp += (((ll)1)<<(removed[i].size()-j-1));
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
            vS += (((ll)1)<<(start.size()-i-1));
        }
    }
    for(int i = finish.size()-1; i>=0; i--){
        if(finish[i] == '1'){
            vF += (((ll)1)<<(finish.size()-i-1));
        }
    }


    bool ans = false;
    vector<ll> vec = {vS, vF};
    for(int j = 0; j< vec.size(); j++){
        unordered_set<ll> U;
        queue<ll> Q;

        Q.push(vec[j]);
        U.insert(vec[j]);
        int used = 1;
        int limit = n*k + 1;

        while(!Q.empty() && used < limit){
            ll v = Q.front();
            Q.pop();

            if(v == vec[(j+1)%2]){
                ans = true;
            }

            for(int i = 0; i<n; i++){
                ll temp = v;
                temp ^= (((ll)1)<<i);
                if(U.find(temp) == U.end() && S.find(temp) == S.end()){
                    Q.push(temp);
                    U.insert(temp);
                    used++;
                }
            }
            if(used >= limit){
                ans = true;
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

    int op = 0;
    for(int test = 1; test<=1'000'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        // bool ansB = brute();
        bool ansS = solve();
        // if(ansB != ansS){
        //     cout<<"ERROR\n";
        //     cout<<"BRUTE: "<<ansB<<"\n";
        //     cout<<"SOLVE: "<<ansS<<"\n";
        //     printData();
        //     return 0;
        // }
        cout<<"CORRECT\n";
    }

    return 0;
}