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

void printGraph(PII pos){
    bool specific = false;
    if(pos != MP(-1,-1)){
        specific = true;
    }
    int count = 1;
    for(auto itr = graph.begin(); itr!= graph.end(); itr++){
        if(!specific || itr->first.first == pos || itr->second.first.first == pos){
            cout<<count<<" | ";
            cout<<"("<<itr->first.first.first<<", "<<itr->first.first.second<<")x("<<itr->first.second.first<<", "<<itr->first.second.second<<")";
            cout<<"->";
            cout<<"("<<itr->second.first.first.first<<", "<<itr->second.first.first.second<<")x("<<itr->second.first.second.first<<", "<<itr->second.first.second.second<<")";
            cout<<"LEN"<<itr->second.second<<"\n";
        }

        count++;
    }
}

bool leftOrder(PII a, PII b){
    return a.first + a.second < b.first + b.second;
}

bool rightOrder(PII a, PII b){
    return a.first - a.second > b.first - b.second;
}

void createGraph(){
    vector<PII> points;
    for(int i = 1; i<n; i+=2){
        points.PB(MP(i,0));
    }
    for(int i = 1; i<m; i+=2){
        points.PB(MP(0,i));
    }
    for(int i = 0 ; i<blocks.size(); i++){
        points.PB(blocks[i] + MP(-1,0));
        points.PB(blocks[i] + MP(0,-1));
        points.PB(blocks[i] + MP(-1,-2));
        points.PB(blocks[i] + MP(-2,-1));
    }
    for(int i = 1; i<m; i+=2){
        points.PB(MP(n,i));
    }
    for(int i = 1; i<n; i+=2){
        points.PB(MP(i,m));
    }
    
    //left
    sort(points.begin(), points.end(), greater<pair<int,int>>());
    stable_sort(points.begin(), points.end(), leftOrder);
    for(int i = 0; i<points.size(); i+=2){
        int len = points[i+1].second-points[i].second;
        if(len < 0) len *= -1;
        graph.insert(MP(MP(points[i], MP(-1,1)), MP(MP(points[i+1], MP(-1,1)), len)));
        graph.insert(MP(MP(points[i+1], MP(1,-1)), MP(MP(points[i], MP(1,-1)), len)));
    }

    //right
    sort(points.begin(), points.end());
    stable_sort(points.begin(), points.end(), rightOrder);
    for(int i = 0; i<points.size(); i+=2){
        int len = points[i+1].second-points[i].second;
        if(len < 0) len *= -1;
        graph.insert(MP(MP(points[i], MP(1,1)), MP(MP(points[i+1], MP(1,1)), len)));
        graph.insert(MP(MP(points[i+1], MP(-1,-1)), MP(MP(points[i], MP(-1,-1)), len)));
    }
}

void compressWall(PII pos){
    PII dir1, dir2;
    if(pos.second == m){ // top
        dir1 = MP(1,-1);
        dir2 = MP(-1,-1);
    }
    if(pos.first == n){ // right
        dir1 = MP(-1,1);
        dir2 = MP(-1,-1);
    }
    if(pos.second == 0){ // bottom
        dir1 = MP(-1,1);
        dir2 = MP(1,1);
    }
    if(pos.first == 0){ // left
        dir1 = MP(1,1);
        dir2 = MP(1,-1);
    }

    auto cur1 = graph[MP(pos,dir1)];
    auto cur2 = graph[MP(pos,dir2)];

    pair<PII,PII> temp = cur1.first;
    PII neg = MP(-1,-1);
    temp.second *= neg;
    auto it = graph.find(temp);
    if(it == graph.end()) {
        cout<<"ERROR - edges not found\n";
    }
    it->second.first = cur2.first;
    it->second.second = cur1.second+cur2.second;

    temp = cur2.first;
    temp.second *= neg;
    it = graph.find(temp);
    if(it == graph.end()) {
        cout<<"ERROR - edges not found\n";
    }
    it->second = cur1;
    it->second.second = cur1.second+cur2.second;
}

void compressGraph(){
    for(int i = 1; i<n; i+=2){ // top
        compressWall(MP(i,m));
    }
    for(int i = 1; i<m; i+=2){ // right
        compressWall(MP(n,i));
    }
    for(int i = 1; i<n; i+=2){ // bottom
        // if(i == n/2) continue;
        compressWall(MP(i,0));
    }
    for(int i = 1; i<m; i+=2){ // left
        compressWall(MP(0,i));
    }
}

void mergeEdges(pair<pair<PII,PII>,int> cur1, pair<pair<PII,PII>,int> cur2){
    PII flip = MP(-1,-1);

    auto temp = cur1.first;
    temp.second *= flip;
    auto itr = graph.find(temp);
    itr->second.first = cur2.first;
    itr->second.second = cur1.second+cur2.second + 1;

    cout<<"("<<itr->first.first.first<<", "<<itr->first.first.second<<")x("<<itr->first.second.first<<", "<<itr->first.second.second<<")";
    cout<<"->";
    cout<<"("<<itr->second.first.first.first<<", "<<itr->second.first.first.second<<")x("<<itr->second.first.second.first<<", "<<itr->second.first.second.second<<")";
    cout<<"LEN"<<itr->second.second<<"\n";
    

    temp = cur2.first;
    temp.second *= flip;
    itr = graph.find(temp);
    itr->second.first = cur1.first;
    itr->second.second = cur1.second+cur2.second  + 1;

    cout<<"("<<itr->first.first.first<<", "<<itr->first.first.second<<")x("<<itr->first.second.first<<", "<<itr->first.second.second<<")";
    cout<<"->";
    cout<<"("<<itr->second.first.first.first<<", "<<itr->second.first.first.second<<")x("<<itr->second.first.second.first<<", "<<itr->second.first.second.second<<")";
    cout<<"LEN"<<itr->second.second<<"\n";
}

int isWall(PII pos){
    if(pos.second == 0 || pos.second == m){
        return 1;
    }
    if(pos.first == 0 || pos.first == n){
        return 2;
    }
    return -1;
}

void bounceWall(PII& dir, int type){
    if(type == 1){
        dir.second *= -1;
    }
    if(type == 2){
        dir.first *= -1;
    }
}

ull traverseGraph(){
    ull ans = 0;

    PII pos = MP(n/2, 0);
    PII dir = MP(-1,1);

    map<pair<PII,PII>,int> blocksMap;
    for(int i = 0; i<blocks.size(); i++){
        //top
        blocksMap.insert(MP(MP(blocks[i] + MP(-1,0), MP(1,-1)), i));
        blocksMap.insert(MP(MP(blocks[i] + MP(-1,0), MP(-1,-1)), i));

        //right
        blocksMap.insert(MP(MP(blocks[i] + MP(0,-1),MP(-1,1)), i));
        blocksMap.insert(MP(MP(blocks[i] + MP(0,-1),MP(-1,-1)), i));

        //bottom
        blocksMap.insert(MP(MP(blocks[i] + MP(-1,-2),MP(1,1)), i));
        blocksMap.insert(MP(MP(blocks[i] + MP(-1,-2),MP(-1,1)), i));

        //left
        blocksMap.insert(MP(MP(blocks[i] + MP(-2,-1),MP(1,1)), i));
        blocksMap.insert(MP(MP(blocks[i] + MP(-2,-1),MP(1,-1)), i));
    }  

    vector<bool> used(k+1, false);

    int countBlock = k;
    int bb = 0;
    while(countBlock > 0){
        // bb++;
        // if(bb> 6) return 0;
        // printGraph(pos)
        auto cur = graph[MP(pos,dir)];
        pos = cur.first.first;
        dir = cur.first.second;
        ans += cur.second;
        auto itrB = blocksMap.find(MP(pos,dir));
        if(itrB == blocksMap.end()){
            //wall bounce
            int type = isWall(pos);
            bounceWall(dir, type);
        }else{
            int type;
            if(used[itrB->second]){
                type = isWall(pos);
                bounceWall(dir, type);
                continue;
            }
            used[itrB->second] = true;
            //remove block
            PII t = blocks[itrB->second] + MP(-1,0), r = blocks[itrB->second] + MP(0,-1), b = blocks[itrB->second] + MP(-1,-2), l = blocks[itrB->second] + MP(-2,-1);

            vector<pair<pair<pair<PII,PII>,int>,pair<pair<PII,PII>,int>>> vec;
            //left
            auto curTL = graph[MP(t,MP(-1,1))];
            auto curRL = graph[MP(r,MP(1,-1))];
            auto curBL = graph[MP(b,MP(1,-1))];
            auto curLL = graph[MP(l,MP(-1,1))];

            auto curTR = graph[MP(t,MP(1,1))];
            auto curRR = graph[MP(r,MP(1,1))];
            auto curBR = graph[MP(b,MP(-1,-1))];
            auto curLR = graph[MP(l,MP(-1,-1))];

            vec.PB(MP(curRR,curBR));
            vec.PB(MP(curLL,curBL));
            vec.PB(MP(curTR,curLR));
            vec.PB(MP(curTL,curRL));

            // vec.PB(MP(curTL,curRL));
            // vec.PB(MP(curTR,curLR));
            // vec.PB(MP(curLL,curBL));
            // vec.PB(MP(curRR,curBR));

            int start = 0;
            if(pos == t){
                start = 0;
            }else if(pos == r){
                start = 1;
            }else if(pos == b){
                start = 2;
            }else{
                start = 3;
            }

            cout<<countBlock<<"\n";
            for(int i = 0; i<4; i++){
                auto p1 = vec[(start+i+1)%4].first;
                auto p2 = vec[(start+i+1)%4].second;
                mergeEdges(p1,p2);
            }

            countBlock--;

            //bounce
            type;
            if(pos == t || pos == b){
                type = 1;
            }else{
                type = 2;
            }
            bounceWall(dir, type);
        }
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