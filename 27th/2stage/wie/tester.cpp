#include <algorithm>
#include <iostream>
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
vector<PII> col;
PII shortCol, tallCol;

void getData() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    col.PB(MP(a, b));
  }
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  shortCol = MP(a, b);
  tallCol = MP(c, d);
}

void getRandom() {
  srand(time(0));

  n = rand() % 10 + 1;

  for (int i = 0; i < n; i++) {
    int a = rand() % n + 1, b = rand() % 3 + 2;
    col.PB(MP(a, b));
  }
  int a = rand() % n + 1, b = rand() % 5 + 3, c = rand() % n + 1,
      d = rand() % 5 + 3;
  shortCol = MP(a, b);
  tallCol = MP(c, d);
}

void printData() {
  cout << "DATA: \n";
  cout << n << "\n";
  for (int i = 0; i < col.size(); i++) {
    cout << col[i].first << " " << col[i].second << "\n";
  }
  cout << shortCol.first << " " << shortCol.second << "\n";
  cout << tallCol.first << " " << tallCol.second << "\n";
}

bool pairCompare(PII a, PII b) {
  if (a.first == b.first) {
    return a.second > b.second;
  }
  return a.first < b.first;
}

int brute() {
  int ans = 0;
  vector<int> pos;
  for (int i = 0; i < n; i++) {
    pos.PB(i);
  }

  do {
    vector<PII> domino;
    for (int i = 0; i < col.size(); i++) {
      domino.PB(col[i]);
    }
    int indAdd = 0;
    for (int i = 0; i < shortCol.first; i++) {
      domino.PB(MP(pos[indAdd] ,shortCol.second));
      indAdd++;
    }
    for (int i = 0; i < tallCol.first; i++) {
      domino.PB(MP(pos[indAdd], tallCol.second));
      indAdd++;
    }

    sort(domino.begin(), domino.end(), pairCompare);

    // left
    int ind = domino.front().first;
    int index = 0;
    int size = 1;

    while (ind < 10000 && index < domino.size() - 1) {
      if (ind + domino[index].second >= domino[index + 1].first) {
        ind = domino[index + 1].first;
        index++;
        size++;
      } else {
        ans = max(size, ans);
        size = 1;

        index++;
        ind = domino[index].first;
        index++;
      }
    }
    ans = max(size, ans);

    // right
    ind = domino.back().first;
    index = domino.size() - 1;
    size = 1;

    while (ind < 10000 && index < domino.size() - 1) {
      if (ind - domino[index].second <= domino[index + 1].first) {
        ind = domino[index + 1].first;
        index++;
        size++;
      } else {
        ans = max(size, ans);
        size = 1;

        index++;
        ind = domino[index].first;
        index++;
      }
    }
    ans = max(size, ans);

  } while(next_permutation(pos.begin(), pos.end()));

  return ans;
}

int solve() {

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
    int ansB = brute();
    int ansS = solve();
    if (ansB != ansS) {
      cout << "ERROR\n";
      cout << "BRUTE: " << ansB << "\n";
      cout << "SOLVE: " << ansS << "\n";
      printData();
      return 0;
    }
  }

  return 0;
}