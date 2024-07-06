#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

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

PII operator+(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return MP(lhs.first + rhs.first, lhs.second + rhs.second);
}

PII operator+=( pair<int, int>& lhs, const pair<int, int>& rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
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

void getRandom(){
    blocks.clear();

    srand(time(0));

    n = rand()%10+1;
    m = rand()%10+1;
    k = rand()%(n*m/2)+1;
    vector<vector<bool>> vis(n+1, vector<bool>(m+1, false));
    for(int i =0 ; i<k; i++){
        int a = 0;
        int b = 0;
        while(a == b || vis[a][b]){
            a = rand()%n+1;
            b = rand()%m+1;
        }
        blocks.PB(MP(a,b));
    }
    startX = n;
    startY = 0;
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<" "<<k<<"\n";
    for(int i = 0; i<k; i++){
        cout<<blocks[i].first<<" "<<blocks[i].second<<"\n";
    }
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

int isBlock(PII cord, PII dir){

    for(int i = 0; i<k; i++){
        PII cen = centerBlock(blocks[i]);
        vector<PII> temp;
        temp.PB(MP(cen.first + 1, cen.second));
        temp.PB(MP(cen.first - 1, cen.second));
        temp.PB(MP(cen.first, cen.second + 1));
        temp.PB(MP(cen.first, cen.second - 1));

        for(int j = 0; j<temp.size(); j++){
            if(temp[j] == cord){
                return i;
            }
        }
    }

    return -1;
}

ull brute(){
    ull ans = 0;
    int blocksLeft = k;
    PII cord = MP(startX, startY);
    PII dir = MP(-1,1);
    vector<bool> vis(k+1, false);

    while(blocksLeft > 0){
        ans++;
        cord += dir;
        int w = isWall(cord);

        if(w == 1){
            dir.first *= -1;
        }else if(w == 2){
            dir.second *= -1;
        }else{
            int b = isBlock(cord, dir);

            if(b >= 0 && !vis[b]){
                vis[b] = true;
                blocksLeft--;
                if(blocks[b].first-1 == cord.first){
                    dir.second *= -1;
                }else if(blocks[b].second-1 == cord.second){
                    dir.first *= -1;
                }
            }
        }
    }

    return ans;
}

PII reflect(int cord, int dir){

}

void mergetPath(PII cord, PII dir){

}

void mergeBlock(){

}

void mergeWall(){

}

void removeBlock(){

}

ull solve(){

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1 ;test++){
        if(op == 1){
            getData();   
        }else{
            getRandom();
        }

        for(int i = 0; i<k; i++){
            blocks[i].first *= 2;
            blocks[i].second *= 2;
        }
        n *= 2;
        m *= 2;

        ull ansB = brute();
        ull ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}