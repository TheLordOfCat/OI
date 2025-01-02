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
    // cin>>n;
    // plane.PB(vector<char>(n+1, '0'));
    // for(int i = 1; i<=n; i++){
    //     plane.PB(vector<char>());
    //     plane[i].PB('0');
    //     for(int j = 1; j<=n; j++){
    //         char c;
    //         cin>>c;
    //         plane[i].PB(c);

    //         if(c == 'P'){
    //             P = MP(i,j);
    //         }else if(c == 'K'){
    //             K = MP(i,j);
    //         }
    //     }
    // }
    n = 1001;
    plane.PB(vector<char>(n+1, '0'));
    for(int i = 1; i<=2; i++){
        plane.PB(vector<char>());
        plane[i].PB('0');
        for(int j = 1; j<=n; j++){
            char c;
            int ops = rand()%3+1;
            if(ops == 1 || ops == 2){
                c = '.';
            }else{
                c = 'X';
            }
            plane[i].PB(c);
        }
    }
    for(int i = 3; i<=n; i++){
        plane.PB(vector<char>());
        plane[i].PB('0');
        for(int j = 1; j<=n; j++){
            plane[i].PB('X');
        }
    }

    plane[1][1] = 'P';
    plane[1][n] = 'K';
    P = MP(1,1);
    K = MP(1,n);
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
                if(ans[v.first+i][v.second] == INF && (plane[v.first+i][v.second] == '.' || plane[v.first+i][v.second] == '#' || plane[v.first+i][v.second] == 'P' || plane[v.first+i][v.second] == 'K')){
                    ans[v.first+i][v.second] = ans[v.first][v.second] + 1;
                    if(plane[v.first+i][v.second] == '.') Q.push(MP(v.first+i, v.second));
                }
            }
        }

        for(int i = -1; i<=1; i++){
            if(v.second + i <=n && v.second + i>=1){
                if(ans[v.first][v.second+i] == INF && (plane[v.first][v.second+i] == '.' || plane[v.first][v.second+i] == '#' || plane[v.first][v.second+i] == 'P' || plane[v.first][v.second+i] == 'K')){
                    ans[v.first][v.second+i] = ans[v.first][v.second] + 1;
                    if(plane[v.first][v.second+i] == '.') Q.push(MP(v.first, v.second+i));
                }
            }
        }
    }

    return ans;
}

void processRow(int r, vector<char> &row, vector<int>& dist, vector<vector<vector<int>>>& proposed, int in){
    vector<int> prop(n+1, INF);
    for(int i = 1; i<=n; i++){
        if(row[i] != 'X'){
            int temp = dist[i];
            if(i > 1){
                if(in == 0){
                    temp = min(dist[i], prop[i-1]+1);
                }else{
                    temp = min(dist[i], prop[n-i+2]+1);
                }
            }
            if(in == 0){
                prop[i] = min(prop[i], temp);
            }else{
                prop[n-i+1] = min(prop[n-i+1], temp);
            }
        }else{
            if(in == 0){
                prop[i] = INF;
            }else{
                prop[n-i+1] = INF;
            }
        }
    }

    for(int i =0; i<=n; i++){
        proposed[r][i].back() = min(proposed[r][i].back(), prop[i]);
    }
}

void processCol(int c, vector<char> &col, vector<int>& dist, vector<vector<vector<int>>>& proposed, int in){
    vector<int> prop(n+1, INF);
    for(int i = 1; i<=n; i++){
        int temp = dist[i];
        if(col[i] != 'X'){
            if(i > 1){
                if(in == 0){
                    temp = min(dist[i], prop[i-1]+1);
                }else{
                    temp = min(dist[i], prop[n-i+2]+1);
                }
            }
            if(in == 0){
                prop[i] = min(prop[i], temp);
            }else{
                prop[n-i+1] = min(prop[n-i+1], temp);
            }
        }else{
            if(in == 0){
                prop[i] = INF;
            }else{
                prop[n-i+1] = INF;
            }
        }
    }

    for(int i = 0; i<prop.size(); i++){
        proposed[i][c].back() = min(proposed[i][c].back(), prop[i]);
    }
}

void getProposedRow(int row, vector<vector<vector<int>>>& proposed, vector<vector<int>>& dist){
    processRow(row, plane[row], dist[row], proposed, 0);
    vector<char> pC;
    pC.PB('0');
    for(int i = n; i>=1; i--){
        pC.PB(plane[row][i]);
    }
    
    vector<int> d = {INF};
    for(int i = n; i>=1; i--){
        d.PB(dist[row][i]);
    }
    processRow(row, pC, d, proposed, 1);
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

    processCol(col, pC, d, proposed, 0);
    pC.clear();
    pC.PB('0');
    for(int i = n; i>=1; i--){
        pC.PB(plane[i][col]);
    }
    d.clear();
    d.PB(INF);
    for(int i = n; i>=1; i--){
        d.PB(dist[i][col]);
    }
    processCol(col, pC,d, proposed, 1);
}

vector<vector<int>> getDp(vector<vector<int>> &distP, vector<vector<int>> &distK){
    vector<vector<int>> dp(n+1, vector<int>(n+1, 00));

    //get proposed
    vector<int> temp = {INF};
    vector<vector<vector<int>>> proposed(n+1, vector<vector<int>>(n+1, temp));
    for(int i = 1; i<=n; i++){
        getProposedRow(i, proposed, distP);
        getProposedCol(i, proposed, distP);
    }
    for(int i = 0; i<=n; i++){
        for(int j = 0; j<=n; j++){
            proposed[i][j].PB(INF);
        }
    }
    for(int i = 1; i<=n; i++){
        getProposedRow(i, proposed, distK);
        getProposedCol(i, proposed, distK);
    }

    // for(int i = 0; i<proposed.size(); i++){
    //     for(int j =0 ;j <proposed[i].size(); j++){
    //         cout<<"(";
    //         if(proposed[i][j][0] != INF){
    //             cout<<proposed[i][j][0];
    //         }else{
    //             cout<<"-1";
    //         }
    //         cout<<", ";
            
    //         if(proposed[i][j][1] != INF){
    //             cout<<proposed[i][j][1];
    //         }else{
    //             cout<<"-1";
    //         }
    //         cout<<") ";
    //     }
    //     cout<<"\n";
    // }

    //get dp
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
    while(n.first != P.first || n.second != P.second){
        PII p = previous[n.first][n.second];
        if(p.first < n.first){
            ans.PB('D');
        }else if(p.first > n.first){
            ans.PB('G');
        }else if(p.second < n.second){
            ans.PB('P');
        }else{
            ans.PB('L');
        }
        n = p;
    }

    reverse(ans.begin(), ans.end());

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
    if(get<0>(ansS) == -1){
        cout<<"NIE\n";
        return 0;
    }
    cout<<get<0>(ansS)<<"\n";
    cout<<get<1>(ansS).first<<" "<<get<1>(ansS).second<<"\n";
    // for(int i = 0; i<get<2>(ansS).size(); i++){
    //     cout<<get<2>(ansS)[i]<<" ";
    // }
    for(int i = 0; i<get<2>(ansS).size(); i++){
        char move = get<2>(ansS)[i];
        cout<<move;
    }

    return 0;
}