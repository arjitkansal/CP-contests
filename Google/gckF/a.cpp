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

int ddx[] = {-1,0,0,1}, ddy[] = {-1,-1,1,1};
map<pi,bool> blocked;
bool valid_move(int x,int y,int dx,int dy,int& s) {
  if(x+dx<1 || x+dx>s || y+dy<1 || y+dy>=2*(x+dx) || blocked[{x+dx,y+dy}]) {
    return false;
  }
  if(y&1) return dx>=0;
  return dx<=0;
}
int make_all_moves(int player, int x, int y, int& s) {
  cout << player << x << y << "\n";
  int ret = 0;
  bool canMove = false;
  for(auto dx : ddx) {
    for(auto dy : ddy) {
      if(valid_move(x,y,dx,dy,s)) {
        canMove = true;
        blocked[{x+dx,y+dy}] = true;
        ret = max(ret,1 + make_all_moves(1,x+dx,y+dy,s));
        blocked[{x+dx,y+dy}] = false;
      }
    }
  }
  return ret;
}
// map<map<int,int
int make_move(int player, int xa, int ya, int xb, int yb, int& s) {
  // if(min(xa,xb)<1 || max(xa,xb)>s || min(ya,yb)<1 || ya>=2*xa || yb>=2*xb) {
  //   return (player==0) ? 1e9: -1e9;
  // }
  int ret = 0;
  if(player == 0) {
    bool canMove = false;
    for(auto dx : ddx) {
      for(auto dy : ddy) {
        if(valid_move(xa,ya,dx,dy,s)) {
          canMove = true;
          blocked[{xa+dx,ya+dy}] = true;
          ret = max(ret,1 + make_move(1,xa+dx,ya+dy,xb,yb,s));
          blocked[{xa+dx,ya+dy}] = false;
        }
      }
    }
    // if(xa==1 && ya==1) {
    //   cout << canMove << "Hi\n";
    // }
    if(!canMove) {
      ret -= make_all_moves(1,xb,yb,s);
    }
  }
  else {
    bool canMove = false;
    for(auto dx : ddx) {
      for(auto dy : ddy) {
        if(valid_move(xb,yb,dx,dy,s)) {
          // if(xb==2 && yb==1) {
          //   cout<<dx<<" "<<dy<<"HIHI\n";
          // }
          canMove = true;
          blocked[{xb+dx,yb+dy}] = true;
          ret = min(ret,-1 + make_move(0,xa,ya,xb+dx,yb+dy,s));
          blocked[{xb+dx,yb+dy}] = false;
        }
      }
    }
    // if(xb==2 && yb==1) {
    //   cout << canMove << "HiHi\n";
    // }
    if(!canMove) {
      ret += make_all_moves(0,xa,ya,s);
    }
  }
  return ret;
}
void solve() {
  blocked.clear();
  int s, xa, ya, xb, yb, c;
  cin >> s >> xa >> ya >> xb >> yb >> c;
  // assert(s==2);
  int x,y;
  REP(i,0,c-1) {
    cin>>x>>y;
    blocked[{x,y}] = true;
  }
  blocked[{xa,ya}] = true;
  blocked[{xb,yb}] = true;
  cout << make_move(0,xa,ya,xb,yb,s);
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
