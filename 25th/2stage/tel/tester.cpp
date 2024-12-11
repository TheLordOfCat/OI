#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const ll llINF = 9'000'000'000'000'000'000;
const ull ullINF = 18'000'000'000'000'000'000;

#define MP make_pair
#define PII pair<int,int>
#define MT make_tuple
#define PB push_back

int n, m;
vector<tuple<char,int,int,int>> promts;

void getData(){
    promts.clear();

    cin>>n>>m;
    for(int i =0 ; i<m; i++){
        char t;
        cin>>t;
        int a, b, c;
        if(t == 'P'){
            cin>>a>>b>>c;
        }
        if(t == 'U'){
            cin>>a;
            b = -1; c = -1;
        }
        if(t == 'Z'){
            cin>>a>>b;
            c = -1;
        }

        promts.PB(MT(t,a,b,c));
    }
}

void getRandom(){
    promts.clear();
    
    srand(time(0));

    n = rand()%10+2;
    m = rand()%5+1;
    vector<bool> stations(n+1, false);
    int curStations = 0;
    for(int i = 0; i<m; i++){
        char t; int a, b, c;
        int temp = rand()%3+1;

        if(temp == 2){
            if(curStations > 0){
                t = 'U';
                a = rand()%n+1;
                while(!stations[a]){
                    stations[a] = false;
                    curStations--;
                }
                b = -1;
                c = -1;
            }else{
                temp = 1;
            }
        }

        if(temp == 1){
            t = 'P';
            a = rand()%n+1;
            while(stations[a]){
                a = rand()%n+1;
            }
            b = rand()%20+5;
            c = rand()%5+5;
            curStations++;
        }

        if(temp == 3){
            t = 'Z';
            a = -1;
            b = -1;
            while(a != b){
                a = rand()%n+1;
                b = rand()%n+1;
            }
            if(a>b){
                swap(a,b);
            }
            c = -1;
        }

        promts.PB(MT(t,a,b,c));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<promts.size(); i++){
        char t = get<0>(promts[i]);
        int a = get<1>(promts[i]), b = get<2>(promts[i]), c = get<3>(promts[i]); 
        cout<<t<<" "<<a<<" "<<b<<" "<<c<<"\n";
    }
}

vector<int> brute(){
    vector<PII> poles(n+1, MP(0,0));
    vector<int> signal(n+1, 0);
    vector<int> ans;

    for(int i =0 ; i<m; i++){
        char type = get<0>(promts[i]);
        if(type == 'P'){
            int x = get<1>(promts[i]), s = get<2>(promts[i]), a = get<3>(promts[i]);
            poles[x] = MP(s,a);
            //right
            int ind = x;
            int val = s;
            while(ind <=n && val > 0){
                signal[ind] += val;
                val -= a;
                ind++;
            }

            //left
            ind = x-1;
            val = s-a;
            while(ind >= 0 && val > 0){
                signal[ind] += val;
                val -= a;
                ind--;
            }
        }
        if(type == 'U'){
            int x = get<1>(promts[i]);
            //right
            int ind = x;
            int val = poles[x].first;
            while(ind <=n && val > 0){
                signal[ind] -= val;
                val -= poles[x].second;
                ind++;
            }

            //left
            ind = x-1;
            val = poles[x].first-poles[x].second;
            while(ind >= 0 && val > 0){
                signal[ind] -= val;
                val -= poles[x].second;
                ind--;
            }
        }
        if(type =='Z'){
            int sum = 0;
            int x1 = get<1>(promts[i]), x2 = get<2>(promts[i]);
            for(int i = x1; i<=x2; i++){
                sum += signal[i];
            }
            ans.PB(sum/(x2-x1+1));
        }
    }
    return ans;
}

vector<ll> solve(){
    
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
        vector<int> ansB = brute();
        vector<ll> ansS = solve();
        for(int j= 0 ; j<ansB.size(); j++){
            if(ansB[j] != ansS[j]){
                cout<<"ERROR\n";
                cout<<"BRUTE: ";
                for(int o = 0; o<ansB.size(); o++){
                    cout<<ansB[o]<<" ";
                }
                cout<<"\nSOLVE: ";
                for(int o = 0; o<ansS.size(); o++){
                    cout<<ansS[o]<<" ";
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