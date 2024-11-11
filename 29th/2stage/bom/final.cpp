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

vector<vector<int>> getDist(PII start){
    vector<vector<int>> ans(n+1, vector<int>(n+1, INF));
    ans[start.first][start.second] = 0;
    queue<pair<PII, int>> Q;
    Q.push(MP(start, 0));

    while(!Q.empty()){
        PII v = Q.front().first;
        int len = Q.front().second;
        Q.pop();

        if(v.first-1 > 0){
            if(ans[v.first-1][v.second] == INF){
                char c = plane[v.first-1][v.second];
                if(c != 'X'){
                    ans[v.first-1][v.second] = len+1; 
                }          
                if(c == '.'){
                    Q.push(MP(MP(v.first-1, v.second), len+1));
                }
            }
        }
        if(v.first + 1 <= n){
            if(ans[v.first+1][v.second] == INF){
                char c = plane[v.first+1][v.second];
                if(c != 'X'){
                    ans[v.first+1][v.second] = len+1;           
                }
                if(c == '.'){
                    Q.push(MP(MP(v.first+1, v.second), len+1));
                }
            }
        }
        if(v.second-1 > 0){
            if(ans[v.first][v.second-1] == INF){
                char c = plane[v.first][v.second-1];
                if(c != 'X'){
                    ans[v.first][v.second-1] = len+1;           
                }
                if(c == '.'){
                    Q.push(MP(MP(v.first, v.second-1), len+1));
                }
            }
        }
        if(v.second + 1 <= n){
            if(ans[v.first][v.second+1] == INF){
                char c = plane[v.first][v.second+1];
                if(c != 'X'){
                    ans[v.first][v.second+1] = len+1;           
                }
                if(c == '.'){
                    Q.push(MP(MP(v.first, v.second+1), len+1));
                }
            }
        }
    }

    return ans;
}

int processBomb(PII b, vector<vector<int>> &dist){
    if(plane[b.first][b.second] != '.'){
        return INF;
    }
    vector<int> vertical(n+1, 0), horizontal(n+1, 0);

    int last = INF;
    //bottom
    int ind = n;
    while(ind != b.first && ind > 0){
        if(plane[ind][b.second] != 'X'){
            vertical[ind] = min(dist[ind][b.second], last+1);
            last = vertical[ind];
        }else{
            last = INF;
            vertical[ind] = INF;
        }
        ind--;
    }
    //up
    last = INF;
    ind = 1;
    while(ind != b.first && ind <=n){
        if(plane[ind][b.second] != 'X'){
            vertical[ind] = min(dist[ind][b.second], last+1);
            last = vertical[ind];
        }else{
            last = INF;
            vertical[ind] = INF;
        }
        ind++;
    }
    //left
    last = INF;
    ind = 1;
    while(ind != b.second && ind <= n){
        if(plane[b.first][ind] != 'X'){
            horizontal[ind] = min(dist[b.first][ind], last+1);
            last = horizontal[ind];
        }else{
            last = INF;
            horizontal[ind] = INF;
        }
        ind++;
    }
    //right
    last = INF;
    ind = n;
    while(ind != b.second && ind > 0){
        if(plane[b.first][ind] != 'X'){
            horizontal[ind] = min(dist[b.first][ind], last+1);
            last = horizontal[ind];
        }else{
            last = INF;
            horizontal[ind] = INF;
        }
        ind--;
    }

    int ans = INF;
    if(b.first-1 > 0){
        ans = min(ans, vertical[b.first-1]);
    }
    if(b.first+1 <= n){
        ans = min(ans, vertical[b.first+1]);
    }
    if(b.second-1 > 0){
        ans = min(ans, horizontal[b.second-1]);
    }
    if(b.second+1 <= n){
        ans = min(ans, horizontal[b.second+1]);
    }

    return ans+1;
}

vector<vector<int>> getDp(vector<vector<int>> &dist){
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            int temp = processBomb(MP(i,j), dist);
            dp[i][j] = temp;
        }
    }

    return dp;
}

vector<vector<PII>> processMoves(PII start){
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

    return previous;
}

vector<int> getMoves(PII b){
    vector<vector<PII>> startMoves = processMoves(P);
    vector<vector<PII>> endMoves = processMoves(K);

    vector<int> ans;
    bool ok = true;
    PII v = K;
    while(v.first != b.first || v.second != b.second){
        PII p = endMoves[v.first][v.second];
        if(p.first < v.first){
            ans.PB(3);
        }else if(p.first > v.first){
            ans.PB(1);
        }else if(p.second < v.second){
            ans.PB(2);
        }else{
            ans.PB(4);
        }
        v = p;
    }
    v = b;
    while(v.first != P.first || v.second != P.second){
        PII p = startMoves[v.first][v.second];
        if(p.first < v.first){
            ans.PB(3);
        }else if(p.first > v.first){
            ans.PB(1);
        }else if(p.second < v.second){
            ans.PB(2);
        }else{
            ans.PB(4);
        }
        v = p;
    }

    reverse(ans.begin(), ans.end());

    return ans;
}

tuple<int, PII, vector<int>> solve(){
    tuple<int, PII, vector<int>> ans = MT(INF, MP(-1,-1), vector<int>());

    vector<vector<int>> distP = getDist(P);
    vector<vector<int>> distK = getDist(K);

    vector<vector<int>> dpP = getDp(distP);
    vector<vector<int>> dpK = getDp(distK);
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(plane[i][j] == '.' ){
                ll temp = (ll)dpP[i][j] + (ll)dpK[i][j];
                if(temp < get<0>(ans)){
                    ans = MT(dpP[i][j] + dpK[i][j], MP(i,j), vector<int>()); 
                }
            }
        }
    }

    vector<int> previous = getMoves(get<1>(ans));

    return MT(get<0>(ans), get<1>(ans), previous);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;

    getData();

    tuple<int,PII,vector<int>> ansS = solve();
    cout<<get<0>(ansS)<<"\n";
    cout<<get<1>(ansS).first<<" "<<get<1>(ansS).second<<"\n";
    for(int i = 0; i<get<2>(ansS).size(); i++){
        cout<<get<2>(ansS)[i]<<" ";
    }
    cout<<"\n";


    return 0;
}