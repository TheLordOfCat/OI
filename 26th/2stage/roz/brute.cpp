#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define PII pair<int,int>
#define PB push_back
#define PLL pair<ll,ll>
#define MT make_tuple

int M;
int q;
vector<tuple<char,int,int>> query;

void getData(){
    cin>>M;
    cin>>q;
    for(int i = 0; i<q; i++){
        char t;
        cin>>t;
        int a, b = -INF;
        if(t == 'd'){
            cin>>a;
        }else if(t == 'k'){
            cin>>a>>b;
        }else if(t == 's'){
            cin>>a;
        }
        query.PB(MT(t,a,b));
    }
}

void getRandom(){
    srand(time(0));
    M = rand()%10+1;
    q = rand()%10+1;
    int totalSize = 0;
    for(int i = 0; i<q; i++){
        char t;
        int temp = rand()%3;
        if(temp == 0 || totalSize < 2){
            t = 'd';
        }else if(temp == 1){
            t = 'k';
        }else if(temp == 2){
            t = 's';
        }
        int a, b = -INF;
        if(t == 'd'){
            a = rand()%10+1;
            totalSize++;
        }else if(t == 'k'){
            a = rand()%totalSize+1;
            b = rand()%10+1;
        }else if(t == 's'){
            a = rand()%totalSize+1;
        }
        query.PB(MT(t,a,b));
    }
    query.PB(MT('s', totalSize, -INF));
}

void printData(){
    cout<<"DATA:\n";
    cout<<M<<"\n";
    cout<<q<<"\n";
    for(int i =0 ;i<q; i++){
        char t = get<0>(query[i]);
        int a = get<1>(query[i]), b = get<2>(query[i]);
        cout<<t<<" "<<a<<" "<<b<<"\n";
    }
}

vector<ll> brute(){
    vector<ll> vec;

    vector<ll> ans;
    int curM = -1;
    for(int i = 0; i<q; i++){
        char t = get<0>(query[i]); 
        int a = get<1>(query[i]), b = get<2>(query[i]);
        if(t == 'd'){
            vec.PB(a);
            curM++;
        }else if(t == 'k'){
            vec[curM-(a-1)] += b;
        }else if(t == 's'){
            ll count = 0;
            for(int j = max(curM-(a-1), 0); j<=curM; j++){
                count += vec[j];
            }
            ans.PB(count);
        }
    }

    return ans;
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
        vector<ll> ansB = brute();
        for(int j = 0; j<ansB.size(); j++) cout<<ansB[j]<<" ";
    }

    return 0;
}