#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

#include <ctime>
#include <cstdlib>

using ll = long long int;
using ull = unsigned long long int;

const int INF = 2'000'000'000;
const int llINF = 9'000'000'000'000'000'000;
const int ullINF = 18'000'000'000'000'000'000;

using namespace std;

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
        char c;
        cin>>c;
        int a, b, c;
        if(c == 'P'){
            cin>>a>>b>>c;
        }
        if(c == 'U'){
            cin>>a;
            b = -1; c = -1;
        }
        if(c == 'Z'){
            cin>>a>>b;
            c = -1;
        }

        promts.PB(MT(c,a,b,c));
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
        char c; int a, b, c;
        int temp = rand()%3+1;

        if(temp == 2){
            if(curStations > 0){
                c = 'U';
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
            c = 'P';
            a = rand()%n+1;
            while(stations[a]){
                a = rand()%n+1;
            }
            b = rand()%20+5;
            c = rand()%5+5;
            curStations++;
        }

        if(temp == 3){
            c = 'Z';
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

        promts.PB(MT(c,a,b,c));
    }
}

void printData(){
    cout<<"DATA: \n";
    cout<<n<<" "<<m<<"\n";
    for(int i = 0; i<promts.size(); i++){
        char c = get<0>(promts[i]);
        int a = get<1>(promts[i]), b = get<2>(promts[i]), c = get<3>(promts[i]); 
        cout<<c<<" "<<a<<" "<<b<<" "<<c<<"\n";
    }
}

vector<int> brute(){
    vector<int> ans;
    vector<PII> poles(n+1, MP(0,0));
    vector<int> signal(n+1, 0);

    for(int i = 0; i<m; i++){
        char c = get<0>(promts[i]);
        int a = get<1>(promts[i]), b = get<2>(promts[i]), c = get<3>(promts[i]); 

        if(c == 'P'){
            poles[a] = MP(b,c);
            
            signal[a] = b;
            
            int temp = b-c;
            int ind = a+1;
            while(temp > 0){
                signal[a] += temp;
                ind += 1;
                temp -= c;

                if(ind > n){
                    break;
                }
            }

            temp = b-c;
            ind = a-1;
            while(temp > 0){
                signal[a] += temp;
                ind -= 1;
                temp -= c;

                if(ind > 0){
                    break;
                }
            }
        }
        
        if(c == 'U'){
            b = poles[a].first;
            c = poles[a].second;

            signal[a] -= b;
            
            int temp = b-c;
            int ind = a+1;
            while(temp > 0){
                signal[a] -= temp;
                ind += 1;
                temp -= c;
                if(ind > n){
                    break;
                }
            }

            temp = b-c;
            ind = a-1;
            while(temp > 0){
                signal[a] -= temp;
                ind -= 1;
                temp -= c;

                if(ind > 0){
                    break;
                }
            }

            poles[a] = MP(0,0);
        }

        if(c == 'Z'){
            int sum = 0;
            for(int i = a; i<=b; i++){
                sum+= signal[i];
            }
            ans.PB(sum / (a-b+1));
        }
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
    for(int test = 1; test <= 1; test++){
        cout<<"TEST nr."<<test<<" = ";
        if(op == 1){
            getData();
        }else{
            getRandom();
        }
        vector<int> ansB = brute();
        vector<int> ansS = solve();
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