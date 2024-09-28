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
    ull minHeight = 99;
    ull offset = 97;

    while ((((ull)1) << j) <= K) {
        int type = 0;

        // numer 1
        if ((((ull)1) << j) & K) {
            type++;
        }

        // numer 2
        if ((((ull)1) << (j+1)) & K) {
            type += 2;
        }

        // mark the connections
        if (type == 1) {
            for (int o = offset; o >= 0; o--) {
                if(plane[minHeight][o] == 0) break;
                plane[minHeight][o] = 0;
            }
        } else if (type == 2) {
            for (int o = offset; o >= 0; o--) {
                if(plane[minHeight-1][o] == 0) break;
                plane[minHeight - 1][o] = 0;
            }
        } else if (type == 3) {
            plane[minHeight][offset] = 0;
            for (int o = offset; o >= 0; o--) {
                if(plane[minHeight - 1][o] == 0) break;
                plane[minHeight - 1][o] = 0;
            }
        }

        minHeight -= 3;
        offset -= 1;
        j += 2;
    }
    // cout<<"\n\n\n";
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

    getData();
    vector<vector<int>> ansS = solve();

    cout << ansS.size() << "\n";
    for (int i = 0; i < ansS.size(); i++) {
        for (int j = 0; j < ansS[i].size(); j++) {
            if (ansS[i][j] == 1) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << "\n";
    }

    return 0;
}
