#include <iostream>
#include <vector>
#include <tuple> 
#include <queue>
#include <algorithm>

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

int n;
vector<vector<char>> plane;
PII P, K;

void getData(){
    cin>>n;
    plane.PB(vector<char>(n+1, '0'));
    for(int i = 1; i<=n; i++){
        plane.PB(vector<char>());
        plane[i].PB('0');
        for(int j = 1; j<=n; j++){
            char c;
            cin>>c;
            plane[i].PB(c);

            if(c == 'P'){
                P = MP(i,j);
            }else if(c == 'K'){
                K = MP(i,j);
            }
        }
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+2;
    plane.PB(vector<char>(n+1, '0'));
    for(int i = 1; i<=n; i++){
        plane.PB(vector<char>());
        plane[i].PB('0');
        for(int j = 1; j<=n; j++){
            int type = rand()%3;
            char c;
            if(type == 0 || type == 1){
                c = '.';
            }else{
                c = '#';
            }
            plane[i].PB(c);
        }
    }

    P = MP(rand()%n+1, rand()%n+1);
    K = P;
    while(K.first == P.first && K.second == P.second){
        K = MP(rand()%n+1, rand()%n+1);
    }

    plane[P.first][P.second] = 'P';
    plane[K.first][K.second] = 'K';

}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            cout<<plane[i][j];
        }
        cout<<"\n";
    }
}

tuple<int, PII, vector<int>> brute(){
    tuple<int,PII,vector<int>> ans = MT(INF, MP(-1,-1), vector<int>());

    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            vector<vector<char>> bombPlane = plane;
            
            //correct the plane
            if(bombPlane[i][j] == '.'){

                for(int o = j; o>0; o--){
                    if(bombPlane[i][o] == '#'){
                        bombPlane[i][o] = '.';
                    }else if(bombPlane[i][o] == 'X'){
                        break;
                    }
                }
                for(int o = j; o<=n; o++){
                    if(bombPlane[i][o] == '#'){
                        bombPlane[i][o] = '.';
                    }else if(bombPlane[i][o] == 'X'){
                        break;
                    }
                }
                for(int o = i; o>0; o--){
                    if(bombPlane[o][j] == '#'){
                        bombPlane[o][j] = '.'; 
                    }else if(bombPlane[o][j] == 'X'){
                        break;
                    }
                }
                for(int o = i; o<=n; o++){
                    if(bombPlane[o][j] == '#'){
                        bombPlane[o][j] = '.'; 
                    }else if(bombPlane[o][j] == 'X'){
                        break;
                    }
                }
            }

            cout<<"BOMB: "<<i<<" "<<j<<"\n";
            for(int i = 1; i<=n; i++){
                for(int j = 1; j<=n; j++){
                    cout<<bombPlane[i][j]<<" ";
                }
                cout<<"\n";
            }
            cout<<"\n";
        
            //find the shortes path
            vector<vector<PII>> previous(n+1, vector<PII>(n+1, MP(-1,-1)));
            queue<PII> Q;
            Q.push(P);

            while(!Q.empty()){
                PII v = Q.front();
                Q.pop();
                if(v.first == K.first && v.second == K.second){
                    break;
                }

                for(int o = -1; o<2; o+=2){
                    if(v.first + o > 0 && v.first + o <=n){
                        if(previous[v.first+o][v.second].first == -1 && (bombPlane[v.first +o][v.second] == '.' || bombPlane[v.first +o][v.second] == 'K')){
                            Q.push(MP(v.first+o, v.second));
                            previous[v.first+o][v.second] = v;
                        }
                    }
                }
                for(int o = -1; o<2; o+=2){
                    if(v.second + o > 0 && v.second + o <= n){
                        if(previous[v.first][v.second+o].first == -1 && (bombPlane[v.first][v.second+o] == '.' || bombPlane[v.first][v.second+o] == 'K')){
                            Q.push(MP(v.first, v.second+o));
                            previous[v.first][v.second + o] = v;
                        }
                    }
                }
            }

            for(int i = 1; i<=n; i++){
                for(int j = 1; j<=n; j++){
                    cout<<"("<<previous[i][j].first<<" "<<previous[i][j].second<<") ";
                }
                cout<<"\n";
            }
            cout<<"\n";

            //get the distance 
            bool ok = true;
            vector<int> dir;
            PII v = K;
            while(v.first != P.first || v.second != P.second){
                PII p = previous[v.first][v.second];
                if(p.first == -1 && p.second == -1){
                    ok = false;
                    break;
                }
                if(p.first < v.first){
                    dir.PB(3);
                }else if(p.first > v.first){
                    dir.PB(1);
                }else if(p.second < v.second){
                    dir.PB(2);
                }else{
                    dir.PB(4);
                }
                v = p;
            }

            if(ok){
                reverse(dir.begin(), dir.end());
                if(dir.size() < get<0>(ans)){
                    ans = MT(dir.size(), MP(i,j), dir);
                }
            }
        }
    }

    return ans;
}

vector<vector<int>> getDist(PII start){
    vector<vector<int>> ans(n, vector<int>(n, INF));
    ans[start.first][start.second] = 0;
    queue<pair<PII, int>> Q;
    Q.push(MP(start, 0));

    while(!Q.empty()){
        PII v = Q.front().first;
        int len = Q.front().second;
        Q.pop();

        if(v.first-1 >= 0 && ans[v.first-1][v.second] == INF){
            char c = plane[v.first-1][v.second];
            ans[v.first-1][v.second] = len+1;           
            if(c == '.'){
                Q.push(MP(MP(v.first-1, v.second), len+1));
            }
        }
        if(v.first < n-1 && ans[v.first+1][v.second] == INF){
            char c = plane[v.first+1][v.second];
            ans[v.first+1][v.second] = len+1;           
            if(c == '.'){
                Q.push(MP(MP(v.first+1, v.second), len+1));
            }
        }
        if(v.second > 0 && ans[v.first][v.second-1] == INF){
            char c = plane[v.first][v.second-1];
            ans[v.first][v.second-1] = len+1;           
            if(c == '.'){
                Q.push(MP(MP(v.first, v.second-1), len+1));
            }
        }
        if(v.second < n-1 && ans[v.first][v.second+1] == INF){
            char c = plane[v.first][v.second+1];
            ans[v.first][v.second+1] = len+1;           
            if(c == '.'){
                Q.push(MP(MP(v.first, v.second+1), len+1));
            }
        }
    }

    return ans;
}

int processBomb(PII b, vector<vector<int>> &dist){
    if(plane[b.first][b.second] != '.'){
        return INF;
    }
    vector<int> vertical(n, 0), horizontal(n, 0);

    int last = INF;
    //up
    int ind = n-1;
    while(ind != b.first){
        if(plane[b.first][b.second] != 'X'){
            vertical[ind] = min(dist[ind][b.second], last+1);
            last = vertical[ind];
        }else{
            last = INF;
        }
        ind--;
    }
    //bottom
    last = INF;
    ind = 0;
    while(ind != b.first){
        if(plane[b.first][b.second] != 'X'){
            vertical[ind] = min(dist[ind][b.second], last+1);
            last = vertical[ind];
        }else{
            last = INF;
        }
        ind++;
    }
    //left
    last = INF;
    ind = 0;
    while(ind != b.second){
        if(plane[b.first][b.second] != 'X'){
            horizontal[ind] = min(dist[b.first][ind], last+1);
            last = vertical[ind];
        }else{
            last = INF;
        }
        ind++;
    }
    //right
    last = INF;
    ind = n-1;
    while(ind != b.second){
        if(plane[b.first][b.second] != 'X'){
            horizontal[ind] = min(dist[b.first][ind], last+1);
            last = vertical[ind];
        }else{
            last = INF;
        }
        ind--;
    }

    int ans = INF;
    if(b.first-1 >= 0){
        ans = min(ans, vertical[b.first-1]);
    }
    if(b.first+1 < n){
        ans = min(ans, vertical[b.first+1]);
    }
    if(b.second-1 >= 0){
        ans = min(ans, horizontal[b.first-1]);
    }
    if(b.second+1 < n){
        ans = min(ans, horizontal[b.first+1]);
    }

    return ans;
}

vector<vector<int>> getDp(PII b, vector<vector<int>> &dist){
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            int temp = processBomb(b, dist);
            dp[i][j] = temp;
        }
    }

    return dp;
}

vector<vector<int>> processMoves(PII start){

}

vector<vector<int>> getMoves(PII b){
    vector<vector<int>> startMoves = processMoves(P);
    vector<vector<int>> endMoves = processMoves(K);

    
}

tuple<int, PII, vector<int>> solve(){
    tuple<int, PII, vector<int>> ans = MT(INF, MP(-1,-1), vector<int>());

    vector<vector<int>> distP = getDist(P);
    vector<vector<int>> distK = getDist(K);

    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            vector<vector<int>> dpP = getDp(MP(i,j), distP);
            vector<vector<int>> dpK = getDp(MP(i,j), distK);

            if(dpP[i][j] + dpK[i][j] < get<0>(ans)){
                ans = MT(dpP[i][j] + dpK[i][j], MP(i,j), vector<int>()); 
            }
        }
    }

    // vector<vector<int>> moves = getMoves(get<1>(ans));
    vector<int> previous;
    // PII ind = K;
    // while(ind.first != P.first && ind.second != P.second){
    //     int type = moves[ind.first][ind.second];
    //     previous.PB(type);
    //     if(type == 0){
    //         ind.first -= 1;
    //     }else if(type == 1){
    //         ind.second += 1;
    //     }else if(type == 2){
    //         ind.first += 1;
    //     }else if(type == 3){
    //         ind.second -= 1;
    //     }
    // }
    // reverse(previous.begin(), previous.end());

    return MT(get<0>(ans), get<1>(ans), previous);
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
        tuple<int,PII,vector<int>> ansB = brute();
        tuple<int,PII,vector<int>> ansS = solve();
        if(get<0>(ansB) != get<0>(ansS)){
            cout<<"ERROR\n";
            cout<<"BURTE: ";
            cout<<get<0>(ansB)<<"\n";
            cout<<get<1>(ansB).first<<" "<<get<1>(ansB).second<<"\n";
            for(int i = 0; i<get<2>(ansB).size(); i++){
                cout<<get<2>(ansB)[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: ";
            cout<<get<0>(ansS)<<"\n";
            cout<<get<1>(ansS).first<<" "<<get<1>(ansS).second<<"\n";
            for(int i = 0; i<get<2>(ansS).size(); i++){
                cout<<get<2>(ansS)[i]<<" ";
            }
            cout<<"\n";
            printData();
        }    
        cout<<"CORRECT\n";
    }

    return 0;
}