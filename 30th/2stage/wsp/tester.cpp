#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back

int n, m, k;
vector<int> f;
vector<PII> edges;

void getData(){
    f.clear(); edges.clear();

    cin>>n>>m>>k;
    f.PB(-1);
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        f.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    f.clear(); edges.clear();

    srand(time(0));

    n = rand()%10+1;
    m = rand()%10+1;
    k = rand()%8+1;

    f.PB(-1);
    for(int i = 0; i<n; i++){
        int temp =  rand()%10+1;
        f.PB(temp);
    }

    for(int i = 1; i<=n; i++){
        int con = rand()%k+1;
        for(int j = 1; j<=con; j++){
            edges.PB(MP(i, i+j));
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<" "<<k<<"\n";
    for(int i = 1; i<f.size(); i++){
        cout<<f[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<edges.size(); i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

vector<int> brute(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        if(a < b){
            graph[a].PB(b);
        }else{
            graph[b].PB(a);
        }
    }

    //process verticies
    vector<int> ans(n+1, 0);

    for(int i = n; i>=1; i--){
        int temp = 0;
        vector<bool> used(n+1, false);
        queue<int> Q;
        Q.push(i);
        temp += f[i];
        used[i] = true;
        while(!Q.empty()){
            int v = Q.front();
            Q.pop();

            for(int j = 0; j<graph[v].size(); j++){
                int cur = graph[v][j];
                if(!used[cur]){
                    used[cur] = true;
                    Q.push(cur);
                    temp += f[cur];
                }
            }
        }

        ans[i] = temp;
    }
    
    return ans;
}

vector<int> solve(){
    //create graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<edges.size(); i++){
        int a = edges[i].first, b = edges[i].second;
        if(a < b){
            graph[a].PB(b);
        }else{
            graph[b].PB(a);
        }
    }


}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 1; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 1; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"SOLVE: ";
                for(int j = 1; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                printData();
                return 0;
            }
        }
    }

    return 0;
}