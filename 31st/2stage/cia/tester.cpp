#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back
#define PLL pair<ll,ll>
#define MT make_tuple

int n;
vector<int> d;
int q;
vector<tuple<int,int,int>> query;

void getData(){
    d.clear(); query.clear();
    cin>>n;
    for(int i =0; i<n; i++){
        int temp;
        cin>>temp;
        d.PB(temp);
    }
    cin>>q;
    for(int i =0 ; i<q; i++){
        int a, b, c;
        cin>>a>>b>>c;
        query.PB(MT(a,b,c));
    }
}

void getRandom(){
    d.clear(); query.clear();

    srand(time(0));

    n = rand()%10+1;
    int totalLen = 0;
    for(int i =0; i<n; i++){
        int temp = rand()%2+1;
        d.PB(temp);
        totalLen += temp;
    }
    q = rand()%10+1;
    for(int i = 0; i<q; i++){
        int l = rand()%totalLen+1, r = rand()%totalLen+1;
        if(l > r) swap(l,r);
        int k = rand()%3+1;
        query.PB(MT(l,r,k));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<d[i]<<" ";
    }
    cout<<"\n";
    cout<<q<<"\n";
    for(int i= 0; i<q; i++){
        int l = get<0>(query[i]), r = get<1>(query[i]), k = get<2>(query[i]);
        cout<<l<<" "<<r<<" "<<k<<"\n";
    }
}

vector<int> brute(){
    //create actual binary sequence
    vector<int> seq;
    int type = 1;
    for(int i = 0; i<d.size(); i++){
        for(int  j =0; j < d[i]; j++){
            seq.PB(type);
        }
        type = (type+1)%2;
    }

    //process queries
    vector<int> ans;
    for(int i = 0; i<q; i++){
        int l = get<0>(query[i]), r = get<1>(query[i]), k = get<2>(query[i]);
        queue<int> Q;
        
        //get 1 sequences
        int ind = 0;
        while(seq[ind] == 1) ind++;
        int len = 0;
        while(ind<seq.size()){
            if(seq[ind] == 1){
                len++;
            }else if(len != 0){
                Q.push(len);
                len = 0;
            }
            ind++;
        }

        ind = 0;
        int lenBeg = 0;
        while(seq[ind] == 1){
            lenBeg++;
            ind++;
        }

        ind = seq.size()-1;
        int lenEnd = 0;
        while(seq[ind] == 1){
            lenEnd++;
            ind--;  
        }

        //process sequences
        int bestComb = 0;
        while(k >= 0){
            if(Q.size() == 0 && lenBeg == 0 && lenEnd == 0) break;
            
            if(Q.size() > 0 && k >= 2){
                if(Q.front() > lenBeg && Q.front() > lenEnd ){
                    bestComb += Q.front();
                    k -= 2;
                }else if(lenBeg > Q.front() && lenBeg > lenEnd){
                    bestComb += lenBeg;
                    k-=1;
                    lenBeg = 0;
                }else{
                    bestComb += lenEnd;
                    k-=1;
                    lenEnd = 0;
                }
            }else{
                if( lenBeg > lenEnd){
                    bestComb += lenBeg;
                    k-=1;
                    lenBeg = 0;
                }else{
                    bestComb += lenEnd;
                    k-=1;
                    lenEnd = 0;
                }
            }
        }
        ans.PB(bestComb);
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
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++) cout<<ansB[j]<<" ";
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++) cout<<ansS[j]<<" ";
                cout<<"\n";
                printData();
                return 0;
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}