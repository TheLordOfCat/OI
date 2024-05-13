#include<iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using namespace std;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>

int n, k;
vector<int> c;
int m,l;
vector<int> x;
vector<int> y;

void getData(){
    cin>>n>>k;
    for(int i =0 ;i<n; i++){
        int temp;
        cin>>temp;
        c.PB(temp);
    }
    cin>>m>>l;
    for(int i = 0; i<m; i++){
        int temp;
        cin>>temp;
        x.PB(temp);
    }
    for(int i = 0 ; i<l; i++){
        int temp;
        cin>>temp;
        y.PB(temp);
    }
}

void getRandom(){
    srand(time(0));
    c.clear();
    x.clear();
    y.clear();

    // n =rand()%20+3;
    // k = rand()%n+1;
    n = 10;
    k = 3;
    vector<bool> used(k+1, false);
    int K = 0;
    for(int i = 0; i<n; i++){
        int temp = rand()%k+1;
        if(k == K){
            c.PB(temp);
        }else{
            while(used[temp]){
                temp = rand()%k+1;
            }
            used[temp] = true;
            K++;
            c.PB(temp);
        }
    }
    // l = min(rand()%(n-1)+1,k-1);
    // m = min(rand()%(n-1)+1,k-1);
    m = 2;
    l = 1;
    used.clear();
    int last = 1;
    used.assign(k+1,false);
    used[last] = true;
    for(int i =0 ; i<m; i++){
        int temp = rand()%k+1;
        while(used[temp]){
            temp = rand()%k+1;
        }
        used[temp] = true;
        x.PB(temp);
    }
    x.PB(last);
    m++;
    used.clear();
    used.assign(k+1,false);
    used[last] = true;
    for(int i =0 ; i<l; i++){
        int temp = rand()%k+1;
        while(used[temp]){
            temp = rand()%k+1;
        }
        used[temp] = true;
        y.PB(temp);
    }
    y.PB(last);
    l++;
}

void printData(){
    cout<<n<<" "<<k<<"\n";
    for(auto t:c){
        cout<<t<<" ";
    }
    cout<<"\n";
    cout<<m<<" "<<l<<"\n";
    for(auto t:x){
        cout<<t<<" ";
    }
    cout<<"\n";
    for(auto t:y){
        cout<<t<<" ";
    }
    cout<<"\n";
}

vector<int> brute(){
    vector<int> ans;
    for(int i = 0; i<n; i++){
        bool ok = true;
        if(c[i] != x.back()){
            ok = false;
        }
        int ind = i;
        if(ok){
            for(int j = m-1; j>=0; j--){
                if(c[ind] != x[j]){
                    j++;
                    ind--;
                }
                if(ind == 0){
                    ok = false;
                    break;
                }
            }
        }
        int left = ind;

        ind = i;
        if(ok){
            for(int j = l-1; j>=0; j--){
                if(c[ind] != y[j]){
                    j++;
                    ind++;
                }
                if(ind == n-1){
                    ok = false;
                    break;
                }
            }
        }
        int right = ind;
        bool sameHouse = false;
        for(int i  = 0; i<n/2; i++){
            if(i >= left ) break;
            if(n-i-1 <= right ) break;
            if(c[i] == c[n-i-1]){
                sameHouse = true;
                break;
            }
        }

        if(ok && sameHouse){
            ans.PB(i+1);
        }
    }
    return ans;
}

vector<int> solve(){
    int left = 1;
    for(int i = 0; i<m-1; i++){
        if(c[left] != x[i]){
            left++;
            i--;
        }
        if(left >= n){
            break;
        }
    }
    int right = n-2;
    for(int i = 0; i<l-1; i++){
        if(c[right] != y[i]){
            right--;
            i--;
        }
        if(right < 0){
            break;
        }
    }
    vector<int> ans;
    for(int i = left; i<=right; i++){
        if(c[i] == x[m-1]){
            ans.PB(i+1);
        }
    }
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
        vector<int> ansB = brute();
        vector<int> ansS = solve();
        if(ansB.size() != ansS.size()){
            cout<<"ERROR\n";
            cout<<"BRUTE: ";
            cout<<ansB.size()<<"\n";
            for(int i = 0; i<ansB.size(); i++){
                cout<<ansB[i]<<" ";
            }
            cout<<"\n";
            cout<<"SOLVE: ";
            cout<<ansS.size()<<"\n";
            for(int i = 0; i<ansS.size(); i++){
                cout<<ansS[i]<<" ";
            }
            cout<<"\n";
            printData();
            return 0;
        }else{
            for(int i =0 ;i<ansB.size(); i++){
                if(ansB[i] != ansS[i]){
                    cout<<"ERROR\n";
                    cout<<"BRUTE: ";
                    cout<<ansB.size()<<"\n";
                    for(int i = 0; i<ansB.size(); i++){
                        cout<<ansB[i]<<" ";
                    }
                    cout<<"\n";
                    cout<<"SOLVE: ";
                    cout<<ansS.size()<<"\n";
                    for(int i = 0; i<ansS.size(); i++){
                        cout<<ansS[i]<<" ";
                    }
                    cout<<"\n";
                    printData();
                    return 0;
                }
            }
        }
        cout<<"CORRECT\n";
    }

    return 0;
}