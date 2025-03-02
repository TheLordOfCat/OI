#include<iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back

const int MOD = 1'000'000'007;

int n;
vector<pair<char, vector<int>>> rep;

void getData(){
    rep.clear();

    cin>>n;
    for(int i =0; i< n; i++){
        char c;
        cin>>c;
        if(c == 'N'){
            int a, b;
            cin>>a>>b;
            vector<int> vec = {a,b};
            rep.PB(MP(c,vec));
        }else{
            int a;
            cin>>a;
            vector<int> vec = {a};
            rep.PB(MP(c,vec));
        }
    }
}

void getRandom(){
    rep.clear();

    srand(time(0));

    n = 1'000'000;
    for(int i = 0; i<n; i++){
        vector<int> temp = {i+1};
        rep.PB(MP('T', temp));
    }

    // n = rand()%10+1;
    // vector<int> player;
    // for(int  i = 1; i<=n ;i++){
    //     player.PB(i);
    // }

    // int r = rand()%n+1;
    // for(int i = 0; i<r; i++){
    //     next_permutation(player.begin(), player.end());
    // }

    // rep.assign(n, pair<char,vector<int>>());
    // for(int i = 0; i<player.size(); i++){
    //     int type = rand()%2;
    //     if(type == 0){
    //         vector<int> temp = {i+1};
    //         rep[player[i]] = MP('T', temp);
    //     }else{
    //         int f = rand()%n+1;
    //         while(i+1 != f){
    //             f = rand()%n+1;
    //         }
    //         vector<int> temp = {i+1, f};
    //         rep[player[i]] = MP('N', temp);
    //     }
    // }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<rep.size(); i++){
        cout<<rep[i].first<<" ";
        for(int j = 0; j<rep[i].second.size(); j++){
            cout<<rep[i].second[j]<<" ";
        }
        cout<<"\n";
    }
}

pair<bool, vector<int>> brute(){
    pair<bool, vector<int>> ans;

    vector<vector<int>> posCand(n+1, vector<int>());
    for(int i =0 ; i<rep.size(); i++){
        for(int j = 0;j <rep[i].second.size(); j++){
            posCand[rep[i].second[j]].PB(i+1);
        }
    }

    vector<int> players;
    for(int i = 1; i<=n; i++) players.PB(i);

    vector<int> first;
    do{
        bool ok = true;
        for(int i = 0; i<players.size(); i++){
            bool found = false;
            for(int j = 0; j<posCand[i+1].size(); j++){
                if(posCand[i+1][j] == players[i]){ // erorr
                    found = true;
                    break;
                }
            }
            if(!found){
                ok = false;
                break;
            }
        }

        if(ok){
            if(first.size() == 0){
                first.assign(n, 0);
                for(int i =0; i<players.size(); i++){
                    first[players[i]-1] = i+1;
                }
            }else{
                if(ans.second.size() == 0) ans.second.PB(1);
                ans.second.back()++;
            }
        }

    }while(next_permutation(players.begin(), players.end()));

    if(ans.second.size() == 0){
        ans = MP(true, first);
    }else{
        ans.first = false;
    }

    return ans;
}

vector<vector<PII>> getSCC(vector<int> &conPlayer, vector<int> &conPos, vector<vector<vector<int>>>& graph){
    vector<vector<PII>> scc;

    vector<vector<bool>> vis(n+1, vector<bool>(2, false));
    for(int i = 0; i<conPos.size(); i++){
        if(conPos[i] != 0){
            vis[i][0] = true;
        }
    }
    for(int i = 0; i<conPlayer.size(); i++){
        if(conPlayer[i] != 0){
            vis[i][1] = true;
        }
    }

    for(int i = 1; i<=n; i++){
        for(int j = 0; j<=1; j++){
            if(!vis[i][j]){
                vis[i][j] = true;

                vector<PII> comp;
                queue<PII> Q;
                Q.push(MP(i,j));
                comp.PB(MP(i,j));

                while(!Q.empty()){
                    PII v = Q.front();
                    Q.pop();

                    for(int o = 0; o<graph[v.first][v.second].size(); o++){
                        int cur = graph[v.first][v.second][o];
                        if(!vis[cur][(v.second+1)%2]){
                            vis[cur][(v.second+1)%2] = true;
                            Q.push(MP(cur, (v.second+1)%2));
                            comp.PB(MP(cur, (v.second+1)%2));
                        }
                    }
                }
                scc.PB(comp);
            }
        }
    }

    return scc;
}

bool checkIntergity(vector<PII> &comp, vector<vector<vector<int>>>& graph){
    queue<PII> Q;
    vector<vector<bool>> vis(n+1, vector<bool>(n+1, false));

    for(int i = 0; i<comp.size(); i++){
        Q.push(comp[i]);
    }

    int countPlayers = 0, countPos = 0;
    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();

        if(vis[v.first][v.second]){
            continue;
        }
        if(v.second == 0){
            countPos++;
        }else{
            countPlayers++;
        }

        vis[v.first][v.second] = true;
        for(int i =0; i<graph[v.first][v.second].size(); i++){
            int cur = graph[v.first][v.second][i];
            if(vis[cur][(v.second+1)%2]){
                Q.push(MP(cur,(v.second+1)%2));
            }
        }
    }

    if(countPos != countPlayers){
        return false;
    }
    return true;
}

void removeLine(PII start, vector<int> &conPlayer, vector<int> &conPos, vector<vector<int>>& edges, vector<vector<vector<int>>>& graph){
    queue<PII> Q;
    Q.push(start);

    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();

        for(int i = 0; i<graph[v.first][v.second].size(); i++){
            int cur = graph[v.first][v.second][i];
            edges[cur][(v.second+1)%2]--;
            if(edges[cur][(v.second+1)%2] <= 1){
                if(v.second == 0){
                    if(conPlayer[cur] == 0){
                        Q.push(MP(cur,(v.second+1)%2));
                    }
                    if(conPos[v.first] == 0 && conPlayer[cur] == 0){
                        conPos[v.first] = cur;
                        conPlayer[cur] = v.first;
                    }
                }else{
                    if(conPos[cur] == 0){
                        Q.push(MP(cur,(v.second+1)%2));
                    }
                    if(conPlayer[v.first] == 0 && conPos[cur] == 0){
                        conPlayer[v.first] = cur;
                        conPos[cur] = v.first;
                    }
                }
            }
        }
    }
}   

pair<bool,vector<int>> solve(){
    //create graph 0 - pos, 1 - player
    vector<vector<vector<int>>> graph(n+1, vector<vector<int>>(2, vector<int>()));
    for(int i = 0; i<rep.size(); i++){
        for(int j = 0; j<rep[i].second.size(); j++){
            graph[i+1][1].PB(rep[i].second[j]);
            graph[rep[i].second[j]][0].PB(i+1);
        } 
    }

    vector<vector<int>> edges(n+1, vector<int>(2,0));
    for(int i = 1; i<= n; i++){
        for(int j = 0;j <=1; j++){
            edges[i][j] = graph[i][j].size();
        }
    }

    vector<int> conPlayer(n+1, 0), conPos(n+1, 0);
    //get SCC
    vector<vector<PII>> scc = getSCC(conPlayer, conPos, graph);

    //verify intergirty
    for(int i = 0; i<scc.size(); i++){
        if(!checkIntergity(scc[i], graph)){
            vector<int> temp = {0};
            return MP(false,temp);
        }
    }

    //remove single lines
    for(int i = 1; i<=n; i++){
        if(graph[i][1].size() == 1){
            removeLine(MP(i,1), conPlayer, conPos, edges, graph);
        }
    }

    //get SCC
    scc = getSCC(conPlayer, conPos, graph);

    //get ans
    if(scc.size() == 0){
        vector<int> comb;
        for(int i = 1; i<=n; i++){
            comb.PB(conPlayer[i]);
        }
        return MP(true, comb);
    }
    
    int ans = 1;
    for(int i = 0; i<scc.size(); i++){
        ans *= 2;
        ans %= MOD;
    }
    vector<int> temp = {ans};

    return MP(false, temp);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1 ; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        pair<bool,vector<int>> ansB = brute();
        pair<bool,vector<int>> ansS = solve();
        bool ok = true;
        if(ansB.first != ansS.first){
            ok = false;
        }

        if(ansB.second.size() != ansS.second.size()){
            ok = false;
        }else{
            for(int i = 0; i<ansB.second.size(); i++){
                if(ansB.second[i] != ansS.second[i]){
                    ok = false;
                    break;
                }
            }
        }

        if(!ok){
            cout<<"ERROR\n";
            cout<<"BRUTE:\n";
            if(ansB.first){
                cout<<"TAK\n";
            }else{
                cout<<"NIE\n";
            }
            for(int i = 0; i<ansB.second.size(); i++){
                cout<<ansB.second[i]<<"\n";
            }
            cout<<"SOLVE:\n";
            if(ansS.first){
                cout<<"TAK\n";
            }else{
                cout<<"NIE\n";
            }
            for(int i = 0; i<ansS.second.size(); i++){
                cout<<ansS.second[i]<<"\n";
            }
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}