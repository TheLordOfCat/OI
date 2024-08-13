#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PIC pair<int,char>
#define PB push_back
#define MT make_tuple

bool operator==(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

int n, m;
vector<tuple<int,int,char>> edges;
int d;
vector<int> query;

void getData(){
    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        char c;
        cin>>c;
        edges.PB(MT(a,b,c));
    }
    cin>>d;
    for(int i = 0; i<d; i++){
        int temp;
        cin>>temp;
        query.PB(temp);
    }
}

void getRandom(){
    edges.clear();
    query.clear();

    srand(time(0));

    n = rand()%10+1;
    m = 0;
    for(int i = 1; i <= n; i++){
        int con = rand()%3+1;
        for(int j = 0; j<con; j++){
            int temp = i;
            while(temp == i){
                temp = rand()%n+1;
            }
            int type = rand()%2+1;
            char c;
            if(type == 1){
                c = 'a';
            }else{
                c = 'b';
            }
            edges.PB(MT(i,temp,c));
            m++;
        }
    }

    vector<bool> vis(n+1, false);
    d = rand()%n+1;
    for(int i = 0; i<d; i++){
        int temp = rand()%n+1;
        while(!vis[temp]){
            temp = rand()%n+1;
        }
        vis[temp] = true;
        query.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i= 0; i<edges.size(); i++){
        cout<<get<0>(edges[i])<<" "<<get<1>(edges[i])<<" "<<get<2>(edges[i])<<"\n";
    }
    cout<<d<<"\n";
    for(int i= 0; i<query.size(); i++){
        cout<<query[i]<<" ";
    }
    cout<<"\n";
}

vector<vector<char>> brute(){
    //creating the graph
    vector<vector<PIC>> graph(n+1, vector<PIC>());
    vector<vector<PIC>> graphR(n+1, vector<PIC>());
    for(int i = 0; i<m; i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graphR[b].PB(MP(a,c));
    }

    vector<vector<char>> ans;

    for(int i = 0; i<d; i++){
        queue<PII> Q;
        Q.push(MP(query[i], query[i+1]));

        vector<vector<tuple<int,int,char>>> pre(n+1, vector<tuple<int,int,char>>(n+1, MT(-1, -1, '1')));

        PII V = MP(-1,-1);
        char add = '-';

        while(!Q.empty()){
            PII v = Q.front();
            Q.pop();

            bool found = false;

            for(int j = 0; j<graph[v.first].size(); j++){
                int cur1 = graph[v.first][j].first;
                char c1 = graph[v.first][j].second;

                for(int o = 0; o<graphR[v.second].size(); o++){
                    int cur2 = graphR[v.second][o].first;
                    char c2 = graphR[v.second][o].second;

                    if(c1 == c2){
                        pre[cur1][cur2] = MT(v.first,v.second,c1);
                        if(cur1 == cur2){
                            found = true;
                            V = MP(cur1, cur2);
                            break;
                        }else if(cur1 == v.second && cur2 == v.first){
                            found = true;
                            add = c1;
                            V = v;
                            break;
                        }

                        Q.push(MP(cur1, cur2));
                    }
                }
                if(found){
                    break;
                }
            }
        }

        vector<char> temp;
        if(V.first == -1){
            ans.PB(temp);
            continue;
        }
        while(get<0>(pre[V.first][V.second]) != -1){
            int a = get<0>(pre[V.first][V.second]), b = get<1>(pre[V.first][V.second]); char c = get<2>(pre[V.first][V.second]);
            temp.PB(c);
            V = MP(a,b);
        }
        int len = temp.size();
        if(add != '-'){
            temp.PB(add);
            len -= 1;

        }
        for(int j = 0; j<=len; j++){
            temp.PB(temp[j]);
        }

        ans.PB(temp);
    }

    return ans;
}

vector<vector<char>> solve(){
    //creating the graph
    vector<vector<PIC>> graph(n+1, vector<PIC>());
    vector<vector<PIC>> graphR(n+1, vector<PIC>());
    for(int i = 0; i<m; i++){
        int a = get<0>(edges[i]), b = get<1>(edges[i]), c = get<2>(edges[i]);
        graph[a].PB(MP(b,c));
        graphR[b].PB(MP(a,c));
    }

    //creating the graph ''
    vector<vector<tuple<int,int,char>>> graphS(n+1, vector<tuple<int,int,char>>());
    vector<vector<tuple<int,int,char>>> graphSR(n+1, vector<tuple<int,int,char>>());
    for(int i = 0; i<m; i++){
        
    }   
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<= 1; test ++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<vector<char>> ansB = brute();
        vector<vector<char>> ansS = solve();
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: \n";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j].size()<<" ";
                    for(int o = 0; o<ansB[j].size(); o++){
                        cout<<ansB[j][o];
                    }
                    cout<<"\n";
                } 
                cout<<"SOLVE: \n";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j].size()<<" ";
                    for(int o = 0; o<ansS[j].size(); o++){
                        cout<<ansS[j][o];
                    }
                    cout<<"\n";
                } 
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}