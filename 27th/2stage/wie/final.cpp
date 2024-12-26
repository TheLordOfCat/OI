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

bool customE(PII a, PII b){
    if(a.second == b.second){
        return a.first < b.first;
    }
    return a.second < b.second;
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
    vector<PLL> gapsUse(c.size()+1, MP(0,0));
    vector<bool> used(n+1, false);
    priority_queue<PII> E;
    queue<int> Q;
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

        ll multi = tallCol.second/shortCol.second;
        if(div <= shortCount + tallCount*multi){ //add gap
            ll t = div/multi;
            if(t > tallCount){
                t = tallCount;
            }
            tallCount -= t;
            div -= multi*t;

            gapsUse[end].second = t;
            if(div > 0){
                if(shortCount > div){
                    shortCount -= div;
                    gapsUse[end].first = div;
                }else{ //excessive tall
                    tallCount--;
                    gapsUse[end] = MP(0, t+1);
                    E.push(MP(end, div));
                }
            }
            Q.push(end);
            end++;
        }else{ // remove gap
            if(Q.size() != 0){
                int v = Q.front();
                PLL p = gapsUse[v];
                used[v] = true;
                Q.pop();

                shortCount += p.first;
                tallCount += p.second;

                if(!E.empty()){
                    PII e = E.top();
                    E.pop();

                    if(shortCount >= e.second){
                        shortCount -= e.second;
                        gapsUse[e.first].first--;
                        gapsUse[e.first].second += e.second;
                    }

                    E.push(e);
                }

                beg++;
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