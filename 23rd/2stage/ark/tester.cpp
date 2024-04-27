#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include <cstdlib>
#include <ctime>

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
int startX = m;
int startY = 0;

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

void getRandom() {
    n = rand() % 10 + 1;
    m = rand() % 10 + 1;
    int g = gcd(n, m);
    if (g != 1) {
        n /= g;
        m /= g;
    }
    k = rand() % (n * m);
    vector<vector<bool>> vis(m + 1, vector<bool> (n + 1, false));
    for (int i = 0; i < k; i++) {
        int a = rand() % n + 1;
        int b = rand() % m + 1;
        if (!vis[a][b]) {
            blocks.PB(MP(a, b));
            vis[a][b] = true;
        } else {
            k--;
        }
    }
}

void printData() {
    cout << n << " " << m << " " << k << "\n";
    for (int i = 0; i < k; i++) {
        cout << blocks[i].first << " " << blocks[i].second << "\n";
    }
}

pair<bool, bool> isWall(int x, int y) {
    // second value idicates the which wall is conntact made with
    if (x == 0 || x == m) {
        return MP(true, true);
    }
    if (y == 0 || y == n) {
        return MP(true, false);
    }
    return MP(false, false); // second value not used
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

pair<int, int> reflect(pair<int, int> d, bool side) {
    if (side) { // changing only x
        d.first *= -1;
    } else { // changing only y
        d.second *= -1;
    }
    return d;
}

ull brute() {
    ull ans = 0;
    int K = k;
    int curX = startX;
    int curY = startY;
    pair<int, int> dir = MP(-1, 1);
    vector<bool> vis(k + 1, false);

    while (K > 0) {
        pair<bool, bool> wall = isWall(curX, curY);
        if (wall.first) {
            reflect(dir, wall.second);
        } else {
            pair<int, int> mid = middle(curX, curY, dir);
            for (int i = 0; i < k; i++) {
                if (blocks[i].first == mid.first && blocks[i].second == mid.second && !vis[i]) {
                    if (mid.first != curX) {
                        reflect(dir, true);
                    } else if (mid.second != curY) {
                        reflect(dir, false);
                    }
                    vis[i] = true;
                }
            }
        }
        curX += dir.first;
        curY += dir.second;
        ans++;
    }

    return ans;
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
        if (lhs.cord.first != rhs.cord.first) {
            return lhs.cord.first < rhs.cord.first;
        }else if(lhs.cord.second == rhs.cord.second){
            return lhs.cord.second < rhs.cord.second;
        }else if(lhs.dir.first == lhs.dir.second){
            return lhs.dir.first < rhs.dir.first;
        }else{
            return lhs.dir.second < rhs.dir.second;
        }
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
    graph.insert(MP(start,MP(final,b.first-a.first)));
    start.dir.first *= -1;
    start.dir.second *= -1;
    final.dir.first *= -1;
    final.dir.second *= -1;
    graph.insert(MP(final,MP(start,b.first-a.first)));
}

void createGraph(){
    //right tilted

    //finding points of intrest
    vector<pair<int,PII>> intrestPoint;
    intrestPoint.PB(MP(0,MP(0,0)));
    for(int i = 1; i<=n; i++){
        intrestPoint.PB(MP((-1)*i,MP(i,0)));
        intrestPoint.PB(MP(m-i,MP(i,m)));
    }
    for(int i = 1; i<=m; i++){
        intrestPoint.PB(MP(i,MP(0,i)));
        intrestPoint.PB(MP(i-n,MP(n,i)));
    }
    for(int i = 0; i<k; i++){
        pair<int,int> mid = MP(blocks[i].first-1, blocks[i].second-1);
        intrestPoint.PB(MP(mid.second - (mid.first-1),MP(mid.first, mid.second-1)));
        intrestPoint.PB(MP(mid.second - (mid.first+1),MP(mid.first, mid.second+1)));
        intrestPoint.PB(MP(mid.second-1 - (mid.first),MP(mid.first-1, mid.second)));
        intrestPoint.PB(MP(mid.second+1 - (mid.first),MP(mid.first+1, mid.second)));
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
    intrestPoint.PB(MP(0,MP(0,0)));
    for(int i = 1; i<=n; i++){
        intrestPoint.PB(MP(i,MP(i,0)));
        intrestPoint.PB(MP(m+i,MP(i,m)));
    }
    for(int i = 1; i<=m; i++){
        intrestPoint.PB(MP(i,MP(0,i)));
        intrestPoint.PB(MP(i+n,MP(n,i)));
    }
    for(int i = 0; i<k; i++){
        pair<int,int> mid = MP(blocks[i].first-1, blocks[i].second-1);
        intrestPoint.PB(MP(mid.second + (mid.first-1),MP(mid.first, mid.second-1)));
        intrestPoint.PB(MP(mid.second + (mid.first+1),MP(mid.first, mid.second+1)));
        intrestPoint.PB(MP(mid.second-1 + (mid.first),MP(mid.first-1, mid.second)));
        intrestPoint.PB(MP(mid.second+1 + (mid.first),MP(mid.first+1, mid.second)));
    }
    //sorting
    sort(intrestPoint.begin(), intrestPoint.end(), customPairSort);

    //creating edges
    for(int i = 0; i<intrestPoint.size()-1; i++){
        if(intrestPoint[i].first == intrestPoint[i+1].first){
            makeEdge(intrestPoint[i].second, intrestPoint[i+1].second, MP(-1,1));
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
    //walls
    for(int i = 1; i<=n; i++){
        //bottom
        pos a = graph[pos(MP(i,0), MP(-1,1))].first;
        pos b = graph[pos(MP(i,0), MP(1,1))].first;
        int lena = graph[pos(MP(i,0), MP(-1,1))].second;
        int lenb = graph[pos(MP(i,0), MP(1,1))].second;
        compressEdge(a,b,lena+lenb);
        
        //top
        a = graph[pos(MP(i,m), MP(-1,-1))].first;
        b = graph[pos(MP(i,m), MP(1,-1))].first;
        lena = graph[pos(MP(i,0), MP(-1,-1))].second;
        lenb = graph[pos(MP(i,0), MP(1,-1))].second;
        compressEdge(a,b,lena+lenb);
    }
    for(int i = 1; i<=m; i++){
        //left
        pos a = graph[pos(MP(0,i), MP(1,1))].first;
        pos b = graph[pos(MP(0,i), MP(1,-1))].first;
        int lena = graph[pos(MP(0,i), MP(1,1))].second;
        int lenb = graph[pos(MP(0,i), MP(1,-1))].second;
        compressEdge(a,b,lena+lenb);
        
        //right
        a = graph[pos(MP(i,m), MP(-1,1))].first;
        b = graph[pos(MP(i,m), MP(-1,-1))].first;
        lena = graph[pos(MP(i,m), MP(-1,1))].second;
        lenb = graph[pos(MP(i,m), MP(-1,-1))].second;
        compressEdge(a,b,lena+lenb);
    }
}

map<PII, bool> remBlock;

ull traverse(){
    ull ans = 0;
    int K = k;

    for(int i = 0; i<k; i++){
        remBlock.insert(MP(blocks[i], false));
    }

    pos cur(MP(startX,startY),MP(-1,1));
    while(K > 0){
        ans += graph[cur].second;
        cur = graph[cur].first;
        if(remBlock.find(cur.cord) != remBlock.end()){
            if(!remBlock[cur.cord]){
                K--;
                remBlock[cur.cord] = true;

                pair<int,int> mid = middle(cur.cord.first, cur.cord.second,cur.dir);

                if(cur.cord.first != mid.first){
                    cur.dir.second *= -1;
                }else if(cur.cord.second != mid.second){
                    cur.dir.first *= -1;
                }

                pos a = graph[pos(MP(mid.first-1, mid.second), MP(-1,-1))].first;
                pos b = graph[pos(MP(mid.first, mid.second+1), MP(1,1))].first;
                int lena = graph[pos(MP(mid.first-1, mid.second), MP(-1,-1))].second;
                int lenb = graph[pos(MP(mid.first, mid.second+1), MP(1,1))].second;
                compressEdge(a,b, lena+lenb);

                a = graph[pos(MP(mid.first, mid.second-1), MP(-1,-1))].first;
                b = graph[pos(MP(mid.first+1, mid.second), MP(1,1))].first;
                lena = graph[pos(MP(mid.first, mid.second-1), MP(-1,-1))].second;
                lenb = graph[pos(MP(mid.first+1, mid.second), MP(1,1))].second;
                compressEdge(a,b, lena+lenb);
                
                a = graph[pos(MP(mid.first-1, mid.second), MP(-1,1))].first;
                b = graph[pos(MP(mid.first, mid.second-1), MP(1,-1))].first;
                lena = graph[pos(MP(mid.first-1, mid.second), MP(-1,1))].second;
                lenb = graph[pos(MP(mid.first, mid.second-1), MP(1,-1))].second;
                compressEdge(a,b, lena+lenb);

                a = graph[pos(MP(mid.first, mid.second+1), MP(-1,1))].first;
                b = graph[pos(MP(mid.first+1, mid.second), MP(1,-1))].first;
                lena = graph[pos(MP(mid.first, mid.second+1), MP(-1,1))].second;
                lenb = graph[pos(MP(mid.first+1, mid.second), MP(1,-1))].second;
                compressEdge(a,b, lena+lenb);
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

    int op = 1;
    for (int test = 1; test <= 1; test++) {
        cout << "TEST nr." << test << " = ";
        if (op == 1) {
            getData();
        } else {
            getRandom();
        }
        // scaling up by 2 to have no fractions
        n *= 2;
        m *= 2;
        for (int i = 0; i < k; i++) {
            blocks[i].first *= 2;
            blocks[i].second *= 2;
        }

        ull ansB = brute();
        ull ansS = solve();
        if (ansB != ansS) {
            cout << "ERROR\n";
            cout << "BRUTE: " << ansB << "\n";
            cout << "SOLVE: " << ansS << "\n";
            printData();
            return 0;
        }
        cout << "CORRECT\n";
    }

    return 0;
}