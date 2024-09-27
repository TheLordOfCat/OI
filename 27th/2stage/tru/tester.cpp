#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

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

int n;

const ull MAXN = 1'000'000'000'000'000'0;

void getData() { 
    cin >> n; 
}

void getRandom() { 
    n = rand() % 20 + 1;
}

void printData() { 
    cout << "DATA: \n" << n << "\n"; 
}

ull gcd(ull a, ull b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ull numberDivsors(ull v) {
    ull ans = 0;

    for (ull i = 1; i * i <= v; i++) {
            if (v % i == 0) {
                ans += 2;
            if (i * i == v) {
                ans--;
            }
        }
    }

    return ans;
}

tuple<ull, ull, ull> brute() {
    tuple<ull, ull, ull> ans = MT(0, 0, 0);

    for (ull i = 1; i <= n; i++) {
        for (ull j = i; j >= 1; j--) {
            ull divA = numberDivsors(i);
            ull divB = numberDivsors(j);
            ull g = gcd(i, j);
            ull divG = numberDivsors(g);

            ull temp = divA + divB - divG;

            if (get<0>(ans) < temp) {
                ans = MT(temp, i, j);
            }
        }
    }

    return ans;
}

vector<ull> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

ull numberDivsorsOpti(ull v){
    ull ans = 1;
    for(ll i = 0; i<primes.size(); i++){
        ll count = 0;
        while(v%primes[i] == 0){
            count++;
            v /= primes[i];
        }
        ans *= (1+count);
    }

    return ans;
}

void genAntiPrime(ll a, ll j, ll cand, ll div, ull &border, ull &antiPrime, ull &antiPrimeDiv) {
    if (a > primes.size())
        return;
    if (div > antiPrimeDiv) {
        antiPrime = cand;
        antiPrimeDiv = div;
    } else if (cand > antiPrime) {
        antiPrime = cand;
    }
    for (int i = 1; i <= j; i++) {
        if (primes[a] * cand > border) return;
        cand *= primes[a];
        genAntiPrime(a + 1, i, cand, div * (i + 1), border, antiPrime, antiPrimeDiv);
    }
}

void genCandRec(ll primeInd, ll powerPrime, ll cand, ll div, ull t2, ull &border, vector<pair<ull,ull>> &candidates, ull &minDiv) {
    if (primeInd > primes.size()) return;

    // predict number of divisors
    ull temp = div / (t2 + 1);
    ull p = 0;
    ull num = 1 << t2;
    while (num < border) {
        t2++;
        num *= 2;
    }

    if(temp < 1<<(12)){
        temp = 1<<(12);
    }

    temp *= (p + t2 + 1);

    if (temp < minDiv) {
        return;
    }

    for (int i = 1; i <= powerPrime; i++) {
        if (primes[primeInd] * cand > border) {
            candidates.PB(MP(cand,div * i));
            return;
        }
        cand *= primes[primeInd];
        if (primeInd == 0) {
            genCandRec(primeInd + 1, i, cand, div * (i + 1), i, border, candidates, minDiv);
        } else {
            genCandRec(primeInd + 1, i, cand, div * (i + 1), t2, border, candidates, minDiv);
        }
    }
}

void genCandidates(ull v, vector<pair<ull,ull>> &candidates) {
    if (v <= 100) {
        for (int i = 1; i < v; i++) {
            ll div = numberDivsors(i);
            candidates.PB(MP(i,div));
        }
    } else {
        // anit prime numbers
        ull antiPrime = 0;
        ull antiPrimeDiv = 0;

        genAntiPrime(0, 54, 1, 1, v, antiPrime, antiPrimeDiv);

        antiPrimeDiv /= 2;

        // generate candidates
        genCandRec(0, 54, 1, 1, 0, v, candidates, antiPrimeDiv);
    }
}

vector<tuple<ull, ull, ull>> getRange() {
    vector<tuple<ull, ull, ull>> ans;

    ull v = MAXN;
    while (v >= 1) {
        vector<pair<ull,ull>> candidates;
        genCandidates(v, candidates);

        tuple<ull, ull, ull> best = MT(0, 0, 0);

        for (ll i = 0; i < candidates.size(); i++) {
            for (ll j = i; j >= 0; j--) {
                ull divA = candidates[i].second;
                ull divB = candidates[j].second;
                ull g = gcd(candidates[i].first, candidates[j].first);
                ull divG = numberDivsorsOpti(g);

                ull temp = divA + divB - divG;

                if (get<0>(best) < temp) {
                    best = MT(candidates[i].first, candidates[j].first, temp);
                }
            }
        }

        ans.PB(best);
        if(max(get<0>(best), get<1>(best)) == 0) break;
        v = max(get<0>(best), get<1>(best)) - 1;
    }

    return ans;
}

tuple<ull, ull, ull> solve() {
    vector<tuple<ull, ull, ull>> range;
    if (range.size() == 0) {
        // generate
        range = getRange();

        for (int i = 0; i < range.size(); i++) {
            cout << get<0>(range[i]) << " " << get<1>(range[i]) << " "<< get<2>(range[i]) << "\n";
        }
    }

    for (int i = 0; i < range.size() - 1; i++) {
        if (max(get<0>(range[i + 1]), get<1>(range[i + 1])) > n) {
            return MT(get<2>(range[i + 1]), get<0>(range[i + 1]), get<1>(range[i + 1]));
        }
    }
    return MT(get<2>(range.back()), get<0>(range.back()), get<1>(range.back()));
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
        tuple<ull, ull, ull> ansB = brute();
        tuple<ull, ull, ull> ansS = solve();
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
    }

    return 0;
}