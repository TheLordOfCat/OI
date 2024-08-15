#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

#define PII pair<int,int>
#define MP make_pair
#define PB push_back

int n;
vector<int> x;
vector<int> y;
vector<PII> edges;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        y.PB(temp);
    }
    for(int i = 0; i<n-1; i++){
        int a, b;
        cin>>a>>b;
        edges.PB(MP(a,b));
    }
}

void getRandom(){
    n = rand()%10+1;
    //testing "NIE"
    for(int i = 0; i<n; i++){
        int temp = rand()%11;
        x.PB(temp);
    }
    for(int i = 0; i<n; i++){
        int temp = rand()%11;
        y.PB(temp);
    }

    //testing "TAK"
    // int sum = 0;
    // for(int i = 0; i<n; i++){
    //     int temp = rand()%11;
    //     x.PB(temp);
    //     sum += temp;
    // }
    // for(int i = 0; i<n-1; i++){
    //     if(sum != 0){
    //         int temp = rand()%sum;
    //         y.PB(temp);
    //     }else{
    //         y.PB(0);
    //     }
    // }
    // y.PB(sum);

    int ind = 2;
    for(int i = 1; i<=n; i++){
        int con = rand()%3+1;
        for(int j =0 ; j<con;j ++){
            edges.PB(MP(i,ind));
            ind++;
            if(ind > n){
                break;
            }
        }
        if(ind > n){
            break;
        }
    }

}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<x[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<n; i++){
        cout<<y[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<n; i++){
        cout<<edges[i].first<<" "<<edges[i].second<<"\n";
    }
}

ll brute(){
    
}

ll solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op =1;
    for(int test = 1; test<=1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        ll ansB = brute();
        ll ansS = solve();
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