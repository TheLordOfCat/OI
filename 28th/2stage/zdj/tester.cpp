#include <iostream>
#include <vector>
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

int n, m;
vector<PII> relat;

void getData(){
    relat.clear();

    cin>>n>>m;
    for(int i = 0; i<m; i++){
        int a, b;
        cin>>a>>b;
        relat.PB(MP(a,b));
    }
}

void getRandom(){
    relat.clear();
    srand(time(0));

    n = rand()%10+1;
    m = 0;
    for(int i = 1; i<n; i++){
        relat.PB(MP(i,i+1));
        m++;
    }
    relat.PB(MP(n,1));
    m++;

    int ind = 1;
    while(ind != n){
        int con = rand()%n+1;
        if(ind == n){
            relat.PB(MP(1,n));
            m++;
        }else if(ind + con >n){
            relat.PB(MP(ind,n));
            m++;
        }else{
            relat.PB(MP(ind,con+ind));
            ind += con;
            m++;
        }  
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<relat.size(); i++){
        cout<<relat[i].first<<" "<<relat[i].second<<"\n";
    }
}

vector<int> brute(){
    vector<vector<int>> graph(n+1, vector<int>());
    for(int i = 0; i<relat.size(); i++){
        int a = relat[i].first, b = relat[i].second;
        graph[a].PB(b);
        graph[b].PB(a);
    }


    vector<int> ans;
    vector<int> perm;

    for(int i = 1; i<=n; i++){
        perm.PB(i);
    }

    do{
        bool ok = true;
        for(int i = 1; i<=n; i++){
            int countB = 0, countS = 0;
            for(int j = 0; j<graph[i].size(); j++){
                int cur = graph[i][j];
                if(perm[i-1] > perm[cur-1]){
                    countS++;
                }else{
                    countB++;
                }
            }
            if(countB != countS){
                ok = false;
            }
        }

        if(ok){
            ans = perm;
        }
    }while(next_permutation(perm.begin(), perm.end()));

    return ans;
}

vector<int> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        if(ansB.size() != ansS.size()){
            cout<<"ERROR\n";
            cout<<"BRUTE: ";
            for(int j =0 ; j<ansB.size(); j++){
                cout<<ansB[j]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: ";
            for(int j =0 ; j<ansS.size(); j++){
                cout<<ansS[j]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        }else{
            for(int i = 0; i<ansB.size(); i++){
                if(ansB[i] != ansS[i]){
                    cout<<"ERROR\n";
                    cout<<"BRUTE: ";
                    for(int j =0 ; j<ansB.size(); j++){
                        cout<<ansB[j]<<" ";
                    }
                    cout<<"\n";
                    cout<<"SOLVE: ";
                    for(int j =0 ; j<ansS.size(); j++){
                        cout<<ansS[j]<<" ";
                    }
                    cout<<"\n";
                    printData();
                    return 0;
                }
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}