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

void printData(){
    cout<<"DATA: \n";
    cout<<m<<"\n";
    for(int i = 0; i<code.size(); i++){
        cout<<code[i];
    }
    cout<<"\n";
}

struct xDominant {
    bool operator()(const PII& a, const PII& b) const {
        if (a.first != b.first)
            return a.first < b.first;
        return a.second < b.second;
    }
};

struct yDominant {
    bool operator()(const PII& a, const PII& b) const {
        if (a.second != b.second)
            return a.second < b.second;
        return a.first < b.first;
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
            continue;
        }

        S.push(MT(v,type, true));
        if(graphBlock[v].size() == 4){
            S.push(MT(graphBlock[v][3], 3, false));
            S.push(MT(graphBlock[v][2], 2, false));
            S.push(MT(graphBlock[v][1], 1, false));
            S.push(MT(graphBlock[v][0], 0, false));
        }
    }
    return posBlockX;
}

vector<int> getDepth(int& maxDepth, vector<vector<int>>& graph){
    vector<int> depth(code.size(), -1);
    stack<PII> Q;
    Q.push(MP(0,0));
    while(!Q.empty()){
        PII v = Q.top();
        Q.pop();
        depth[v.first] = v.second;
        maxDepth = max(maxDepth, v.second);

        for(int i = 0; i < graph[v.first].size(); i++){
            int cur = graph[v.first][i];
            Q.push(MP(cur, v.second+1));
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

void recGraph(int p, vector<vector<int>>& graph, int& ind){
    if(p != -1){
        graph[p].PB(ind);
    }
    
    int temp = ind;
    ind++;

    if(code[temp] == 4){
        recGraph(temp, graph, ind);
        recGraph(temp, graph, ind);
        recGraph(temp, graph, ind);
        recGraph(temp, graph, ind);
    }
}

PII solve(){
    int maxDepth = 0;

    //get basic graph
    vector<vector<int>> graphBlock(code.size(), vector<int>());
    int itrCode = 0;
    recGraph(-1, graphBlock, itrCode);
    
    //get posBlock
    int globalInd = 0;
    vector<PII> posBlockX = getPosBlock(graphBlock, globalInd);

    //get max Depth size
    vector<int> depth = getDepth(maxDepth, graphBlock);
   
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

    getData();

    PII ansS = solve();
    cout<<ansS.first<<"\n"<<ansS.second<<"\n";

    return 0;
}