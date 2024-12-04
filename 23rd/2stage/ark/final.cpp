#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

PII& operator+=( PII& lhs, PII& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

PII& operator -=(PII& lhs, PII& rhs){
    lhs.first -= rhs.first;
    lhs.second -= rhs.second;
    return lhs;
}

PII& operator *=(PII& lhs, PII& rhs){
    lhs.first *= rhs.first;
    lhs.second *= rhs.second;
    return lhs;
}

PII operator +(const PII& a, const PII& b){
    PII ans = MP(0,0);
    ans.first = a.first + b.first;
    ans.second = a.second + b.second;
    return ans;
}

PII operator -(const PII& a, const PII& b){
    PII ans = MP(0,0);
    ans.first = a.first - b.first;
    ans.second = a.second - b.second;
    return ans;
}

bool operator ==(const PII& a, const PII& b){
    if(a.first == b.first && a.second == b.second){
        return true;
    }
    return false;
}

int n, m, k;
vector<PII> blocks;

void getData(){
    cin>>n>>m>>k;
    for(int i = 0; i<k ;i++){
        int a, b;
        cin>>a>>b;
        blocks.PB(MP(a,b));
    }
}

map<pair<PII,PII>, pair<pair<PII,PII>, ull>> graph;

bool leftOrder(PII a, PII b){
    return a.first + a.second == b.first + b.second;
}

bool rightOrder(PII a, PII b){
    return a.first - a.second == b.first - b.second;
}

void createGraph(){
    vector<PII> points;
    for(int i = 1; i<m; i+=2){
        points.PB(MP(0,i));
    }
    for(int i = 1; i<n; i+=2){
        points.PB(MP(i,0));
    }
    for(int i = 0 ; i<blocks.size(); i++){
        points.PB(blocks[i] + MP(-1,0));
        points.PB(blocks[i] + MP(0,-1));
        points.PB(blocks[i] + MP(-2,-1));
        points.PB(blocks[i] + MP(-1,-2));
    }
    for(int i = 1; i<m; i+=2){
        points.PB(MP(n,i));
    }
    for(int i = 1; i<n; i+=2){
        points.PB(MP(i,m));
    }
    
    //left
    stable_sort(points.begin(), points.end(), leftOrder);
    for(int i = 0; i<points.size(); i+=2){
        graph.insert(MP(MP(points[i], MP(-1,1)), MP(MP(points[i+1], MP(-1,1)), points[i+1].first-points[i].first)));
        graph.insert(MP(MP(points[i+1], MP(1,-1)), MP(MP(points[i], MP(1,-1)), points[i+1].first-points[i].first)));
    }

    //right
    stable_sort(points.begin(), points.end(), rightOrder);
    for(int i = 0; i<points.size(); i+=2){
        graph.insert(MP(MP(points[i], MP(1,1)), MP(MP(points[i+1], MP(1,1)), points[i+1].first-points[i].first)));
        graph.insert(MP(MP(points[i+1], MP(-1,-1)), MP(MP(points[i], MP(-1,-1)), points[i+1].first-points[i].first)));
    }
}

void compressWall(PII pos){
    PII dir1, dir2;
    if(pos.first == 0){
        dir1 = MP(1,-1);
        dir2 = MP(1,1);
    }
    if(pos.first == m){
        dir1 = MP(-1,1);
        dir2 = MP(-1,-1);
    }
    if(pos.second == 0){
        dir1 = MP(-1,1);
        dir2 = MP(1,1);
    }
    if(pos.second == m){
        dir1 = MP(-1,-1);
        dir2 = MP(1,-1);
    }

    auto cur1 = graph[MP(pos,dir1)];
    auto cur2 = graph[MP(pos,dir2)];

    pair<PII,PII> temp = cur1.first;
    PII neg = MP(-1,-1);
    temp.second *= neg;
    auto it = graph.find(temp);
    it->second.first = cur2.first;
    it->second.second = cur1.second+cur2.second;

    temp = cur2.first;
    temp.second *= neg;
    it = graph.find(temp);
    it->second = cur1;
    it->second.second = cur1.second+cur2.second;
}

void compressGraph(){
    for(int i = 1; i<m; i+=2){ // top
        compressWall(MP(n,i));
    }
    for(int i = 1; i<n; i+=2){ // right
        compressWall(MP(i,m));
    }
    for(int i = 1; i<m; i+=2){ // bottom
        compressWall(MP(0,i));
    }
    for(int i = 1; i<n; i+=2){ // left
        compressWall(MP(i,0));
    }
}

void mergeEdges(pair<pair<PII,PII>,int> cur1, pair<pair<PII,PII>,int> cur2){
    PII flip = MP(-1,-1);

    auto temp = cur1.first;
    temp.second *= flip;
    auto itr = graph.find(temp);
    itr->second.first = cur2.first;
    itr->second.second = cur1.second+cur2.second;

    temp = cur2.first;
    temp.second *= flip;
    itr = graph.find(temp);
    itr->second.first = cur1.first;
    itr->second.second = cur1.second+cur2.second;
}

ull traverseGraph(){
    ull ans = 0;

    PII pos = MP(n/2, 0);
    PII dir = MP(-1,1);

    map<PII,int> blocksMap;
    for(int i = 0; i<blocks.size(); i++){
        blocksMap.insert(MP(blocks[i] + MP(-1,0), i));
        blocksMap.insert(MP(blocks[i] + MP(0,-1), i));
        blocksMap.insert(MP(blocks[i] + MP(-1,-2), i));
        blocksMap.insert(MP(blocks[i] + MP(-2,-1), i));
    }  

    int countBlock = k;
    while(countBlock > 0){
        auto cur = graph[MP(pos,dir)];
        pos = cur.first.first;
        dir = cur.first.second;
        ans += cur.second;
        auto itrB = blocksMap.find(pos);
        if(itrB == blocksMap.end()){
            cout<<"LOGIC BAD eroror\n";
            return 0;
        }
        
        //remove block
        PII t = blocks[itrB->second] + MP(-1,0), r = blocks[itrB->second] + MP(0,-1), b = blocks[itrB->second] + MP(-1,-2), l = blocks[itrB->second] + MP(-2,-1);

        //left
        auto curT = graph[MP(t,MP(-1,1))];
        auto curR = graph[MP(r,MP(1,1))];
        auto curB = graph[MP(b,MP(-1,-1))];
        auto curL = graph[MP(l,MP(-1,1))];

        mergeEdges(curT,curR);
        mergeEdges(curL,curB);

        //right
        curT = graph[MP(t,MP(1,1))];
        curR = graph[MP(r,MP(1,-1))];
        curB = graph[MP(b,MP(1,-1))];
        curL = graph[MP(t,MP(-1,-1))];

        mergeEdges(curT,curL);
        mergeEdges(curR,curB);
    }

    return ans;
}

ull solve(){
    //create graph
    createGraph();
    //compress graph
    compressGraph();
    //traverse graph
    ull ans = traverseGraph();
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();   
    //scaling the grid
    for(int i = 0; i<k; i++){
        blocks[i].first *= 2;
        blocks[i].second *= 2;
    }
    n *= 2;
    m *= 2;

    ull ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}