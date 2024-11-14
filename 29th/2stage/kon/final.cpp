#include <iostream>
#include <vector>
#include <stack>

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
    int totalGuests = 1;
    for(int i = 0; i<input.size(); i++){
        char c = input[i].first;
        int x = input[i].second;
        totalGuests++;
        if(c == 'Z'){
            if(group[totalGuests]){
                point[totalGuests] = point[x];
            }else{
                graph.PB(vector<PII>());
                graph.back().PB(MP(edges[x].first, totalGuests)); //posibble error
                graph.back().PB(MP(edges[x].second, x)); 
                edges[totalGuests] = MP(edges[x].first, graph.size()-1);

                graph[point[x].first].pop_back();
                graph[point[x].second].erase(graph[point[x].second].begin());

                graph[point[x].first].PB(MP(graph.size()-1, totalGuests));
                graph[point[x].second].PB(MP(graph.size()-1, x));
            }
        }
        if(c == 'W'){
            if(group[totalGuests]){
                point[totalGuests] = edges[x];
            }else{
                graph.PB(vector<PII>());
                graph.back().PB(MP(point[x].second, totalGuests));
                edges[totalGuests] = MP(point[x].second, graph.size()-1);

                graph[point[x].second].PB(MP(graph.size()-1, totalGuests));
            }
        }
    }
}

vector<int> traverseGraph(vector<vector<PII>>& graph){
    vector<int> ans;

    stack<tuple<int, int, bool>> S;
    S.push(MT(1, 1, false));
    vector<bool> vis(graph.size(), false);

    while(!S.empty()){
        int v = get<0>(S.top());
        int label = get<1>(S.top());
        bool b = get<2>(S.top());
        S.pop();

        if(b){
            ans.PB((-1)*label);
            continue;
        }
        if(vis[v]){
            continue;
        }

        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            if(!vis[cur.first]){
                vis[cur.first] = true;
                S.push(MT(v, cur.second, true));
                S.push(MT(cur.first, cur.second, false));
            }
        }
    }

    return ans;
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

int queryTree(int l, int r, int R, vector<int>& tree){
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

void updateTree(int v, int R, vector<int>& tree){
    int V = leaf(v, R);

    while(V >= 1){
        tree[V] += 1;
        V = parent(V);
    }
}

vector<int> solve(){
    graphX.clear(); graphY.clear(); pointX.clear(); pointY.clear(); edgesX.clear(); edgesY.clear();

    //split guests into groups
    vector<bool> groupX(q+1, false), groupY(q+1, false);
    vector<int> setX;
    vector<int> setY;

    groupX[1] = true;
    groupY[2] = true;
    int totalGuests = 2;
    for(int i = 0; i<input.size(); i++){
        char c = input[i].first;
        int x =  input[i].second;
        if(c != '?'){
            totalGuests++;
            if(groupX[x]){
                groupY[totalGuests] = true;
                setY.PB(totalGuests);
            }
            if(groupY[x]){
                groupX[totalGuests] = true;
                setX.PB(totalGuests);
            }
        }
    }   

    //create graph
    getDominant(graphX, pointX, edgesX, groupX);
    getDominant(graphY, pointY, edgesY, groupY);

    //create seg tree
    vector<int> travX = traverseGraph(graphX);
    vector<int> travY = traverseGraph(graphY);

    tuple<vector<int>, int, int> segX = buildTree(travX);
    tuple<vector<int>, int, int> segY = buildTree(travY);

    //get ans
    vector<int> ans;
    totalGuests = 2;
    for(int i =0; i<input.size(); i++){
        char c = input[i].first;
        int x = input[i].second;
        totalGuests++;
        if(c == '?'){
            int temp;
            if(groupX[totalGuests]){
                temp = queryTree(pointX[x].first, pointX[x].second, get<1>(segX), get<0>(segX));
            }
            if(groupY[totalGuests]){
                temp = queryTree(pointY[x].first, pointY[x].second, get<1>(segY), get<0>(segY));
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