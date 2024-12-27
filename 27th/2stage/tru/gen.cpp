#include <iostream>
#include <stack>
#include <tuple>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int, int>
#define PB push_back
#define MT make_tuple
#define PLL pair<ll,ll>

ll n;

const ll MAXN = 1'000'000'000'000'000'0;

void getData() { 
    cin >> n; 
}

ll gcd(ll a, ll b){
    if(b == 0){
        return a;
    }
    return gcd(b, a%b);
}

ll numDivisors(ll num){
    ll ans = 0;
    for(ll i = 1; i*i <=num; i++){
        if(num%i == 0){
            ans+=2;
            if(i == num/i){
                ans--;
            }
        }
    }

    return ans;
}

vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};

void genCand(ll pInd, ll limit, ll v, ll div, vector<PLL>& cand){
    cand.PB(MP(v, div));

    for(int i = 1; i<=limit; i++){
        if(primes[pInd] > MAXN/v){
            return;
        }
        v *= primes[pInd];
        genCand(pInd+1, i, v, div*(i+1), cand);
    }
}

ll findLog(){
    ll ans =0;
    ll num = 1;
    while(n > num){
        num *= 2;
        ans++;
    }
}

bool customComparePLL(PLL a, PLL b){
    if(a.first == b.first){
        return a.second > b.second;
    }
    return a.first < b.first;
}

void genCandP(ll pInd, ll limit, ll base, ll v, ll div, vector<ll> b, vector<pair<PLL, vector<ll>>>& cand, bool type){
    if(div >= base && !type){
        cand.PB(MP(MP(v, div),b));
    }

    ll p = 0;
    if(pInd >= primes.size()){
        return;
    }
    genCandP(pInd+1, limit, base, v, div, b, cand, true);
    while(v*primes[pInd] < limit){
        if(primes[pInd] > MAXN/v){
            return;
        }
        v *= primes[pInd];
        p++;
        vector<ll> bCopy = b;
        bCopy[pInd] = (p+1);
        genCandP(pInd+1, limit, base, v, div*(p+1), bCopy, cand, false);
    }
}

tuple<ll,ll,ll> getRange(ll antiP, ll divP, ll nextAntiP){
    vector<pair<PLL, vector<ll>>> pCand;
    vector<ll> power(primes.size(), 0);
    genCandP(0, nextAntiP, divP/2, 1, 1, power, pCand, false);

    tuple<ll, ll, ll> ans = MT(0, 0, 0);
    for(int i = 0; i<pCand.size(); i++){
        for(int j = i+1; j<pCand.size(); j++){
            ll div1 = pCand[i].first.second;
            ll div2 = pCand[j].first.second;
            // ll g = numDivisors(gcd(pCand[i].first.first, pCand[j].first.first));
            ll g = 1;
            for(int o = 0; o<primes.size(); o++){
                g *= min(pCand[i].second[o], pCand[j].second[o]);
            }

            ll temp = div1 + div2 - g;
            if( temp > get<0>(ans)){
                ans = MT(temp, max(pCand[i].first.first, pCand[j].first.first), min(pCand[i].first.first, pCand[j].first.first));
            }else if(temp == get<0>(ans)){
                if(max(pCand[i].first.first, pCand[j].first.first) > get<1>(ans)){
                    ans = MT(temp, max(pCand[i].first.first, pCand[j].first.first), min(pCand[i].first.first, pCand[j].first.first));
                }
            }
        }
    }
    return ans;
}

tuple<ll, ll, ll> solve() {
    if(n<=48){ // to litlle to be anitPimred 
        tuple<ll, ll, ll> ans = MT(0, 0, 0);
        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                ll div1 = numDivisors(i);
                ll div2 = numDivisors(j);
                ll g = numDivisors(gcd(i,j));

                ll temp = div1 + div2 - g;
                if( temp > get<0>(ans)){
                    ans = MT(temp, i,j);
                }
            }
        }
        return ans;
    }

    //get antiPrimes
    vector<PLL> antiPrimes;
    vector<PLL> antiCand;
    ll l = findLog();
    genCand(0, MAXN, 1, 1, antiCand);

    sort(antiCand.begin(), antiCand.end(), customComparePLL);

    PLL best = antiCand.front();
    for(int i = 1; i<antiCand.size(); i++){
        if(antiCand[i].second > best.second){
            antiPrimes.PB(best);
            best = antiCand[i];
        }
    }

    // for(int i = 0; i<antiPrimes.size(); i++){
    //     cout<<antiPrimes[i].first<<"\n";
    // }

    //get range
    vector<tuple<ll, ll, ll>> range;

    ll last = MAXN;
    // ll last = antiPrimes[11].first;
    ll antiInd = antiPrimes.size()-1;
    // ll antiInd = 10;
    while(antiInd >= 0){
        tuple<ll,ll,ll> temp = getRange(antiPrimes[antiInd].first, antiPrimes[antiInd].second, last);
        range.PB(temp);
        cout<<"range.PB(MT("<<get<0>(temp)<<", "<<get<1>(temp)<<", "<<get<2>(temp)<<"));\n";
        last = get<1>(temp);
        if(last < antiPrimes[antiInd].first){
            antiInd--;
        }
    }

    //get ans;
    tuple<ll,ll,ll> ans;
    for(int i =0; i<range.size(); i++){
        if(i == range.size()-1){
            ans = range[i];
            break;
        }else if(get<1>(range[i+1]) > n){
            ans = range[i];
            break;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    tuple<ll, ll, ll> ansS = solve();
    cout << get<0>(ansS) << "\n";
    cout << get<1>(ansS) << " " << get<2>(ansS) << "\n";

    return 0;
}