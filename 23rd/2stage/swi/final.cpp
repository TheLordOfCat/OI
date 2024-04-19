#include<iostream>
#include <vector>
#include <queue>
#include <set>

#include <cstdlib>
#include <ctime>

using namespace std;

struct range{
    int a;
    int b;
    int l;
    range(int a1, int b1, int l1){
        a = a1;
        b = b1;
        l = l1;
    }
    range(){
        a = -1;
        b = -1;
        l = -1;
    }

    bool operator<(const range &other) const {
        if(l != other.l)
            return l<other.l;
        if (a != other.a)
            return a < other.a;
        return b < other.b;

    }
};

int n, m;
vector<range> R;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        range temp;
        cin>>temp.a>>temp.b>>temp.l;
        R.push_back(temp);
    }
}

int solve(){
    vector<set<range>> S(n+1,set<range>());
    int maxL = 0;
    for(int i = 0; i<m; i++){
        S[R[i].l].insert(R[i]);
        maxL = max(maxL, R[i].l);
    }

    int power = 0;
    while(1<<power < maxL) power++;

    for(int i = power-1; i>= 1; i--){
        int before = 1<<(i-1);
        for(int j = 1<<(i+1); j>= 1<<(i); j--){
            for(auto x = S[j].begin(); x != S[j].end(); x++){
                range cur = *x;
                range t1 = cur;
                t1.l = before;
                if(S[before].find(t1) != S[before].end()){
                    S[before].insert(t1);
                }
                range t2 = cur;
                t2.a = cur.a + cur.l - before;
                t2.b = cur.b + cur.l - before;
                t2.l = before;
                if(S[before].find(t2) != S[before].end()){
                    S[before].insert(t2);
                }
            }
        }
    }

    vector<vector<int>> graph(n+1, vector<int>());
    for(auto r = S[0].begin(); r != S[0].end(); r++){
        range cur = *r;
        graph[cur.a].push_back(cur.b);
        graph[cur.b].push_back(cur.a);
    }

    vector<bool>vis(n+1, false);
    int ans = 0;
    for(int i = 1; i<=n; i++){
        if(!vis[i]){
            ans++;
            queue<int> Q;
            Q.push(i);
            vis[i] = true;
            while(!Q.empty()){
                int v = Q.front();
                Q.pop();
                for(int j = 0; j<graph[v].size(); j++){
                    int cur = graph[v][j];
                    if(!vis[cur]){
                        Q.push(cur);
                        vis[cur] = true;
                    }
                }
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    int ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}