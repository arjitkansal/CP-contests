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

int a[N], cnt_overall = 0, pref[N];
int t1[N], cnt[N], t = 0;
vector<int> v[N], positions[N];
void dfs(int i, int p) {
  t1[i] = ++t;
  positions[a[i]].pb(t);
  cnt[i] = 1;
  for(auto it : v[i]) {
    if(it!=p) {
      dfs(it,i);
      cnt[i] += cnt[it];
    }
  }
}
void update_prefix_sum(int l, int r, int d = -1) {
  pref[l] += d;
  pref[r+1] -= d;
}
bool check_val_in_range(int val, int l, int r) {
  if(l>r) {
    return false;
  }
  int i = lower_bound(all(positions[val]), l) - positions[val].begin();
  return (i!=positions[val].size() && positions[val][i]<=r);
}
void process_subtree(int val, int l, int r) {
  if(check_val_in_range(val,l,r)) {
    cnt_overall++;
    update_prefix_sum(l,r);
  }
}
void process_parent_subtree(int val, int t1, int cnt) {
  if(check_val_in_range(val,1,t1-1) || check_val_in_range(val,t1+cnt,t)) {
    cnt_overall++;
    update_prefix_sum(1,t1-1);
    update_prefix_sum(t1+cnt,t);
  }
}
void dfs1(int i, int p) {
  if(i!=p) {
    process_parent_subtree(a[i],t1[i],cnt[i]);
  }
  for(auto it : v[i]) {
    if(it!=p) {
      process_subtree(a[i],t1[it],t1[it]+cnt[it]-1);
      dfs1(it,i);
    }
  }
}
void coordinate_compression(int n) {
  set<int> s;
  REP(i,1,n) {
    s.insert(a[i]);
  }
  unordered_map<int,int,custom_hash> mp;
  int cnt = 0;
  for(auto it:s) {
    mp[it] = ++cnt;
  }
  REP(i,1,n) {
    a[i] = mp[a[i]];
  }
}
void solve() {
  int n;
  cin >> n;
  REP(i,1,n) {
    cin >> a[i];
  }
  coordinate_compression(n);
  int x,y;
  REP(i,1,n-1) {
    cin >> x >> y;
    v[x].pb(y);
    v[y].pb(x);
  }
  dfs(1,1);
  dfs1(1,1);
  int cnt_distinctive_roots = 0;
  REP(i,1,t) {
    pref[i] += pref[i-1];
    if(pref[i] + cnt_overall == 0) {
      cnt_distinctive_roots++;
    }
  }
  cout << cnt_distinctive_roots;
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
