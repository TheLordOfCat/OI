#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

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

    // n = rand()%10+1;
    n = 150'000;
    // m = rand()%10+1;
    m = 2;

    for(int i =0 ; i<n; i++){
        // int temp = rand()%10+1;
        int temp = i+1;
        c.PB(temp);
    } 
    for(int i =0 ; i<n; i++){
        // int temp = rand()%11;
        int temp = 0;
        s.PB(temp);
    }
    for(int i =0; i<m; i++){
        vector<int> vec;
        for(int j = 0; j<n; j++){
            // int lastMin = 0;
            // if(a.size() > 0) lastMin = a.back()[j];
            // int temp = rand()%10+lastMin;
            int temp = 30*(i+1) + ((j+1)%17) + 1;
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

bool compareCustomPII(const PII a, const PII b){
    if(a.first == b.first){
        a.second < b.second;
    }
    return a.first > b.first;
}

ll solve(){
    //prepare sets
    vector<multiset<int>> aS(a.size(), multiset<int>());
    for(int i =0 ; i<a.size(); i++){
        for(int j = 0; j<a[i].size(); j++){
            aS[i].insert(a[i][j]);
        }
    }
    
    //simulate
    vector<PII> curLine;
    for(int i = 0; i<c.size(); i++){
        curLine.PB(MP(c[i],i));
    }

    sort(curLine.begin(), curLine.end(), compareCustomPII);
    
    for(int i = 0; i<curLine.size(); i++){
        curLine[i].first = s[curLine[i].second];
    }

    for(int i = 0; i<a.size(); i++){
        for(int j = 0; j<curLine.size(); j++){
            auto itr = aS[i].lower_bound(curLine[j].first);
            if(itr == aS[i].end()){
                return llINF;
            }
            curLine[j].first = *itr;
            aS[i].erase(itr);
        }
    }

    //answer
    ll ans = 0;
    for(int i = 0; i<curLine.size(); i++){
        ans += ((ll)curLine[i].first-(ll)s[curLine[i].second])*((ll)c[curLine[i].second]);
    }
    
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        // cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        ll ansS = solve();
        if(ansS == llINF){
            cout<<"NIE\n";
        }else{
            cout<<ansS<<"\n";
        }
    }

    return 0;
}