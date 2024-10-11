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
        
            //find the shortes path
            vector<vector<PII>> prev(n+1, vector<PII>(n+1, MP(-1,-1)));
            queue<PII> Q;
            Q.push(P);

            while(!Q.empty()){
                PII v = Q.front();
                Q.pop();
                if(v.first == K.first && v.second == K.second){
                    break;
                }

                for(int o = -1; o<2; o+=2){
                    if(prev[v.first+o][v.second].first == -1){
                        Q.push(MP(v.first+o, v.second));
                        prev[v.first+o][v.second] = v;
                    }
                }
                for(int o = -1; o<2; o+=2){
                    if(prev[v.first][v.second+o].first == -1){
                        Q.push(MP(v.first, v.second+o));
                        prev[v.first][v.second + o] = v;
                    }
                }
            }

            //get the distance 
            vector<int> dir;
            PII v = K;
            while(v.first != P.first && v.second != P.second){
                PII p = prev[v.first][v.second];
                if(p.first < v.first){
                    dir.PB(1);
                }else if(p.first > v.first){
                    dir.PB(3);
                }else if(p.second < v.second){
                    dir.PB(4);
                }else{
                    dir.PB(2);
                }
            }

            reverse(dir.begin(), dir.end());
            if(dir.size() < get<0>(ans)){
                ans = MT(dir.size(), MP(i,j), dir);
            }
        }
    }

    return ans;
}

tuple<int, PII, vector<int>> solve(){

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