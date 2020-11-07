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

const int N = (int)2e5+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

void solve() {
    int n;
    cin>>n;
    vector<int> divisors, primes;
    int sqr = sqrt(n);
    REP(i,2,sqr) {
        if(n%i==0) {
            divisors.pb(i);
            if(i!=(n/i)) {
                divisors.pb(n/i);
            }
        }
    }
    divisors.pb(n);
    int m = n;
    REP(i,2,sqr) {
        if(m%i==0) {
            primes.pb(i);
            while(m%i==0) {
                m/=i;
            }
        }
    }
    if(m>1) {
        primes.pb(m);
    }
    if(primes.size()==1) {
        for(auto it:divisors) {
            cout<<it<<" ";
        }
        cout<<"\n0";
        return;
    }
    sort(all(primes));
    //vector<int> vv;
    unordered_map<int,bool,custom_hash> mp;
    REP(i,0,(int)primes.size()-2) {
        mp[primes[i]] = false;
        mp[primes[i]*primes[i+1]] = false;
        //vv.pb(primes[i]*primes[i+1]);
    }
    mp[primes.back()] = false;
    //if(!mp.count(primes[0]*primes.back())) {
      //  vv.pb(primes[0]*primes.back());
    //}
    mp[primes[0]*primes.back()] = false;
    unordered_map<int,vector<int>,custom_hash> temp;
    for(auto it:primes) {
        temp[it].pb(it);
    }
    for(auto it:divisors) {
        if(!mp.count(it)) {
            for(auto p:primes) {
                if(it%p==0) {
                    temp[p].pb(it);
                    break;
                }
            }
        }
    }
    /*for(auto it:vv) {
        for(auto p:primes) {
            if(it%p==0) {
                temp[p].pb(it);
                break;
            }
        }
    }
    */
    REP(i,0,(int)primes.size()-2) {
        temp[primes[i]].pb(primes[i]*primes[i+1]);
    }
    if(primes.size()>2) {
        temp[primes.back()].pb(primes[0]*primes.back());
    }
    int ans = 0;
    int first = -1, last = -1;
    for(auto it:primes) {
        for(auto i:temp[it]) {
            if(i!=n) {
                if(last != (-1)) {
                    if(__gcd(last, i)==1) {
                        ans++;
                    }
                }
                last = i;
                if(first==(-1)) {
                    first = i;
                }
                cout<<i<<" ";
            }
        }
    }
    last = n;
    cout<<n;
    if(__gcd(last,first)==1) {
        ans++;
    }
    cout<<"\n"<<ans;

}
int main() {
    //freopen("output.txt","r",stdin);
    //freopen("output.txt","w",stdout);

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    cin>>T;
    REP(TC,1,T) {
        //cout<<"Case #"<<TC<<": ";
        solve();
        cout<<"\n";
    }
}
