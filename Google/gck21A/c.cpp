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

multiset<pii> ms;
multiset<pii>::iterator it;
int h[Q][Q],n,m,x,y,_x,_y;
int dx[] = {-1,0,0,1};
int dy[] = {0,-1,1,0};
void update_cell_height(int x, int y, int nheight) {
  ms.erase({h[x][y],{x,y}});
  h[x][y] = nheight;
  ms.insert({h[x][y],{x,y}});
}
void process_cell(ll& ans, pi c) {
  x = c.first, y = c.second;
  REP(k,0,3) {
    _x = x + dx[k], _y = y + dy[k];
    if(_x>0 && _x<=n && _y>0 && _y<=m && h[_x][_y]<h[x][y]-1) {
      ans += h[x][y]-1-h[_x][_y];
      update_cell_height(_x,_y,h[x][y]-1);
    }
  }
}
void solve() {
  ms.clear();
  cin >> n >> m;
  REP(i,1,n) {
    REP(j,1,m) {
      cin >> h[i][j];
      ms.insert({h[i][j],{i,j}});
    }
  }
  pii cell;
  ll ans = 0;
  while(!ms.empty()) {
    it = ms.end(); it--;
    cell = *it;
    ms.erase(it);
    process_cell(ans, cell.second);
  }
  cout << ans;
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
