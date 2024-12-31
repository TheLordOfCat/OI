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

int maxGuesses = 1'000'000;

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

vector<int> getGroup(int type, int maxVer){
    vector<int> ans;
    vector<bool> part(maxVer, false);
    if(type == 0){
        part[1] = true;
        ans.PB(1);
    }else{
        part[2] = true;
        ans.PB(2);
    }
    int ind = 3;
    for(int i = 0; i<input.size(); i++){
        if(input[i].first == 'W'){
            if(!part[input[i].second]){
                ans.PB(ind);
            }
            ind++;
        }else if(input[i].first == 'Z'){
            if(part[input[i].second]){
                ans.PB(ind);
            }
            ind++;
        }
    }

    return ans;
}

pair<vector<PII>, vector<vector<PII>>> getGraph(vector<int>& mainGroup, int &maxVer){
    vector<PII> loc(maxVer+1,MP(0,0));
    vector<PII> point(maxVer+1, MP(0,0));
    vector<vector<PII>> graph;
    graph.PB(vector<PII>());
    graph.PB(vector<PII>());
    if(mainGroup.front() == 1){
        graph[0].PB(MP(1,2));
        point[1] = MP(0,1);
        loc[2] = MP(0,1);
    }else{
        graph[0].PB(MP(1,1));
        point[2] = MP(0,1);
        loc[1] = MP(0,1);
    }

    vector<bool> part(maxVer+1, false);
    for(int i = 0; i<mainGroup.size(); i++){
        part[mainGroup[i]] = true;
    }
    
    int ind = 3;
    for(int i =0 ; i<input.size(); i++){
        if(input[i].first == '?'){
            continue;
        }
        int x = input[i].second;
        if(part[x]){
            if(input[i].first == 'W'){
                //extend
                graph.PB(vector<PII>());
                graph[point[x].second].PB(MP(graph.size()-1, ind));
                point[x].second = graph.size()-1;
                loc[ind] = MP(point[x].second, graph.size()-1);
            }else{
                point[ind] = point[x];
            }
        }else{
            if(input[i].first == 'W'){
                point[ind] = loc[x];
            }else{
                //switch
                graph.PB(vector<PII>());
                int cur;
                for(int j = 0; j<graph[loc[x].first].size(); i++){
                    if(graph[loc[x].first][j].second == x){
                        cur = j;
                        break;
                    }
                }

                graph.back().PB(MP(loc[x].second, x));
                graph[loc[x].first][cur] = MP(graph.size()-1,ind);
                loc[ind] = MP(loc[x].first, graph.size()-1);
                loc[x].first = graph.size()-1;
            }
        }
        ind++;
    }
    return MP(point, graph);
}

pair<vector<int>, vector<PII>> getPath(vector<vector<PII>> &graph, int maxVer, vector<PII>& convert){
    vector<int> ans1;
    vector<PII> ans2(maxVer+1, MP(-1,-1));

    stack<pair<PII,bool>> S;
    S.push(MP(MP(0,-1),false));

    while(!S.empty()){
        PII v = S.top().first;
        bool b = S.top().second;
        S.pop();
        if(b){
            ans1.PB((-1)*v.second);
            ans2[v.second].second = ans1.size()-1;
            convert[v.first].second = ans1.size()-1;
            continue;
        }

        if(v.second != -1){
            ans1.PB(v.second);
            ans2[v.second].first = ans1.size()-1;
            convert[v.first].first = ans1.size()-1;
        }

        for(int i = 0; i<graph[v.first].size(); i++){
            PII cur = graph[v.first][i];
            S.push(MP(cur, true));
            S.push(MP(cur, false));
        }
    }

    return MP(ans1,ans2);
}

int left(int v){
    return v*2;
}

int right(int v){
    return v*2+1;
}

int leaf(int v, int R){
    return R+v+1;
}

int parent(int v){
    return v/2;
}

vector<int> buildTree(int &R, vector<int>& base){
    int depth = 0;
    R = 0;
    while((1<<depth) < base.size()){
        R += (1<<depth);
        depth++;
    }

    vector<int> tree(R+(1<<depth)+2, 0);
    return tree;
}   

int query(int l, int r, int R, vector<int>& tree){
    int ans = 0;
    int vL = leaf(l, R);
    int vR = leaf(r, R);

    ans += tree[vL];
    if(vL != vR){
        ans += tree[vR];
    }

    while(parent(vL) != parent(vR)){
        if(left(parent(vL)) == vL){
            ans += tree[right(parent(vL))];
        }
        if(right(parent(vR)) == vR){
            ans += tree[left(parent(vR))];
        }
        vL = parent(vL);
        vR = parent(vR);
    }
    return ans;
}

void updateSingle(int v, int R, vector<int>& tree, int val){
    int V = leaf(v,R);

    while(V >= 1){
        tree[V] += val;
        V = parent(V);
    }
}

vector<int> solve(){
    //max ver
    int maxVer = 2;
    for(int i =0; i<input.size(); i++){
        if(input[i].first != '?'){
            maxVer++;
        }
    }

    //split into groups
    vector<int> X = getGroup(0, maxVer);
    vector<int> Y = getGroup(1, maxVer);

    //get graphs
    pair<vector<PII>, vector<vector<PII>>> graphX = getGraph(X, maxVer);
    pair<vector<PII>, vector<vector<PII>>> graphY = getGraph(Y, maxVer);

    //get traversal
    vector<PII> convertX(maxVer, MP(-1,-1)), convertY(maxVer, MP(-1,-1));
    pair<vector<int>,vector<PII>> pathX = getPath(graphX.second, maxVer, convertX);
    pair<vector<int>,vector<PII>> pathY = getPath(graphY.second, maxVer, convertY);

    //create segTree
    int RX, RY;
    vector<int> treeX = buildTree(RX, pathX.first);
    vector<int> treeY = buildTree(RY, pathY.first);
    
    //get ans
    vector<int> ans;
    vector<bool> part(maxVer, false);
    for(int i = 0; i<X.size(); i++){
        part[X[i]] = true;
    }
    int ind = 3;

    //initialilize
    updateSingle(pathX.second[2].first, RX, treeX, 1);
    updateSingle(pathX.second[2].second, RX, treeX, -1);
    updateSingle(pathY.second[1].first, RY, treeY, 1);
    updateSingle(pathY.second[1].second, RY, treeY, -1);

    for(int i = 0; i<input.size(); i++){
        int x = input[i].second;
        if(input[i].first == '?'){
            int temp;
            if(part[x]){
                temp = query(convertX[graphX.first[x].first].first, convertX[graphX.first[x].second].first-1, RX, treeX);
            }else{
                temp = query(pathY.second[x].first, pathY.second[x].second, RY, treeY);
            }
            ans.PB(temp);
        }else{
            if(part[ind]){
                updateSingle(pathY.second[x].first, RY, treeY, 1);
                updateSingle(pathY.second[x].second, RY, treeY, -1);
            }else{
                updateSingle(pathX.second[x].first, RX, treeX, 1);
                updateSingle(pathX.second[x].second, RX, treeX, -1);
            }
            ind++;
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