#include <iostream>
#include <vector>

using namespace std;

#define PB push_back

int n, m;
vector<int> A, B;

void getData() {
cin >> n >> m;
for (int i = 0; i < n; i++) {
int temp;
cin >> temp;    
A.PB(temp);
}
for (int i = 0; i < m; i++) {
int temp;
cin >> temp;
B.PB(temp);
}
}

void getRandom() {
srand(time(0));
n = rand() % 10 + 1;
m = rand() % 15 + 1;
for (int i = 0; i < n; i++) {
int temp = rand() % 10 + 1;
A.PB(temp);
}
for (int i = 0; i < m; i++) {
int temp = rand() % 10 + 1;
B.PB(temp);
}
}

void printData() {
cout << n << " " << m << "\n";
for (int i = 0; i < n; i++) {
cout << A[i] << " ";
}
cout << "\n";
for (int i = 0; i < m; i++) {
cout << B[i] << " ";
}
cout << "\n";
}

int brute() {
int ans = 0;
for(int i = 0; i<n; i++){
for(int j = 0; j<m;j ++){

}
}
return ans;
}

int solve() {}

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
    return 0;
    }
    cout << "CORRECT\n";
    }
    return 0;
}