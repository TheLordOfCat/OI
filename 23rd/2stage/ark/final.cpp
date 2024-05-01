#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>

#define MP make_pair
#define PII pair<int, int>
#define PB push_back

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;

const ull ullINF = 18'000'000'000'000;
const int INF = 2'000'000'000;

int n, m, k;
vector<pair<int, int>> blocks;
int startX;
int startY;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

void getData() {
    cin >> m >> n >> k;
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        blocks.PB(MP(a, b));
    }
}

pair<int, int> middle(int x, int y, pair<int, int> d) {
    if (x % 2 == 0) {
        if (d.first == 1) {
            return MP(x + 1, y);
        } else {
            return MP(x - 1, y);
        }
    } else {
        if (d.second == 1) {
            return MP(x, y + 1);
        } else {
            return MP(x, y - 1);
        }
    }
    return MP(INF, INF);
}

struct pos{
    PII dir;
    PII cord;
    pos(PII cord1, PII dir1){
        dir = dir1;
        cord = cord1;
    }
    pos(){
        dir = MP(0,0);
        cord = MP(-1,-1);
    }
};

struct comparePos {
    bool operator()(const pos& lhs, const pos& rhs) const {
        return tie(lhs.cord.first, lhs.cord.second, lhs.dir.first, lhs.dir.second) < 
        tie(rhs.cord.first, rhs.cord.second, rhs.dir.first, rhs.dir.second);
    }
};

map<pos,pair<pos,int>, comparePos> graph;

bool customPairSort(pair<int,PII> a, pair<int,PII> b){
    if(a.first == b.first){
        if(a.second.first == b.second.first){
            return a.second.second < b.second.second;
        }
        return a.second.first < b.second.first;
    }
    return a.first < b.first;
}

void makeEdge(PII a, PII b, PII dir){
    pos start(a,dir);
    pos final(b, dir);
    if(graph.find(start) == graph.end()){
        graph.insert(MP(start,MP(final,b.first-a.first)));
    }
    start.dir.first *= -1;
    start.dir.second *= -1;
    final.dir.first *= -1;
    final.dir.second *= -1;
    if(graph.find(final) == graph.end()){
        graph.insert(MP(final,MP(start,b.first-a.first)));
    }
}

void createGraph(){
    //right tilted

    //finding points of intrest
    vector<pair<int,PII>> intrestPoint;
    for(int i = 1; i<m; i++){
        intrestPoint.PB(MP((-1)*i,MP(i,0)));
        intrestPoint.PB(MP(n-i,MP(i,n)));
    }
    for(int i = 1; i<n; i++){
        intrestPoint.PB(MP(i,MP(0,i)));
        intrestPoint.PB(MP(i-m,MP(m,i)));
    }
    for(int i = 0; i<k; i++){
        pair<int,int> mid = MP(blocks[i].first-1, blocks[i].second-1);
        intrestPoint.PB(MP(mid.second - (mid.first-1),MP(mid.first-1, mid.second)));
        intrestPoint.PB(MP(mid.second - (mid.first+1),MP(mid.first+1, mid.second)));
        intrestPoint.PB(MP(mid.second-1 - (mid.first),MP(mid.first, mid.second-1)));
        intrestPoint.PB(MP(mid.second+1 - (mid.first),MP(mid.first, mid.second+1)));
    }
    //sorting
    sort(intrestPoint.begin(), intrestPoint.end(), customPairSort);

    //creating edges
    for(int i = 0; i<intrestPoint.size()-1; i++){
        if(intrestPoint[i].first == intrestPoint[i+1].first){
            makeEdge(intrestPoint[i].second, intrestPoint[i+1].second, MP(1,1));
        }
    }

    //left tilted

    //finding points of intrest
    intrestPoint.clear();
    for(int i = 1; i<m; i++){
        intrestPoint.PB(MP(i,MP(i,0)));
        intrestPoint.PB(MP(n+i,MP(i,n)));
    }
    for(int i = 1; i<n; i++){
        intrestPoint.PB(MP(i,MP(0,i)));
        intrestPoint.PB(MP(i+m,MP(m,i)));
    }
    for(int i = 0; i<k; i++){
        pair<int,int> mid = MP(blocks[i].first-1, blocks[i].second-1);
        intrestPoint.PB(MP(mid.second + (mid.first-1),MP(mid.first-1, mid.second)));
        intrestPoint.PB(MP(mid.second + (mid.first+1),MP(mid.first+1, mid.second)));
        intrestPoint.PB(MP(mid.second-1 + (mid.first),MP(mid.first, mid.second-1)));
        intrestPoint.PB(MP(mid.second+1 + (mid.first),MP(mid.first, mid.second+1)));
    }
    //sorting
    sort(intrestPoint.begin(), intrestPoint.end(), customPairSort);

    //creating edges
    for(int i = 0; i<intrestPoint.size()-1; i++){
        if(intrestPoint[i].first == intrestPoint[i+1].first){
            makeEdge(intrestPoint[i].second, intrestPoint[i+1].second, MP(1,-1));
        }
    }

}

void compressEdge(pos a, pos b, int len){
    a.dir.first *= -1;
    a.dir.second *= -1;
    graph.erase(a);
    graph.insert(MP(a,MP(b,len)));

    a.dir.first *= -1;
    a.dir.second *= -1;
    b.dir.first *= -1;
    b.dir.second *= -1;
    graph.erase(b);
    graph.insert(MP(b,MP(a,len)));
}

void compressGraph(){
    for(int i = 1; i<m; i++){
        //bottom
        pos a = graph[pos(MP(i,0), MP(-1,1))].first;
        pos b = graph[pos(MP(i,0), MP(1,1))].first;
        int lena = graph[pos(MP(i,0), MP(-1,1))].second;
        int lenb = graph[pos(MP(i,0), MP(1,1))].second;
        compressEdge(a,b,lena+lenb);
    }
    for(int i = 1; i<n; i++){ 
        //right
        pos a = graph[pos(MP(m,i), MP(-1,1))].first;
        pos b = graph[pos(MP(m,i), MP(-1,-1))].first;
        int lena = graph[pos(MP(m,i), MP(-1,1))].second;
        int lenb = graph[pos(MP(m,i), MP(-1,-1))].second;
        compressEdge(a,b,lena+lenb);
    }
    for(int i = 1; i<m; i++){
        //top
        pos a = graph[pos(MP(i,n), MP(-1,-1))].first;
        pos b = graph[pos(MP(i,n), MP(1,-1))].first;
        int lena = graph[pos(MP(i,n), MP(-1,-1))].second;
        int lenb = graph[pos(MP(i,n), MP(1,-1))].second;
        compressEdge(a,b,lena+lenb);
    }
    for(int i = 1; i<n; i++){
        //left
        pos a = graph[pos(MP(0,i), MP(1,1))].first;
        pos b = graph[pos(MP(0,i), MP(1,-1))].first;
        int lena = graph[pos(MP(0,i), MP(1,1))].second;
        int lenb = graph[pos(MP(0,i), MP(1,-1))].second;
        compressEdge(a,b,lena+lenb);
    }
}

map<PII, bool> remBlock;

ull traverse(){
    ull ans = 0;
    int K = k;

    for(int i = 0; i<k; i++){
        remBlock.insert(MP(MP(blocks[i].first-1, blocks[i].second-1), false));
    }

    pos cur(MP(startX,startY),MP(-1,1));
    while(K > 0){
        ans += graph[cur].second;
        cur = graph[cur].first;
        if(cur.cord.first == 0 || cur.cord.first == m){
            cur.dir.first *= -1;
        }else if(cur.cord.second == 0 || cur.cord.second == n){
            cur.dir.second *= -1;
        }else if(remBlock.find(middle(cur.cord.first, cur.cord.second, cur.dir)) != remBlock.end()){
            pair<int,int> blockCords = middle(cur.cord.first, cur.cord.second, cur.dir);
            if(!remBlock[blockCords]){
                K--;
                remBlock[blockCords] = true;

                pair<int,int> mid = middle(cur.cord.first, cur.cord.second,cur.dir);

                if(cur.cord.first == mid.first){
                    cur.dir.second *= -1;
                }else if(cur.cord.second == mid.second){
                    cur.dir.first *= -1;
                }

                pos a = graph[pos(MP(mid.first-1, mid.second), MP(-1,-1))].first;
                pos b = graph[pos(MP(mid.first, mid.second+1), MP(1,1))].first;
                int lena = graph[pos(MP(mid.first-1, mid.second), MP(-1,-1))].second;
                int lenb = graph[pos(MP(mid.first, mid.second+1), MP(1,1))].second;
                compressEdge(a,b, lena+lenb+1);

                a = graph[pos(MP(mid.first, mid.second-1), MP(-1,-1))].first;
                b = graph[pos(MP(mid.first+1, mid.second), MP(1,1))].first;
                lena = graph[pos(MP(mid.first, mid.second-1), MP(-1,-1))].second;
                lenb = graph[pos(MP(mid.first+1, mid.second), MP(1,1))].second;
                compressEdge(a,b, lena+lenb+1);
                
                a = graph[pos(MP(mid.first-1, mid.second), MP(-1,1))].first;
                b = graph[pos(MP(mid.first, mid.second-1), MP(1,-1))].first;
                lena = graph[pos(MP(mid.first-1, mid.second), MP(-1,1))].second;
                lenb = graph[pos(MP(mid.first, mid.second-1), MP(1,-1))].second;
                compressEdge(a,b, lena+lenb+1);

                a = graph[pos(MP(mid.first, mid.second+1), MP(-1,1))].first;
                b = graph[pos(MP(mid.first+1, mid.second), MP(1,-1))].first;
                lena = graph[pos(MP(mid.first, mid.second+1), MP(-1,1))].second;
                lenb = graph[pos(MP(mid.first+1, mid.second), MP(1,-1))].second;
                compressEdge(a,b, lena+lenb+1);
            }
        }
    }

    return ans;
}

ull solve() {
    //create graph
    createGraph();
    //compress graph
    compressGraph();
    //traverse graph
    ull ans = traverse();
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    getData();

    //startig pos
    startX = m;
    startY = 0;
    // scaling up by 2 to have no fractions
    n *= 2;
    m *= 2;
    for (int i = 0; i < k; i++) {
        blocks[i].first *= 2;
        blocks[i].second *= 2;
    }


    ull ansS = solve();

    cout << ansS << "\n";

    return 0;
}