#include<iostream>
#include <vector>

#include <cstdlib>
#include <ctime>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;
const int MAXZ = 50;
const int MAXN = 100'000;
const int MAXM = 100'000;

int z;
int n,m;
vector<vector<int>> logs;//t - j - i

void getData(){
    logs.clear();
    cin>>n>>m;
    logs.assign(n+1, vector<int>());
    for(int o = 0; o<m; o++){
        int t,j,i;
        cin>>t>>j>>i;
        logs[o].PB(t);
        logs[o].PB(j);
        logs[o].PB(i);
    }
}

void getRandom(){
    srand(time(0));
    n =rand()%5+1;
    m = rand()%10+1;
    logs.clear();
    logs.assign(n+1, vector<int>());
    for(int o = 0; o<m; o++){
        int t = rand()%m+1,j = rand()%n+1,i = rand()%n;
        logs[o].PB(t);
        logs[o].PB(j);
        logs[o].PB(i);
    }
}

void printData(){
    cout<<n<<" "<<m<<"\n";
    for(int o = 0; o<m; o++){
        cout<<logs[o][0]<<" "<<logs[o][1]<<" "<<logs[o][2]<<"\n";
    }
}

int brute(){
    bool ok = true;
    int ans = 0;
    for(int i = 0; i<m; i++){
        int home = n, before = 0, work = 0, after = 0, gone = 0;
        vector<pair<PII,int>> attend(m+1, MP(MP(0,0),INF));
        vector<PII> range(n+1, MP(INF,INF));
        for(int j = 0; j<=i; j++){
            int t = logs[j][0];
            int p = logs[j][1];
            if(attend[t].second == logs[j][2]+1 || attend[t].second == INF){
                attend[t].second = logs[j][2]+1;
                if(range[p].first > t){
                    if(range[p].first != INF){
                        attend[range[p].first].first.first--;
                    }
                    attend[t].first.first++;
                    range[p].first = t;
                }
                if(range[p].second < t){
                    if(range[p].second != INF){
                        attend[range[p].second].first.second--;
                    }
                    attend[t].first.second++;
                    range[p].second = t;
                }
            }else{
                ok = false;
                break;
            }
        }
        for(int j = 1; j<=m; j++){
            int curWork = before+ work+after;
            if(curWork > attend[j].second){

            }else if(curWork <attend[j].second){
                int dif = attend[j].second- curWork;
                if(dif > home){
                    ok =false;
                    break;
                }else{
                    home -= dif;
                    before += dif;
                }
            }
        }

        if(ok){
            ans++;
        }else{
            break;
        }
    }
    return ans;
}

int solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cin>>z;
    z= 1;
    for(int i =0; i<z; i++){
        int op = 1;
        for(int test = 1; test<=1; test++){
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
                return 0;
            }
            cout<<"CORRECT\n";
        }
    }

    return 0;
}