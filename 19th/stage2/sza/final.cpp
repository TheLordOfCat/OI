#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

using ll = long long int;
using ull = unsigned long long int;

const int MAXK = 100'000;
const int INF = 2'000'000'000;

int n;
vector<tuple<int,int,int>> items;
int p;
vector<tuple<int,int,int>> stealPlans;

void getData(){
    cin>>n;
    for(int i =0; i<n; i++){
        int c,a,b;
        cin>>c>>a>>b;
        items.PB(MT(c,a,b));
    }
    cin>>p;
    for(int i =0; i<p; i++){
        int m,k,s;
        cin>>m>>k>>s;
        stealPlans.PB(MT(m,k,s));
    }
}

struct CustomComparator {
    bool operator()(const pair<int, PII>& a, const pair<int, PII>& b) const {
        if (a.first < b.first) {
            return true;
        } else if (a.first > b.first) {
            return false;
        } else {
            if (a.second.first == 1 && b.second.first == 0) {
                return false; 
            } else if (a.second.first == 0 && b.second.first == 1) {
                return true; 
            } else {
                return a.second.second < b.second.second; 
            }
        }
    }
};

vector<int> solve(){
    vector<pair<int,PII>> order;
    for(int i = 0; i<n; i++){
        order.PB(MP(get<1>(items[i]), MP(0, i)));
    }
    for(int i = 0; i<p; i++){
        order.PB(MP(get<0>(stealPlans[i]), MP(1, i)));
    }

    sort(order.begin(), order.end(), CustomComparator());

    vector<int> mostTime(MAXK+1, 0);
    mostTime[0] = INF;
    vector<int> ans(p,0);

    for(int i = 0; i<order.size(); i++){
        int ind = order[i].second.second;
        if(order[i].second.first == 0){
            int c = get<0>(items[ind]), a = get<1>(items[ind]), b = get<2>(items[ind]);
            for(int j = MAXK; j>=c; j--){
                mostTime[j] = max(mostTime[j], min(mostTime[j-c],b));
            }
        }else{
            int m = get<0>(stealPlans[ind]), k = get<1>(stealPlans[ind]), s = get<2>(stealPlans[ind]);
            if(mostTime[k] > m+s){
                ans[ind] = 1;
            }else{
                ans[ind] = 0;
            }
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    vector<int> ansS = solve();
    for(int j =0; j<ansS.size(); j++){
        if(ansS[j] == 0){
            cout<<"NIE\n";
        }else{
            cout<<"TAK\n";
        }
    }

    return 0;
}