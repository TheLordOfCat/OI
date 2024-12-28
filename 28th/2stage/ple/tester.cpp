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

#define PII pair<int, int>
#define MP make_pair
#define PB push_back

int n;
vector<ull> w;

void getData() {
    w.clear();

    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp;
        cin >> temp;
        w.PB(temp);
    }
}

void getRandom() {
    w.clear();

    srand(time(0));
    
    // n = rand() % 10 + 1;
    n = 8;
    for (int i = 0; i < n; i++) {
        ull temp = rand() % 20 + 1;
        w.PB(temp);
    }
}

void printData() {
    cout << "DATA: \n";
    cout << n << "\n";
    for (int i = 0; i < w.size(); i++) {
        cout << w[i] << " ";
    }
    cout << "\n";
}

vector<vector<ll>> bruteUsed;

vector<ll> brute() {
    vector<ll> ans;
    vector<vector<ll>> used;

    ll sumTotal = 0;
    for(int i =0; i<w.size(); i++){
        sumTotal += w[i];
    }

    int lastCount = 0;
    for(ll i = 1; i<= sumTotal; i++){
        //simulate
        int count = 0;
        ll sum = i;
        vector<ll> temp;
        for(int j = 0; j< w.size(); j++){
            if(w[j] <= sum){
                count++;
                sum -= w[j];
                temp.PB(j);
            }
        }
        if(count > lastCount){
            ans.PB(i);
            bruteUsed.PB(temp);
            lastCount = count;
        }
    }

    return ans;
}

vector<ll> solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for (int test = 1; test <= 10; test++) {
        cout << "TEST nr." << test << " = ";
        if (op == 1) {
            getData();
        } else {
            getRandom();
        }
        vector<ll> ansB = brute();
        vector<ll> ansS = solve();
        for (int i = 0; i < ansB.size(); i++) {
            if (ansB[i] != ansS[i]) {
                cout << "ERROR\n";
                printData();
                cout << "BRUTE: \n";
                for (int j = 0; j < ansB.size(); j++) {
                    cout << ansB[j] << " ";
                }
                cout << "\n";
                cout << "SOLVE: \n";
                for (int j = 0; j < ansS.size(); j++) {
                    cout << ansS[j] << " ";
                }
                cout << "\n";
                cout<<i<<" - ";
                for(int j = 0; j<bruteUsed[i].size(); j++){
                    cout<<bruteUsed[i][j]<<" ";
                }
                cout<<"\n";
                return 0;
            }
        }
        cout << "CORRECT\n";
    }

    return 0;
}
