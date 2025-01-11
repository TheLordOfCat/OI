#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PB push_back
#define PII pair<int,int>
#define MP make_pair
#define PLL pair<ll,ll>

int n, m;
vector<int> c;
vector<int> s;
vector<vector<int>> a;

void getData(){
    c.clear(); s.clear(); a.clear();
    
    cin>>n>>m;
    for(int i =0 ; i<n; i++){
        int temp;
        cin>>temp;
        c.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        s.PB(temp);
    }
    for(int i = 0; i<m; i++){
        a.PB(vector<int>());
        for(int j = 0; j<n; j++){
            int temp;
            cin>>temp;
            a.back().PB(temp);
        }
    }
}

void getRandom(){
    c.clear(); s.clear(); a.clear();

    srand(time(0));

    n = rand()%10+1;
    m = rand()%10+1;

    for(int i =0 ; i<n; i++){
        int temp = rand()%10+1;
        c.PB(temp);
    } 
    for(int i =0 ; i<n; i++){
        int temp = rand()%11;
        s.PB(temp);
    }
    for(int i =0; i<m; i++){
        vector<int> vec;
        for(int j = 0; j<n; j++){
            int lastMin = 0;
            if(a.size() > 0) lastMin = a.back()[j];
            int temp = rand()%10+lastMin;
            vec.PB(temp);
        }
        a.PB(vec);
    } 
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<c.size(); i++){
        cout<<c[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<s.size(); i++){
        cout<<s[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<a.size(); i++){
        for(int j = 0; j<a[i].size(); j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}

ll recBrute(int ind, vector<int> last){
    ll ans = INF;
    if(ind >= m) return 0;
    vector<int> cur = a[ind];
    sort(cur.begin(), cur.end());
    do{ 
        bool ok = true;
        ll base = 0;

        for(int i = 0; i<n; i++){
            if(last[i] <= cur[i]){
                base += (cur[i]-last[i])*c[i]; 
            }else{
                ok = false;
                break;
            }
        }

        if(ok){
            ll temp = recBrute(ind+1, cur);
            ans = min(temp + base, ans);
        }   
    }while(next_permutation(cur.begin(), cur.end()));
    return ans;
}

ll brute(){
    ll ans = recBrute(0,s);
    return ans;
}

ll solve(){

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
        ll ansB = brute();
        ll ansS = solve();
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