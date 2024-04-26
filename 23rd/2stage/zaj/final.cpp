#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define PB push_back

int n, m;
vector<int> A, B;

void getData() {
    cin >> n >> m;
    A.push_back(-1);
    B.push_back(-1);
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

int solve() {
    // creating prevA, prevB
    int maxNum = 0;
    for(int i = 0; i<n; i++) maxNum = max(maxNum, A[i]);
    for(int i = 0; i<m; i++) maxNum = max(maxNum, B[i]);
    vector<int> prevA(n+1, -1), prevB(m+1, -1);

    vector<int> last(maxNum+1, -1);
    for(int i = n; i>0; i--){
        prevA[i] = last[A[i]];
        last[A[i]] = i;
    }

    last.clear();
    for(int i = 0; i<maxNum+1; i++) last.PB(-1);

    for(int i = m; i>0; i--){
        prevB[i] = last[B[i]];
        last[B[i]] = i;
    }

    // filling WNP
    vector<int> NWP[2] = {vector<int>(m+1, 0), vector<int>(m+1, 0)};

    vector<int> mem(m+1, 0); //holding the NWP for the last val
    for(int j = 0; j<=m; j++){
        NWP[0][j] = 0;
    }
    for(int i = 1; i<=n; i++){
        NWP[i%2][0] = 0;
        for(int j = 1;j<=m; j++){
            if(A[i] == B[j] && prevA[i] > 0 && prevB[j] > 0){
                NWP[i%2][j] = mem[prevB[j]] + 2;
            }else{
                NWP[i%2][j] = 0;
            }
            NWP[i%2][j] = max(NWP[i%2][j], max(NWP[i%2][j-1], NWP[(i-1)%2][j]));
        }
        for(int j = 1; j<=m; j++){
            if(A[i] == B[j]){
                mem[j] = NWP[(i-1)%2][j-1]; 
            }
        }
    }

    int ans = NWP[n%2].back();
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();
    int ansS = solve();
    cout << ansS << "\n";

    return 0;
}