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

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
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