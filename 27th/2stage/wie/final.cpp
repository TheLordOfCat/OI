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
    tallCol = MP(a, b);
    shortCol = MP(c, d);
}

ll solvePush(vector<PLL> c){
    ll ans = shortCol.first + tallCol.first + 1;

    //catapilar method
    vector<ll> gaps;
    for(int i =0; i<c.size()-1; i++){
        ll len = c[i+1].first - (c[i].first+c[i].second);
        gaps.PB(len);
    }

    int beg = 0, end = 0;
    queue<PLL> Q;
    queue<bool> E;
    ll den = 0;
    ll excessive = 0;
    ll shortCount = shortCol.first, tallCount = tallCol.first;
    while(end != c.size()-1){
        ll len = gaps[end];

        if(len < 0){
            end++;
            ll b = end-beg+1 + shortCol.first + tallCol.first;
            ans = max(ans, b);
            continue;
        }

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
            PLL g;
            if(shortCount == 0){
                tallCount -= 1;
                g = MP(t+1, 0);
                E.push(true);
                excessive++;
            }else{
                shortCount -= div;
                g = MP(t, div);
                E.push(false);
            }
            Q.push(g);
            end++;
        }else{ // remove gap
            if(Q.size() != 0){
                PLL v = Q.front();
                Q.pop();

                bool b = E.front();
                E.pop();
                
                if(b){
                    if(den > 0){
                        v.first--;
                        v.second++;
                        den--;
                    }
                    excessive--;
                }

                beg++;
                shortCount += v.first;
                tallCount += v.second;

                while(den != excessive){
                    shortCount--;
                    den++;
                    tallCount++;
                }
            }else{
                beg++;
                end++;
            }
        }

        ll b = end-beg+1 + shortCol.first + tallCol.first;
        ans = max(ans, b);
    }

    return ans;
}

ll solve() {
    ll ans = shortCol.first + tallCol.first + 1;

    ll temp = solvePush(col);
    ans = max(ans, temp);

    vector<PLL> colCopy = col;
    ll last = colCopy.back().first; 
    for(int i = colCopy.size()-1; i>=0; i--){
        colCopy[i].first = last - colCopy[i].first;
    }

    reverse(colCopy.begin(), colCopy.end());

    temp = solvePush(colCopy);
    ans = max(ans, temp);
    
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