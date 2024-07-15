#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ll = long long int;
using ull = unsigned long long int;

int n, k;
vector<int> c;
int lenX, lenY;
vector<int> vecX;
vector<int> vecY;

void getData(){
    cin>>n>>k;
    for(int i = 0; i<n; i++){
        int temp;
        cin>>temp;
        c.PB(temp);
    }
    cin>>lenX>>lenY;
    for(int i = 0; i<lenX; i++){
        int temp;
        cin>>temp;
        vecX.PB(temp);
    }
    for(int i =0; i < lenY; i++){
        int temp;
        cin>>temp;
        vecY.PB(temp);
    }
}

void getRandom(){
    c.clear();
    vecX.clear();
    vecY.clear();

    srand(time(0));
    
    n = rand()%10+1;
    k = 1;
    for(int i =0; i<n; i++){
        int op = rand()%10+1;
        int temp;
        if(op > 7){
            k++;
            temp = k;
        }else{
            temp = rand()%k+1;
        }
        c.PB(temp);
    }

    lenX = rand()%k+1;
    lenY = rand()%k+1;
    for(int i = 0; i<lenX; i++){
        int temp = rand()%k+1;
        vecX.PB(temp);
    }
    for(int i = 0; i<lenY; i++){
        int temp = rand()%k+1;
        vecY.PB(temp);
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<k<<"\n";
    for(int i = 0; i<n; i++){
        cout<<c[i]<<" ";
    }
    cout<<"\n";
    cout<<lenX<<" "<<lenY<<"\n";
    for(int i = 0; i<lenX; i++){
        cout<<vecX[i]<<" ";
    }
    cout<<"\n";
    for(int i = 0; i<lenY; i++){
        cout<<vecY[i]<<" ";
    }
    cout<<"\n";
}

vector<int> brute(){
    vector<bool> vis;
    for(int i = 1; i<=k; i++){
        int left;
        int right;
        for(int j = 0; j<n; j++){
            if(c[j] == i){
                left = j;
                break;
            }
        }
        for(int j = n-1; j>=0; j--){
            if(c[j] == i){
                right = j;
                break;
            }
        }

        int ind = 0;
        for(int j = left+1; j< n; j++){
            if(c[j] == vecX[ind]){
                ind++;
                if(ind >= lenX-1){
                    left = j+1;
                    break;
                }
            }
        }

        ind = 0;
        for(int j = right-1; j >=0 ; j--){
            if(c[j] == vecY[ind]){
                ind++;
                if(ind >= lenY-1){
                    right = j+1;
                    break;
                }
            }
        }

        for(int j = left; j<=right; j++){
            if(c[j] == vecX.back()){
                vis[j] = true;
            }
        }
    }

    vector<int> ans;
    for(int i = 0; i<n; i++){
        if(vis[i]){
            ans.PB(i);
        }
    }

    return ans;
}

vector<int> solve(){

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int op = 1;
    for(int test = 1; test<=1; test++){
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        if(ansB.size() != ansS.size()){
            cout<<"ERORR\n";
            cout<<"BRUTE:\n";
            cout<<ansB.size()<<"\n";
            for(int j =0; j<ansB.size(); j++){
                cout<<ansB[j]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE:\n";
            cout<<ansS.size()<<"\n";
            for(int j =0; j<ansS.size(); j++){
                cout<<ansS[j]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        }
        for(int i = 0; i<ansB.size(); i++){
            if(ansB[i] != ansS[i]){
                cout<<"ERORR\n";
                cout<<"BRUTE:\n";
                cout<<ansB.size()<<"\n";
                for(int j =0; j<ansB.size(); j++){
                    cout<<ansB[j]<<" ";
                }
                cout<<"\n";
                cout<<"SOLVE:\n";
                cout<<ansS.size()<<"\n";
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