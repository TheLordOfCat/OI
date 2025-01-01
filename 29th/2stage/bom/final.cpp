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
    queue<PII> Q;
    Q.push(start);

    ans[start.first][start.second] = 0;
    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();

        for(int i = -1; i<=1; i++){
            if(v.first + i <=n && v.first + i>=1){
                if(ans[start.first+i][start.second] == INF){
                    ans[start.first+i][start.second] = ans[start.first][start.second] + 1;
                }
            }
        }

        for(int i = -1; i<=1; i++){
            if(v.second + i <=n && v.second + i>=1){
                if(ans[start.first][start.second+i] == INF){
                    ans[start.first][start.second+i] = ans[start.first][start.second] + 1;
                }
            }
        }
    }

    return ans;
}

void processRow(int r, vector<char> &row, vector<int>& dist, vector<vector<vector<int>>>& proposed, int in){
    for(int i = 1; i<=n; i++){
        if(row[i] != '#'){
            int temp = dist[i];
            if(i > 1){
                temp = min(dist[i], proposed[r][i-1].back()+1);
            }
            if(in == 0){
                proposed[r][i].back() = min(proposed[r][i].back(), temp);
            }else{
                proposed[r][n-i+1].back() = min(proposed[r][i].back(), temp);
            }
        }else{
            if(in == 0){
                proposed[r][i].back() = INF;
            }else{
                proposed[r][n-i+1].back() = INF;
            }
        }
    }
}

void processCol(int c, vector<char> &col, vector<int>& dist, vector<vector<vector<int>>>& proposed, int in){
    for(int i = 1; i<=n; i++){
        int temp = dist[i];
        if(col[i] != '#'){
            if(i > 1){
                temp = min(dist[i], proposed[i-1][c].back()+1);
            }
            if(in == 0){
                proposed[i][c].back() = min(proposed[i][c].back(), temp);
            }else{
                proposed[n-i+1][c].back() = min(proposed[i][n-i+1].back(), temp);
            }
        }else{
            if(in == 0){
                proposed[i][c].back() = INF;
            }else{
                proposed[n-i+1][c].back() = INF;
            }
        }
    }
}

void getProposedRow(int row, vector<vector<vector<int>>>& proposed, vector<vector<int>>& dist){
    processRow(row, plane[row], dist[row], proposed, 0);
    vector<char> pC = plane[row];
    reverse(pC.begin(), pC.end());
    vector<int> d = dist[row];
    reverse(d.begin(), d.end());
    processRow(row, pC,d, proposed, 1);
}

void getProposedCol(int col, vector<vector<vector<int>>>& proposed, vector<vector<int>>& dist){
    vector<char> pC;
    for(int i =0 ; i<=n; i++){
        pC.PB(plane[i][col]);
    }
    vector<int> d;
    for(int i =0 ; i<=n; i++){
        d.PB(dist[i][col]);
    }

    processRow(col, pC, d, proposed, 0);
    reverse(pC.begin(), pC.end());
    reverse(d.begin(), d.end());
    processRow(col, pC,d, proposed, 1);
}

vector<vector<int>> getDp(vector<vector<int>> &distP, vector<vector<int>> &distK){
    vector<vector<int>> dp(n+1, vector<int>(n+1, 00));

    //get proposed
    vector<int> temp = {INF,INF};
    vector<vector<vector<int>>> proposed(n+1, vector<vector<int>>(n+1, temp));
    for(int i = 1; i<=n; i++){
        getProposedRow(i, proposed, distP);
        getProposedCol(i, proposed, distK);
    }
    for(int i = 1; i<=n; i++){
        getProposedCol(i, proposed, distP);
        getProposedCol(i, proposed, distK);
    }

    //ge dp
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            if(proposed[i][j][0] != INF && proposed[i][j][1] != INF){
                dp[i][j] = proposed[i][j][0] + proposed[i][j][1];
            }else{
                dp[i][j] = INF;
            }   
        }
    }

    return dp;
}

vector<char> getPath(PII start){
    vector<vector<char>> planeCopy = plane;

    for(int j = start.second-1; j>=1; j--){
        if(planeCopy[start.first][j] == '#'){
            planeCopy[start.first][j] = '.';
        }else if(planeCopy[start.first][j] == 'X'){
            break;
        }
    }
    for(int j = start.second+1; j<=n; j++){
        if(planeCopy[start.first][j] == '#'){
            planeCopy[start.first][j] = '.';
        }else if(planeCopy[start.first][j] == 'X'){
            break;
        }
    }
    for(int j = start.first-1; j>=1; j--){
        if(planeCopy[j][start.second] == '#'){
            planeCopy[j][start.second] = '.';
        }else if(planeCopy[j][start.second] == 'X'){
            break;
        }
    }
    for(int j = start.first+1; j<=n; j++){
        if(planeCopy[j][start.second] == '#'){
            planeCopy[j][start.second] = '.';
        }else if(planeCopy[j][start.second] == 'X'){
            break;
        }
    }

    queue<PII> Q;
    Q.push(P);
    vector<vector<PII>> previous(n+1, vector<PII>(n+1, MP(-1,-1)));
    previous[P.first][P.second] = MP(INF,INF);

    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();
        if(v.first == K.first && v.second == K.second){
            break;
        }

        for(int o = -1; o<2; o+=2){
            if(v.first + o > 0 && v.first + o <=n){
                if(previous[v.first+o][v.second].first == -1 && (planeCopy[v.first +o][v.second] == '.' || planeCopy[v.first +o][v.second] == 'K')){
                    Q.push(MP(v.first+o, v.second));
                    previous[v.first+o][v.second] = v;
                }
            }
        }
        for(int o = -1; o<2; o+=2){
            if(v.second + o > 0 && v.second + o <= n){
                if(previous[v.first][v.second+o].first == -1 && (planeCopy[v.first][v.second+o] == '.' || planeCopy[v.first][v.second+o] == 'K')){
                    Q.push(MP(v.first, v.second+o));
                    previous[v.first][v.second + o] = v;
                }
            }
        }
    }

    vector<char> ans;
    PII n = K;
    while(n.first != P.first && n.second != P.second){
        PII p = previous[p.first][p.second];
        if(p.first < n.first){
            ans.PB('D');
        }else if(p.first > n.first){
            ans.PB('G');
        }else if(p.second < n.second){
            ans.PB('P');
        }else{
            ans.PB('L');
        }
    }

    return ans;
}

tuple<int, PII, vector<char>> solve(){
    tuple<int, PII, vector<char>> ans = MT(INF, MP(-1,-1), vector<char>());

    vector<vector<int>> distP = getDist(P);
    vector<vector<int>> distK = getDist(K);

    vector<vector<int>> dp = getDp(distP, distK); 

    for(int i = 1; i<=n; i++){
        for(int j  = 1; j<=n; j++){
            if(dp[i][j] < get<0>(ans)){
                get<0>(ans) = dp[i][j];
                get<1>(ans) = MP(i,j);
            }
        }
    }

    if(get<0>(ans) == INF){
        return MT(-1, MP(-1,-1), vector<char>());
    }

    vector<char> previous = getPath(get<1>(ans));

    get<2>(ans) = previous;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    tuple<int,PII,vector<char>> ansS = solve();
    cout<<get<0>(ansS)<<"\n";
    cout<<get<1>(ansS).first<<" "<<get<1>(ansS).second<<"\n";
    // for(int i = 0; i<get<2>(ansS).size(); i++){
    //     cout<<get<2>(ansS)[i]<<" ";
    // }
    for(int i = 0; i<get<2>(ansS).size(); i++){
        char move = get<2>(ansS)[i];
        cout<<move<<"\n";
    }

    return 0;
}