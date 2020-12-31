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
const int M = (int)1e3+5;
const int Q = 301;
const int logN = 19;

int col[M];
vector<int> adj[M];
bool intersecting(pi a, pi b) {
  return max(a.first, b.first) <= min(a.second, b.second);
}
bool dfs(int i, int c) {
  if(col[i] != -1) {
    return (col[i] == c);
  }
  col[i] = c;
  for(auto it : adj[i]) {
    if(!dfs(it, 1-c)) {
      return false;
    }
  }
  return true;
}
void solve() {
  int n;
  cin >> n;
  REP(i,0,n-1) {
    adj[i].clear();
    col[i] = -1;
  }
  vector<pii> v(n);
  REP(i,0,n-1) {
    cin >> v[i].second.first >> v[i].second.second >> v[i].first;
    REP(j,0,i-1) {
      if(v[i].first == v[j].first && intersecting(v[i].second, v[j].second)) {
        adj[i].pb(j);
        adj[j].pb(i);
      }
    }
  }
  REP(i,0,n-1) {
    if(col[i] == -1 && !dfs(i,0)) {
      cout << "NO";
      return;
    }
  }
  cout << "YES";
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
