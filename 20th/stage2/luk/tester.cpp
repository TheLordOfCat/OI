#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ll = long long int;
using ull = unsigned long long int;

int n;
vector<PII> edges;

void getData(){
    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    edges.clear();

    srand(time(0));

    n = rand()%10+1;
    int last = 2;
    for(int i =0; i<n-1; i++){
        int a, b;
        int con = rand()%5+1;

        for(int j = 0; j<con; j++){
            if(edges.size() != n-1){
                a = i+1;
                b = last;
                last++;
                edges.PB(MP(a,b));
            }else{
                break;
            }
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i =0; i<n-1; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

struct qCompare{
    bool operator()(const PII a, const PII b){
        if(a.second == b.second){
            return a.first < b.first;
        }
        return a.second < b.second;
    }
};

int brute(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0; i<edges.size(); i++){
        int a = edges[i].first;
        int b = edges[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }

    int ans = n;
    for(int i = 1; i<=n; i++){
        bool ok = true;

        priority_queue<PII, vector<PII>, qCompare> Q;
        vector<bool> vis(n+1, false);
        Q.push(MP(1, 1));
        int turn = 1;
        int count = 0;
        while(!Q.empty()){
            int v = Q.top().first;
            int l = Q.top().second;
            Q.pop();

            vis[v] = true;

            count++;
            if(turn > l){
                ok = false;
                break;
            }

            if(count == i){
                turn++;
                count = 0;
            }

            for(int j = 0; j<graph[v].size(); j++){
                int cur=  graph[v][j];
                if(!vis[cur]){
                    Q.push(MP(cur,l+1));
                }
            }

        } 

        if(ok){
            ans = i;
            break;
        }
    }

    return ans;
}

int solve(){

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        int ansB = brute();
        int ansS = solve();
        if(ansB != ansS){
            cout<<"ERORR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}