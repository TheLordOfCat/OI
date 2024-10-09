#include <iostream>
#include <vector>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

ull n, k, c;

void getData(){
    cin>>n>>k>>c;
}

vector<ull> factorization(ull x){
    vector<ull> ans;
    
    ull f = x;
    if(f%2 == 0){
            ans.PB(2);
            while(f%2 == 0){
                f /= 2;
            }
        }

    for(ull i = 3; i*i<=x; i+=2){
        if(f%i == 0){
            ans.PB(i);
            while(f%i == 0){
                f /= i;
            }
        }
    }

    if (f > 1) {
        ans.push_back(f);
    }

    return ans;
}

ull setInEx(ull x, vector<ull>& primes){
    ull ans = x;

    ull comb = 1<<primes.size();
    
    for(int i = 1; i<comb; i++){
        ull count = 0;
        ull multi = 1;
        for(int j = 0; j<primes.size(); j++){
            if((1<<j) & i){
                count++;
                multi *= primes[j];
            }
        }
        multi = x/multi;

        if(count%2 == 0){
            ans += multi;
        }else{
            ans -= multi;
        }
    }

    return ans;
}

ull binarySearch(vector<ull>& primes){
    ull left = 1, right = 10*n;
    while(left < right){
        ull mid = (left+right)/2;
        ull coprimes = setInEx(mid, primes);

        if(coprimes == k){
            return mid;
        }else if(coprimes > k){
            right = mid-1;
        }else{
            left = mid+1;
        }
    }

    return 0;
}

vector<ull> solve(){
    vector<ull> primes = factorization(n);

    ull ind = binarySearch(primes);

    vector<ull> ans;

    ull count = 0;
    while(count != c){
        bool ok = true;
        for(int i = 0; i<primes.size(); i++){
            if(ind % primes[i] == 0){
                ok = false;
                break;
            }
        }

        if(ok){
            count++;
            ans.PB(ind);
        }
        ind++;
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    vector<ull> ansS = solve();

    for(int j = 0; j<ansS.size(); j++){
        cout<<ansS[j]<<" ";
    }

    return 0;
}