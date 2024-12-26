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
            if(i == n/i){
                ans--;
            }
        }
    }

    return ans;
}

vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

void genCand(ll pInd, ll limit, ll v, ll div, vector<PLL>& cand){
    cand.PB(MP(v, div));

    for(int i = 1; i<limit; i++){
        if(primes[pInd] > n/v){
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

tuple<ll, ll, ll> solve() {
    if(n<=48){
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
    vector<ll> antiPrimes;
    vector<PLL> antiCand;
    ll l = findLog();
    genCand(0, l, 1, 1, antiCand);

    sort(antiCand.begin(), antiCand.end(), customComparePLL);

    PLL best = antiCand.front();
    for(int i = 1; i<antiCand.size(); i++){
        if(antiCand[i].second > best.second){
            antiPrimes.PB(best.first);
            best = antiCand[i];
        }
    }

    //get range
    vector<tuple<ll, ll, ll>> range;




    //get ans;
    tuple<ll,ll,ll> ans;
    for(int i =0; i<range.size(); i++){
        if(i == range.size()-1){
            ans = range[i];
            break;
        }else if(get<0>(range[i+1]) > n){
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
    cout << get<1>(ansS) << " " << get<1>(ansS) << "\n";

    return 0;
}