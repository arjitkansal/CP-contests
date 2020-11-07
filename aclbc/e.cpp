#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define mod 998244353
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

vector<int> queries;
ll temp[N<<2],st[N<<2],upd[N<<2];
void build(int id,int l,int r) {
  if(r-l==1) {
    st[id] = temp[id] = 1;
    return;
  }
  int mid = (l+r)/2;
  build(id<<1,l,mid);
  build(id<<1|1,mid,r);
  temp[id] = st[id] = (st[id<<1] * power(10,r-mid) + st[id<<1|1]) % mod;
}
void apply(int id, int val) {
  st[id] = (temp[id] * queries[val-1]) % mod;
  upd[id] = val;
}
void push(int id) {
  if(upd[id]) {
    apply(id<<1,upd[id]);
    apply(id<<1|1,upd[id]);
    upd[id] = 0;
  }
}
void update(int id,int l,int r,int x,int y,int d) {
  if(r<=x || l>=y) {
    return;
  }
  else if(l>=x && r<=y) {
    upd[id] = queries.size();
    st[id] = (temp[id] * d) % mod;
    return;
  }
  int mid = (l+r)/2;
  push(id);
  update(id<<1,l,mid,x,y,d);
  update(id<<1|1,mid,r,x,y,d);
  st[id] = (st[id<<1] * power(10,r-mid) + st[id<<1|1]) % mod;
}
void solve() {
    int n,q;
    cin>>n>>q;
    build(1,1,n+1);
    int l,r,d;
    while(q--) {
      cin>>l>>r>>d;
      queries.pb(d);
      update(1,1,n+1,l,r+1,d);
      cout<<st[1]<<"\n";
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
