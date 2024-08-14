#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back

int n,m,k,d;
vector<PII> query;

void getData(){
    cin>>n>>m>>k>>d;
    for(int i =0; i<m; i++){
        int r, x;
        cin>>r>>x;
        query.PB(MP(r,x));
    }
}

void getRandom(){
    query.clear();
    
    srand(time(0));

    n = rand()%8+1;
    m = rand()%5+1;
    k = rand()%10+1; 
    d = rand()%d;

    vector<int> t(n+1, 0);

    for(int i = 0; i<m; i++){
        int r = rand()%n+1;
        if(rand()%4+1 == 1){    
            int x = rand()%t[r]+1;
            query.PB(MP(r,x*(-1)));
        }else{
            int x = rand()%10+1;
            t[r] += x;
            query.PB(MP(r,x));
        }
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<" "<<k<<" "<<d<<"\n";
    for(int i = 0; i<m; i++){
        cout<<query[i].first<<" "<<query[i].second<<"\n";
    } 
}

vector<int> brute(){
    vector<int> ans;
    
    vector<int> t(n+1, 0);
    for(int o = 0; o<m; o++){
        int r = query[o].first;
        int x = query[o].second;

        t[r] += x;

        bool ok = true;

        vector<int> s(n+1, k);
        for(int i = 1; i<=n; i++){
            int g = t[i];
            for(int j = i; j<=i+d && j<=n; j++){
                int temp = min(g,s[j]);
                g -= temp;
                s[j] -= temp;
                if(g == 0){
                    break;
                }
            }
            if(g > 0){
                ok = false;
                break;
            }
        }

        if(ok){
            ans.PB(1);
        }else{
            ans.PB(0);
        }
    }

    return ans;
}

vector<int> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"Test nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<m; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j =0 ;j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j =0 ;j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}