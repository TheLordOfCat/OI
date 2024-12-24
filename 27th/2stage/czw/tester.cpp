#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <stack>
#include <tuple>
#include <string>
#include <map>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back
#define MT make_tuple

const int MOD = 1'000'000'007;

int m;
vector<int> code;

void getData(){
    code.clear();

    cin>>m;

    string temp;
    cin>>temp;
    for(int i =0 ; i<temp.size(); i++){
        code.PB(temp[i]-'0');
    }
}

void getRandom(){
    code.clear();

    m = rand()%2+1;

    stack<PII> S;
    S.push(MP(1, 0));
    int ind = 2;
    while(!S.empty()){
        PII v = S.top();
        S.pop();

        if(v.second == m){
            for(int i = 0; i<4; i++){
                code.PB(rand()%2);
            }
            continue;
        }

        int con = rand()%3;
        if(con == 0){
            code.PB(0);            
        }else if(con == 1){
            code.PB(1);
        }else if(con == 2){
            code.PB(4);
            for(int i = 0; i<4; i++){
                S.push(MP(ind, v.second+1));
                ind++;
            }
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<m<<"\n";
    for(int i = 0; i<code.size(); i++){
        cout<<code[i];
    }
    cout<<"\n";
}

PII brute(){
    vector<vector<int>> plane((1<<m), vector<int>((1<<m), 0));

    //fill the plane
    stack<pair<PII,int>> S;
    S.push(MP(MP(0,0), 0));
    int ind = 0;

    while(!S.empty()){
        PII pos = S.top().first;
        int depth = S.top().second;
        S.pop();

        if(code[ind] == 1){
            int len = (1<<(m-depth));
            for(int i = pos.first; i<pos.first + len; i++){
                for(int j = pos.second; j<pos.second+len; j++){
                    plane[i][j] = 1;
                }
            }
        }else if(code[ind] == 4){
            int len = (1<<(m-depth-1));
            S.push(MP(pos, depth+1));
            S.push(MP(MP(pos.first, pos.second+len), depth+1));
            S.push(MP(MP(pos.first+len, pos.second), depth+1));
            S.push(MP(MP(pos.first+len, pos.second+len), depth+1));
        }
        ind++;
    }

    //get ans
    PII ans = MP(0,0);
    vector<vector<bool>> used((1<<m), vector<bool>((1<<m), false));
    for(int i = 0; i<(1<<m); i++){
        for(int j = 0; j<(1<<m); j++){
            if(used[i][j] || plane[i][j] == 0){
                continue;
            }
            stack<PII> S;
            S.push(MP(i,j));
            used[i][j] = true;
            int area = 1;
            while(!S.empty()){
                PII v = S.top();
                S.pop();

                if(v.first > 0){
                    if(!used[v.first-1][v.second] && plane[v.first-1][v.second] == 1){
                        used[v.first-1][v.second] = true;
                        area++;
                        S.push(MP(v.first-1, v.second));
                    }
                }
                if(v.second > 0){
                    if(!used[v.first][v.second-1] && plane[v.first][v.second-1] == 1){
                        used[v.first][v.second-1] = true;
                        area++;
                        S.push(MP(v.first, v.second-1));
                    }
                }
                if(v.first+1 < (1<<m)){
                    if(!used[v.first+1][v.second] && plane[v.first+1][v.second] == 1){
                        used[v.first+1][v.second] = true;
                        area++;
                        S.push(MP(v.first+1, v.second));
                    }
                }
                if(v.second+1 < (1<<m)){
                    if(!used[v.first][v.second+1] && plane[v.first][v.second+1] == 1){
                        used[v.first][v.second+1] = true;
                        area++;
                        S.push(MP(v.first, v.second+1));
                    }
                }
            }

            ans.first++;
            ans.second = max(ans.second, area);
        }
    }

    return ans;
}

struct xDominant {
    bool operator()(const pair<PII,int>& a, const pair<PII,int>& b) const {
        if (a.first.first != b.first.first)
            return a.first.first < b.first.first;
        return a.first.second < b.first.second;
    }
};

struct yDominant {
    bool operator()(const pair<PII,int>& a, const pair<PII,int>& b) const {
        if (a.first.second != b.first.second)
            return a.first.second < b.first.second;
        return a.first.first < b.first.first;
    }
};

vector<PII> getPosBlock(vector<vector<int>> &graphBlock, int& globalInd){
    vector<PII> posBlockX(code.size(), MP(-1,-1));
    stack<tuple<int,int,bool>> S;
    S.push(MT(0,0, false));
    while(!S.empty()){
        int v = get<0>(S.top()), type = get<1>(S.top());
        bool b = get<2>(S.top());
        S.pop();

        if(b){
            if(code[v] == 4){
                int maxim = 0, minim = 0;
                for(int i =0 ; i<graphBlock[v].size(); i++){
                    int cur = graphBlock[v][i];
                    maxim = max(maxim, posBlockX[cur].second);
                    minim = min(minim, posBlockX[cur].first);
                }
                posBlockX[v] = MP(minim, maxim);
            }else{
                if(type == 0 || type == 2){
                    posBlockX[v] = MP(globalInd, globalInd+1);
                    globalInd++;
                }else if(type == 1 || type == 3){
                    posBlockX[v] = posBlockX[v-1];
                }
            }
        }

        S.push(MT(v,type, true));
        if(graphBlock[v].size() == 4){
            S.push(MT(graphBlock[v][0], 0, false));
            S.push(MT(graphBlock[v][1], 1, false));
            S.push(MT(graphBlock[v][2], 2, false));
            S.push(MT(graphBlock[v][3], 3, false));
        }
    }
}

vector<int> getDepth(int& maxDepth){
    vector<int> depth(code.size(), -1);
    stack<PII> Q;
    Q.push(MP(0,0));
    while(!Q.empty()){
        PII v = Q.top();
        Q.pop();
        depth[v.first] = v.second;
        maxDepth = max(maxDepth, v.second);

        if(code[v.first] == 4){
            Q.push(MP(v.first+1, v.second+1));
            Q.push(MP(v.first+2, v.second+1));
            Q.push(MP(v.first+3, v.second+1));
            Q.push(MP(v.first+4, v.second+1));
        }
    }

    return depth;
}

void connnectEdgeX(map<PII,int, xDominant> &s, int g, int t1, int t2, vector<bool>& con, vector<vector<int>>& graph, int ind){
    auto lower = s.lower_bound(MP(g, t1));
    auto upper = s.upper_bound(MP(g, t2));

    for(auto itr = lower; itr != upper; itr++){
        if(code[itr->second] == 1 && !con[itr->second]){
            graph[ind].PB(itr->second); 
            con[itr->second] = true;
        }
    }
}

void connnectEdgeY(map<PII,int, yDominant> &s, int g, int t1, int t2, vector<bool>& con, vector<vector<int>>& graph, int ind){
    auto lower = s.lower_bound(MP(t1, g));
    auto upper = s.upper_bound(MP(t2, g));

    for(auto itr = lower; itr != upper; itr++){
        if(code[itr->second] == 1 && !con[itr->second]){
            graph[ind].PB(itr->second); 
            con[itr->second] = true;
        }
    }
}

vector<vector<int>> getGraph(vector<PII> &posBlockX, vector<PII> &posBlockY){
    vector<vector<int>> graph(code.size(), vector<int>());
    map<PII,int, xDominant> sX;
    map<PII,int, yDominant> sY;

    for(int i = 0; i<code.size(); i++){
        if(code[i] == 1){
            sX.insert(MP(MP(posBlockX[i].first, posBlockY[i].first), i));
            sX.insert(MP(MP(posBlockX[i].second, posBlockY[i].second), i));
            sY.insert(MP(MP(posBlockX[i].first, posBlockY[i].first), i));
            sY.insert(MP(MP(posBlockX[i].second, posBlockY[i].second), i));
        }   
    }

    for(int i = 0; i<code.size(); i++){
        int x1 = posBlockX[i].first, x2 = posBlockX[i].second;
        int y1 = posBlockY[i].first, y2 = posBlockY[i].second;
        vector<bool> con(code.size(), false);
        if(code[i] == 1){
            connnectEdgeX(sX,x1,y1,y2,con,graph,i); 
            connnectEdgeX(sX,x2,y1,y2,con,graph,i); 
            connnectEdgeY(sY,y1,x1,x2,con,graph,i); 
            connnectEdgeY(sY,y2,x1,x2,con,graph,i); 
        }
    }
    return graph;
}

vector<int> getArea(vector<int>& depth, int maxDepth){
    vector<int> area;
    vector<int> depthSup(maxDepth+1, 0);
    depthSup.back() = 1;
    for(int i = depthSup.size()-2; i>=0; i--){
        depthSup[i] = depthSup[i-1]*2;
        depthSup[i] &= MOD;
    }
    
    for(int i = 0; i<depth.size(); i++){
        area.PB(depthSup[i]);
    }

    return area;
}

PII solve(){
    int maxDepth = 0;

    //fill the plane
    vector<vector<int>> graphBlock(code.size(), vector<int>());
    for(int i = 0; i<code.size(); i++){
        if(code[i] == 4){
            graphBlock[i].PB(i+1);
            graphBlock[i].PB(i+2);
            graphBlock[i].PB(i+3);
            graphBlock[i].PB(i+4);
        }
    }
    
    //get posBlock
    int globalInd = 0;
    vector<PII> posBlockX = getPosBlock(graphBlock, globalInd);

    //get max Depth size
    vector<int> depth = getDepth(maxDepth);
   
    //rotate
    vector<PII> posBlockY(code.size(), MP(-1,-1));
    for(int i = 0; i<posBlockX.size(); i++){
        posBlockY[i] = MP(globalInd-posBlockX[i].first, globalInd-posBlockX[i].second);
    }
    
    //create graph
    vector<vector<int>> graph = getGraph(posBlockX, posBlockY);

    //get area
    vector<int> area = getArea(depth, maxDepth);

    //get ans
    PII ans = MP(0,0);
    vector<bool> used(code.size(), false);
    for(int i = 0; i<code.size(); i++){
        if(code[i] == 1 && !used[i]){
            stack<int> S;
            S.push(i);
            used[i] = true;
            int maxArea = area[i];

            while(!S.empty()){
                int v = S.top();
                S.pop();

                for(int i =0; i<graph[v].size(); i++){
                    int cur = graph[v][i];
                    if(!used[cur]){
                        S.push(cur);
                        maxArea += area[cur];
                        area[cur] %= MOD;
                    }
                }
            }

            ans.first++;
            ans.second = max(ans.second, maxArea);
        }
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
        PII ansB = brute();
        PII ansS = solve();
        if(ansB.first != ansS.first || ansB.second != ansS.second){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<ansB.first<<"\n"<<ansB.second<<"\n";
            cout<<"SOLVE: \n";
            cout<<ansS.first<<"\n"<<ansS.second<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}