#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <map>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

int n, m, k;
vector<PII> blocks;
int startX, startY;

void getData(){
    cin>>n>>m>>k;
    for(int i = 0; i<k ;i++){
        int a, b;
        cin>>a>>b;
        blocks.PB(MP(a,b));
    }
    startX = n;
    startY = 0;
}

ull solve(){
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();   
    //scaling the grid
    for(int i = 0; i<k; i++){
        blocks[i].first *= 2;
        blocks[i].second *= 2;
    }
    n *= 2;
    m *= 2;

    ull ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}