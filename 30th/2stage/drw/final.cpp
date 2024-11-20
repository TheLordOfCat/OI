#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n;
vector<int> a;

void getData(){
    a.clear();

    cin>>n;
    for(int i =0 ; i<n; i++){
        int temp;
        cin>>temp;
        a.PB(temp);
    }
}   

int solve(){
    //get the larges
    int maxValue = -1;
    for(int i = 0; i<a.size(); i++){
        maxValue = max(maxValue, a[i]);
    }

    //group numbers
    vector<int> group(2*maxValue+1, 0);
    for(int i = 0; i<a.size(); i++){
        group[a[i]]++;
    }
    group[maxValue]--;

    //reduce
    for(int i = 1; i<group.size(); i++){
        if(group[i] > 2){
            group[i] -= 2;
            group[i+i]++;
        }
    }

    //process knapsack
    bitset<2500000> knapsack;

    for(int i = 1; i<group.size(); i++){
        if(group[i] > 0){
            bitset<2500000> temp = knapsack;
            temp <<i;
            auto next = knapsack|temp;
            knapsack = next;
        }
        if(group[i] == 2){
            bitset<2500000> temp = knapsack;
            temp <<i;
            temp <<i;
            auto next = knapsack|temp;
            knapsack = next;
        }
    }

    int ans = -1;
    for(int i = 2500000; i>= 1; i--){
        if(knapsack.test(i)){
            ans = i;
            break;
        }
    }

    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    getData();

    int ansS = solve();
    cout<<ansS<<"\n";

    return 0;
}