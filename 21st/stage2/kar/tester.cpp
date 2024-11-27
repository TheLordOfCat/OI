#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

const int INF = 2'000'000'000;

int n;
vector<PII> cards;
int m;
vector<PII> query;

void getData(){
    cards.clear(); query.clear();

    cin>>n;
    cards.PB(MP(-1,-1));
    for(int i = 0; i<n; i++){
        int a, b;
        cin>>a>>b;
        cards.PB(MP(a,b));
    }    
    cin>>m;
    for(int i =0; i<m; i++){
        int a, b;
        cin>>a>>b;
        query.PB(MP(a,b));
    }
}

void getRandom(){
    cards.clear(); query.clear();

    srand(time(0));

    // n = rand()%10+1;
    n = 4;
    cards.PB(MP(INF,INF));
    for(int i = 0; i<n; i++){
        int a = rand()%10+1;
        int b = rand()%10+1;
        cards.PB(MP(a,b));
    }

    // m = rand()%10+1;
    m = 4;
    for(int i = 0; i<m; i++){
        int a = rand()%n + 1;
        int b = rand()%n + 1;
        query.PB(MP(a,b));
    }
}

void printData(){
    cout<<n<<"\n";
    for(int  i =0; i<cards.size(); i++){
        cout<<cards[i].first<<" "<<cards[i].second<<"\n";
    }
    cout<<m<<"\n";
    for(int i = 0; i<query.size(); i++){
        cout<<query[i].first<<" "<<query[i].second<<"\n";
    }
}

vector<bool> brute(){
    vector<bool> ans;
    vector<PII> cB = cards;

    for(int i = 0; i<m; i++){
        //swap
        int s1 = query[i].first, s2 = query[i].second;
        swap(cB[s1],cB[s2]);

        //verify
        bool ok = true;
        int head = -1;
        for(int j = 1 ;j <=n; j++){
            int a = cB[j].first, b = cB[j].second;
            if(a >= head && b >= head){
                head = min(a,b);
            }else if(a >= head){
                head = a;
            }else if(b >= head){
                head = b;
            }else{
                ok = false;
            }
        }
        ans.PB(ok);
    }

    return ans;
}

vector<bool> solve(){
    
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
        vector<bool> ansB = brute();
        vector<bool> ansS = solve();
        for(int i = 0; i <m; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int i = 0; i<m; i++){
                    cout<<ansB[i]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int i = 0; i<m; i++){
                    cout<<ansS[i]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}