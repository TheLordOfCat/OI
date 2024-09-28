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

    n = rand() % 10 + 1;
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

vector<ull> brute() {
    vector<ull> ans;

    ull sum = 0;
    for (int i = 0; i < w.size(); i++) {
        sum += w[i];
    }

    ull ind = 1;
    for (int i = 1; i <= n; i++) {
        ull left = ind;
        ull count = 0;

        for (int j = 0; j < w.size(); j++) {
            if (count == i) {
                break;
            }
            if (w[j] <= left) {
                left -= w[j];
                count++;
            }
        }

        if (count < i) {
            ind++;
            i--;
        } else {
            ans.PB(ind);
        }
    }

    return ans;
}

vector<ull> solve() {}

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
        vector<ull> ansB = brute();
        vector<ull> ansS = solve();
        for (int i = 0; i < ansB.size(); i++) {
            if (ansB[i] != ansS[i]) {
                cout << "ERROR\n";
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
                return 0;
            }
        }
        cout << "CORRECT\n";
    }

    return 0;
}
