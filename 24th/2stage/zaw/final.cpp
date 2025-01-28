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

    n = rand()%10+1;
    vector<int> player;
    for(int  i = 1; i<=n ;i++){
        player.PB(i);
    }

    int r = rand()%n+1;
    for(int i = 0; i<r; i++){
        next_permutation(player.begin(), player.end());
    }

    rep.assign(n, pair<char,vector<int>>());
    for(int i = 0; i<player.size(); i++){
        int type = rand()%2;
        if(type == 0){
            vector<int> temp = {i+1};
            rep[player[i]] = MP('T', temp);
        }else{
            int f = rand()%n+1;
            while(i+1 != f){
                f = rand()%n+1;
            }
            vector<int> temp = {i+1, f};
            rep[player[i]] = MP('N', temp);
        }
    }
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

pair<bool,vector<int>> solve(){
    //create graph 0 - pos, 1 - player
    vector<vector<vector<int>>> graph(n+1, vector<vector<int>>(2, vector<int>()));
    for(int i = 0; i<rep.size(); i++){
        for(int j = 0; j<rep[i].second.size(); j++){
            graph[i+1][1].PB(rep[i].second[j]);
            graph[rep[i].second[j]][0].PB(i+1);
        } 
    }

    queue<PII> Q;

    for(int i = 1; i<=n; i ++){
        if(graph[i][0].size() == 0){
            vector<int> temp = {0};
            return MP(false, temp);
        }else if(graph[i][0].size() == 1){
            Q.push(MP(i,0));
        }
    }

    //mark 
    vector<int> usedPos(n+1, -1), usedPlayer(n+1, -1);
    for(int i =0 ; i<rep.size(); i++){
        if(rep[i].first == 'T'){
            if(usedPos[rep[i].second.front()] == -1){
                usedPos[rep[i].second.front()] = i+1;
                usedPlayer[i+1] = rep[i].second.front();
                if(graph[rep[i].second.front()].size() > 1){
                    Q.push(MP(rep[i].second.front(), 0));
                }
            }else{
                vector<int> temp = {0};
                return MP(false, temp);
            }
        }else{
            if(graph[rep[i].second.front()][0].size() == 1){
                usedPos[rep[i].second.front()] = i+1;
                usedPlayer[i+1] = rep[i].second.front();
            }
            if(graph[rep[i].second.back()][0].size() == 1){
                usedPos[rep[i].second.back()] = i+1;
                usedPlayer[i+1] = rep[i].second.back();
            }

            if(graph[rep[i].second.back()][0].size() == 1 && graph[rep[i].second.front()][0].size() == 1){
                vector<int> temp = {0};
                return MP(false, temp);
            }
        }
    }

    //get all the single lines
    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();
        
        for(int i = 0; i<graph[v.first][v.second].size(); i++){
            int cur = graph[v.first][v.second][i];
            if(v.second == 0){
                if(usedPlayer[cur] == -1){
                    if(usedPos[v.first] == -1){
                        usedPos[v.first] = cur;
                        usedPlayer[cur] = v.first;
                    }
                    Q.push(MP(cur, 1));
                }
            }else{
                if(usedPos[cur] == -1){
                    if(usedPlayer[v.first] == -1){
                        usedPlayer[v.first] = cur;
                        usedPos[cur] = v.first;
                    }
                    Q.push(MP(cur,0));
                }
            }
        }

        if(v.second == 1){
            if(usedPlayer[v.first] == -1){
                vector<int> temp = {0};
                return MP(false, temp);
            }
        }
    }

    //get all the looops
    vector<int> loop;

    for(int i = 1; i<=n; i++){
        int len = 0;
        queue<PII> S;
        if(usedPlayer[i] == -1){
            S.push(MP(i+1, 0));
        }

        while(!S.empty()){
            PLL v = S.front();
            S.pop();

            for(int i = 0; i<graph[v.first][v.second].size(); i++){
                int cur = graph[v.first][v.second][i];
                if(v.second == 0){
                    if(!usedPlayer[cur]){
                        S.push(MP(cur, 1));
                        usedPlayer[cur] = v.first;
                        len++;
                    }
                }else{
                    if(!usedPos[cur]){
                        S.push(MP(cur, 0));
                        usedPos[cur] = v.first;
                    }
                }
            }
        }

        if(len != 0) loop.PB(len);
    }

    //get ans
    if(loop.size() == 0){
        vector<int> comb(n, 0);
        for(int i = 1; i<=n; i++){
            comb[i-1] = usedPlayer[i];
            if(usedPlayer[i] == -1){
                vector<int> temp = {0};
                return MP(false, temp);
            }
        }
        return MP(true, comb);
    }

    vector<int> tempVec = {1};
    pair<bool, vector<int>> ans = MP(false, tempVec);
    for(int i = 0; i<loop.size(); i++){
        ans.second.front() *= (1<<loop[i]);
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1 ; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        pair<bool,vector<int>> ansS = solve();
        
        if(ansS.first){
            cout<<"TAK\n";
        }else{
            cout<<"NIE\n";
        }
        for(int i = 0; i<ansS.second.size(); i++){
            cout<<ansS.second[i]<<"\n";
        }

    }

    return 0;
}