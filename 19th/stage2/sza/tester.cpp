#include <iostream>
#include <vector>
#include <tuple>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define MT make_tuple

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;

int n;
vector<tuple<int,int,int>> items;
int p;
vector<tuple<int,int,int>> stealPlans;

void getData(){
    cin>>n;
    for(int i =0; i<n; i++){
        int c,a,b;
        cin>>c>>a>>b;
        items.PB(MT(c,a,b));
    }
    cin>>p;
    for(int i =0; i<p; i++){
        int m,k,s;
        cin>>m>>k>>s;
        stealPlans.PB(MT(m,k,s));
    }
}

void getRandom(){
    items.clear();
    stealPlans.clear();

    srand(time(0));

    n = rand()%10+1;
    for(int i = 0; i<n; i++){
        int c = rand()%10+1;
        int a = rand()%10+1;
        int b = rand()%10+1;
        if(a > b) swap(a,b);
        items.PB(MT(c,a,b));
    }
    p = rand()%10+1;
    for(int i = 0; i<p; i++){
        int m = rand()%10+1;
        int k = rand()%15+1;
        int s=  rand()%8+1;
        stealPlans.PB(MT(m,k,s));
    }

}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<get<0>(items[i])<<" "<<get<1>(items[i])<<" "<<get<2>(items[i])<<"\n";
    }
    cout<<p<<"\n";
    for(int i = 0; i<n; i++){
        cout<<get<0>(items[i])<<" "<<get<1>(items[i])<<" "<<get<2>(items[i])<<"\n";
    }
}

vector<int> brute(){
    vector<int> ans;
    for(int i = 0; i<p; i++){
        int m = get<0>(stealPlans[i]), k = get<1>(stealPlans[i]), s = get<2>(stealPlans[i]);
        //iteams of intrest
        vector<tuple<int,int,int>> curItems;
        for(int j = 0; j<n; j++){
            int c = get<0>(items[j]), a = get<1>(items[j]), b = get<2>(items[j]);
            if(m <= a && a < s){
                curItems.PB(items[j]);
            }
        }

        //traverse throuhg items
        int ok = 0;
        for(int j = 0; j<curItems.size(); j++){
            vector<tuple<int,int,int>> chosen;
            for(int j = 0; j<curItems.size(); j++){
                if(i && 1<<j){
                    chosen.PB(items[j]);
                }
            }

            //verifying

            //check for sum
            int sum = 0;
            for(int j = 0; j<chosen.size(); j++){
                sum += get<1>(chosen[j]);
            }
            if(sum != k){
                continue;
            }

            //check for range
            int left = 0;
            int right = INF;
            for(int j = 0; j<chosen.size(); j++){
                left = max(left, get<0>(chosen[j]));
                right = min(right, get<0>(chosen[j]) + get<2>(chosen[j]));
            }
            if(right <= left){
                continue;
            }

            //good
            ok = 1;
            break;
        }
        ans.PB(ok);
    }
    return ans;
}

vector<int> solve(){

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
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        for(int i = 0; i<p; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j =0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j =0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}