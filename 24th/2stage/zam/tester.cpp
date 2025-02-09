#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back
#define PLL pair<ll,ll>
#define MT make_tuple

ll w, h;
int n, m;
ll xP, yP;
ll xK, yK;
vector<tuple<PLL,PLL>> blocks;
vector<PLL> danger;

void getData(){
    blocks.clear();
    danger.clear();

    cin>>w>>h>>n>>m;
    cin>>xP>>yP;
    cin>>xK>>yK;
    for(int i = 0; i<n; i++){
        ll x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        blocks.PB(MT(MP(x1,y1), MP(x2,y2)));
    }
    for(int i = 0; i<m; i++){
        ll x,y;
        cin>>x>>y;
        danger.PB(MP(x,y));
    }
}

void getRandom(){
    blocks.clear();
    danger.clear();

    srand(time(0));

    w = rand()%10+2;
    h = rand()%10+2;
    n = 0; m = 0;

    xP = 1; yP = 1;
    xK = w-1; yK = h-1;

    int prevCol = 0;
    for(ll i = 2; i<w-1; i++){
        if(rand()%2 == 0){
            int sep = rand()%h+1;
            vector<bool> used(h+1, false);
            int count = 2;
            used[0] = true;
            used[h]  = true;
            
            while(count < sep){
                int a = 0;
                while(used[a]){
                    a = rand()%(h+1);
                }
                used[a] = true;
                count++;
            }

            ll cur = 0;
            for(ll j = 1; j<=h; j++){
                if(used[j]){
                    ll x1 = prevCol, y1 = cur, x2 = i, y2 = j;
                    blocks.PB(MT(MP(x1,y1),MP(x2,y2)));
                    n++;
                    cur = j;
                }
            }
            prevCol = i;
        }
    }

    if(prevCol != w){
        blocks.PB(MT(MP(prevCol, 0), MP(w,h)));
        n++;
    }

    vector<vector<int>> separetion(h+1, vector<int>(w+1, -1));
    for(int i = 0; i<n; i++){
        ll x1 = get<0>(blocks[i]).first, y1 = get<0>(blocks[i]).second, x2 = get<1>(blocks[i]).first, y2 = get<1>(blocks[i]).second;
        for(ll j = x1; j<=x2; j++){
            for(ll o = y1; o<=y2; o++){
                separetion[o][j] = i;
            }
        }
    }

    for(int i = separetion.size()-1; i>=0; i--){
        for(int j = 0;j <separetion[i].size();j ++){
            cout<<separetion[i][j]<<" ";
        }
        cout<<"\n";
    }

    vector<bool> blocked(n+1, false);

    for(int i = 1; i<n; i++){
        if(rand()%3 == 0){
            break;
        }else if(rand()%2 == 0){
            continue;
        }

        blocked[i] = true;

        queue<PLL> Q;
        vector<vector<bool>> vis(h+1, vector<bool>(w+1, false));
        Q.push(MP(1,1));
        vis[1][1] = true;

        while(!Q.empty()){
            PLL v = Q.front();
            Q.pop();

            for(int i = -1; i<2; i+=2){
                if(v.first + i <= 0 || v.first + i > w){
                    continue;
                }
                for(int j = -1;j <2; j+=2){
                    if(v.second + j <= 0 || v.second + j > h){
                        continue;   
                    }

                    if(!blocked[separetion[v.second+j][v.first+i]] && !vis[v.second+j][v.first+i]){
                        Q.push(MP(v.first+i, v.second+j));
                        vis[v.second+j][v.first+i] = true;
                    }
                }
            }
        }

        if(!vis[h][w]){
            blocked[i] = false;
        }else{
            m++;
            danger.PB(MP(get<0>(blocks[i]).first+1, get<0>(blocks[i]).second+1));
        }
    }

    for(int i = 0; i<m; i++){
        cout<<danger[i].first<<" "<<danger[i].second<<"\n";
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<w<<" "<<h<<" "<<n<<" "<<m<<"\n";
    cout<<xP<<" "<<yP<<"\n";
    cout<<xK<<" "<<yK<<"\n";
    for(int i = 0; i<n; i++){
        ll x1 = get<0>(blocks[i]).first, y1 = get<0>(blocks[i]).second, x2 = get<1>(blocks[i]).first, y2 = get<1>(blocks[i]).second;
        cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<"\n";
    }
    for(int i =0 ; i< m; i++){
        cout<<danger[i].first<<" "<<danger[i].second<<"\n";
    }
}

int brute(){
    //create plane
    vector<vector<int>> plane(h, vector<int>(w, -1));
    for(int o = 0; o<blocks.size(); o++){
        for(ll x = get<0>(blocks[o]).first; x<=get<1>(blocks[o]).second; x++){
            for(ll y = get<0>(blocks[o]).second; y<=get<1>(blocks[o]).second; x++){
                plane[y][x] = o;
            }   
        }
    }

    vector<bool> marked(n+1, false);
    for(int i = 0; i<danger.size(); i++){
        marked[plane[danger[i].second][danger[i].first]] = true;
    }

    //traverse plane
    queue<PLL> Q;
    Q.push(MP(xK,yK));
    vector<vector<int>> vis(h+1, vector<int>(w+1, -1));
    while(!Q.empty()){
        PLL v = Q.front();
        Q.pop();

        for(int i = -1; i<=1; i+=2){
            if(v.first + i <= 0 || v.first + i>w){
                continue;
            }
            for(int j = -1; j<=1; j+=2){
                if(v.second + j<= 0 || v.second + j > h){
                    continue;
                }

                if(vis[v.second+j][v.first+i] == -1 && !marked[plane[v.second+j][v.first+i]]){
                    if(plane[v.second+j][v.first+i] != plane[v.second][v.first]){
                        vis[v.second+j][v.first+i] = vis[v.second][v.first] +1;
                    }else{
                        vis[v.second+j][v.first+i] = vis[v.second][v.first];
                    }
                }
            }
        }
    }

    //ans
    return vis[yP][xP];
}

int solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 2; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        int ansB = brute();
        int ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}