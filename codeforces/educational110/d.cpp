#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define mod ((int)1e9+7)
#define lim 1000000000000000007
#define lim1 18446744073709551615  //Unsigned
#define sq(a) ((a)*(a))
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define mms(v,i) memset(v,i,sizeof(v))
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define REP(i,a,b) for (int i = a; i <= b; i++)
#define REPN(i,a,b) for (int i = a; i >= b; i--)
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef pair<int,int> pi;
typedef pair<ll,ll> PL;
typedef pair<ll,int> PLI;
typedef pair<int,ll> PIL;
typedef pair<int,pair<int,int> > pii;
typedef pair<double,double> pdd;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> indexed_set;
ll power(ll a,ll b) {
   a %= mod;
   ll res=1;
   while(b){
      if(b%2==1) res=(res*a)%mod;
      a=(a*a)%mod;
      b>>=1;
   }
   return res;
}
ll gcdll(ll a,ll b) {
    if (b==0) return a;
    return gcdll(b,a%b);
}
int gcd(int a,int b) {
    if (b==0) return a;
    return gcd(b,a%b);
}

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const int N = (1<<19);
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

int potentialWinnersCount[N], matchIndex[N], matchNumbers[N];
string s;
void calculatePotentialWinners(int id) {
    char matchResult = s[matchNumbers[id]];
    if(matchResult == '0') {
        potentialWinnersCount[id] = potentialWinnersCount[2*id];
    }
    else if(matchResult == '1') {
        potentialWinnersCount[id] = potentialWinnersCount[2*id+1];
    }
    else {
        potentialWinnersCount[id] = potentialWinnersCount[2*id] + potentialWinnersCount[2*id+1];
    }
}
void matches(int id, int l, int r) {
    if(l==r) {
        potentialWinnersCount[id] = 1;
        return;
    }
    int mid = (l+r)/2;
    matches(2*id,l,mid);
    matches(2*id+1,mid+1,r);
    calculatePotentialWinners(id);
}
void processQuery(int matchNumber, char matchResult) {
    if(s[matchNumber] != matchResult) {
        s[matchNumber] = matchResult;
        int matchId = matchIndex[matchNumber];
        while(matchId > 0) {
            calculatePotentialWinners(matchId);
            matchId /= 2;
        }
    }
}
void initializeTournament() {
    int n = s.size(), currentLevelCount = 0, currentLevelTotal = 1, r = 1;
    REPN(i,n-1,0) {
        matchIndex[i] = r - currentLevelCount;
        matchNumbers[r-currentLevelCount] = i;
        currentLevelCount++;
        if(currentLevelCount == currentLevelTotal) {
            currentLevelTotal *= 2;
            currentLevelCount = 0;
            r = 2*r+1;
        }
    }

}
void solve() {
    int k;
    cin >> k >> s;
    initializeTournament();
    int teamsCount = (1<<k);
    matches(1,1,teamsCount);
    int q,p;
    cin >> q;
    char c;
    while(q--) {
        cin >> p >> c;
        processQuery(p-1,c);
        cout << potentialWinnersCount[1] << "\n";
    }
}
int main() {
    //freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    // cin>>T;
    REP(TC,1,T) {
        //cout<<"Case #"<<TC<<": ";
        solve();
        // cout<<"\n";
    }
}
