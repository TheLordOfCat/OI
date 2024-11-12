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

tuple<int,PII> processBomb(PII b, vector<vector<int>> &dist){
    if(plane[b.first][b.second] != '.'){
        return MT(INF,MP(INF,INF));
    }
    vector<int> vertical(n+1, 0), horizontal(n+1, 0);
    vector<PII> verticalJump(n+1, MP(-1,-1)), horizontalJump(n+1, MP(-1,-1));

    int last = INF;
    //bottom
    int ind = n;
    while(ind != b.first && ind > 0){
        if(plane[ind][b.second] != 'X'){
            if(dist[ind][b.second] < last+1){
                verticalJump[ind] = MP(ind,b.second);
                vertical[ind] = dist[ind][b.second];
            }else{
                verticalJump[ind] = verticalJump[ind-1];
                vertical[ind] = last+1;
            }
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
            if(dist[ind][b.second] < last+1){
                verticalJump[ind] = MP(ind,b.second);
                vertical[ind] = dist[ind][b.second];
            }else{
                verticalJump[ind] = verticalJump[ind+1];
                vertical[ind] = last+1;
            }
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
            if(dist[b.first][ind] < last+1){
                verticalJump[ind] = MP(b.first, ind);
                vertical[ind] = dist[b.first][ind];
            }else{
                verticalJump[ind] = verticalJump[ind-1];
                vertical[ind] = last+1;
            }
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
            if(dist[b.first][ind] < last+1){
                verticalJump[ind] = MP(b.first, ind);
                vertical[ind] = dist[b.first][ind];
            }else{
                verticalJump[ind] = verticalJump[ind+1];
                vertical[ind] = last+1;
            }
            last = horizontal[ind];
        }else{
            last = INF;
            horizontal[ind] = INF;
        }
        ind--;
    }

    int ans = INF;
    PII j = MP(-1,-1);
    if(b.first-1 > 0){
        if(ans > vertical[b.first-1]){
            ans = vertical[b.first-1];
            j = verticalJump[b.first-1];
        }
    }
    if(b.first+1 <= n){
        if(ans > vertical[b.first+1]){
            ans = vertical[b.first+1];
            j = verticalJump[b.first+1];
        }
    }
    if(b.second-1 > 0){
        if(ans > horizontal[b.second-1]){
            ans = horizontal[b.second-1];
            j = horizontalJump[b.second-1];
        }
    }
    if(b.second+1 <= n){
        if(ans > horizontal[b.second+1]){
            ans = horizontal[b.second+1];
            j = horizontalJump[b.second+1];
        }
    }

    return MP(ans+1,j);
}

pair<vector<vector<int>>,vector<vector<PII>>> getDp(vector<vector<int>> &dist){
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    vector<vector<PII>> jump(n+1, vector<PII>(n+1, MP(0,0)));

    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            tuple<int, PII> temp = processBomb(MP(i,j), dist);
            dp[i][j] = get<0>(temp);
            jump[i][j] = get<1>(temp);
        }
    }

    return MP(dp,jump);
}

vector<vector<PII>> processMoves(PII start){
    vector<vector<PII>> previous(n+1, vector<PII>(n+1, MP(-1,-1)));
    queue<PII> Q;
    Q.push(start);

    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();

        for(int o = -1; o<2; o+=2){
            if(v.first + o > 0 && v.first + o <=n){
                if(previous[v.first+o][v.second].first == -1 && plane[v.first +o][v.second] != 'P' && plane[v.first +o][v.second] != 'K'){
                    if(plane[v.first +o][v.second] == '.'){
                        Q.push(MP(v.first+o, v.second));
                    }
                    previous[v.first+o][v.second] = v;
                }
            }
        }
        for(int o = -1; o<2; o+=2){
            if(v.second + o > 0 && v.second + o <= n){
                if(previous[v.first][v.second+o].first == -1 && plane[v.first][v.second + o] != 'P' && plane[v.first][v.second+o] != 'K'){
                    if(plane[v.first][v.second+o] == '.' ){
                        Q.push(MP(v.first, v.second+o));
                    }
                    previous[v.first][v.second + o] = v;
                }
            }
        }
    }

    return previous;
}

vector<int> getMoves(PII b, vector<vector<PII>> jumpP, vector<vector<PII>> jumpK){
    vector<vector<PII>> startMoves = processMoves(P);
    vector<vector<PII>> endMoves = processMoves(K);

    vector<int> ans;
    PII v = jumpK[b.first][b.second];
    while(v.first != K.first || v.second != K.second){
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

    v = jumpP[b.first][b.second];
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

    pair<vector<vector<int>>,vector<vector<PII>>> dpP = getDp(distP);
    pair<vector<vector<int>>,vector<vector<PII>>> dpK = getDp(distK);
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(plane[i][j] == '.' ){
                ll temp = (ll)dpP.first[i][j] + (ll)dpK.first[i][j];
                if(temp < get<0>(ans)){
                    ans = MT(dpP.first[i][j] + dpK.first[i][j], MP(i,j), vector<int>()); 
                }
            }
        }
    }

    vector<int> previous = getMoves(get<1>(ans), dpP.second, dpK.second);

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