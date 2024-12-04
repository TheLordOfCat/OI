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

PII operator -=(const PII& a, const PII& b){
    PII ans = MP(0,0);
    ans.first = a.first - b.first;
    ans.second = a.second - b.second;
    return ans;
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

    // n = rand()%10+1;
    // m = rand()%10+1;
    n = 3;
    m = 2;
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
    cout<<n/2<<" "<<m/2<<" "<<k/2<<"\n";
    for(int i = 0; i<k; i++){
        cout<<blocks[i].first/2<<" "<<blocks[i].second/2<<"\n";
    }
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

ull brute(){
    PII pos = MP(n/2, 0), dir = MP(-1, 1);
    int countBlock = k;
    ull ans = 0;
    vector<bool> used(k+1, false);
    while(countBlock > 0){
        pos += dir;
        ans++;
        int w = isWall(pos);
        if(w != -1){
            bounceWall(dir, w);
        }else{
            int b = -1;
            int type = -1;
            for(int i = 0; i<blocks.size(); i++){
                if(!used[i]){
                    if(pos == blocks[i]+MP(-1,0)){ // top
                        b = i;
                        type = 1;
                        break;
                    }
                    if(pos == blocks[i]+MP(0,-1)){ // right
                        b = i;
                        type =2;
                        break;
                    }
                    if(pos == blocks[i]+MP(-1,-2)){ //bottom
                        b = i;
                        type = 1;
                        break;
                    }
                    if(pos == blocks[i]+MP(-2,-1)){ // left
                        b = i;
                        type = 2;
                        break;
                    }
                }
            }
            if(b != -1){
                countBlock--;
                used[b] = true;
                bounceWall(dir,type);
            }
        }
    }    

    return ans;
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

        //scaling the grid
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