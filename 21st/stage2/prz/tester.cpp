#include <iostream>
#include <vector>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using namespace std;

#define MP make_pair
#define PII pair<int,int>
#define PB push_back

using ll = long long int;
using ull = unsigned long long int;

const int MAXN = 1'000'000;
const int MAXK = 1'000'000;

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
    vector<bool> vis(n+1, false);
    for(int i = 1; i<=k; i++){
        int left = MAXN+1;
        int right = -1;
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
                    right = j-1;
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
            ans.PB(i+1);
        }
    }

    return ans;
}

bool customSortLeft(const PII a, const PII b){
    return a.first < b.first;
}

bool customSortRight(const PII a, const PII b){
    return a.first > b.first;
}

vector<int> solve(){
    vector<PII> colorPairs(k+1, MP(-1,-1));

    //left
    vector<PII> lastLeft(k+1, MP(MAXN+1, MAXN+1));
    for(int i = 1; i<=k; i++) lastLeft[i].second = i;
    vector<int> next(n+1, MAXN+1);
    for(int i = n-1; i>=0; i--){
        next[i] = lastLeft[c[i]].first;
        lastLeft[c[i]].first = i;
    }

    vector<int> seg(n+1, 0);
    vector<int> chain(lenX-1, 0);
    for(int i = 0; i<lenX-1; i++){
        chain[i] = lastLeft[vecX[i]].first;
    }
    sort(lastLeft.begin(), lastLeft.end(), customSortLeft);

    for(int i = 0; i<k; i++){
        int ind = 0;
        bool ok = true;
        for(int j = 0; j<chain.size(); j++){
            while(chain[j] <= ind){
                chain[j] = next[chain[j]];
                if(chain[j] > n){
                    ok = false;
                    break;
                }
            }
            if(!ok){
                break;
            }else{
                ind = chain[j];
            }
        }
        if(ok){
            colorPairs[lastLeft[i].second].first = chain.back();
        }else{
            for(int j = i; j<k; j++){
                colorPairs[lastLeft[i].second].first = MAXN+1;
            }
            break;
        }
    }

    //right
    vector<PII> lastRight(k+1, MP(-1,-1));
    for(int i = 1; i<=n; i++) lastRight[i].second = i;
    for(int i = 0; i<n; i++){
        next[i] = lastRight[c[i]].first;
        lastRight[c[i]].first = i;
    }

    chain.clear();
    chain.assign(lenY-1, 0);

    for(int i = 0; i<lenX-1; i++){
        chain[i] = lastRight[vecY[i]].first;
    }
    sort(lastRight.begin(), lastRight.end(), customSortRight);

    for(int i = 0; i<k; i++){
        int ind = 0;
        bool ok = true;
        for(int j = 0; j<chain.size(); j++){
            while(chain[j] >= ind){
                chain[j] = next[chain[j]];
                if(chain[j] > n){
                    ok = false;
                    break;
                }
            }
            if(!ok){
                break;
            }else{
                ind = chain[j];
            }
        }
        if(ok){
            colorPairs[lastLeft[i].second].second = chain.back();
        }else{
            for(int j = i; j<k; j++){
                colorPairs[lastLeft[i].second].second = -1;
            }
            break;
        }
    }     

    //plotting the segments
    for(int i = 1; i<=k; i++){
        if(!(colorPairs[i].first > n || colorPairs[i].second < 0)){
            seg[colorPairs[i].first]++;
            seg[colorPairs[i].second]--;
        }
    }

    //getting the ans
    vector<int> ans;
    int sum = 0;
    for(int i = 0; i<n; i++){
        sum += seg[i];
        if(sum > 0){
            if(vecX.back() == c[i]){
                ans.PB(i+1);
            }
        }
    }

    return ans;
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