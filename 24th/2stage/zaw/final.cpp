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
    srand(time(0));

    n = rand()%10;
    for(int i =0; i< n; i++){
        char c;
        if(rand()%2 == 0){
            c = 'T';
        }else{
            c = 'N';
        }

        if(c == 'N'){
            int a = rand()%n+1, b= rand()%n+1;
            if(a == b){
                if(a == n){
                    b--;
                }else{
                    b++;
                }
            }
            vector<int> vec = {a,b};
            rep.PB(MP(c,vec));
        }else{
            int a = rand()%n+1;
            vector<int> vec = {a};
            rep.PB(MP(c,vec));
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

    for(int i = 1; i<=n; i ++){
        if(graph[i][0].size() == 0){
            vector<int> temp = {0};
            return MP(false, temp);
        }
    }

    queue<PII> Q;

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

    while(!Q.empty()){
        PII v = Q.front();
        Q.pop();
        
        bool ok = false;
        for(int i = 0; i<graph[v.first][v.second].size(); i++){
            int cur = graph[v.first][v.second][i];
            if(v.second == 0){
                if(!usedPlayer[cur]){
                    Q.push(MP(cur, 1));
                    usedPlayer[cur] = true;
                }
            }else{
                if(!usedPos[cur]){
                    ok = true;
                    Q.push(MP(cur,0));
                    usedPos[cur] = v.first;
                }
            }
        }

        if(!ok){
            vector<int> temp = {0};
            return MP(false, temp);
        }
    }

    //get all the looops
    vector<int> loop;

    for(int i = 1; i<=n; i++){
        int len = 0;
        queue<PII> Q;
        if(usedPlayer[i] == -1){
            Q.push(MP(i+1, 0));
        }

        while(!Q.empty()){
            PLL v = Q.front();
            Q.pop();

            for(int i = 0; i<graph[v.first][v.second].size(); i++){
                int cur = graph[v.first][v.second][i];
                if(v.second == 0){
                    if(!usedPlayer[cur]){
                        Q.push(MP(cur, 1));
                        usedPlayer[cur] = v.first;
                        len++;
                    }
                }else{
                    if(!usedPos[cur]){
                        Q.push(MP(cur, 0));
                        usedPos[cur] = v.first;
                    }
                }
            }
        }

        loop.PB(len);
    }

    //get ans
    if(loop.size() == 0){
        vector<int> comb;
        for(int i = 1; i<=n; i++){
            comb.PB(usedPos[i]);
            if(usedPos[i] == -1){
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