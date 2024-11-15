#include <iostream>
#include <vector>
#include <stack>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int q;
vector<pair<char,int>> input;

int maxGeusts = 1'000'000;

void getData(){
    cin>>q;
    for(int i = 0; i<q; i++){
        char c;
        cin>>c;
        int x;
        cin>>x;
        input.PB(MP(c,x));
    }
}

vector<vector<PII>> graphX, graphY;
vector<PII> pointX, pointY;
vector<PII> edgesX, edgesY;

void getDominant(vector<vector<PII>>& graph, vector<PII>& point, vector<PII>& edges, vector<bool>& group){
    int totalGuests = 2;
    for(int i = 0; i<input.size(); i++){
        char c = input[i].first;
        int x = input[i].second;
        if(c == 'Z'){
            totalGuests++;
            if(group[totalGuests]){
                graph.PB(vector<PII>());
                graph.back().PB(MP(edges[x].first, totalGuests));
                graph[edges[x].first].PB(MP(graph.size()-1, totalGuests));

                graph.back().PB(MP(edges[x].second, x)); 
                graph[edges[x].second].PB(MP(graph.size()-1, x));

                edges[totalGuests] = MP(edges[x].first, graph.size()-1);
                edges[x] = MP(graph.size()-1, edges[x].second);
            }else{
                point[totalGuests] = point[x];
            }
        }
        if(c == 'W'){
            totalGuests++;
            if(group[totalGuests]){
                graph.PB(vector<PII>());
                graph.back().PB(MP(point[x].second, totalGuests));
                edges[totalGuests] = MP(point[x].second, graph.size()-1);
                graph[point[x].second].PB(MP(graph.size()-1, totalGuests));
                point[x] = MP(point[x].first, graph.size()-1);
            }else{
                point[totalGuests] = edges[x];
            }
        }
    }
}

pair<vector<int>, vector<PII>> traverseGraph(vector<vector<PII>>& graph, vector<PII>& edges){
    vector<int> ans1;
    vector<PII> ans2(graph.size(), MP(-1,-1));

    stack<pair<int,bool>> S;
    S.push(MP(0, false));
    vector<bool> vis(graph.size(), false);

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();

        if(b){
            ans1.PB((-1)*v);
            ans2[v].second = ans1.size()-1;
            continue;
        }
        if(vis[v]){
            continue;
        }
        ans1.PB(v);
        ans2[v].first = ans1.size()-1;
        vis[v] = true;

        S.push(MP(v, true));
        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            if(!vis[cur.first] && ((edges[cur.second].first == v && edges[cur.second].second == cur.first) || (edges[cur.second].second == v && edges[cur.second].first == cur.first))){
                S.push(MP(cur.first, false));
            }
        }
    }

    return MP(ans1,ans2);
}

int parent(int v){
    return v/2;
}

int left(int v){
    return 2*v;
}

int right(int v){
    return 2*v+1;
}

int leaf(int v, int R){
    return R+v;
}

tuple<vector<int>, int, int> buildTree(vector<int>& trav){
    vector<int> segTree;
    int R = 0;
    int depth = 0;
    while((1<<depth) < trav.size()){
        R += (1<<depth);
        depth++;
    }
    
    segTree.assign((R+(1<<depth)), 0);
    segTree[leaf(trav.front(), R)] = 1;
    return MT(segTree, R, depth);
}

int queryTree(int tL, int tR, int l, int r, int v, vector<int>& tree){
    int vL = leaf(l, R);
    int vR = leaf(r, R);

    int ans = 0;
    ans += tree[vL];
    if(vL != vR) ans += tree[vR];

    while(parent(vL) != parent(vR)){
        if(left(parent(vL)) == vL){
            ans += right(parent(vL));
        }
        if(right(parent(vR)) == vR){
            ans += left(parent(vR));
        }
        vL = parent(vL);
        vR = parent(vR);
    }

    return ans;
}

void updateTree(int v, int R, int val, vector<int>& tree){
    int V = leaf(v, R);

    while(V >= 1){
        tree[V] += val;
        V = parent(V);
    }
}

vector<int> solve(){
    graphX.clear(); graphY.clear(); pointX.clear(); pointY.clear(); edgesX.clear(); edgesY.clear();

    graphX.assign(2, vector<PII>()); graphY.assign(2, vector<PII>());
    pointX.assign(q+1, MP(-1,-1)); pointY.assign(q+1, MP(-1,-1));
    edgesX.assign(q+1, MP(-1,-1)); edgesY.assign(q+1, MP(-1,-1)); 

    //split guests into groups
    vector<bool> groupX(q+1, false), groupY(q+1, false); 
    vector<int> setX = {1};
    vector<int> setY = {2};

    edgesX[1] = MP(0,1);
    pointX[2] = MP(0,1);
    pointY[1] = MP(0,1);
    edgesY[2] = MP(0,1);

    graphX[0].PB(MP(1,1));
    graphX[1].PB(MP(0,1));
    graphY[0].PB(MP(1,2));
    graphY[1].PB(MP(0,2));

    groupX[1] = true;
    groupY[2] = true;
    int totalGuests = 2;
    for(int i = 0; i<input.size(); i++){
        char c = input[i].first;
        int x =  input[i].second;
        if(c != '?'){
            totalGuests++;
            if(groupX[x]){
                if(c == 'W'){
                    groupY[totalGuests] = true;
                    setY.PB(totalGuests);
                }
                if(c == 'Z'){
                    groupX[totalGuests] = true;
                    setX.PB(totalGuests);
                }
            }
            if(groupY[x]){
                if(c == 'W'){
                    groupX[totalGuests] = true;
                    setX.PB(totalGuests);
                }
                if(c == 'Z'){
                    groupY[totalGuests] = true;
                    setY.PB(totalGuests);
                }
            }
        }
    }   

    //create graph
    getDominant(graphX, pointX, edgesX, groupX);
    getDominant(graphY, pointY, edgesY, groupY);

    //create seg tree
    pair<vector<int>, vector<PII>> travX = traverseGraph(graphX, edgesX);
    pair<vector<int>, vector<PII>> travY = traverseGraph(graphY, edgesY);

    tuple<vector<int>, int, int> segX = buildTree(travX.first);
    tuple<vector<int>, int, int> segY = buildTree(travY.first);

    //get ans
    vector<int> ans;
    totalGuests = 2;
    //initialize 1
    updateTree(travX.second[edgesX[1].first].first, get<1>(segX), 1, get<0>(segX));
    updateTree(travX.second[edgesX[1].first].second, get<1>(segX), -1, get<0>(segX));

    //intailize 2
    updateTree(travY.second[edgesY[2].first].first, get<1>(segY), 1, get<0>(segY));
    updateTree(travY.second[edgesY[2].first].second, get<1>(segY), -1, get<0>(segY));
    for(int i =0; i<input.size(); i++){
        char c = input[i].first;
        int x = input[i].second;
        if(c != '?'){
            totalGuests++;
            if(groupX[x]){
                updateTree(travX.second[edgesX[x].first].first, get<1>(segX), 1, get<0>(segX));
                updateTree(travX.second[edgesX[x].first].second, get<1>(segX), -1, get<0>(segX));
            }
            if(groupY[x]){
                updateTree(travY.second[edgesY[x].first].first, get<1>(segY), 1, get<0>(segY));
                updateTree(travY.second[edgesY[x].first].second, get<1>(segY), -1, get<0>(segY));
            }   
        }
        if(c == '?'){
            int temp;
            if(groupX[x]){
                int vt = travY.second[pointY[x].first].first, vb = travY.second[pointY[x].second].second;
                int R= get<1>(segY);
                temp = queryTree(left(1,R), get<0>(segY).size(), leaf(vt,R), leaf(vb, R), 1, get<0>(segY));
            }
            if(groupY[x]){
                int vt = travX.second[pointX[x].first].first, vb = travX.second[pointX[x].second].second;
                temp = queryTree(vt, vb, get<1>(segX), get<0>(segX));
            }
            ans.PB(temp);
        }
    }
    
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    vector<int> ansS = solve();

    for(int i =0; i< ansS.size(); i++){
        cout<<ansS[i]<<" ";
    }
    return 0;
}