#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int, int>
#define PULLI pair<ull,int>
#define PLL pair<ll,ll>
#define MP make_pair
#define PB push_back

int n;
vector<PLL> col;
PLL shortCol, tallCol;

void getData() {
    col.clear();

    cin >> n;
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        col.PB(MP(a, b));
    }
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    shortCol = MP(a, b);
    tallCol = MP(c, d);
}

ll solve() {
    ll ans = shortCol.first + tallCol.first;

    //catapilar method
    vector<ll> gaps;
    for(int i =0; i<col.size()-1; i++){
        ll len = col[i+1].first - (col[i].first+col[i].second);
        gaps.PB(len);
    }

    int beg = 0, end = 0;
    queue<PLL> Q;
    ll shortCount = shortCol.first, tallCount = tallCol.first;
    while(end != col.size()-1){
        ll len = gaps[end];

        ll div = len/shortCol.second;
        ll r = len - div*shortCol.second;
        if(r != 0){
            div++;
        }

        if(div <= shortCount + tallCount){ //add gap
            ll t = div/2;
            if(t > tallCount){
                t = tallCount;
            }
            tallCount -= t;
            div -= t*2;
            shortCount -= div;
            PLL g = MP(t, div);
            Q.push(g);
        }else{ // remove gap
            if(Q.size() == 0){
                PLL v = Q.front();
                Q.pop();

                beg++;
                shortCount += v.first;
                tallCount += v.second;
            }
        }

        ans = max(ans, end-beg + shortCol.first + tallCol.first);
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    ll ansS = solve();
    cout <<ansS << "\n";

    return 0;
}