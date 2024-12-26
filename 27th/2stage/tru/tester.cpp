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

ll n;

const ll MAXN = 1'000'000'000'000'000'0;

void getData() { 
    cin >> n; 
}

void getRandom() { 
    n = rand() % 20 + 1;
}

void printData() { 
    cout << "DATA: \n" << n << "\n"; 
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

tuple<ll, ll, ll> brute() {
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

vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

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
    vector<tuple<ll, ll, ll>> range;


}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for (int test = 1; test <= 1; test++) {
        cout << "TEST nr." << test << " = ";
        if (op == 1) {
            getData();
        } else {
            getRandom();
        }

        tuple<ll, ll, ll> ansB = brute();
        tuple<ll, ll, ll> ansS = solve();
        if (get<0>(ansB) != get<0>(ansS)) {
            cout << "ERROR\n";
            cout << "BRUTE: \n";
            cout << get<0>(ansB) << "\n";
            cout << get<1>(ansB) << " " << get<1>(ansB) << "\n";
            cout << "SOLVE: \n";
            cout << get<0>(ansS) << "\n";
            cout << get<1>(ansS) << " " << get<1>(ansS) << "\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}