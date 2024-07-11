#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

using ll = long long int;
using ull = unsigned long long int;

const int INF = 1'000'000'000;

int n, s, m;
vector<PII> well;
vector<tuple<PII,int,vector<int>>> dep;

void getData(){
    cin>>n>>s>>m;
    for(int i = 0; i<s; i++){
        int p, d;
        cin>>p>>d;
        well.PB(MP(p,d));
    }
    for(int i = 0; i<m;  i++){
        PII ran;
        int len;
        vector<int> vec;
        cin>>ran.first>>ran.second>>len;
        for(int j = 0; j<len; j++){
            int temp;
            cin>>temp;
            vec.PB(temp);
        } 
        dep.PB(MT(ran,len,vec));
    }
}

void getRandom(){
    well.clear();
    dep.clear();
    
    srand(time(0));

    n = rand()%10+1;
    s = rand()%n+1;
    m = rand()%2+1;
    vector<bool> vis(n+1, false);
    for(int i = 0; i<s; i++){
        int temp = rand()%n+1;
        while(!vis[temp]){
            temp = rand()%n+1;
        }
        vis[temp] = true;
        int depth = rand()%10+1;
        well.PB(MP(temp, depth));
    }

    for(int i = 0; i<m; i++){
        PII ran = MP(0,0);
        while(ran.first == ran.second){
            ran.first = rand()%n+1;
            ran.second = rand()%n+1;
        }
        
        if(ran.first > ran.second){
            swap(ran.first, ran.second);
        }
        int dif = ran.second - ran.first + 1;
        int len = rand()%(dif-1) +1;
        vector<bool> vis(dif, false);

        vector<int> sup;
        for(int j = 0; j<len; j++){
            int temp = rand()%dif;
            while(!vis[temp]){
                temp = rand()%dif;
            }
            vis[temp] = true;
            sup.PB(temp+ran.first);
        }

        dep.PB(MT(ran,len,sup));
    }
}

void printData(){
    cout<<"DATA:\n";
    cout<<n<<" "<<s<<" "<<m<<"\n";
    for(int i = 0; i<s; i++){
        cout<<well[i].first<<" "<<well[i].second<<"\n";
    }
    for(int i = 0; i<m; i++){
        PII ran = get<0> (dep[i]);
        int len = get<1> (dep[i]);
        vector<int> vec = get<2> (dep[i]);
        cout<<ran.first<<" "<<ran.second<<" "<<len<<" ";
        for(int j = 0; j<len; j++){
            cout<<vec[j]<<" ";
        }
        cout<<"\n";
    }
}

vector<int> brute(){
    vector<int> input(n+1, 0);
    vector<vector<int>> graph(n+1, vector<int>());
    
    vector<int> ans(n+1, INF);
    for(int i = 0; i<s; i++){
        ans[well[i].first] = well[i].second;
    }

    for(int i = 0; i<m; i++){
        PII ran = get<0>(dep[i]);
        int len = get<1>(dep[i]);
        vector<int> sup = get<2>(dep[i]);
        for(int j = 0; j<len; j++){
            int ind = 0;
            for(int o = ran.first; o<=ran.second; o++){
                if(o != sup[ind]){
                    graph[sup[j]].PB(o);
                    input[o]++;
                }else{
                    ind++;
                }
            }
        }
    }

    queue<PII> Q;
    for(int i = 1; i<=n; i++){
        if(input[i] == 0){
            Q.push(MP(i,ans[i]));
            break;
        }
    }

    if(Q.empty()){
        return vector<int>();
    }

    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();
        for(int i = 0; i<graph[v.first].size(); i++){
            int cur = graph[v.first][i];
            ans[cur] = min(ans[cur], v.second-1);
            if(ans[cur] < 0){
                return vector<int>();
            }
            Q.push(MP(cur,ans[cur]));
        }
    }

    return ans;
} 

vector<int> solve(){

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1 ;test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        if(ansB.size() != ansS.size()){
            cout<<"NIE\n";
            cout<<"BRUTE: \n";
            cout<<ansB.size()<<"\n";
            for(int i = 0; i<ansB.size(); i++){
                cout<<ansB[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: \n";
            cout<<ansS.size()<<"\n";
            for(int i = 0; i<ansS.size(); i++){
                cout<<ansS[i]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        }else{
            for(int i = 0; i<n; i++){
                if(ansB[i] != ansS[i]){
                    cout<<"NIE\n";
                    cout<<"BRUTE: \n";
                    cout<<ansB.size()<<"\n";
                    for(int i = 0; i<ansB.size(); i++){
                        cout<<ansB[i]<<" ";
                    }
                    cout<<"\n";
                    cout<<"SOLVE: \n";
                    cout<<ansS.size()<<"\n";
                    for(int i = 0; i<ansS.size(); i++){
                        cout<<ansS[i]<<" ";
                    }
                    cout<<"\n";
                    printData();
                    return 0;
                }
            }
        }
    }

    return 0;
}