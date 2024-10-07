#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PLL pair<ll,ll>
#define PB push_back
#define MT make_tuple

int n, X, z;
vector<int> x;
vector<int> k;

void getData(){
    x.clear();
    k.clear();

    cin>>n>>X>>z;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<z; i++){
        int temp;
        cin>>temp;
        k.PB(temp);
    }
}

bool compareQuery(PLL a, PLL b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first < b.first;
}

bool compareOrg(PLL a, PLL b){
    if(a.first == b.first){
        return a.second > b.second;
    }
    return a.first < b.first;
}

void updateQ(queue<tuple<ll,ll,ll>>& Q, vector<PLL>& org, ll& index, ll& sim, vector<PLL>& ans, vector<PLL>& querys){
    while(get<2>(Q.front()) + index > querys[sim].first){
        if(sim >= querys.size()) break;
        ans[querys[sim].second] = (MP(get<1>(Q.front()) + get<0>(Q.front())*(querys[sim].first - index) + get<0>(Q.front())/2, 1));
        sim++;
    }

    index += get<2>(Q.front());
    Q.push(MT(get<0>(Q.front())/2, get<1>(Q.front()), get<2>(Q.front())*2));
    Q.pop();
}

void updateOrg(queue<tuple<ll,ll,ll>>& Q, vector<PLL>& org, ll& index, ll& sim, vector<PLL>& ans, vector<PLL>& querys){
    while(index == querys[sim].first){ 
        ans[querys[sim].second] = (MP(org.back().second + org.back().first/2, 1));
        sim++;
    }
    Q.push(MT(org.back().first/2, org.back().second, 2));
    org.pop_back();
    index++;   
}

vector<PLL> solve(){    
    //avoid fractions
    ll maxDiv = 1<<30;
    vector<ll> pla;
    for(int i = 0; i < x.size(); i++){
        ll temp = x[i];
        temp *= maxDiv;
        pla.PB(temp);
    }
    
    //get base queue
    vector<PLL> org;
    for(int i = 1; i<pla.size(); i++){
        org.PB(MP(pla[i] - pla[i-1], pla[i-1]));
    }

    sort(org.begin(), org.end(), compareOrg);
    // reverse(org.begin(), org.end());
    
    //sort querys
    vector<PLL> querys;
    for(int i = 0; i<k.size(); i++){
        querys.PB(MP(k[i], i));
    } 
    sort(querys.begin(), querys.end(), compareQuery);

    //simulating
    vector<PLL> ans(k.size(), MP(0,0));

    queue<tuple<ll,ll,ll>> Q;
    ll sim = 0;
    ll index = 1;
    while(sim != querys.size()){
        if(org.size() > 0 && Q.size() > 0){ //both queues have numbers
            if(org.back().first == get<0>(Q.front())){
                if(org.back().second < get<1>(Q.front())){
                    updateOrg(Q, org, index, sim, ans, querys);
                }else{
                    updateQ(Q, org, index, sim, ans, querys);
                }
            }else if(org.back().first < get<0>(Q.front())){//div Queue better
                updateQ(Q, org, index, sim,ans, querys);
            }else{
                updateOrg(Q, org, index, sim,ans, querys);//original queue better
            }

        }else if(org.size() > 0){ //only original queue
            updateOrg(Q, org, index, sim,ans, querys);
        }else{  //only div queue
            updateQ(Q, org, index, sim, ans, querys);
        }
    }

    //back to fractions
    for(int i = 0; i<ans.size(); i++){
        int pwr = 30;
        while(ans[i].first %2 == 0 && pwr > 0){
            ans[i].first /= 2;
            pwr--;
        }
        ans[i] = MP(ans[i].first, (1<<pwr));
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<PLL> ansS = solve();
    for(int j = 0; j<ansS.size(); j++){
        cout<<ansS[j].first<<"/"<<ansS[j].second<<"\n";
    } 

    return 0;
}