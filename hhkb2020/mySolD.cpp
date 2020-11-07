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

ll getPowerSum(ll n) {
  return ((n*(n+1))/2)%mod;
}
ll getSecondPowerSum(ll n) {
  return ((n*(n+1)%mod)*(2*n+1)%mod)*power(6,mod-2)%mod;
}
ll getThirdPowerSum(ll n) {
  ll ret = getPowerSum(n);
  return ret * ret % mod;
}
void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    if(n < a + b) {
      cout << 0;
      return;
    }
    ll ans = 0;
    {
      ll p = a + b;
      ll val = (((n-p+1)*(n-p+2)%mod)*(2*n-2*p+3)%mod)*2%mod;
      val = (val * power(3,mod-2))%mod;
      ans = val;
      // cout << val << "\n";
    }
    {
      ll p = a + b - 1;
      ll p1 = ((n-p)*(n-p+1)*4) % mod;
      // p = max(a,b);
      ll q = max(a,b);
      ll p2 = (n+1) * (p-q+1) % mod - (p*(p+1))/2 + (q*(q-1))/2;
      p2 %= mod;
      ll val = p1 * p2 % mod;
      ans = (ans + val) % mod;
      // cout << val << "\n";
    }
    {
      ll p = n - (a + b);
      ll val = (getPowerSum(p) + 2 * getSecondPowerSum(p) + getThirdPowerSum(p)) % mod;
      ans = (ans + 4 * val) % mod;
      // cout << 4 * val << "\n";
    }
    ans %= mod;
    if(ans < 0) ans += mod;
    cout << ans;
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
