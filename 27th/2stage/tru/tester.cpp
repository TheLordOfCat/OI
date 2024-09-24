#include <iostream>
#include <vector>
#include <tuple>
#include <stack>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n;

const ull MAXN = 1'000'000'000'000'000'0;

void getData(){
    cin>>n;
}

void getRandom(){
    n = rand()%20+1;
}

void printData(){
    cout<<"DATA: \n"<<n<<"\n";
}

ull gcd(ull a, ull b){
    while(b){
        a %= b;
        swap(a,b);
    }
    return a;
}

ull numberDivsors(ull v){
    ull ans = 0;

    for(ull i = 1; i*i<=v; i++){
        if(v %i == 0){
            ans += 2;
            if(i*i == v){
                ans--;        
            }
        }
    }

    return ans;
}

tuple<ull,ull,ull> brute(){
    tuple<ull,ull,ull> ans = MT(0,0,0);

    for(ull i = 1; i <= n; i++){
        for(ull j = i; j >= 1; j--){
            ull divA = numberDivsors(i);
            ull divB = numberDivsors(j);
            ull g = gcd(i,j);
            ull divG = numberDivsors(g);

            ull temp = divA+divB-divG;
            
            if(get<0>(ans) < temp){
                ans = MT(temp, i, j);
            }
        }
    }

    return ans;
}

vector<ull> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41};

void genAntiPrime(ll a, ll j, ll cand, ll div, ull& border, ull& antiPrime, ull& antiPrimeDiv){
    if(a>primes.size()) return;
    if(div > antiPrimeDiv){
        antiPrime = cand;
        antiPrimeDiv = div;
    }else if(cand > antiPrime){
        antiPrime = cand;
    }
    for(int i = 1; i<=j; i++){
        if(primes[a]*cand > border) return;
        cand *= primes[a];
        genAntiPrime(a+1, i, cand, div*(i+1), border, antiPrime, antiPrimeDiv);
    }
}

void genCandRec(ll a, ll j, ll cand, ll div, ull& border, vector<ull>& candidates){
    if(a>primes.size()) return;
    
    //predict number of divisors

    for(int i = 1; i<=j; i++){
        if(primes[a]*cand > border){
            candidates.PB(cand);
            return;
        }
        cand *= primes[a];
        genCandRec(a+1, i, cand, div*(i+1), border, candidates);
    }
}

void genCandidates(ull v, vector<ull>& candidates){
    if(v <= 100){
        for(int i = 1; i<v; i++){
            candidates.PB(i);
        }
    }else{
        //anit prime numbers
        ull antiPrime = 0;
        ull antiPrimeDiv = 0;

        genAntiPrime(0, 54, 1, 1, v, antiPrime, antiPrimeDiv);

        //generate candidates
        genCandRec(0, 54, 1, 1, v, candidates);
    }
}

vector<tuple<ull,ull,ull>> getRange(){
    vector<tuple<ull,ull,ull>> ans;

    ull v = MAXN;
    while(v >= 1){
        vector<ull> candidates;
        genCandidates(v, candidates);

        tuple<ull,ull,ull> best = MT(0,0,0);

        for(ull i = 0; i < candidates.size(); i++){
            for(ull j = i; j >= 0; j--){
                ull divA = numberDivsors(candidates[i]);
                ull divB = numberDivsors(candidates[j]);
                ull g = gcd(candidates[i],candidates[j]);
                ull divG = numberDivsors(g);

                ull temp = divA+divB-divG;
                
                if(get<0>(best) < temp){
                    best = MT(candidates[i], candidates[j], temp);
                }
            }
        }

        ans.PB(best);
        v = max(get<0>(best), get<1>(best))-1;
    }

    return ans;
}

tuple<ull,ull,ull> solve(){
    vector<tuple<ull,ull,ull>> range;    
    if(range.size() == 0){
        //generate 
        range = getRange();

        for(int i = 0; i<range.size(); i++){
            cout<<get<0>(range[i])<<" "<<get<1>(range[i])<<" "<<get<2>(range[i])<<"\n";
        }
    }

    for(int i = 0; i< range.size()-1; i++){
        if(max(get<0>(range[i+1]), get<1>(range[i+1])) > n){
            return MT(get<2>(range[i+1]), get<0>(range[i+1]), get<1>(range[i+1]));
        }
    }
    return MT(get<2>(range.back()), get<0>(range.back()), get<1>(range.back()));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        tuple<ull,ull,ull> ansB = brute();
        tuple<ull,ull,ull> ansS = solve();
        if(get<0>(ansB) != get<0>(ansS)){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<get<0>(ansB)<<"\n";
            cout<<get<1>(ansB)<<" "<<get<1>(ansB)<<"\n";
            cout<<"SOLVE: \n";
            cout<<get<0>(ansS)<<"\n";
            cout<<get<1>(ansS)<<" "<<get<1>(ansS)<<"\n";
            printData();
            return 0;
        }
    }

    return 0;
}