#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back
#define PIV pair<int,vector<int>>

int n, s;
vector<int> a;

void getData(){
    a.clear();

    cin>>n>>s;
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
    s = rand()%10+2;
    for(int i =0 ; i<n; i++){
        int temp = rand()%20;
        a.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<s<<"\n";
    for(int i =0; i<n; i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

PIV brute(){
    PIV ans = MP(INF, vector<int>());
    vector<int> perm;
    for(int i = 0; i<n; i++){
        perm.PB(i);
    }

    do{
        int skips = 0;
        int cur = 0;
        for(int i = 0; i<perm.size(); i++){
            if(cur == s-1){
                skips++;
                cur = 0;
            }
            cur += (a[perm[i]]+1)%s;
        }

        if(skips < ans.first){
            ans.first = skips;
            vector<int> temp;
            for(int i = 0; i<perm.size(); i++){
                temp.PB(perm[i]);
            }
            ans.second = temp;
        }

    }while(next_permutation(perm.begin(), perm.end()));
    
    return ans;
}

PIV solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <= 1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        PIV ansB = brute();
        PIV ansS = solve();
        if(ansB.first != ansS.first){
            cout<<"ERROR\n";
            cout<<"BRUTE: \n";
            cout<<ansB.first<<"\n";
            for(int i = 0; i<ansB.second.size(); i++){
                cout<<ansB.second[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: \n";
            cout<<ansS.first<<"\n";
            for(int i = 0; i<ansS.second.size(); i++){
                cout<<ansS.second[i]<<" ";
            }
            cout<<"\n";
            return 0;
        }
        cout<<"CORRECT\n";
    }

    return 0;
}