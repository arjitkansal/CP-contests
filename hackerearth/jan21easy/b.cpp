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

int a[N], b[N];
vector<pi> temp;
int cnt(int n, int m, int k) {
  int ret = 0;
  REP(i,1,n) {
    if(a[i] + b[1] <= k) {
      int lo = 1, hi = m, mi;
      while(lo < hi) {
        mi = 1 + (lo + hi)/2;
        if(a[i] + b[mi] <= k) {
          lo = mi;
        }
        else {
          hi = mi-1;
        }
      }
      ret += lo;
    }
  }
  return ret;
}
int find_kth_greatest_value(int n, int m, int k) {
  int lo = 0, hi = 3e8, mi;
  while(lo < hi) {
    mi = (lo + hi)/2;
    if(cnt(n,m,mi)>=k) {
      hi = mi;
    }
    else {
      lo = mi+1;
    }
  }
  return lo;
}
void solve() {
  int n,m;
  cin >> n >> m;
  assert(n*m < 5e8);
  REP(i,1,n) {
    cin >> a[i];
  }
  REP(i,1,m) {
    cin >> b[i];
  }
  int x,y;
  cin >> x >> y;
  int gx = find_kth_greatest_value(n,m,x);
  int gy = find_kth_greatest_value(n,m,y);

  REP(i,1,n) {
    REP(j,1,m) {
      if(a[i]+b[j]>gx && a[i]+b[j]<gy) {
        temp.pb({i,j});
      }
    }
  }
  cout << temp.size() << "\n";
  for(pi it : temp) {
    cout << "(" << it.first << "," << it.second << ") ";
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
