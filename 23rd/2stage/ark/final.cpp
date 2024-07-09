#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

bool operator==(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    if (lhs.first == rhs.first && lhs.second == rhs.second) {
        return true;  
    }
    return false;   
}

bool operator!=(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    if (lhs.first != rhs.first || lhs.second != rhs.second) {
        return true;  
    }
    return false;   
}

PII operator+(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return MP(lhs.first + rhs.first, lhs.second + rhs.second);
}

PII& operator+=( pair<int, int>& lhs, const pair<int, int>& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

PII& operator*=( pair<int, int>& lhs, const pair<int, int>& rhs) {
    lhs.first *= rhs.first;
    lhs.second *= rhs.second;
    return lhs;
}

PII operator*( const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return MP(lhs.first * rhs.first, lhs.second * rhs.second);
}

int n, m, k;
vector<PII> blocks;

int startX, startY;

void getData(){
    cin>>n>>m>>k;
    for(int i = 0; i<k ;i++){
        int a, b;
        cin>>a>>b;
        blocks.PB(MP(a,b));
    }
    startX = n;
    startY = 0;
}

//return center of a block in scaled grid
PII centerBlock(PII cord){
    return MP(cord.first - 1, cord.second-1);
}

//0 - not wall, 1 - side walls, 2 - floors
int isWall(PII cord){
    if(cord.first == 0 || cord.first == n){
        return 1;
    }
    if(cord.second == 0 || cord.second == m){
        return 2;
    }
    return 0;
}

map<tuple<PII,PII>, tuple<PII,PII, ull>> graphMap;

tuple<PII,PII, ull> graph(PII cord, PII dir){
    return graphMap[MT(cord,dir)];
}

void mergePath(PII cord1, PII dir1, PII cord2, PII dir2, int lon = 0){
    int len = get<2>(graphMap[MT(cord1, dir1*(MP(-1,-1)))]) + get<2>(graphMap[MT(cord2, dir2*(MP(-1,-1)))]) + lon;
    dir1 *= MP(-1,-1);
    graphMap.erase(MT(cord1, dir1));
    graphMap.insert(MP(MT(cord1,dir1),MT(cord2,dir2, len)));
    
    dir1 *= MP(-1,-1);
    dir2 *= MP(-1,-1);
    graphMap.erase(MT(cord2, dir2));
    graphMap.insert(MP(MT(cord2,dir2),MT(cord1,dir1, len)));
    // cout<<"("<<cord1.first<<" "<<cord1.second<<")"<<" <-> "<<"("<<cord2.first<<" "<<cord2.second<<")"<<"\n";
}

void removeBlock(PII b){
    PII top = MP(b.first, b.second+1);
    PII bottom = MP(b.first, b.second-1);
    PII left = MP(b.first-1, b.second);
    PII right = MP(b.first+1, b.second);

    tuple<PII,PII,ull> t1, t2;

    //left - top
    t1 = graph(left, MP(-1,-1));
    t2 = graph(top, MP(1,1));
    if(get<0>(t1) == MP(0,0)) get<0>(t1) = left;
    if(get<0>(t2) == MP(0,0)) get<0>(t2) = top;
    mergePath(get<0>(t1), get<1>(t1), get<0>(t2), get<1>(t2), 1);

    //top - right
    t1 = graph(top, MP(-1,1));
    t2 = graph(right, MP(1,-1));
    if(get<0>(t1) == MP(0,0)) get<0>(t1) = top;
    if(get<0>(t2) == MP(0,0)) get<0>(t2) = right;
    mergePath(get<0>(t1), get<1>(t1),  get<0>(t2), get<1>(t2), 1);

    //right - bottom
    t1 = graph(right, MP(1,1));
    t2 = graph(bottom, MP(-1,-1));
    if(get<0>(t1) == MP(0,0)) get<0>(t1) = right;
    if(get<0>(t2) == MP(0,0)) get<0>(t2) = bottom;
    mergePath(get<0>(t1), get<1>(t1), get<0>(t2), get<1>(t2), 1);

    //bottom - left
    t1 = graph(bottom, MP(1,-1));
    t2 = graph(left, MP(-1,1));
    if(get<0>(t1) == MP(0,0)) get<0>(t1) = bottom;
    if(get<0>(t2) == MP(0,0)) get<0>(t2) = left;
    mergePath(get<0>(t1), get<1>(t1), get<0>(t2), get<1>(t2), 1);
}

bool rightOrineted(PII a, PII b){
    return a.first - a.second > b.first - b.second;
}

bool leftOrineted(PII a, PII b){
    return a.first + a.second < b.first + b.second;
}

void createGraph(){
    vector<PII> intrestPoints;
    for(int i = 1; i<n; i += 2){
        intrestPoints.PB(MP(i,0));
    }
    for(int i = 1; i<m; i += 2){
        intrestPoints.PB(MP(0,i));
    }
    for(int i = 0; i<k; i++){
        PII cen = centerBlock(blocks[i]);
        intrestPoints.PB(MP(cen.first, cen.second - 1));
        intrestPoints.PB(MP(cen.first + 1, cen.second));
        intrestPoints.PB(MP(cen.first - 1, cen.second));
        intrestPoints.PB(MP(cen.first, cen.second + 1));
    }
    for(int i = 1; i<n; i += 2){
        intrestPoints.PB(MP(i,m));
    }
    for(int i = 1; i<m; i += 2){
        intrestPoints.PB(MP(n,i));
    }

    stable_sort(intrestPoints.begin(), intrestPoints.end(), rightOrineted);

    for(int i = 0; i<=intrestPoints.size(); i+=2){
        ull len = intrestPoints[i+1].first - intrestPoints[i].first;
        graphMap.insert(MP(MT(intrestPoints[i], MP(1,1)), MT(intrestPoints[i+1], MP(1,1), len)));
        graphMap.insert(MP(MT(intrestPoints[i+1], MP(-1,-1)), MT(intrestPoints[i], MP(-1,-1), len)));
        // cout<<"("<<intrestPoints[i].first<<" "<<intrestPoints[i].second<<")"<<" <-> "<<"("<<intrestPoints[i+1].first<<" "<<intrestPoints[i+1].second<<")"<<"\n";
    }
    
    stable_sort(intrestPoints.begin(), intrestPoints.end(), leftOrineted);

    for(int i = 0; i<=intrestPoints.size(); i+=2){
        ull len = intrestPoints[i].first - intrestPoints[i+1].first;
        graphMap.insert(MP(MT(intrestPoints[i], MP(-1,1)), MT(intrestPoints[i+1], MP(-1,1), len)));
        graphMap.insert(MP(MT(intrestPoints[i+1], MP(1,-1)), MT(intrestPoints[i], MP(1,-1), len)));
        // cout<<"("<<intrestPoints[i].first<<" "<<intrestPoints[i].second<<")"<<" <-> "<<"("<<intrestPoints[i+1].first<<" "<<intrestPoints[i+1].second<<")"<<"\n";
    }
}

void compressGraph(){
    vector<PII> intrestPoints;
    for(int i = 1; i<n; i += 2){
        if(i == startX) continue;
        tuple t1 = graph(MP(i,0), MP(-1,1));
        tuple t2 = graph(MP(i,0), MP(1,1));
        // cout<<"("<<i<<" "<<0<<"): ";
        mergePath(get<0>(t1), get<1>(t1), get<0>(t2), get<1>(t2));
    }
    for(int i = 1; i<m; i += 2){
        tuple t1 = graph(MP(0,i), MP(1,-1));
        tuple t2 = graph(MP(0,i), MP(1,1));
        // cout<<"("<<0<<" "<<i<<"): ";
        mergePath(get<0>(t1), get<1>(t1), get<0>(t2), get<1>(t2));
    }
    for(int i = 1; i<n; i += 2){
        tuple t1 = graph(MP(i,m), MP(-1,-1));
        tuple t2 = graph(MP(i,m), MP(1,-1));
        // cout<<"("<<i<<" "<<m<<"): ";
        mergePath(get<0>(t1), get<1>(t1), get<0>(t2), get<1>(t2));
    }
    for(int i = 1; i<m; i += 2){
        tuple t1 = graph(MP(n,i), MP(-1,-1));
        tuple t2 = graph(MP(n,i), MP(-1,1));
        // cout<<"("<<n<<" "<<i<<"): ";
        mergePath(get<0>(t1), get<1>(t1), get<0>(t2), get<1>(t2));
    }
}

ull traverseGraph(){
    ull ans = 0;

    PII cord = MP(startX, startY);
    PII dir = MP(-1,1);

    map<PII,bool> blocksMap;
    for(int i = 0; i<k; i++){
        blocksMap.insert(MP(centerBlock(blocks[i]), false));
    }

    int blocksLeft = k;
    while(blocksLeft > 0){
        tuple t = graph(cord, dir);
        ans += get<2>(t);

        PII nextCord = get<0>(t);
        PII nextDir = get<1>(t);

        int w = isWall(nextCord);
        if(w == 1){
            nextDir.first *= -1;
        }else if(w == 2){
            nextDir.second *= -1;
        }else{
            auto it = blocksMap.find(MP(nextCord.first + nextDir.first, nextCord.second));
            if(it != blocksMap.end()){
                nextDir.first *= -1;

                removeBlock(it->first);
                blocksLeft--;
            }else{
                it = blocksMap.find(MP(nextCord.first, nextCord.second + nextDir.second));
                if(it != blocksMap.end()){
                    nextDir.second *= -1;
                    removeBlock(it->first);
                    blocksLeft--;
                }
            }
        }

        cord = nextCord;
        dir = nextDir;
    }

    return ans;
} 

ull solve(){
    // cout<<"======================STANDARD: \n\n";
    createGraph();
    // cout<<"=====================COMPRESSSED: \n\n";
    compressGraph();
    // cout<<"=====================REMOVED BLOCKS: \n\n";
    ull ans = traverseGraph();
    return ans;
    // return 0;
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