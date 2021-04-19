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

const int N = (int)5e4+5;
const int M = (int)3e3+5;
const int Q = (int)1e5+5;
const int logN = 19;

// set<int> s;
int x[N],y[N],l[N],ts[N],t,cnt[N],c[Q],w[Q];
ll a[N],ans[Q];
vector<int> v[N];
void dfs(int i, int p) {
  cnt[i] = 1;
  ts[i] = t++;
  for(auto it: v[i]) {
    if(it!=p) {
      dfs(it,i);
      cnt[i] += cnt[it];
    }
  }
}

ll g[N<<1];
void apply(int i, ll v) {
  g[i] = gcdll(g[i],v);
}
void update_range(int l, int r, ll x) {
  for(;l<r;l/=2,r/=2) {
    if(l&1) apply(l++,x);
    if(r&1) apply(--r,x);
  }
}


vector<PIL> cost[Q<<1];
vector<int> st[Q<<1], rem;

void process(int x, int n, ll toll) {
  int l = ts[x] + n - 1, r = ts[x] + cnt[x] + n - 1;
  update_range(l,r,toll);
}

ll get_val(int i) {
  int p;
  REPN(h,17,1) {
    p = i>>h;
    if(p && g[p]) {
      apply(p<<1,g[p]);
      apply(p<<1|1,g[p]);
      g[p] = 0;
    }
  }
  return g[i];
}
void solve() {
  // s.clear();
  REP(i,1,2*Q-1) {
    cost[i].clear();
    st[i].clear();
  }
  t = 1;
  int n,q;
  cin >> n >> q;
  REP(i,1,n) {
    g[i] = g[i+n] = 0;
    v[i].clear();
    cnt[i] = 0;
    // s.insert(i);
    // g[i] = 0;
  }

  REP(i,1,n-1) {
    cin >> x[i] >> y[i]>> l[i] >> a[i];
    v[x[i]].pb(y[i]);
    v[y[i]].pb(x[i]);
  }
  dfs(1,1);

  REP(i,1,n-1) {
    if(ts[x[i]] > ts[y[i]]) {
      cost[l[i]].pb({x[i],a[i]});
    }
    else {
      cost[l[i]].pb({y[i],a[i]});
    }
  }

  REP(i,1,q) {
    cin >> c[i] >> w[i];
    st[w[i]].pb(i);
  }

  REP(i,1,2*Q-1) {
    for(auto it : cost[i]) {
      process(it.first,n,it.second);
    }
    for(auto q : st[i]) {
      ans[q] = get_val(ts[c[q]] + n-1);
    }
  }

  REP(i,1,q) {
    cout << ans[i] << " ";
  }
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
        cout<<"Case #"<<TC<<": ";
        solve();
        cout<<"\n";
    }
}
