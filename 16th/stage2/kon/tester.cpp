#include <iostream>
#include <vector>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

int n, k;
vector<vector<int>> pasen;

void getData(){
    cin>>n>>k;
    for(int i =1; i<n; i++){
        vector<int> vec;
        for(int j =1; j <=n-i; j++){
            int temp;
            cin>>temp;
            vec.PB(temp);
        }
        pasen.PB(vec);
    }
}

void getRandom(){
    pasen.clear();

    srand(time(0));

    n = rand()%10+1;
    for(int i =1; i<n; i++){
        vector<int> vec;
        for(int j =1; j <=n-i; j++){
            int temp = rand()%10+1;
            vec.PB(temp);
        }
        pasen.PB(vec);
    }
}

void printData(){

}

vector<int> brute(){

}

vector<int> solve(){

}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1 ;test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();

        //comparison type 1
        for(int i = 0; i<k; i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int j = 0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE: ";
                for(int j = 0; j<ansS.size(); j++){
                    cout<<ansS[j]<<" ";
                }
                cout<<"\n";
                return 0;
            }
        }

        //comparison type 2
    }

    return 0;
}