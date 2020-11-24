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

int a[N], suff_max[N], st[N<<1];
int min_range(int l, int r) {
  int ret = INT_MAX;
  for(;l<r;l>>=1,r>>=1) {
    if(l&1) ret = min(ret, st[l++]);
    if(r&1) ret = min(ret, st[--r]);
  }
  return ret;
}
void solve(bool print_answers, bool print_test_case) {
    int n;
    cin>>n;
    REP(i,1,n) {
      cin >> a[i];
      st[i-1+n] = a[i];
    }
    if(print_test_case) {
      cout << n << "\n";
      REP(i,1,n) {
        cout << a[i] << " ";
      }
      cout << "\n";
      return;
    }
    if(!print_answers) {
      return;
    }
    suff_max[n] = a[n];
    REPN(i,n-1,1) {
      st[i] = min(st[i<<1], st[i<<1|1]);
      suff_max[i] = max(suff_max[i+1],a[i]);
    }

    int left_max = 0;
    REP(i,1,n-2) {
      left_max = max(left_max, a[i]);
      if(a[n] <= left_max) {
        int j;
        {
          int lo = i+2, hi = n, mi;
          while(lo < hi) {
            mi = (lo + hi) / 2;
            if(suff_max[mi] <= left_max) {
              hi = mi;
            }
            else {
              lo = mi + 1;
            }
          }
          j = lo;
        }
        if(suff_max[j] == left_max && min_range(i+1+n-1,j-1+n) == left_max) {
          int x = i;
          int z = n+1-j;
          int y = n - x - z;
          cout << "YES\n" << x << " " << y << " " << z;
          return;
        }
      }
    }
    cout << "NO";
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
        solve(T < 10, TC >= 70 && TC <= 80);
        if(T < 10) cout<<"\n";
    }
}
