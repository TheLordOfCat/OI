#include <iostream>
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

ull K;

void getData() { 
    cin >> K; 
}

void getRandom() {
    srand(time(0));

    K = rand() % 20 + 1;
}

void printData() { 
    cout << "DATA: \n" << K << "\n"; 
}

bool verify(vector<vector<int>> &plane) {
    vector<vector<ull>> dp(plane.size(), vector<ull>(plane.size(), 0));

    for (int i = 0; i < plane.size(); i++) {
        for (int j = 0; j < plane[i].size(); j++) {
            if (plane[i][j] == 1) {
                ull sum = 0;
                if (i > 0) {
                    sum += dp[i - 1][j];
                }
                if (j > 0) {
                    sum += dp[i][j - 1];
                }
                dp[i][j] = sum;
            }
        }
    }
    if (dp[plane.size() - 1][plane.size() - 1] == K) {
        return true;
    } else {
        return false;
    }
}

vector<vector<int>> solve() {
    vector<vector<int>> plane(100, vector<int>(100, 1));

    PII ind = MP(plane.size() - 1, plane.size() - 1);

    // getting the defult patches
    while (ind.second != 0) {
        // cover one block
        for (int i = ind.second; i >= ind.second - 3; i--) {
            for (int j = ind.first; j >= ind.first - 1; j--) {
                plane[i][j] = 0;
            }
        }
        ind = MP(ind.first - 1, ind.second - 3);
    }

    // marking the first column
    for (int i = 0; i < 100; i++) {
        plane[i][0] = 0;
    }

    // for(int i = 0; i<plane.size(); i++){
    //     for(int  j =0; j<plane[i].size(); j++){
    //         cout<<plane[i][j];
    //     }
    //     cout<<"\n";
    // }
    ull j = 0;

    while ((1 << j) < K) {
        int type = 0;

        // numer 1
        if ((1 << j) & K) {
            type++;
        }

        // numer 2
        if ((1 << (j + 1)) & K) {
            type &= (1 << (j + 1));
        }

        j += 2;

        // mark the connections
        ull minHeight = 0;
        ull offset = 99;

        for (int i = 0; i < j; i++) {
            minHeight += 3;
            offset -= 1;
        }

        if (type == 1) {
            for (int j = offset; j >= 0; j--) {
                plane[minHeight][j] = '0';
            }
        } else if (type == 2) {
            for (int j = offset; j >= 0; j--) {
                plane[minHeight + 1][j] = '0';
            }
        } else if (type == 3) {
            plane[minHeight][offset - 1] = '0';
            for (int j = offset; j >= 0; j--) {
                plane[minHeight + 1][j] = '0';
            }
        }
    }
    // for(int i = 0; i<plane.size(); i++){
    //     for(int  j =0; j<plane[i].size(); j++){
    //         cout<<plane[i][j];
    //     }
    //     cout<<"\n";
    // }

    return plane;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for (int test = 1; test <= 1; test++) {
        if (op == 1) {
            getData();
        } else {
            getRandom();
        }
        vector<vector<int>> ansS = solve();
        if (verify(ansS)) {
            cout << "ERROR\n";
            cout << "SOLVE: ";
            cout << ansS.size() << "\n";
            for (int i = 0; i < ansS.size(); i++) {
                for (int j = 0; j < ansS[i].size(); j++) {
                    if (ansS[i][j] == 0) {
                        cout << "#";
                    } else {
                        cout << ".";
                    }
                }
                cout << "\n";
            }
        }
    }

    return 0;
}
