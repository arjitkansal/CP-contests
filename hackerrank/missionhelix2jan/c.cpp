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

vector<pi> ans;
set<int> pos;
multiset<pi> ms;
int a[N];
string s;
int prev(int x) {
  auto it = pos.lower_bound(x);
  if(it == pos.begin()) {
    return -1;
  }
  it--;
  return *it;
}
int next_pos(int x) {
  auto it = pos.upper_bound(x);
  if(it == pos.end()) {
    return -1;
  }
  return *it;
}
void solve() {
  int n;
  cin >> n >> s;
  REP(i,0,n-1) {
    pos.insert(i);
    cin >> a[i];
  }
  REP(i,1,n-1) {
    if(s[i]!=s[i-1]) {
      ms.insert({abs(a[i]-a[i-1]),i-1});
    }
  }
  while(!ms.empty()) {
    auto it = ms.begin();
    pi temp = *it;
    int x = temp.second;
    auto p = pos.upper_bound(x);
    int y = *p;
    ans.pb({x,y});
    pos.erase(x);
    pos.erase(y);
    ms.erase(it);
    int px = prev(x);
    int ny = next_pos(y);
    if(px>=0 && s[px]!=s[x]) {
      ms.erase(ms.find({abs(a[px]-a[x]),px}));
    }
    if(ny!=(-1) && s[ny]!=s[y]) {
      ms.erase(ms.find({abs(a[ny]-a[y]),y}));
    }
    if(min(px,ny)>=0 && s[px]!=s[ny]) {
      ms.insert({abs(a[px]-a[ny]),px});
    }
  }
  cout << ans.size();
  for(auto it: ans) {
    cout << "\n" << it.first + 1 << " " << it.second + 1;
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
        cout<<"\n";
    }
}
