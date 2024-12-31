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

int q;
vector<pair<char,int>> input;

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

void getRandom(){
    input.clear();
    
    srand(time(0));

    q = rand()%10+1;
    int guests = 2;
    for(int i =0 ; i< q; i++){
        int type = rand()%3+1;
        char c;
        if(type == 1){
            c = 'W'; 
            guests++;
        }else if(type == 2){
            c = 'Z';
            guests++;
        }else{
            c = '?';
        }
        int x = rand()%guests+1;
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<q<<"\n";
    for(int i = 0; i<input.size(); i++){
        cout<<input[i].first<<" "<<input[i].second<<"\n";
    }
}

vector<int> brute(){
    vector<vector<int>> graph(3, vector<int>());
    graph[1].PB(2);
    graph[2].PB(1);

    vector<int> ans;

    for(int i =0; i<q; i++){
        char c = input[i].first;
        int x = input[i].second;
        if(c == 'Z'){
            graph.PB(vector<int>());
            for(int j = 0; j<graph[x].size(); j++){
                int cur = graph[x][j];
                graph[cur].PB(graph.size()-1);
                graph[graph.size()-1].PB(cur);
            }
        }
        if(c == 'W'){
            graph.PB(vector<int>());
            graph[x].PB(graph.size()-1);
            graph[graph.size()-1].PB(x);
        }
        if(c == '?'){
            ans.PB(graph[x].size());
        }
    }

    return ans;
}

vector<int> getGroup(int type){
    vector<int> ans;
    for(int i = 0; i<input.size(); i++){
        if(input[i].first != '?'){
            if(type == 0){
                ans.PB(input[i].second);       
            }
            type = (type+1)%2;
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
    }else{
        graph[0].PB(MP(1,1));
        point[2] = MP(0,1);
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
                graph.back().PB(MP(graph[loc[x].first][cur].first, ind));
                graph[loc[x].first][cur].first = graph.size()-1;
            }
        }
        ind++;
    }
    return MP(point, graph);
}

pair<vector<int>, vector<PII>> getPath(vector<vector<PII>> &graph){
    vector<int> ans1;
    vector<PII> ans2;

    stack<pair<int,bool>> S;
    S.push(MP(0,false));

    while(!S.empty()){
        int v = S.top().first;
        bool b = S.top().second;
        S.pop();
        if(b){
            ans1.PB((-1)*v);
            ans2[v].second = ans1.size()-1;
            continue;
        }

        S.push(MP(v, true));
        for(int i = 0; i<graph[v].size(); i++){
            PII cur = graph[v][i];
            ans1.PB(cur.second);
            ans2[v].first = ans1.size()-1;
            S.push(MP(cur.first, false));
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
    return R+v;
}

int parent(int v){
    return v/2;
}

vector<int> buildTree(int &R, vector<int>& base){
    int depth = 0;
    int R = 0;
    while((1<<depth) < base.size()){
        R += (1<<depth);
        depth++;
    }

    vector<int> tree(R+(1<<depth)+1, 0);
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
    vector<int> X = getGroup(0);
    vector<int> Y = getGroup(1);

    //get graphs
    pair<vector<PII>, vector<vector<PII>>> graphX = getGraph(X, maxVer);
    pair<vector<PII>, vector<vector<PII>>> graphY = getGraph(Y, maxVer);

    //get traversal
    pair<vector<int>,vector<PII>> pathX = getPath(graphX.second);
    pair<vector<int>,vector<PII>> pathY = getPath(graphY.second);

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
    for(int i = 0; i<input.size(); i++){
        int x = input[i].second;
        if(input[i].first == '?'){
            int temp;
            if(part[x]){
                temp = query(pathX.second[x].first, pathX.second[x].first, RX, treeX);
            }else{
                temp = query(pathY.second[x].first, pathY.second[x].first, RY, treeY);
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

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: \n";
                for(int i =0; i< ansB.size(); i++){
                    cout<<ansB[i]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: \n";
                for(int i =0; i< ansS.size(); i++){
                    cout<<ansS[i]<<" ";
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