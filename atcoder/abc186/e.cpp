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
ll power(ll a,ll b,int m) {
   ll res=1;
   while(b){
      if(b%2==1) res=(res*a)%m;
      a=(a*a)%m;
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
ll lcmm(ll a, ll b) {
  return ((ll)a*b)/gcdll(a,b);
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

unordered_map<int,int,custom_hash> primeFactorization(int n) {
  unordered_map<int,int,custom_hash> mp;
  for(int i=2;(ll)i*i<=n;i++) {
    while(n%i==0) {
      if(!mp[i]) mp[i] = i;
      else mp[i] *= i;
      n/=i;
    }
  }
  if(n>1) mp[n] = n;
  return mp;
}
int totientFactor(int k) {
  unordered_map<int,int,custom_hash> mp = primeFactorization(k);
  int ret = 1;
  for(auto p: mp) {
    ret *= (p.second / p.first) * (p.first - 1);
  }
  return ret;
}
int calculateModuloInverse(int k, int n) {
  int p = totientFactor(n) - 1;
  return power(k,p,n);
}
void solve() {
    int n,s,k;
    cin >> n >> s >> k;
  if(n==k) { cout << -1;
            return;}
    ll movesToReturn = lcmm(n,k)/k;
    k%=n;
    int g = gcd(s,k);
    s/=g, k/=g;
    if(gcd(n,k) > 1) {
      cout << -1;
      return;
    }
    int invK = calculateModuloInverse(k,n);
    cout << ((ll)invK * (n-s)) % min((ll)n,movesToReturn);
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
