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

void getRandom(){
    a.clear();
    
    srand(time(0));

    n = rand()%10+1;
    for(int i = 0; i<n; i++){
        int temp = rand()%10+1;
        a.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<a[i]<<" ";
    }
}

int brute(){
    vector<int> aPrem = a;

    sort(aPrem.begin(), aPrem.end());

    int ans = 0;

    do{
        int workTime = 0;
        //simulate
        int curA = 0, curB = 0;
        int ind =0;
        while(ind <n){
            if(curA > 0 || curB>0){
                workTime++;
                curA--;
                curB--;
            }
            if(curA <= 0){
                curA = aPrem[ind];
                ind++;
            }
            if(curB <= 0 && ind<n){
                curB = aPrem[ind];
                ind++;
            }
        }

        workTime += max(curA, curB);
        
        ans = max(workTime, ans);
    }while(next_permutation(aPrem.begin(), aPrem.end()));

    return ans;
}

int solve(){
    //get the larges
    int sum = 0;
    int maxValue = -1;
    for(int i = 0; i<a.size(); i++){
        maxValue = max(maxValue, a[i]);
        sum += a[i];
    }
    sum -= maxValue;

    //group numbers
    vector<int> group(5'000'000+1, 0);
    for(int i = 0; i<a.size(); i++){
        group[a[i]]++;
    }
    group[maxValue]--;

    //reduce
    for(int i = 1; i<group.size(); i++){
        while(group[i] > 2){
            group[i] -= 2;
            group[i+i]++;
        }
    }

    //process knapsack
    bitset<2500001> knapsack;
    bool first = true;

    for(int i = 1; i<=group.size(); i++){
        // cout<<i<<"\n";
        if(group[i] > 0){
            if(first){
                knapsack.set(i);
                first = false;
            }else{
                bitset<2500001> temp = knapsack;
                temp = temp <<i;
                temp.set(i);
                auto next = knapsack|temp;
                knapsack = next;
            }
        }
        if(group[i] == 2){
            bitset<2500001> temp = knapsack;
            temp = temp <<i;
            temp.set(2*i);
            auto next = knapsack|temp;
            knapsack = next;
        }
    }

    int ans = 0;
    for(int i = sum/2; i>= 1; i--){
        if(knapsack.test(i)){
            ans = i;
            break;
        }
    }

    ans += maxValue;

    return ans;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 0;
    for(int test = 1; test<=100'000; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        int ansB = brute();
        int ansS = solve();
        if(ansB != ansS){
            cout<<"ERROR\n";
            cout<<"BRUTE: "<<ansB<<"\n";
            cout<<"SOLVE: "<<ansS<<"\n";
            printData();
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}