#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PB push_back
#define PII pair<int,int>

int n;
vector<char> s;
int q;
vector<PII> seg;

void getData(){
    cin>>n;
    for(int i = 0; i<n; i++){
        char temp;
        cin>>temp;
        s.PB(temp);
    }
    cin>>q;
    for(int i =0; i<q; i++){
        int a, b;
        cin>>a>>b;
        seg.PB(MP(a,b));
    }
}

void getRandom(){
    srand(time(0));

    n = rand()%10+1;
    for(int i = 0; i<n; i++){
        char temp = (rand()%26 + 'a');
        s.PB(temp);
    }
    q = rand()%10+1;
    for(int i = 0; i<q; i++){
        int a = rand()%n+1;
        int b = rand()%n+1;
        if(a == b){
            swap(a,b);
        } 
        seg.PB(MP(a,b));
    }
}

void printData(){
    cout<<n<<"\n";
    for(int i = 0; i<n; i++){
        cout<<s[i];
    }
    cout<<"\n";
    for(int i =0 ;i<q; i++){
        cout<<seg[i].first<<" "<<seg[i].second<<"\n";
    }
}

vector<int> brute(){
    vector<int> ans;
    for(int i = 0; i<q; i++){
        int left = seg[i].first;
        int right = seg[i].second;
        int len = right - left +1;
        
        int smallest = len;
        //finding the smallest divisor
        for(int i = 2; i<=len; i++){
            if(len%i == 0){
                int k = i;
                
                //maximal power
                int a = 1;
                int temp = len;
                while(temp%k == 0){
                    temp /= k;
                    a++;
                }

                int dif = 1;
                for(int j =1; j<= a; j++){
                    dif *= k;
                }
                bool ok = true;
                
                while(ok){
                    //verify
                    for(int j = left; j <= right; j += dif){
                        
                    }

                    if(ok){
                        smallest = min(smallest, dif);
                    }
                }
            }
        }
        ans.PB(smallest);
    }

    return ans;
}

vector<int> sieve(){
    
}

bool hashCompare(int a, int b, int c, int d){

}

bool isCyclyc(int a, int b, int k){
    return hashCompare(a, b-k, a+k, b);
}

vector<int> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test <=1; test++){
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
                for(int i =0; i<ansB.size(); i++){
                    cout<<ansB[i]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int i =0; i<ansS.size(); i++){
                    cout<<ansB[i]<<" ";
                }
                cout<<"\n";
            }
        }
    }

    return 0;
}