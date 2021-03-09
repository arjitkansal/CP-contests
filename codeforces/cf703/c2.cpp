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

const int N = (int)1e5+5;
const int M = (int)3e3+5;
const int Q = 301;
const int logN = 19;

int cnt_queries = 0;
int query(int l, int r) {
  if(l==r) {
    return -1;
  }
  cnt_queries++;
  assert(cnt_queries<=20);
  cout << "? " << l << " " << r << endl;
  int ret;
  cin >> ret;
  return ret;
}
int printAnswer(int ans) {
  cout << "! " << ans << endl;
  exit(0);
}
void solve() {
  int n;
  cin >> n;
  int secondMax = query(1,n);
  if(query(1,secondMax) == secondMax) {
    int lo = 1, hi = secondMax - 1, mi;
    while(lo < hi) {
      mi = 1 + (lo+hi)/2;
      if(query(mi,secondMax) == secondMax) {
        lo = mi;
      }
      else {
        hi = mi-1;
      }
    }
    printAnswer(lo);
  }
  else {
    int lo = secondMax+1, hi = n, mi;
    while(lo < hi) {
      mi = (lo+hi)/2;
      if(query(secondMax,mi) == secondMax) {
        hi = mi;
      }
      else {
        lo = mi+1;
      }
    }
    printAnswer(lo);
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
