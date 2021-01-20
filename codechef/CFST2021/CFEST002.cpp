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

const int N = (int)2e5+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

ll get_common_ratio(ll a, ll b, ll c) {
  ll x = b-a, y = c-b;
  return (y * power(x,mod-2)) % mod;
}
ll temp_func(int n, ll r) {
  ll num = ((power(r,n-3) - 1) * power(r,2)) % mod;
  ll den = power(r-1,mod-2);
  ll ret = (num * den) % mod;
  if(ret < 0) ret += mod;
  return ret;
}
ll get_gp_sum(int n, ll r) {
  ll num = ((power(r,n-3) - 1) * r) % mod;
  ll den = power(r-1,mod-2);
  ll ret = (num * den) % mod;
  if(ret < 0) ret += mod;
  return ret;
}
void solve() {
  int n;
  ll l1,l2,l3;
  cin >> n >> l1 >> l2 >> l3;
  if(n<4) {
    if(n==1) {
      cout << l1 << " " << l1;
    }
    else if(n==2) {
      cout << l2 << " " << l1 + l2;
    }
    else {
      cout << l3 << " " << l1 + l2 + l3;
    }
    return;
  }
  ll r = get_common_ratio(l1,l2,l3);
  ll ln = (l3 + (l2-l1) * temp_func(n,r)) % mod;
  ll sum = (l1 + l2 + l3 + (n-3) * l3) % mod;

  ll c = (((l2-l1) * power(r,2)) % mod) * power(r-1,mod-2) % mod;
  if(c<0) c += mod;

  ll f = get_gp_sum(n,r) - (n-3);
  sum += (c * f) % mod;
  if(sum < 0) sum += mod;
  cout << ln << " " << sum;
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
