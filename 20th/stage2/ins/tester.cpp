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
    logs.assign(m+1, vector<int>());
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
    logs.assign(m+1, vector<int>());
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
        vector<PII> range(n+1, MP(INF,-1));
        //process logs
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
                    if(range[p].second != -1){
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
        //verify
        for(int j = 1; j<=m; j++){
            if(attend[j].second == INF){
                continue;
            }
            work += attend[j].first.first;
            before -= attend[j].first.first;
            if(before < 0){
                home += before;
                before = 0;
            }
            if(home < 0){
                ok = false;
                break;
            }

            int workers = before + work + after;
            if(workers < attend[j].second){
                int dif = attend[j].second - workers;
                before += dif;
                home -= dif;
                if(home < 0){
                    ok = false;
                    break;
                }
            }else if(workers > attend[j].second){
                int dif = workers - attend[j].second;
                after -= dif;
                if(after < 0){
                    dif = (-1)*after;
                    after = 0;
                    before -= dif;
                    if(before < 0){
                        ok = false;
                        break;
                    }
                }
                gone += workers - attend[j].second;
            }
            work -= attend[j].first.second;
            after += attend[j].first.second;
        }
        if(ok){
            ans++;
        }else{
            break;
        }
    }
    return ans;
}

bool verify(int i){
    bool ok = true;
    int home = n, before = 0, work = 0, after = 0, gone = 0;
    vector<pair<PII,int>> attend(m+1, MP(MP(0,0),INF));
    vector<PII> range(n+1, MP(INF,-1));
    //process logs
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
                if(range[p].second != -1){
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
    //verify
    for(int j = 1; j<=m; j++){
        if(attend[j].second == INF){
            continue;
        }
        work += attend[j].first.first;
        before -= attend[j].first.first;
        if(before < 0){
            home += before;
            before = 0;
        }
        if(home < 0){
            ok = false;
            break;
        }

        int workers = before + work + after;
        if(workers < attend[j].second){
            int dif = attend[j].second - workers;
            before += dif;
            home -= dif;
            if(home < 0){
                ok = false;
                break;
            }
        }else if(workers > attend[j].second){
            int dif = workers - attend[j].second;
            after -= dif;
            if(after < 0){
                dif = (-1)*after;
                after = 0;
                before -= dif;
                if(before < 0){
                    ok = false;
                    break;
                }
            }
            gone += workers - attend[j].second;
        }
        work -= attend[j].first.second;
        after += attend[j].first.second;
    }
    return ok;
}

int solve(){
    int ans = 0;
    int left = 0, right = m-1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        bool ok = verify(mid);
        if(ok){
            ans = mid+1;
            left = mid+1;
        }else{
            right = mid-1;
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cin>>z;
    z= 1;
    int op = 0;
    for(int i =0; i<z; i++){
        for(int test = 1; test<=10'000; test++){
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