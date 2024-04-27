#include <iostream>
#include <map>
#include <vector>

#include <cstdlib>
#include <ctime>

#define MP make_pair
#define PII pair<int, int>
#define PB push_back

using namespace std;
using ll = long long int;
using ull = unsigned long long int;

const ull ullINF = 18'000'000'000'000'000;
const int INF = 2'000'000'000;

ull n, m, k;
vector<pair<ull, ull>> blocks;
ull startX = m;
ull startY = 0;

ull gcd(ull a, ull b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

void getData() {
    cin >> m >> n >> k;
    for (int i = 0; i < k; i++) {
        ull a, b;
        cin >> a >> b;
        blocks.PB(MP(a, b));
    }
}

void getRandom() {
    n = rand() % 10 + 1;
    m = rand() % 10 + 1;
    ull g = gcd(n, m);
    if (g != 1) {
        n /= g;
        m /= g;
    }
    k = rand() % (n * m);
    vector<vector<bool>> vis(m + 1, vector<bool> (n + 1, false));
    for (int i = 0; i < k; i++) {
        ull a = rand() % n + 1;
        ull b = rand() % m + 1;
        if (!vis[a][b]) {
            blocks.PB(MP(a, b));
            vis[a][b] = true;
        } else {
            k--;
        }
    }
}

void printData() {
    cout << n << " " << m << " " << k << "\n";
    for (int i = 0; i < k; i++) {
        cout << blocks[i].first << " " << blocks[i].second << "\n";
    }
}

pair<bool, bool> isWall(ull x, ull y) {
    // second value idicates the which wall is conntact made with
    if (x == 0 || x == m) {
        return MP(true, true);
    }
    if (y == 0 || y == n) {
        return MP(true, false);
    }
    return MP(false, false); // second value not used
}

pair<ull, ull> middle(ull x, ull y, pair<int, int> d) {
    if (x % 2 == 0) {
        if (d.first == 1) {
            return MP(x + 1, y);
        } else {
            return MP(x - 1, y);
        }
    } else {
        if (d.second == 1) {
            return MP(x, y + 1);
        } else {
            return MP(x, y - 1);
        }
    }
    return MP(INF, INF);
}

pair<int, int> reflect(pair<int, int> d, bool side) {
    if (side) { // changing only x
        d.first *= -1;
    } else { // changing only y
        d.second *= -1;
    }
    return d;
}

ull brute() {
    ull ans = 0;
    ull K = k;
    ull curX = startX;
    ull curY = startY;
    pair<int, int> dir = MP(-1, 1);
    vector<bool> vis(k + 1, false);

    while (K > 0) {
        pair<bool, bool> wall = isWall(curX, curY);
        if (wall.first) {
            reflect(dir, wall.second);
        } else {
            pair<ull, ull> mid = middle(curX, curY, dir);
            for (int i = 0; i < k; i++) {
                if (blocks[i].first == mid.first && blocks[i].second == mid.second && !vis[i]) {
                    if (mid.first != curX) {
                        reflect(dir, true);
                    } else if (mid.second != curY) {
                        reflect(dir, false);
                    }
                    vis[i] = true;
                }
            }
        }
        curX += dir.first;
        curY += dir.second;
        ans++;
    }

    return ans;
}

ull solve() {

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
        // scaling up by 2 to have no fractions
        n *= 2;
        m *= 2;
        for (int i = 0; i < k; i++) {
        blocks[i].first *= 2;
        blocks[i].second *= 2;
        }

        ull ansB = brute();
        ull ansS = solve();
        if (ansB != ansS) {
        cout << "ERROR\n";
        cout << "BRUTE: " << ansB << "\n";
        cout << "SOLVE: " << ansS << "\n";
        printData();
        return 0;
        }
        cout << "CORRECT\n";
    }

    return 0;
}