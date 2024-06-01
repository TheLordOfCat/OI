#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, m, k;
vector<vector<int>> graph;
vector<pair<PII,int>> query;

void getData(){
    cin>>n>>m>>k;
    graph.assign(n+1, vector<int>());
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        graph[a].PB(b);
        graph[b].PB(a);
    }
    for(int i = 0; i<k; i++){
        int s, t, d;
        cin>>s>>t>>d;
        query.PB(MP(MP(s,t),d));
    }
}

void getRandom(){
    graph.clear();
    query.clear();

    srand(time(0));
    n = rand()%10+1;
    m = rand()%20+1;
    k = rand()%5+1;
    graph.assign(n+1, vector<int>());
    for(int i =0; i<m; i++){
        int a = rand()%n+1;
        int b = rand()%n+1;
        graph[a].PB(b);
        graph[b].PB(a);
    }
    for(int i = 0; i<k; i++){
        int s = rand()%n+1;
        int t = rand()%n+1;
        int d = rand()%(2*n)+1;
        query.PB(MP(MP(s,t),d));
    }
}

void printData(){
    cout<<n<<" "<<m<<" "<<k<<"\n";
    for(int i= 1; i<=n; i++){
        for(int j =0; j<graph[i].size(); j++){
            cout<<i<<" "<<graph[i][j]<<"\n";
        }
    }
    for(int i = 0; i<k; i++){
        cout<<query[i].first.first<<" "<<query[i].first.second<<" "<<query[i].second<<"\n";
    }
}

vector<bool> brute(){
    vector<bool> ans;
    for(int i = 0; i<k; i++){
        int beg = query[i].first.first;
        int end = query[i].first.second;
        int len = query[i].second;
        
        bool ok = false;

        queue<PII> Q;
        Q.push(MP(beg,0));
        while(!Q.empty()){
            int v = Q.front().first;
            int l = Q.front().second;
            Q.pop();

            if(v == end){
                if(l > len){
                    break;
                }else{
                    if(l%2 == len%2){
                        ok = true;
                        break;
                    }
                }
            }
            if(l < len){
                for(int i = 0; i<graph[v].size(); i++){
                    int cur = graph[v][i];
                    Q.push(MP(cur,l+1));
                }
            }

        }

        ans.PB(ok);
    }

    return ans;
}

bool customCompare(pair<PII,int> a, pair<PII,int> b) {
    return a.first.first < b.first.first; 
}

vector<bool> solve(){
    for(int i =0; i<query.size(); i++){
        if(query[i].first.first > query[i].first.second){
            int temp = query[i].first.first;
            query[i].first.first = query[i].first.second;
            query[i].first.second = temp;
        }
    }

    sort(query.begin(), query.end(), customCompare);

    vector<bool> ans(n+1, false);
    int p = -1;
    vector<PII> shortPath(n+1, MP(-1,-1));
    for(int i = 0; i<query.size(); i++){
        int beg = query[i].first.first;
        int end = query[i].first.second;
        int len = query[i].second;

        if(beg != p){
            shortPath.clear();
            shortPath.assign(n+1, MP(-1,-1));

            queue<PII> Q;
            Q.push(MP(beg, 0));
            while(!Q.empty()){
                int v = Q.front().first;
                int l = Q.front().second;
                Q.pop();
                bool next = true;

                if(l%2 == 0){
                    if(shortPath[v].first == -1){
                        shortPath[v].first = l;
                    }else{
                        next = false;        
                    }
                }else{
                    if(shortPath[v].second == -1){
                        shortPath[v].second = l;
                    }else{
                        next = false;        
                    }
                }

                if(next){
                    for(int j = 0; j<graph[v].size(); j++){
                        int cur =graph[v][j];
                        Q.push(MP(cur, len+1));
                    }
                }
            }
        }

        bool ok = false;
        if(len%2 == 0){
            if(shortPath[end].first <= len){
                ok = true;
            }
        }else{
            if(shortPath[end].second <= len){
                ok = true;
            }
        }

        ans.PB(ok);
        p = beg;
    }
    return ans;
}

int main()
{
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
        vector<bool> ansB = brute();
        vector<bool> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j =0;j <ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j =0;j <ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }
    return 0;
}