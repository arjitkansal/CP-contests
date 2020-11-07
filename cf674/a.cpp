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
  int a1,a2,a3;
  cin>>a1>>a2>>a3;
  int b1,b2,b3;
  cin>>b1>>b2>>b3;
  int ans_min=-1, ans_max = -1;
  {
    //Minimum;
    {
      //Max bob wins + remaining max draws
      int a,b,c,d,e,f;
      a = b1, b = b2, c = b3;
      d = a1, e = a2, f = a3;
      ans_min = n - (min(a,e) + min(b,f) + min(c,d));
      {
        int temp = min(a,e);
        a -= temp;
        e -= temp;
      }
      {
        int temp = min(b,f);
        b -= temp;
        f -= temp;
      }
      {
        int temp = min(c,d);
        c -= temp;
        d -= temp;
      }
      ans_min -= (min(a,d) + min(b,e) + min(c,f));
    }
    {
      //Max draws + remaining max bob wins
      int a,b,c,d,e,f;
      a = b1, b = b2, c = b3;
      d = a1, e = a2, f = a3;
      int max_draws = (min(a,d) + min(b,e) + min(c,f));
      {
        int temp = min(a,d);
        a -= temp;
        d -= temp;
      }
      {
        int temp = min(b,e);
        b -= temp;
        e -= temp;
      }
      {
        int temp = min(c,f);
        c -= temp;
        f -= temp;
      }
      ans_min = min(ans_min, n - (max_draws + min(a,e) + min(b,f) + min(c,d)));
    }
  }
  {
    //Maximum;
    int a,b,c,d,e,f;
    a = a1, b = a2, c = a3;
    d = b1, e = b2, f = b3;
    ans_max = min(a,e) + min(b,f) + min(c,d);
  }
  cout << ans_min << " " << ans_max;
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
        cout<<"\n";
    }
}
