#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back
#define MT make_tuple
#define PIV pair<int,vector<int>>

int n, m, d, k;
vector<tuple<int,int,vector<int>>> edges;

void getData(){
    edges.clear();

    cin>>n>>m>>d>>k;
    for(int i = 0; i<m; i++){
        int a, b;
        vector<int> s;
        cin>>a>>b;
        for(int i = 0; i<k; i++){
            int temp;
            cin>>temp;
            s.PB(temp);
        }
        edges.PB(MT(a,b,s));
    }
}

void getRandom(){
    edges.clear();

    n = rand()%10+1;
    m = rand()%10+n;
    d = rand()%n+1;
    k = 1;

    //create path from 1 to n
    for(int i = 0; i<k; i++){
        vector<int> s;
        for(int i =0 ; i<k; i++){
            int temp = rand()%10+1;
            s.PB(temp);
        }
        edges.PB(MT(i+1, i+2, s));
    }
    get<1>(edges.back()) = n;

    //create other edges
    for(int i = k; i<m; i++){
        int a = 1, b = 1;
        while(a == b){
            a = rand()%n+1; b = rand()%n+1;
        }
        vector<int> s;
        for(int i =0 ; i<k; i++){
            int temp = rand()%10+1;
            s.PB(temp);
        }
        edges.PB(MT(a, b, s));
    }
}

void printData(){
    cout<<n<<" "<<m<<" "<<d<<" "<<k<<"\n";
    for(int i = 0; i< edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]);
        vector<int> s = get<2>(edges[i]);
        cout<<a<<" "<<b<<" ";
        for(int j = 0; j<s.size(); j++) cout<<s[i]<<" ";
        cout<<"\n";
    }
}

bool check(int ind, vector<int> val, vector<vector<PIV>> &graph){
    //crate special graph
    vector<vector<int>> graphSpec((1<<(ind+1))*(n+1)+1, vector<int>());
    vector<PII> vecLabel(graphSpec.size(), MP(-1,-1));
    vector<vector<int>> vis(n+1, vector<int>((1<<(ind+1)), -1));

    queue<PII> Q;
    Q.push(MP(1,0));
    vis[1][0] = 1;
    int totalGraphSize = 2;
    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();

        for(int i = 0; i<graph[v.first].size(); i++){
            PIV cur = graph[v.first][i];
            int s = v.second;
            for(int i = 0; i<=ind; i++){
                if(cur.second[i] >= val[i]){
                    s |= (1<<i);
                }
            }
            if(vis[cur.first][s] == -1){
                vis[cur.first][s] = totalGraphSize;
                vecLabel[totalGraphSize] = MP(cur.first,s);

                graphSpec[vis[v.first][v.second]].PB(totalGraphSize);
                graphSpec[totalGraphSize].PB(vis[v.first][v.second]);
                totalGraphSize++;

                Q.push(MP(cur.first, s));
            }
        }
    }    

    //traverse graph
    int exp = (1<<(ind+1))-1;

    Q.push(MP(1,0));
    vector<bool> used(graphSpec.size()+1, false);
    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();
        if(v.second > d) continue;

        if(vecLabel[v.first].first == n){
            if(vecLabel[v.first].second == exp){
                return true;
            }
        }

        for(int i = 0; i< graphSpec[v.first].size(); i++){
            int cur = graphSpec[v.first][i];
            if(!used[cur]){
                Q.push(MP(cur, v.second+1));
                used[cur] = true;
            }
        }   
    }

    return false;
}

void binSearch(int ind, int low, int high, vector<int>& ans, vector<vector<PIV>> &graph){
    int l = low, r = high;
    ans.PB(0);
    while(l<=r){
        int mid = (l+r)/2;
        vector<int> temp = ans;
        temp.back() = mid;
        if(check(ind, temp, graph)){
            ans.back() = mid;
            l = mid+1;
        }else{
            r = mid-1;
        }
    }
}

vector<int> solve(){
    //craete graph
    vector<vector<PIV>> graph(n+1, vector<PIV>());
    for(int i = 0; i<edges.size(); i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]);
        vector<int> vec = get<2>(edges[i]);
        graph[a].PB(MP(b,vec));
        graph[b].PB(MP(a,vec));
    }

    //get ans
    vector<int> ans;
    for(int i = 0; i<k; i++){
        int lowestS = INF, highestS = 0;
        for(int j = 0; j<m; j++){
            vector<int> vec = get<2>(edges[j]);
            lowestS = min(lowestS, vec[i]);
            highestS = max(highestS, vec[i]);
        }
        binSearch(i,lowestS, highestS, ans, graph);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        // cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansS = solve();
        for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<" ";
    }

    return 0;
}