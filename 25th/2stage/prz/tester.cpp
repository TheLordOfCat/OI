#include <iostream>
#include <vector>
#include <queue>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back

int n;
vector<int> x;
vector<int> y;
vector<PII> edges;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        y.PB(temp);
    }
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    n = rand()%10+1;
    //testing "NIE"
    for(int i = 0; i<n; i++){
        int temp = rand()%11;
        x.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int temp = rand()%11;
        y.PB(temp);
    }

    //testing "TAK"
    // int sum = 0;
    // for(int i = 0; i<n; i++){
    //     int temp = rand()%11;
    //     x.PB(temp);
    //     sum += temp;
    // }
    // for(int i = 0; i<n-1; i++){
    //     if(sum != 0){
    //         int temp = rand()%sum;
    //         y.PB(temp);
    //     }else{
    //         y.PB(0);
    //     }
    // }
    // y.PB(sum);

    int ind = 2;
    for(int i = 1; i<=n; i++){
        int con = rand()%3+1;
        for(int j =0 ; j<con;j ++){
            edges.PB(MP(i,ind));
            ind++;
            if(ind > n){
                break;
            }
        }
        if(ind > n){
            break;
        }
    }

}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<x[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<n; i++){
        cout<<y[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<n; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

struct compare{
    bool operator()(const PII a, const PII b){
        return a.second > b.second;
    }
};


ll brute(){
    vector<int> dif(n+1, 0);
    int sum = 0;
    for(int i = 0; i<n; i++){
        sum += y[i]-x[i];
        dif[i] = y[i]-x[i];
    }
    if(sum == 0){
        return -1;
    }

    //creating graph
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i =0 ; i<n-1; i++){
        graph[edges[i].first].PB(edges[i].second);
        graph[edges[i].second].PB(edges[i].first);
    }

    //getting depth
    vector<int> depth(n+1, 0);
    depth[1] = 1;
    queue<PII> bfs;
    bfs.push(MP(1,1));
    while(!bfs.empty()){
        PII v = bfs.front();
        bfs.pop();

        for(int i = 0; i<graph[v.first].size(); i++){
            int cur = graph[v.first][i];
            if(depth[cur] == 0){
                depth[cur] = v.second+1;
                bfs.push(MP(cur, v.second+1));
            }
        }
    }

    ll ans = 0;
    priority_queue<PII, vector<PII>, compare> Q; 
    
    for(int i = 1; i<=n; i++){
        if(dif[i] > 0){
            Q.push(MP(i,depth[i]));
        }
    }

    while(!Q.empty()){
        PII v = Q.top();
        Q.pop();

        if(dif[v.first] > 0){
            ans++;
            dif[v.first] -= graph[v.first].size();
            for(int i = 0; i<graph[v.first].size(); i++){
                int cur = graph[v.first][i];
                dif[cur]++;
                if(dif[cur] > 0){
                    Q.push(MP(cur,depth[cur]));
                }
            }
        }
    }

    return ans;
}

ll solve(){
    vector<int> dif(n+1, 0);
    int sum = 0;
    for(int i = 0; i<n; i++){
        sum += y[i]-x[i];
        dif[i] = y[i]-x[i];
    }
    if(sum == 0){
        return -1;
    }


}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op =1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        ll ansB = brute();
        ll ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}