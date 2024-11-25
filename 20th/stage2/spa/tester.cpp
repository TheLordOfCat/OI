#include<iostream>
#include <vector>
#include <queue>
#include <string>

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

    n = rand()%10+1;
    k = rand()%n+1;

    int vStart = rand()%(1<<n), vFinish = rand()%(1<<n);
    if(vStart == vFinish){
        if(vStart == n){
            vFinish--;
        }else{
            vFinish++;
        }
    }

    vector<int> vRemoved;
    vector<bool> vis((1<<n) + 1, false);
    vis[0] = true;
    for(int i = 0; i<k; i++){
        int temp = 0;
        while(vis[temp]){
            temp = rand()%n+1;
        }
        vis[temp] = true;
        vRemoved.PB(temp);
    }

    while(vStart > 0){
        int c = vStart - (vStart/10)*10;
        start.PB(c + '0');
    }
    while(vFinish > 0){
        int c = vFinish - (vFinish/10)*10;
        finish.PB(c + '0');
    }
    for(int i =0 ; i<vRemoved.size(); i++){
        int temp = vRemoved[i];
        string s;
        
        while(temp > 0){
            int c = temp - (temp/10)*10;
            s.PB(c + '0');
        }

        removed.PB(s);
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
    for(int i = 1; i<(1<<n); i++){
        for(int j = 0; j <n; j++){
            int con = i ^ (1<<j);
            graph[i].PB(con);
            graph[con].PB(i);
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

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1;test<=1 ;test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        bool ansB = brute();
        bool ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}